#!/usr/bin/env lua

require 'luarocks.loader'
require 'socket'

local function to_json(object)
    local data = [[
    'id': ]] .. object.id() .. [[,
    'type': ']] .. object.type() .. "',\n"
    for k, v in pairs(object.read()) do
        data = data .. "    '" .. k .. "': "
        if type(v) == 'number' then
            data = data .. v
        elseif type(v) == 'string' then
            data = data .. "'" .. v .. "'"
        elseif type(v) == 'table' then
            data = data .. "[\n"
            for i, o in pairs(v) do
                data = data .. "        " .. o:id() .. ",\n"
            end
            data = data .. "    ]"
        else
            data = data .. "'UNKNOWN FIELD TYPE'"
        end
        data = data .. ",\n"
    end
    return "{\n" .. data .. "}"
end

local function json_error(code, message, headers)
    local ret = {
            code = code,
            message = message,
            headers = headers,
            data = "{ 'error': '" .. message .. "' }"
    }
    ret.headers['Content-Type'] = 'application/json'
    return function (request)
        return ret
    end
end

local function urlunescape(s)
    s = string.gsub(s, '+', ' ')
    s = string.gsub(s, '%%(%x%x)', function (h)
        return string.char(tonumber(h,16))
    end)
    return s
end

local function get(type)
    return function (request, id)
        if tonumber(id) then
            local o = get_object(id)
            if not type or o.type() == type then
                return {
                    code = 200,
                    message = 'OK',
                    headers = {
                        ['Content-Type'] = 'application/json'
                    },
                    data = to_json(o)
                }
            end
            return {
                code = 404,
                message = 'Not found',
                headers = {
                    ['Content-Type'] = 'application/json'
                },
                data = '{ "error": "No such object!" }'
            }
        end
        local ret = ''
        for k, v in pairs(search(request.args)) do
            if not type or v.type() == type then
                ret = ret .. to_json(v) .. ',\n'
            end
        end
        return {
            code = 200,
            message = 'OK',
            headers = {
                ['Content-Type'] = 'application/json'
            },
            data = '[\n' .. ret .. ']'
        }
    end
end

local function post(type)
    return function (request, id)
        if not tonumber(id) then
            return {
                code = 405,
                message = 'Bad method',
                headers = {
                    ['Content-Type'] = 'application/json',
                    ['Allow'] = 'GET,HEAD'
                },
                data = '{ "error": "Bad method!" }'
            }
        end
        local o = get_object(id)
        if not o or type and o.type() ~= type then
            return {
                code = 404,
                message = 'Not found!',
                headers = {
                    ['Content-Type'] = 'application/json'
                },
                data = '{ "error": "No such object!" }'
            }
        end
        if not tostring(request.post.name) or not tostring(request.post.value) then
            return {
                code = 400,
                message = 'Bad request!',
                headers = {
                    ['Content-Type'] = 'application/json'
                },
                data = '{ "error": "Invalid arguments" }'
            }
        end
        print(request.post.name, request.post.value)
        local code, error = pcall(o.update, request.post.name, request.post.value)
        if not code then
            return {
                code = 400,
                message = 'Bad request!',
                headers = {
                    ['Content-Type'] = 'application/json'
                },
                data = '{ "error": "' .. error .. '" }'
            }
        end
        return {
            code = 200,
            message = 'OK',
            headers = {
                ['Content-Type'] = 'application/json'
            },
            data = to_json(o)
        }
    end
end

local api = {
    HEAD = {
        object = get(),
        person = get('person'),
        group = get('group'),
        event = get('event')
        },
    GET = {
        object = get(),
        person = get('person'),
        group = get('group'),
        event = get('event')
        },
    POST = {
        object = post(),
        person = post('person'),
        group = post('group'),
        event = post('event')
        },
    LINK = {
        object = function () end,
        person = function () end,
        group = function () end,
        event = function () end
        },
    UNLINK = {
        object = function () end,
        person = function () end,
        group = function () end,
        event = function () end
        },
    CREATE = {
        object = function () end,
        person = function () end,
        group = function () end,
        event = function () end
        },
    DELETE = {
        object = function () end,
        person = function () end,
        group = function () end,
        event = function () end
        }
}

function request(request)
    local path
    if request.method == 'GET' and not string.match(request.path, '^' .. config.httpd.api_prefix) then
        if request.path == '/' then
            path = '/index.html'
        else
            path = request.path
        end
        local file = config.httpd.static_dir .. string.gsub(path, '/\.\./', '/')
        local fd, err = io.open(file)
        if not fd then
            return config.httpd.page_404(request)
        else
            return {
                code = 200,
                message = 'OK',
                headers = config.httpd.static[path],
                data = fd:read('*a')
            }
        end
    end
    if string.match(request.path, '^' .. config.httpd.api_prefix) then
        local type = string.match(request.path, '^' .. config.httpd.api_prefix .. '([^/?]*)')
        local id = string.match(request.path, '^' .. config.httpd.api_prefix .. '[^/]*/([0-9]*)')
        local args = string.match(request.path, '^' .. config.httpd.api_prefix .. '[^?]*?(.+)$')
        request.args = {}
        if args then
            for k, v in string.gmatch(args, '([^&=]+)=([^&=]*)') do
                request.args[urlunescape(k)] = urlunescape(v)
            end
        end
        request.post = {}
        if request.method == 'POST' then
            print('POST:', request.post_data)
            for k, v in string.gmatch(request.post_data, '([^&=]+)=([^&=]*)') do
                print('POST:', k, v)
                request.post[urlunescape(k)] = urlunescape(v)
            end
        end
        if api[request.method] and api[request.method][type] then
            return api[request.method][type](request, id)
        else
            return config.httpd.page_404(request)
        end
    end
    return config.httpd.page_404(request)
end

function process(sock)
    local method, path, protocol = string.match(sock:receive('*l'), '^([^ ]*) ([^ ]*) ([^ ]*)$')
    local str, headers = sock:receive('*l'), {}
    while str and str ~= '' do
        local key, value = string.match(str, '^([^:]*): (.+)$')
        headers[key] = value
        str = sock:receive('*l')
    end
    local post_data
    if method == 'POST' then
        post_data, str = '', sock:receive('*l')
        while str and str ~= '' do
            post_data = post_data .. str
            str = sock:receive('*l')
        end
    end
    local response = request({
        method = method,
        path = path,
        protocol = protocol,
        headers = headers,
        post_data = post_data
        })
    response.headers['Content-Length'] = #(response.data)
    if method == 'HEAD' then
        response.data = ''
    end
    str = protocol ..  ' ' .. response.code .. ' ' .. response.message .. '\n'
    for key, value in pairs(response.headers) do
        str = str .. key .. ': ' .. value .. '\n'
    end
    str = str .. '\n' .. response.data
    print(os.date(), method, path, sock:getpeername(), response.code, response.message, response.headers['Content-Length']);
    sock:send(str)
    sock:close()
end

local done = false
function server(host, port)
    sock = socket.bind(host, port)
    print(sock:getsockname())
    while not done do
        process(sock:accept())
    end
    sock:close()
end
 
assert(tostring(config.httpd.host), 'No host specified!')
assert(tonumber(config.httpd.port), 'No port specified!')
assert(tostring(config.httpd.api_prefix), 'No api prefix specified!')
assert(tostring(config.httpd.static_dir), 'No static dir specified!')
dofile(config.httpd.static_dir .. '/properties.lua')
assert(config.httpd.static, 'No static properties specified!')

server(config.httpd.host, config.httpd.port)

