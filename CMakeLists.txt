cmake_minimum_required(VERSION 3.6)
project(lab100p)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp IniParser.cpp IniParser.h SectionNotFound.h ParamNotFound.h SectionNotFound.cpp ParamNotFound.cpp)
add_executable(lab100p ${SOURCE_FILES})