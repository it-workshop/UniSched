#!/usr/bin/env lua

-- UI Variants: 'DummyUI', 'CLI', 'luaui'
config.ui = 'CLI' 

-- storage module. For now 'SQLITE' is the only option
config.storage = 'SQLITE'

local home = os.getenv('HOME')

-- Пути поиска модулей, как storage так и ui
config.modules_path = home .. '/code/build/src/modules/storage:' .. home .. '/code/build/src/modules/ui'

-- Путь к базе
config.sqlite_db = home .. '/.unisched/unisched.db' 

-- Скрипт, выполняемый после запуска (только для config.ui 'luaui')
-- Например, можно использовать для запуска GUI
-- config.script('/path/to/some/script/or/gui_stub.lua')

function onload ()
    print ('Now:', os.date())
end
