#!/usr/bin/env lua

require 'luarocks.loader'
require 'socket'

local done = false

function request(sock)
    return {
        code = 200,
        message = 'OK',
        headers = {
            ['Content-Type'] = 'text/html'
        },
        data = [[
<DOCTYPE html>
<html>
 <head>
  <meta charset=utf8>
  <title>It works!</title>
 </head>
 <body>
  <h1>It works!</h1>
 </body>
</html>
]]
    }
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
    str = str .. '\n' .. response.data
    print(os.date(), method, path, sock:getpeername());
    sock:send(str)
    sock:close()
end

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

server(config.httpd.host, config.httpd.port)

