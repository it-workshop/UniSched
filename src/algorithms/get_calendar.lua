
algorithms.get_calendar = function(object)
    local search_events
    local result = {}
    search_events = function (object)
        if not object or not type(object) == 'table' then error('Object required!') end
        if object.type() == 'event' then
            table.insert(result, object)
        elseif object.type() == 'person' then
            if not object.groups then return end
            for key, obj in pairs(object.groups) do
                search_events(obj)
            end
        else
            if not object.parent_groups then return end
            for key, obj in pairs(object.parent_groups) do
                search_events(obj)
            end
        end
    end
    search_events(object)
    return result
end

