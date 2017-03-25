cmake_minimum_required(VERSION 3.6)
project(WordAnalysis)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp ClassifyValue.h ClassifyValue.cpp WrongInfomation.cpp WrongInfomation.h Table.cpp Table.h)
add_executable(WordAnalysis ${SOURCE_FILES})