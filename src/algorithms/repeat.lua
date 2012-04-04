#!/usr/bin/env lua

algorithms['repeat'] = function (object)
    if !object then
        error('repeat: Object is needed!')
    end
    if object.type() != 'event' then
        error('repeat: Object must be event!')
    end
    local name, start, duration, interval, max_time = tostring(object.name), tonumber(object.start), tonumber(object.duration), tonumber(object.interval), tonumber(object.max_time)
    if not (name and start and duration and interval and max_time) then
        error('fields name, start, duration, interval and max_time must be defined!')
    end
    for time = start + duration, max_time, interval do
        local new_object = create(event)
        for key, value in pairs(object.read()) do
            new_object[key] = value
        end
        new_object['start'] = time
    end
end

