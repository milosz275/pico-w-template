

add_executable(${PROGRAM_NAME}
    main.c
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
    ${CMAKE_CURRENT_LIST_DIR}/../include
)

suppress_pico_sdk_warnings()
pico_enable_stdio_usb(${PROGRAM_NAME} 1)
pico_enable_stdio_uart(${PROGRAM_NAME} 0)
pico_add_extra_outputs(${PROGRAM_NAME})
