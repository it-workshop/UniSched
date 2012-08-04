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
                data = data .. "        " .. o:id() .. "\n"
            end
            data = data .. "    ]"
        else
            data = data .. "'UNKNOWN FIELD TYPE'"
        end
        data = data .. "\n"
    end
    return "{\n" .. data .. "}"
end

api = {
    GET = {
        search = function (request)
            local data = '[\n'
            for k, o in pairs(search(request.args)) do
                data = data .. to_json(o) .. ',\n'
            end
            data = data .. ']'
            return {
                code = 200,
                message = 'OK',
                headers = {
                    ['Content-Type'] = 'application/json'
                },
                data = data
            }
        end
    },
    POST = {},
    DELETE = {}
}

local function urlunescape(s)
    s = string.gsub(s, '+', ' ')
    s = string.gsub(s, '%%(%x%x)', function (h)
        return string.char(tonumber(h,16))
    end)
    return s
end

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
        local func = string.match(request.path, '^' .. config.httpd.api_prefix .. '([^/?]*)')
        local args = string.match(request.path, '^' .. config.httpd.api_prefix .. '[^/?]*?(.+)$')
        request.args = {}
        if args then
            for k, v in string.gmatch(args, '([^&=]+)=([^&=]*)') do
                request.args[urlunescape(k)] = urlunescape(v)
            end
        end
        if api[request.method] and api[request.method][func] then
            return api[request.method][func](request)
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
    local response = request({
        method = method,
        path = path,
        protocol = protocol,
        headers = headers
        })
    str = protocol ..  response.code .. ' ' .. response.message .. '\n'
    for key, value in pairs(response.headers) do
        str = str .. key .. ': ' .. value .. '\n'
    end
    response.headers['Content-Length'] = #(response.data)
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

