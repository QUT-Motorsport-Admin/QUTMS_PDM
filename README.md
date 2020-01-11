![QUTMS Banner](https://github.com/QUT-Motorsport/QUTMS_Master/blob/master/src/qutmsBanner.jpg?raw=true)

# QUTMS_PDM

Main power distribution for high current devices on the car as well as control of the main LV power busses.

## Features

- ATmega1280 microcontroller
- 4 high and low side outputs
- 9 high current high-side outputs
- 2 Analog inputs
- Onboard thermistor temperature sensor
- CANBUS communication with the MCP2515 controller

## Functions

A key function of the PDM is to power the shutdown loop that runs throughout the car powering the AIRs. This uses one of the high current outputs and the low side of one of the high-low outputs.

The PDM controls power to all of the low voltage devices on the car through a few of its high current outputs. While the current limit on each high current output is 7.5 amps, devices are split onto multiple outputs to allow for future expansion.

Every output on the PDM is controlled using pins on the microcontroller that have PWM capability. This is so devices like pumps and fans can have their speeds modulated. 

The two analog inputs are intended to be used for the radiator temperature sensors since the PDM is also controlling the radiator fans.
