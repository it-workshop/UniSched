#!/usr/bin/env lua

-- Load auxiliary tools
dofile('aux.lua')

-- Do not run code twice
ifndef(object, function ()

import('factory')

-- save global namespace
local _ = _G

-- create class
object = {mtab = {}}

-- set metatable for children classes
-- search in this one if not found in children
object.mtab.__index = object
-- change global namespace to class
_G = object

function new(class, ...)
    -- create object
    -- Usage class:new(...)
    factory.create(class, unpack(arg))
end

function construct(self)\
    -- constructor
    -- Usage class:new(...)
end

-- restore global namespace
_G = _

end)    -- ifndef

