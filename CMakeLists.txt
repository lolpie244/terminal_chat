cmake_minimum_required(VERSION 3.21)
project(terminal_chat)

set(CMAKE_CXX_STANDARD 20)

set(LIB_NAME chat-lib)
set(APP_NAME chat)

add_subdirectory(src)
add_subdirectory(app)
