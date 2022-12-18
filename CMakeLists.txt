cmake_minimum_required(VERSION 3.5)
project (googlemock_extension)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

set(DOBBY_GENERATE_SHARED OFF CACHE BOOL "Build shared library")
set(DOBBY_DEBUG OFF CACHE BOOL "Enable debug logging")

add_subdirectory(thirdparty/Dobby)
add_subdirectory(thirdparty/googletest)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

set(GOOGLE_TEST_DIR ${CMAKE_SOURCE_DIR}/thirdparty/googletest)
set(GTEST_DIR ${GOOGLE_TEST_DIR}/googletest)
set(GMOCK_DIR ${GOOGLE_TEST_DIR}/googlemock)

include_directories(
    ${CMAKE_SOURCE_DIR}/gmock-extension/include
    ${GOOGLE_TEST_DIR}/googletest
    ${GOOGLE_TEST_DIR}/googletest/include
    ${GOOGLE_TEST_DIR}/googletest/include/internal
    ${GOOGLE_TEST_DIR}/googlemock
    ${GOOGLE_TEST_DIR}/googlemock/include
    ${GOOGLE_TEST_DIR}/googlemock/include/internal
)

file(GLOB_RECURSE SOURCES RELATIVE 
    ${CMAKE_SOURCE_DIR} 
    ${CMAKE_SOURCE_DIR}/gmock-extension/src/*.cpp
)

add_library(gmock_extension STATIC ${SOURCES})
target_link_libraries(gmock_extension dobby)
set_target_properties(gmock_extension
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

add_subdirectory(tests)
add_subdirectory(examples)
