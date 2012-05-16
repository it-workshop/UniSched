#!/usr/bin/env lua

-- Load auxiliary tools
dofile('aux.lua')

-- Do not run code twice
ifndef(factory, function ()

-- Create factory table
factory = {}

function factory.set_base_class(class, base)
    -- Set base class
    -- Usage: factory.set_base_class(someclass, baseclass)
    assert(class, 'No child class!')
    assert(base, 'No base class!')
    assert(base.mtab, 'No mtab specified in base class!')
    global.setmetatable(class, base.mtab)
end

function factory.create(class, ...)
    -- create object of class and call constructor
    -- Usage: factory.create(someclass, arg1, arg2, ...)
    assert(class, 'No class!')
    local o = {}
    factory.set_base_class(o, class)
    o:construct(unpack(arg))
    return o
end

end) -- ifndef

