cmake_minimum_required(VERSION 3.19 FATAL_ERROR)
project(CppPlay VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(/usr/local/include)
link_directories(/usr/local/lib)

add_executable(check-1 check-1.cc)
add_executable(check-2 check-2.cc)

add_executable(benchmark-functionalplus-range benchmark-functionalplus-range.cc)
target_link_libraries(benchmark-functionalplus-range PRIVATE benchmark)
