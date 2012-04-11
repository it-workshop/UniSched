#!/usr/bin/env lua

function algorithms.found_conflicts(event)
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
    sort (events, function (lhs, rhs) return lhs.start < rhs.start end)
    return events
end

function algorithms.schedule (events)
    local function schedule(event)
        local function busy(event)
            if event.start then return { from = event.start, to = event.start + event.duration } end
            return { from = event.probe, to = event.probe + event.duration }
        end
        if event.start or event.probe then return 0 end
        local traits = algorithms.parse_traits(event.traits)
        local conflicts = algorithms.find_conflicts(event)
        for key, conflict in pairs(conflicts) do
            if conflict.start or conflict.probe then
                table.insert(traits.deny, {busy(conflict)})
            end
        end
        
        for key, trait in pairs(traits) do
            event.probe = trait.from
            for key, conflict in pairs(conflict) do
                if not schedule(conflict) then
                    event.probe = nil
                    break
                end
            end
            if event.probe then
                event.start, event.probe = event.probe, nil
                return 1
            end
        end
        return nil
    end

    for key, event in pairs(events) do
        local traits = algorithms.parse_traits(event.traits)
        algorithms.optimize_traits(traits)
        event.traits = algorithms.make_traits(traits)
    end

    for key, event in pairs(events) do
        schedule(event)
    end
end

