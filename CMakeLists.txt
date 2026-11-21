cmake_minimum_required(VERSION 3.20)
project(AlgoCore-CPP VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Header-only library interface
add_library(algocore INTERFACE)
target_include_directories(algocore INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Test executable
add_executable(algocore_tests tests/test_all.cpp)
target_link_libraries(algocore_tests PRIVATE algocore)

enable_testing()
add_test(NAME AllTests COMMAND algocore_tests)
