cmake_minimum_required(VERSION 3.5)
project (googlemock_extension)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

add_subdirectory(thirdparty/Dobby)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

set(GOOGLE_TEST_DIR ${CMAKE_SOURCE_DIR}/thirdparty/googletest)
set(GTEST_DIR ${GOOGLE_TEST_DIR}/googletest)
set(GMOCK_DIR ${GOOGLE_TEST_DIR}/googlemock)

include_directories(
    ${CMAKE_SOURCE_DIR}/gmock-extension
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
    "${CMAKE_SOURCE_DIR}/gmock-extension/src/*.cpp"
)

add_library(gmocke SHARED ${SOURCES})
target_link_libraries(gmocke dobby)

add_subdirectory(examples)

# add_library(gmocke_static STATIC ${SOURCES})
# target_link_libraries(gmocke_static dobby)
