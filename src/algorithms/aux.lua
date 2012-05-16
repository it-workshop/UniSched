#!/usr/bin/env lua

if not __aux_loaded then
__aux_loaded = true

function ifndef(object, code)
    -- C #ifndef implementation
    -- Usage: ifndef(object, function () some lua code; end)
    if not object then code() end
end

function ifdef(object, code)
    -- C #ifdef implementation
    -- Usage: ifdef(object, function () some lua code; end)
    ifndef(not object, code)
end

function import(class)
    -- run class.lua
    -- if . found the class then it will be replaced with /
    -- Usage: import('package.class')
    -- it will load package/class.lua
    dofile(string.gsub(class, '%.', '/') .. '.lua')
end

import('factory')

local g = _G
function class(parent, code)
    -- create class
    -- Usage: class(parentclass, function() class body; end)
    assert(class = tostring(class), "No class name specified!")
    local class = {}
    local oldg = _G
    _G = class
    class._Global = g
    _G = oldg
    return class
end

