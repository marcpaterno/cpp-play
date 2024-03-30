cmake_minimum_required(VERSION 3.28 FATAL_ERROR)
project(CppPlay VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

Include(FetchContent)
FetchContent_Declare(
  nanobench
  GIT_REPOSITORY https://github.com/martinus/nanobench.git
  GIT_TAG v4.3.11
  GIT_SHALLOW TRUE)


FetchContent_Declare(
  range-v3
  GIT_REPOSITORY https://github.com/ericniebler/range-v3.git
  GIT_TAG 0.12.0
  GIT_SHALLOW TRUE)

FetchContent_Declare(
  functionalplus
  GIT_REPOSITORY https://github.com/Dobiasd/FunctionalPlus.git
  GIT_TAG v0.2.23
  GIT_SHALLOW TRUE)

FetchContent_Declare(
    flux
    GIT_REPOSITORY https://github.com/tcbrindle/flux.git
    GIT_TAG main 
    GIT_SHALLOW TRUE) 


# Now fetch and prepare all the externals for use
FetchContent_MakeAvailable(nanobench range-v3 functionalplus flux)

add_executable(check-1 check-1.cc)
target_include_directories(check-1 PRIVATE ${functionalplus_SOURCE_DIR}/include)

add_executable(check-2 check-2.cc)
target_include_directories(check-2 PRIVATE ${functionalplus_SOURCE_DIR}/include)

add_executable(trivially-copyable-test trivially-copyable-test.cc)

add_executable(benchmark-functionalplus-range benchmark-functionalplus-range.cc)
target_include_directories(benchmark-functionalplus-range PRIVATE ${functionalplus_SOURCE_DIR}/include)
target_link_libraries(benchmark-functionalplus-range PRIVATE nanobench range-v3::range-v3 flux::flux)

add_executable(intersperse-basic intersperse.cc)
target_link_libraries(intersperse-basic PRIVATE range-v3::range-v3)

add_executable(intersperse-range intersperse.cc)
target_link_libraries(intersperse-range PRIVATE range-v3::range-v3)

target_compile_options(intersperse-range BEFORE PRIVATE "-DUSE_RNG=1")
