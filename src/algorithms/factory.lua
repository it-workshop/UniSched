#!/usr/bin/env lua

local _ = _G
module('factory')

local assert = _.assert
local setmetatable = _.setmetatable

function set_base_class(class, base)
    -- Set base class
    -- Usage: factory.set_base_class(someclass, baseclass)
    assert(class, 'No child class!')
    assert(base, 'No base class!')
    assert(base.mtab, 'No mtab specified in base class!')
    setmetatable(class, base.mtab)
end

function create(class, ...)
    -- create object of class and call constructor
    -- Usage: factory.create(someclass, arg1, arg2, ...)
    assert(class, 'No class!')
    local o = {}
    set_base_class(o, class)
    o:construct(unpack(arg))
    return o
end

return _M

