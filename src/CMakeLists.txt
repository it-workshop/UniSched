cmake_minimum_required(VERSION 2.8)

add_executable (raspisator calendar.cpp command_add.cpp command_all.cpp
    command_clone.cpp command_delete.cpp command_dequeue.cpp
    command_enqueue.cpp command_exclude.cpp command_exit.cpp
    command_generate.cpp command_help.cpp command_include.cpp command_link.cpp
    command_merge.cpp command_print.cpp commands.cpp command_select.cpp
    data_storage.cpp event.cpp event_template.cpp file_storage.cpp group.cpp
    main.cpp person.cpp queue.cpp table_data_storage.cpp userinterface.cpp)

add_test(test_batch raspisator ../tests/test.txt)

