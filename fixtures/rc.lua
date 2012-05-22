#!/usr/bin/env lua

config.ui = 'CLI'
-- Possible variants: 'DummyUI', 'CLI', 'LuaUI'

config.storage = 'SQLITE'
-- Possible variants: 'SQLIT

local home = os.getenv('HOME')

config.modules_path = home .. '/code/build/src/modules/storage:' .. home .. '/code/build/src/modules/ui'
-- Path to modules

config.sqlite_db = home .. '/.unisched/unisched.db'
-- Path to sqlite3 database.

-- Some work after loading.
function config.onload ()
    print ('Objects:', #search({}))
    print ('Now:', os.date())
end

