#!/usr/bin/env lua

-- save global namespace
local _ = _G

-- create module
module('task_system')

-- aliases for global objects

local require = _.require
local table = _.table
local pairs = _.pairs

-- load factory and object

local factory = require('factory')
local object = require('object')

factory.set_base_class(_M, object)

-- metatable for children classes
mtab = { __index = _M }

function construct(self, processors, tasks, resources)
    -- constructor
    -- Usage: task_s = task_system:new(processors, tasks, resources)
    self.processors = processors or {}
    self.tasks = tasks or {}
    self.resources = resources or {}
end

function schedule(self, start)
    -- schedule task system
    -- Usage: task_s:schedule(start_time)
    table.sort(self.tasks)
    local tasks = {}
    for k, val in pairs(self.tasks) do table.insert(tasks, val) end
    local time = start
    for i = 1, #self.tasks do
        table.sort(self.processors, 
            function (lhs, rhs)
                return lhs:ready(time) < rhs:ready(time)
            end )
        for k, processor in pairs(self.processors) do
            local ready = processor:ready(time)
            local can_do = {}
            for k, task in pairs(tasks) do
                if task:is_ready(ready) then
                    if #task.processors ~= 0 then
                        table.insert(can_do, task)
                    else
                        for k, proc in pairs(task.processors) do
                            if proc == processor then
                                table.insert(can_do, task)
                                break
                            end
                        end
                    end
                end
            end
            if #can_do ~= 0 then
                table.sort(can_do, self.order)
                local task = can_do[1]
                processor.task(task)
                task.processor = processor
                task.start = task:ready(ready)
                task.finish = task:time(processor)
                for k, val in pairs(tasks) do
                    if val == task then
                        table.remove(tasks, k)
                        break
                    end
                end
                break
            end
        end
    end
end

function order(lhs, rhs)
    -- Does not implemented in this class.
    -- You must to write target specific function
    -- for select order of tasks.
    error ('Not implemented in this class.')
end

return _M

