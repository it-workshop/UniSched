#!/usr/bin/env lua

algorithms.found_conflicts = function (event)
    local events = {}
    local function get_people(obj)
        local people = {}
        if not obj then
            error('Object required!')
        end
        for key, value in pairs(obj.read('people')) do
            table.insert(people, value)
        end
        for key, value in pairs(obj.read('children_group')) do
            for i, person in pairs(get_people(value)) do
                table.insert(people, person)
            end
        end
        local i, j
        while i <= #people do
            j = i + 1
            while j <= #people do
                if people[i] == people[j] then
                    table.remove(people, j)
                else
                    j = j + 1
                end
            end
            i = i + 1
        end
        return people
    end
    for key, value in pairs(get_people(event)) do
        for i, obj in pairs(algorithms.get_calendar(value)) do
            if obj ~= event then
                table.insert(events, obj)
            end
        end
    end
end
