# Specifies the minimum version of CMake required to process this file.
cmake_minimum_required(VERSION 3.21)

# Includes the Pico SDK setup script. This script is typically generated 
# or downloaded to the project directory. It sets up the necessary 
# environment and paths for building projects targeting the Raspberry Pi Pico.
include(pico_sdk_import.cmake)

# Sets the name of the project. This can be used in various parts of the 
# build system, including in the generated project files.
project(pico_lcd_display)

# Initializes the Pico SDK. This must be called before using any SDK-related 
# features or libraries.
pico_sdk_init()

# Create a library for the LCD driver
add_library(lcd_driver STATIC
    src/lcd_driver/lcd_st7789_library.c
    src/lcd_driver/font_5x7.c
)

# Add include directories for the library
target_include_directories(lcd_driver PUBLIC src/lcd_driver)

# Link the LCD driver library with Pico SDK components
target_link_libraries(lcd_driver 
    pico_stdlib
    hardware_spi
    hardware_pwm
)

# Defines an executable target named "lcd_display" that will be built from 
# the source file "main.c".
add_executable(lcd_display src/main.c)

# Links the "lcd_display" target to the necessary libraries:
# - `pico_stdlib`: for basic functions like GPIO control, timing, etc.
# - `hardware_spi`: for SPI communication.
# - `hardware_pwm`: for PWM (used for controlling the backlight).
# - `lcd_driver`: our custom LCD driver library
target_link_libraries(
    lcd_display 
    pico_stdlib   # Standard library for Raspberry Pi Pico
    hardware_spi  # SPI communication library
    hardware_pwm  # PWM control library
    lcd_driver    # Our custom LCD driver library
    hardware_timer 
    pico_multicore
)

# Enables USB output and disables UART output (adjust as needed).
pico_enable_stdio_usb(lcd_display 1)
pico_enable_stdio_uart(lcd_display 0)

# Adds extra output formats for the executable. This generates UF2 and 
# binary files for flashing to the Raspberry Pi Pico.
pico_add_extra_outputs(lcd_display)