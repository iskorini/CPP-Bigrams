cmake_minimum_required(VERSION 3.6)
project(CPP-Bigrams)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES ../CPP-Bigrams/main.cpp ctpl.h ctpl_stl.h)

include_directories("C:\\Program Files\\boost_1_55_0")

add_executable(CPP-Bigrams ${SOURCE_FILES} ctpl.h ctpl_stl.h)