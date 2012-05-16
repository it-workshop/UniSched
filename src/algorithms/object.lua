#!/usr/bin/env lua

-- save global namespace
local _ = _G
-- create module
module('object')

-- aliases for global objects
local require = _.require

-- load factory
local factory = require('factory')

mtab = { __index = _M }
-- metatable for children classes
-- search in this one if not found in children

function new(class, ...)
    -- create object
    -- Usage class:new(...)
    return factory.create(class, unpack(arg))
end

function construct(self)
    -- constructor
    -- Usage class:new(...)
end

return _M

