cmake_minimum_required(VERSION 3.5)
project (googlemock_extension)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD 11)

add_subdirectory(thirdparty/Dobby)

include_directories(
    ${CMAKE_SOURCE_DIR}/gmock-extension
)

file(GLOB_RECURSE SOURCES RELATIVE 
    ${CMAKE_SOURCE_DIR} 
    "${CMAKE_SOURCE_DIR}/gmock-extension/src/*.cpp"
)

add_library(gmocke SHARED ${SOURCES})

target_link_libraries(gmocke dobby)
