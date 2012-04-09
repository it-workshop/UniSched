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

algorithms.parse_traits = function(s)
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

algorithms.make_traits = function(traits)
    return string.format('%s|%s', make_traits_list(traits.allow), make_traits_list(traits.deny))
end

algorithms.traits_optimize = function(traits)
    local comp = function(lhs, rhs)
        return lhs.from < rhs.from
    end
    sort(traits.allow, comp)
    local i = 1
    while i < #(traits.allow) do
        if traits.allow[i].to >= traits.allow[i + 1].from + 1 then
            traits.allow[i].to = math.max(traits.allow[i].to, traits.allow[i + 1].to)
            table.remove(traits.allow, i + 1)
        else
            i = i + 1
        end
    end
    sort(traits.deny, comp)
    i = 1
    while i < #(traits.deny) do
        if traits.deny[i].to >= traits.deny[i].from + 1 then
            traits.deny[i].to = math.max(traits.deny[i].to, traits.deny[i + 1].to)
            table.remove(traits.deny, i + 1)
        else
            i = i + 1
        end
    end
    local j = 1
    i = 1
    while i <= #(traits.allow) or j <= #(traits.deny) do
        if traits.allow[i].from < traits.deny[j].from then
            if traits.allow[i].to >= traits.deny[j].from then
                if traits.allow[i].to <= traits.deny[j].to then
                    traits.allow[i].to = traits.deny[j].from - 1
                else
                    table.insert(traits.allow, i + 1, {from = traits.deny[j].to + 1, to = traits.allow[j].to})
                    i, j = i + 1, j + 1
                end
            end
            i = i + 1
        else
            if traits.allow[i].from <= traits.deny[j].to then
                if traits.allow[i].to > traits.deny[j].to then
                    traits.allow[i].from = traits.deny[j].to + 1
                    j = j + 1
                else
                    table.remove(traits.allow[i])
                end
            else
                j = j + 1
            end
        end
    end
    if #(traits.allow) > 0 then
        table.remove(traits.deny)
    end
end

