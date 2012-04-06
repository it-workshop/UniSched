#!/usr/bin/env lua

local parse_time = function(s)
    local t = {}
    t.year, t.month, t.day, t.hour, t.min, t.sec = string.match(s, '(%d%d%d%d)%-(%d%d)%-(%d%d) (%d%d):(%d%d):(%d%d)')
    return os.time(t)
end

local parse_trait = function(s)
    local from, to = string.match(s, '%((%d%d%d%d%-%d%d%-%d%d %d%d:%d%d:%d%d)|(%d%d%d%d%-%d%d%-%d%d %d%d:%d%d:%d%d)%)')
    local trait = {}
    trait.from, to = parse_time(from), parse_time(to)
    return trait
end

local parse_traits_list = function(s)
    local traits = {}
    for trait in string.gmatch(s, '%(%d%d%d%d%-%d%d-%d%d %d%d:%d%d:%d%d|%d%d%d%d%-%d%d%-%d%d %d%d:%d%d:%d%d%)') do
        table.insert(traits, parse_trait(trait))
    end
end

local parse_traits = function(s)
    local allow, deny = string.match(s, '(.+)\(.+)')
    local traits = {}
    traits.allow, traits.deny = parse_traits_list(allow), parse_traits_list(deny)
    return traits
end

local make_trait = function(trait)
    return string.format('(%s|%s)', os.date('%H %T', trait.from), os.date('%H %T', trait.to))
end

local make_traits_list = function(traits)
    local s = ''
    for i, trait in pairs(traits) do
        s = s..make_trait(trait)
    end
end

local make_traits = function(traits)
    return string.format('%s|%s', make_traits_list(traits.allow), make_traits_list(traits.deny))
end

