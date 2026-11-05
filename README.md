# STM32F103 Bare-Metal Driver Development

Low-level embedded firmware development for STM32F103
(ARM Cortex-M3) using Embedded C and register-level programming.

## Technologies
- Embedded C
- STM32F103C8 / ARM Cortex-M3
- Keil MDK
- Register-level programming

## Project Structure
- Driver/ - GPIO, RCC, ADC, UART, SPI, I2C, EXTI, Timer, USB, AFIO
- Lib/ - DS3231 RTC, ST7735/ST7789 TFT displays, fonts
- Src/ - Application source code

## Objectives
- Study STM32 peripheral registers using RM0008.
- Develop reusable low-level peripheral drivers.
- Understand clock configuration, interrupts, and communication protocols.

## Build
Open 01.uvprojx in Keil MDK and build the project.

## Status
Work in progress. Driver testing and documentation are ongoing.