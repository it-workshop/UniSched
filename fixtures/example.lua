john = create('person')
john['name'] = 'John'
john.update('surname', 'Smith')

jane = create('person')
jane['name'] = 'Jane'   -- this form is shorter...
jane['surname'] = 'Smith'

smiths = create('group')
smiths['name'] = 'Smiths'
smiths.connect(john)
smiths.connect(jane)
print (john['name'] .. ' ' .. john.read('surname'))
print (jane['name'] .. ' ' .. jane['surname'])
print ('In group: ' .. smiths.['name'])

remove(smiths)  -- what is  comfortable? is this
john.remove()   -- or that?
remove(jane)

-- It does not realy differs from C++ but
-- classes and project build is not needed.
--
-- arrays are start from 1. :(
--
