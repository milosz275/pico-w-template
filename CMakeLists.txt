cmake_minimum_required(VERSION 3.25)
set(PROGRAM_NAME PicoWTemplate)

find_package(Perl)
if(NOT PERL_FOUND)
    message(FATAL_ERROR "Perl is needed for generating the fsdata.c file")
endif()

set(PICO_BOARD "pico_w")
include(cmake/utils.cmake)

include(pico-sdk/pico_sdk_init.cmake)
include(pico-extras/pico_sdk_import.cmake)

project(${PROGRAM_NAME} C CXX ASM)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(
    -Wall
    -Werror
)

pico_sdk_init()

add_subdirectory(src)
