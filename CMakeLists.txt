cmake_minimum_required(VERSION 3.10)
project (demo)
set(CMAKE_CXX_STANDARD 14)


set(GOOGLE_TEST_DIR ${PROJECT_SOURCE_DIR}/googletest)
set(GTEST_DIR ${GOOGLE_TEST_DIR}/googletest)
set(GMOCK_DIR ${GOOGLE_TEST_DIR}/googlemock)

include_directories(
    ${PROJECT_SOURCE_DIR}/gmock-extension
    ${PROJECT_SOURCE_DIR}/include
    ${GOOGLE_TEST_DIR}/googletest
    ${GOOGLE_TEST_DIR}/googletest/include
    ${GOOGLE_TEST_DIR}/googletest/include/internal
    ${GOOGLE_TEST_DIR}/googlemock
    ${GOOGLE_TEST_DIR}/googlemock/include
    ${GOOGLE_TEST_DIR}/googlemock/include/internal
)
file(GLOB_RECURSE SOURCES RELATIVE 
    ${CMAKE_SOURCE_DIR} 
    "src/*.cpp"
    ${GTEST_DIR}/src/gtest-all.cc
    ${GMOCK_DIR}/src/gmock-all.cc
    ${GMOCK_DIR}/src/gmock_main.cc
)

add_executable(demo ${SOURCES})
target_link_libraries(demo pthread)


