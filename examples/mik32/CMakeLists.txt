cmake_minimum_required(VERSION 3.28)

set(LIB_SRC_PATH "${CMAKE_CURRENT_LIST_DIR}/../../src")
set(LIB_ARCH_PATH "${LIB_SRC_PATH}/arch/mik32")
set(HARDWARE_PATH "${CMAKE_CURRENT_LIST_DIR}/hardware")
set(FIRMWARE_NAME mik32_firmware)

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/mik32_toolchain.cmake)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-DSERIAL_BAUDRATE=${SERIAL_BAUDRATE})
#From mik32_toolchain.cmake
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS_INIT})
message(STATUS "C FLAGS: ${CMAKE_C_FLAGS}")
project("OV7670 MIK32" C CXX ASM)
enable_language(C CXX ASM)


add_subdirectory(${HARDWARE_PATH})

# Compile library
add_library(mik32_arch_ov7670 ${LIB_ARCH_PATH}/mik32.c)
add_library(mik32_i2c_bitbang ${LIB_ARCH_PATH}/i2c_bitbang.c)
add_library(mik32_sccb ${LIB_ARCH_PATH}/sccb.c)
add_library(mik32_uart ${LIB_ARCH_PATH}/uart.c)
target_include_directories(mik32_sccb PUBLIC ${LIB_SRC_PATH})

target_link_libraries(mik32_uart PUBLIC mik32_hal)
target_link_libraries(mik32_i2c_bitbang PUBLIC mik32_hal)
target_link_libraries(mik32_sccb PUBLIC mik32_uart mik32_i2c_bitbang)
target_link_libraries(mik32_arch_ov7670 PUBLIC mik32_sccb mik32_uart)

target_include_directories(mik32_i2c_bitbang PUBLIC ${LIB_ARCH_PATH})

add_library(mik32_ov7670_lib ${LIB_SRC_PATH}/ov7670.c)
target_link_libraries(mik32_ov7670_lib PUBLIC mik32_arch_ov7670)

target_include_directories(mik32_ov7670_lib PUBLIC ${LIB_ARCH_PATH} ${LIB_SRC_PATH})

# Compile example

add_executable(${FIRMWARE_NAME} main.c)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "Building with flags: ${CMAKE_C_COMPILE_FLAGS}")

target_link_libraries(${FIRMWARE_NAME}
    PRIVATE
        mik32_hal
        mik32_ov7670_lib
)

target_link_directories(${FIRMWARE_NAME}
    PRIVATE
        ${HARDWARE_PATH}/mik32-shared/ldscripts
)