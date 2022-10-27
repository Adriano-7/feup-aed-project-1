cmake_minimum_required(VERSION 3.21)
project(trabalho)

set(CMAKE_CXX_STANDARD 14)

add_executable(trabalho main.cpp Student.cpp Student.h Slot.cpp Slot.h ScheduleManager.cpp ScheduleManager.h ClassSchedule.cpp ClassSchedule.h UcClass.cpp UcClass.h Request.cpp Request.h Test.cpp Test.h)
