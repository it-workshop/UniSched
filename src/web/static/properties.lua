#!/usr/bin/env lua

config.httpd.static = {
}

local extensions = {
    html = 'text/html',
    css = 'text/css',
    js = 'text/javascript',
    png = 'image/png'
}

setmetatable(config.httpd.static, {
    __index = function (table, key)
        for k, v in pairs(extensions) do
            if string.match(key, k .. '$') then
                return { ['Content-Type'] = v }
            end
        end
        return { ['Content-Type'] = 'text/plain' }
    end
})

local function get_file(file)
    local fd = io.open(config.httpd.static_dir .. file)
    if fd then
        return fd:read('*a'), config.httpd.static[file]
    else
        return [[
<!DOCTYPE html>
<html>
 <head>
  <meta charset=utf8>
  <title>404 Not Found!</title>
 </head>
 <body>
  <h1>404 Not Found!</h1>
  <br>
  ']] .. file .. [[' was not found on this server!
 </body>
</html>
]], { ['Content-Type'] = 'text/html' }
    end
end

function config.httpd.page_404(request)
    local data, headers = get_file(request.path)
    data = string.gsub(data, '%PATH%', request.path)
    return {
        code = 404,
        message = 'Not found!',
        headers = headers,
        data = data
    }
end

