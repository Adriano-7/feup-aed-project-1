cmake_minimum_required(VERSION 3.21)
project(trabalho)

set(CMAKE_CXX_STANDARD 14)

add_executable(trabalho main.cpp Student.cpp Student.h Schedule.h Schedule.cpp Lesson.cpp Lesson.h Class.cpp Class.h)
