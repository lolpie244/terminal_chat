cmake_minimum_required(VERSION 3.21)
project(app)

set(CMAKE_CXX_STANDARD 20)


add_library(file_searcher STATIC lib/file_searcher.cpp)
add_executable(app app/main.cpp)

target_include_directories(file_searcher PUBLIC lib)

target_link_libraries(app PRIVATE file_searcher)


