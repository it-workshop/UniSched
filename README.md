# Постановка задачи

В основном, расписатор представляет собой хитрую базу данных для связи объектов типов
"человек", "группа людей" и "событие". С максимально возможной независимостью от
того, что находится снизу и сверху от ядра системы (вид хранения данных и
интерфейс). На данном этапе ничего ценного или полезного данный код не делает.


# Программные требования

1. В данный момент для сборки требуется компилятор, поддерживающий C++11,
   актуальный список можно найти тут:
   http://wiki.apache.org/stdcxx/C++0xCompilierSupport
2. Также для сборки требуется:
   * CMake версии не ниже 2.8.3
   * Boost
3. Для сборки файловой базы данных требуется yaml-cpp версии не ниже 0.5.0
     (в настоящее время доступен из неофициального бранча new-api,
     подробнее см. офсайт проекта: http://code.google.com/p/yaml-cpp, либо,
     например, тут: https://github.com/nebirhos/yaml-cpp/tree/new-api).
3. Для сборки пользовательского интерфейса CLI требуется readline.


# Как собрать

Для сборки на UNIX & UNIX like системах исполните в директории сборки:

    cmake [OPTIONS] path/to/source/directory && make
    
Где path/to/source/directory - путь до директории с исходным кодом.
Настоятельно не рекомендуется сборка в директории репозитория (коммиты с
файлами сборки будут отбрасываться). OPTIONS - параметры сборки, см. ниже

Пример последовательности комманд полностью с "нуля" на системе, где стоит всё,
что нужно для сборки:

    $ cd /tmp
    $ git clone git://github.com/alex-ac/UniSched.git
    $ mkdir /tmp/build-unisched/
    $ cd !$
    $ cmake /tmp/UniSched/
    $ make

После этого в папке /tmp/build-unisched/ должна быть собрана текущая версия
расписатора. Для доступа на запись всё то же саме, только необходимо заменить
адрес репозитория

    $ git clone git@github.com:alex-ac/UniSched.git

Сборка для отладки:
    
    $ cmake -DCMAKE_BUILD_TYPE=Debug /tmp/Unisched

Пути, естественно, на усмотрение.


# Опции сборки
    
Ниже перечисленны переменные cmake, влияющие на конфигурацию сборки
программы. Перед запуском с новыми аргументами необходимо удалить CMakeCache.txt
в директории сборки. Пример использования:

    cmake -D WITH_SQLITE=Y ../UniSched

Подготовить проект к сборке с поддержкой sqlite

Опции:

* Опция(значение по умолчанию) описание
* WITH\_SQLITE(Y) Собирать бэкэнд к базе данных sqlite3 (необходимо наличие в системе библиотеки и заголовков).
* WITH\_DUMMYUI(Y) Собирать пользовательский интерфейс-заглушку, выполняющий некоторый набор основных действий.
* WITH\_CLI(Y) Собирать интерфейс коммандной строки (в разработке)
* WITH\_YAML(Y) Собирать бэкэнд FileStorage, использующий библиотеку yaml-cpp.
* WITH\_TESTS\_CXX11(Y) Прогонять тесты на поддержку компилятором нового стандарта C++11.
* WITH\_TESTS\_CORE(N) Собирать тесты классов Core.
* WITH\_EXT\_PYTHON\_CLI(N) Собирать питоновские биндинги к CLI. Пока что рекомендуется отказаться использовать эту опцию.
* WITH\_NCURSES(N) Собирать интерфейс на ncurses.
* CORE\_ONLY(N) Не собирать вообще никакие модули (отменяет WITH\_CLI, WITH\_YAML, WITH\_NCURSES, WITH\_SQLITE, етц)


# Переменные среды

На работу программы влияют следующие переменные среды:

    +-----------------------+-------------+----------------------------------------------------------+
    | Переменная            | Значение по | Описание                                                 |
    |                       | умолчанию   |                                                          |
    +=======================+=============+==========================================================+
    | UNISCHED_MODULES\_PATH | .           | Путь поиска модулей. Перечисление директорий через ':'   |
    |                       |             | Например:                                                |
    |                       |             | UNISCHED_MODULES_PATH=src/modules/ui:src/modules/storage |
    +-----------------------+-------------+----------------------------------------------------------+


# Как запустить

На текущий момент, работает только интерфейс-заглушка пользователя и базовый CLI.

Поддерживаются следующие аргументы командной строки:

    +-----------------+------------+-------------+----------------------------------------------------+
    | Аргумент        | Параметр   | Модуль      | Описание                                           |
    +=================+============+=============+====================================================+
    | --iface         | Есть       | -           | Выбор модуля пользовательского интерфейса.         |
    |                 |            |             | Будет загружен первый подходящий, если не указан.  |
    +-----------------+------------+-------------+----------------------------------------------------+
    | --storage       | Есть       | -           | Выбор модуля хранения данных. Ни один не будет     |
    |                 |            |             | если не указано.                                   |
    +-----------------+------------+-------------+----------------------------------------------------+
    | --sqlite-db     | Есть       | SQLITE      | Выбор базы данных sqlite. Будет использовано       |
    |                 |            |             | .raspisator.db, если не указано другое             |
    +-----------------+------------+-------------+----------------------------------------------------+
    | --sqlite-create | Нет        | SQLITE      | Создать структуру базы данных. ВНИМАНИЕ, если      |
    |                 |            |             | в базе были какие-то данные, они будут уничтожены. |
    +-----------------+------------+-------------+----------------------------------------------------+
    | --yaml-file     | Есть       | FileStorage | Выбор файла yaml. Будет использовано database.yaml |
    |                 |            |             | если не указано другое.                            |
    +-----------------+------------+-------------+----------------------------------------------------+

Пример запуска:

    ./src/raspisator --iface DummyUI

Если не найдёт модули, 

    UNISCHED_MODULES_PATH=/path/to/dir/with/at/least/one/module.so ./src/raspisator --iface CLI

Базовый CLI тоже пока ничего не умеет, поэтому вообще сомнительно, что
следует собирать и запускать этот проект :)

# Команды CLI

Список доступных комманд для интерфейса CLI без параметров:

*   usage -- показать список комманд с описанием
*   exit (или quit) -- выход
*   toggle\_debug -- переключить возможность вывода дополнительной информации
*   new\_person -- создать запись-человека, три позиционных аргумента: Имя Фамилия Пол(MALE/FEMALE)
*   new\_group -- создать запись-группу, один позиционный аргумент: Имя
*   load -- загрузить из описание объектов из файла. Два аргумента: Тип Файл. Тип может быть трёх видов: Group, Person, Event.

#Code Style

Предлагается следование следующим правилам:

В коде с реализацией класса единственный include с хэдером для этого класса.
Порядок инклюдов:
    
    #include <iostream>
    #include <string>
    #include <vector>

    #include <boost/format.hpp>
    #include <boost/filesystem.hpp>

    #include <abstractui.h>
    #include <group.h>

    #include "utils.hpp"

Т.е. сначала общесистемные+STL, потом boost, потом уже наши хэдеры, между ними одна пустая строка, потом, если есть, какие-то совсем локальные хэдеры. После последнего #include - две пустые строки

Помимо этого, правила для vera++:

    F001 Source files should not use the '\r' (CR) character
    F002 File names should be well-formed
    L001 No trailing whitespace
    L002 Don't use tab characters
    L003 No leading and no trailing empty lines
    L004 Line cannot be too long
    L005 There should not be too many consecutive empty lines
    T001 One-line comments should not have forced continuation
    T002 Reserved names should not be used for preprocessor macros
    T003 Some keywords should be followed by a single space
    T004 Some keywords should be immediately followed by a colon
    T005 Keywords break and continue should be immediately followed by a
            semicolon
    T006 Keywords return and throw should be immediately followed by a semicolon
            or a single space
    T007 Semicolons should not be isolated by spaces or comments from the rest
            of the code
    T008 Keywords catch, for, if, switch and while should be followed by a
            single space
    T009 Comma should not be preceded by whitespace, but should be followed by
            one
    T010 Identifiers should not be composed of 'l' and 'O' characters only
    T011 Curly brackets from the same pair should be either in the same line or
            in the same column
    T017 Unnamed namespaces are not allowed in header files
    T018 Using namespace is not allowed in header files
    T019 Control structures should have complete curly-braced block of code 

Подробнее смотри http://www.inspirel.com/vera/ce/doc/rules/index.html

Тулза для проверки называется vera++, профиль настроек лежит в файле style\_rules

# Вспомогательные инструменты

В директории auxiliary-tools находятся следующие вспомогательные инструменты:

 * yaml2html.sh --- конвертер данных из yaml формата в html страницу с визуализацией.
 * sqlite2html.sh --- конвертер данных из sqlite3 базы данных в html страницу с визуализацией.

