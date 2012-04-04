function test_person()
    local person = create('person')
    person.update('name', 'John')
    person.update('surname', 'Connor')
    person.update('sex', 'MALE')
    person.update('birthday', 300400)

    pers = create('person')
    pers['name'] = 'Harry'
    pers['surname'] = 'Potter'
    pers['sex'] = 'MALE'
    pers['birthday'] = 19283740
end

function test_group()
    local g = create('group')
    g['name'] = 'Miles Davs band'

    local suppa_truppa = create('group')
    suppa_truppa['name'] = 'Suppa-pa... Truppa-pa...'
end

function test_connect()
    local g = create('group')
    g['name'] = 'SW gang'
    
    local r2d2 = create('person')
    r2d2['name'] = 'r2'
    r2d2['surname'] = 'd2'
    r2d2['sex'] = 'MALE'
    r2d2['birthday'] = 100500

    local c3po = create('person')
    c3po['name'] = 'c3'
    c3po['surname'] = 'po'
    c3po['sex'] = 'MALE'
    c3po['birthday'] = 300700

    g.connect(r2d2)
    c3po.connect(g)
end

function show_objects()
    local rez = search({}) -- must be res!
    local i, o, key, value, j, item
    for i, o in pairs(rez) do
        print('--OBJ--')
        for key, value in pairs(o.read()) do
            if type(value) == 'table' then
                print(key..':')
                for j, item in pairs(value) do
                    print(' ', item['name'])
                end
            else
                print(key..': '..value)
            end
        end
    end
end

print('[lua] testing...')

test_person()
print('[test.lua:test_person] PERSON CREATION works!')

test_group()
print('[test.lua:test_group] GROUP CREATION works!')

test_connect()
print('[test.lua:test_connect] CONNECt works!')

show_objects()
print('[test.lua:show_objects] SEARCH works!')

