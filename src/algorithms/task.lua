#!/usr/bin/env lua

-- Load aux tools
dofile('aux.lua')

-- Do not run code twice
ifndef(task, function ()

-- Load parent class and factory.
import('object')

-- Create class table.
task = class (object, function ()

    -- Metatable for children classes
    function mtab.__lt (lhs, rhs)
        -- operator < implementation (true if rhs depends from lhs)
        if lhs == rhs then return false end
        for k, val in pairs(rhs.depends) do
            if lhs == val.task or lhs < val.task then return true end
        end
        return false
    end

    function construct(self)
    -- constructor
    -- Usage: new_task = task:new()
        self.depends = {}
        self.processors = {}
        self.resources = {}
    end

    function depend(self, task)
        -- set self depend from task
        -- Usage: task1:depend(task2)
        assert(totable(task), "Invalid task!")
        if self < task or self == task then error("Circular dependency found!") end
        if task < self then return end
        table.insert(self.depends, task)
    end

    function processor(self, processor)
        -- task can be run on processor
        -- Usage: task:processor(resource)
        assert(totable(processor), "Invalid processor!")
        for k, val in pairs(self.processors) do
            if val == processor then return end
        end
        table.insert(self.processors, processor)
    end

    function resource(self, resource)
        -- resource is needed for task
        -- Usage: task:resource(resource)
        assert(totable(resource), "Invalid resource!")
        for k, val in pairs(self.resources) do
            if val == resource then return end
        end
        table.insert(self.resources, resource)
    end

    function time(self, processor)
        -- Do not use this class directly
        -- You must implement this function to
        -- schedule task system.
        error("Not implemented.")
    end
end) -- class

end) -- ifndef

