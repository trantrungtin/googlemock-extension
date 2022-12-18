cmake_minimum_required(VERSION 3.10)
project (gmocke_examples)
set(CMAKE_CXX_STANDARD 14)

set(ROOT_DIR ${PROJECT_SOURCE_DIR}/..)
set(GOOGLE_TEST_DIR ${ROOT_DIR}/thirdparty/googletest)
set(GTEST_DIR ${GOOGLE_TEST_DIR}/googletest)
set(GMOCK_DIR ${GOOGLE_TEST_DIR}/googlemock)


include_directories(
    ${ROOT_DIR}/gmock-extension/include
    ${PROJECT_SOURCE_DIR}/include
    ${GOOGLE_TEST_DIR}/googletest
    ${GOOGLE_TEST_DIR}/googletest/include
    ${GOOGLE_TEST_DIR}/googlemock
    ${GOOGLE_TEST_DIR}/googlemock/include
)

add_executable(gmocke_examples
    src/Demo.cpp
    tests/DemoTest.cpp
    ${GTEST_DIR}/src/gtest-all.cc
    ${GMOCK_DIR}/src/gmock-all.cc
    ${GMOCK_DIR}/src/gmock_main.cc
)

set(GMOCKE_LIB_PATH ${CMAKE_BINARY_DIR}/libgmocke.dylib)
target_link_libraries(gmocke_examples pthread gmock_extension)

set_target_properties(gmocke_examples
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    PDB_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )
