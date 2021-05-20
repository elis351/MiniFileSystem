cmake_minimum_required(VERSION 3.10)
project(mini-fs C)

set(CMAKE_C_STANDARD 11)

add_executable(mfs
        main.c
        mfs_cli.c)

add_executable(mfs_client
        client_main.c)

add_subdirectory(
        ${mini-fs_SOURCE_DIR}/components
)

target_include_directories(mfs PUBLIC
        ${mini-fs_SOURCE_DIR}/components)