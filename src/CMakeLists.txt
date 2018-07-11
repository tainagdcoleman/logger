cmake_minimum_required (VERSION 3.5)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

find_package(Boost 1.58.0 REQUIRED COMPONENTS log)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_executable(boost_test boost_test.cpp)
    target_link_libraries(boost_test ${Boost_LIBRARIES})
endif()
