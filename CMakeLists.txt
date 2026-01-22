cmake_minimum_required(VERSION 4.2.1)
project(web_server)

set(SOURCE_FILES
    main.c
    server.c
    parser.c
    utils.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
