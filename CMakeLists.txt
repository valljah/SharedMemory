cmake_minimum_required(VERSION 3.5)

project(SharedMemory C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_COMPILER "/opt/homebrew/bin/gcc-13")
set(CMAKE_C_STANDARD 17)

add_executable(Producer producer.c defines.c)
add_executable(Consumer consumer.c defines.c)
