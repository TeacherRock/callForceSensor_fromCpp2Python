cmake_minimum_required(VERSION 3.5)

project (hi_test)

set( basic_cxx17 "c++17" )
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(ForceSensor_dll SHARED "ForceSensor.cpp")

add_executable (run_ForceSensor main.cpp)
target_link_libraries(run_ForceSensor  ForceSensor_dll)