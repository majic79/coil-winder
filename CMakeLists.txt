cmake_minimum_required(VERSION 3.12)

if (NOT DEFINED ENV{PICO_SDK_PATH})
    message(FATAL ERROR "Please set PICO_SDK_PATH Environment Variable")
endif ()
set(PICO_SDK_PATH $ENV{PICO_SDK_PATH})
include(${PICO_SDK_PATH}/external/pico_sdk_import.cmake)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(coil-winder C CXX ASM)

pico_sdk_init()

file(GLOB SRC_C_FILES ${PROJECT_SOURCE_DIR}/*.c)
file(GLOB SRC_CPP_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
file(GLOB SRC_PIO_FILES ${PROJECT_SOURCE_DIR}/*.pio)
add_executable(${PROJECT_NAME} ${SRC_C_FILES} ${SRC_CPP_FILES} ${SRC_PIO_FILES})

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/quadrature_encoder.pio)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    hardware_i2c
    hardware_pio
#    hardware_adc
)