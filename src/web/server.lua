#!/usr/bin/env lua

require 'luarocks.loader'
require 'socket'

local function to_json(object)
    local data = [[
    "id": "]] .. object.id() .. [[",
    "type": "]] .. object.type() .. '"'
    local first = true
    for k, v in pairs(object.read()) do
        data = data .. ',\n    "' .. k .. '": '
        if type(v) == 'number' or type(v) == 'string' then
            data = data .. '"' .. v .. '"'
        elseif type(v) == 'table' then
            data = data .. "[\n"
            for i, o in pairs(v) do
                data = data .. '        "' .. o:id() .. '"'
                if i ~= #v then
                    data =  data .. ','
                end
                data = data .. '\n'
            end
            data = data .. "    ]"
        else
            data = data .. "'UNKNOWN FIELD TYPE'"
        end
        data = data
    end
    return "{\n" .. data .. "\n}"
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
                if ret ~= '' then
                    ret = ret .. ','
                end
                ret = ret .. to_json(v) .. '\n'
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
                code = 500,
                message = 'Internal server error!',
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
                code = 500,
                message = 'Internal server error!',
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

function link(type, connect)
    local create = ''
    if type then
        create = ',CREATE'
    end
    return function(request, id)
        if not tonumber(id) then
            return {
                code = 405,
                message = 'Bad method',
                headers = {
                    ['Content-Type'] = 'application/json',
                    Allow = 'HEAD,GET' .. create
                },
                data = '{ "error": "Bad method" }'
            }
        end
        local o = get_object(id)
        local with = get_object(tonumber(string.match(request.headers.Location, '^/' .. api_prefix .. '/[^/]+/([0-9]+)')))
        if not o or not with then
            return {
                code = 404,
                message = 'Not found',
                headers = {
                    ['Content-Type'] = 'application/json'
                },
                data = '{ "error": "No such object" }'
            }
        end
        local code, error
        if connect then
            code, error = pcall(o.connect, with)
        else
            code, error = pcall(o.disconnect, with)
        end
        if not code then
            return {
                code = 500,
                message = 'Internal server error',
                headers = {
                    ['Content-Type'] = 'application/json'
                },
                data = '{ "error": "Could not connect objects" }'
            }
        end
        return {
            code = 200,
            message = 'OK',
            headers = {
                ['Content-Type'] = 'application/json'
            },
            data = '[\n' .. to_json(o) .. ',\n' .. to_json(with) .. '\n]'
        }
    end
end

local function create_method(type)
    if not type then
        return json_error(405, 'Bad method', { Allow = 'GET,HEAD' })
    end
    return function (request, id)
        local o = create(type)
        if not o then
            return {
                code = 500,
                message = 'Internal server error',
                headers = {
                    ['Content-Type'] = 'application/json'
                },
                data = '{ "error": "Could not create object" }'
            }
        end
        return {
            code = 201,
            message = 'Created',
            headers = {
                ['Content-Type'] = 'application/json',
                Location = config.httpd.api_prefix .. '/' .. type .. '/' .. o.id()
            },
            data = to_json(o)
        }
    end
end

local function delete(type)
    local create = ''
    if type then
        create = ',CREATE'
    end
    return function (request, id)
        if not tonumber(id) then
            return {
                code = 405,
                message = 'Bad method',
                headers = {
                    ['Content-Type'] = 'application/json',
                    Allow = 'HEAD,GET' .. create
                },
                data = '{ "error": "Bad method" }'
            }
        end
        local o = get_object(id)
        if not o then
            return {
                code = 404,
                message = 'Not found',
                headers = {
                    ['Content-Type'] = 'application/json'
                },
                data = '{ "error": "No such object!" }'
            }
        end
        remove(o)
        return {
            code = 204,
            message = 'No content',
            headers = {},
            data = ''
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
        object = link(nil, true),
        person = link('person', true),
        group = link('group', true),
        event = link('event', true)
        },
    UNLINK = {
        object = link(),
        person = link('person'),
        group = link('group'),
        event = link('event')
        },
    CREATE = {
        object = create_method(),
        person = create_method('person'),
        group = create_method('group'),
        event = create_method('event')
        },
    DELETE = {
		object = delete(),
		person = delete('person'),
		group = delete('group'),
		event = delete('event')
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
        local id = string.match(request.path, '^' .. config.httpd.api_prefix .. '[^/]*/([0-9]+)')
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
    local data = sock:receive('*l')
    if not data then
        sock:close()
        return
    end
    local method, path, protocol = string.match(data, '^([^ ]*) ([^ ]*) ([^ ]*)$')
    local str, headers = sock:receive('*l'), {}
    while str and str ~= '' do
        local key, value = string.match(str, '^([^:]*): (.+)$')
        headers[key] = value
        str = sock:receive('*l')
    end
    local post_data
    if method == 'POST' then
        for k, v in pairs(headers) do
            print(k, v)
        end
        post_data = sock:receive(headers['Content-Length'])
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

function server(host, port)
local done = false
    api.POST.shutdown = function (request, id)
        done = true
        return {
            code = 200,
            message = 'OK',
            headers = {
                ['Content-Type'] = 'application/json'
            },
            data = '{ "state": "shutting down" }'
        }
    end
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

