#!/usr/bin/env lua

-- save global namespace
local _ = _G

-- create module
module('resource')

-- aliases for global objects
local require = _.require

-- load factory and object
local factory = require('factory')
local object = require('object')

factory.set_base_class(_M, object)

function construct(self)
    -- constructor
    -- Usage: new_resource = resource:new()
    self.tasks = {}
end

function task(self, task, time)
    -- add task
    -- Usage: resource:task(some_task)
    table.insert(self.tasks, task)
end

function is_ready(self, time)
    if #self.tasks == 0 then return true end
    local task = self.tasks[#self.tasks]
    if task.finish >= time then
        return true
    else
        return false
    end
end

function ready(self, time)
    if #self.tasks == 0 then return time end
    local task = self.tasks[#self.tasks]
    if time and task.finish >= time then
        return task.finish
    else
        return time
    end
end

return _M

