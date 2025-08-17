STM32 DHT11 Sensor (Register-Level, 1-Wire Protocol)
--------------

This project demonstrates how to interface a DHT11 temperature and humidity sensor with an STM32G431RB microcontroller using bare-metal (register-level) programming.

The communication is implemented with the single-wire protocol, without relying on STM32 HAL drivers or high-level libraries.

Key Points
---------
Register-level programming (no HAL)

1-Wire protocol implementation for DHT11 communication

UART (HAL) used only for debugging and printing results

All implementation details are documented directly in the source files

Hardware
--------------------
MCU: STM32G431RB (Nucleo board or similar)

Sensor: DHT11 (temperature + humidity)

Interface: Single data pin (1-Wire protocol)

Debugging: UART output
