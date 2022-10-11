cmake_minimum_required(VERSION 3.21)
project(trabalho)

set(CMAKE_CXX_STANDARD 14)

add_executable(trabalho main.cpp classes/Student.cpp classes/Student.h classes/Schedule.cpp classes/Schedule.h classes/Lesson.cpp classes/Lesson.h classes/Class.cpp classes/Class.h)
