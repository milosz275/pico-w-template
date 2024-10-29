set(PROGRAM_NAME PicoWTemplate)

cmake_minimum_required(VERSION 3.25)

find_package(Perl)
if(NOT PERL_FOUND)
    message(FATAL_ERROR "Perl is needed for generating the fsdata.c file")
endif()

set(PICO_BOARD "pico_w")
include(cmake/utils.cmake)

include(pico-sdk/pico_sdk_init.cmake)
include(pico-extras/pico_sdk_import.cmake)

project(${PROGRAM_NAME})
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(
    -Wall
    -Werror
)

add_executable(${PROGRAM_NAME}
    src/main.c
)

target_link_libraries(${PROGRAM_NAME}
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    pico_multicore
    hardware_adc
)

target_include_directories(${PROGRAM_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/include
)

pico_sdk_init()

pico_enable_stdio_usb(${PROGRAM_NAME} 1)
pico_enable_stdio_uart(${PROGRAM_NAME} 0)

pico_add_extra_outputs(${PROGRAM_NAME})
