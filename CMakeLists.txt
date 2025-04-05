# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD none CACHE STRING "Board type")
set(PICO_PLATFORM rp2040 CACHE STRING "Platform")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(fixed_point_practice C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(fixed_point_practice main.c )

pico_set_program_name(fixed_point_practice "fixed_point_practice")
pico_set_program_version(fixed_point_practice "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(fixed_point_practice 0)
pico_enable_stdio_usb(fixed_point_practice 1)

# Add the standard library to the build
target_link_libraries(fixed_point_practice
        pico_stdlib)

target_sources(fixed_point_practice PUBLIC
        main.c
        fr_types.c)

# Add the standard include files to the build
target_include_directories(fixed_point_practice PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
)

pico_add_extra_outputs(fixed_point_practice)

# Set compile options
add_compile_options(
        -Wall
        #-Wno-format          # int != int32_t as far as the compiler is concerned because gcc has int32_t as long int
        -Wno-unused-function # we have some for the docs that aren't called
        #-Wno-maybe-uninitialized
        # -PICOTOOL_FORCE_FETCH_FROM_GIT
        "-O0"
)