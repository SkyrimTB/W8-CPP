cmake_minimum_required(VERSION 3.10)
project(Lecture_8 CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(my_async my_async.cpp)
add_executable(my_packaged_task my_packaged_task.cpp)
add_executable(my_promise my_promise.cpp)
