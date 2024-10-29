cmake_minimum_required(VERSION 3.25)

find_package(Perl)
if(NOT PERL_FOUND)
    message(FATAL_ERROR "Perl is needed for generating the fsdata.c file")
endif()

set(PICO_BOARD "pico_w")
include(cmake/utils.cmake)

include(pico-sdk/pico_sdk_init.cmake)
include(pico-extras/pico_sdk_import.cmake)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/cmake/credentials.cmake)
    include(cmake/credentials.cmake)
else()
    message(WARNING "Credentials file not found, using default values!")
    set(WIFI_SSID "SSID" CACHE INTERNAL "WiFi SSID for examples")
    set(WIFI_PASSWORD "password" CACHE INTERNAL "WiFi password for examples")
endif()

project(PicoWTemplate)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

add_compile_options(
    -Wall
    -Werror
)

add_executable(PicoWTemplate
    src/main.c
)

target_link_libraries(PicoWTemplate
    pico_stdlib
    pico_cyw43_arch_lwip_threadsafe_background
    pico_lwip_http
    hardware_adc
)

target_include_directories(PicoWTemplate PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/include
)

pico_sdk_init()

pico_add_extra_outputs(PicoWTemplate)

pico_enable_stdio_usb(PicoWTemplate 1)
pico_enable_stdio_uart(PicoWTemplate 0)
