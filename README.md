# Raspberry Pi Pico - Coil Winder

Simple firmware to allow a Raspberry Pi Pico to drive a coil winder of some sort.

UI is comprised of two buttons, and a rotary encoder + push button. A small 128x64 OLED on I2C serves as a convenient user display

Output is two conventional stepper drivers, and feedback is available for limit switches if they are desired.

The Pico PIO sample code for a quadrature encoder is used to drive the user input Rotary encoder.