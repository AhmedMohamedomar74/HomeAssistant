# Home Assistant IoT Project

This project involves monitoring room humidity and temperature and controlling an LED through a user-friendly GUI interface powered by Home Assistant OS. The system utilizes an ESP microcontroller configured with ESPHome for seamless integration and control.

## Overview

The project is designed to provide real-time monitoring and control of environmental conditions in a room. It displays current humidity and temperature values and allows for easy control of an LED using the Home Assistant dashboard.

## Features

- **Humidity and Temperature Monitoring**: Real-time data updates from the ESP microcontroller, displaying current room conditions on the Home Assistant interface.
- **LED Control**: Ability to turn the LED on and off directly from the Home Assistant GUI.
- **ESP Microcontroller with ESPHome**: The ESP microcontroller is configured using ESPHome for easy integration with Home Assistant, simplifying the setup and communication process.

## Components Used

- **ESP Microcontroller**: Configured with ESPHome for communication with Home Assistant.
- **DHT Sensor**: Measures room temperature and humidity.
- **LED**: Controlled from the Home Assistant interface.

## Configuration and Setup

1. **Install Home Assistant OS**: Set up Home Assistant OS on your server or Raspberry Pi.
2. **ESPHome Configuration**: Configure the ESP microcontroller with ESPHome, specifying the pins for the DHT sensor and the LED.
3. **Integration**: Add the ESPHome device to Home Assistant and create a dashboard for monitoring and control.

## How It Works

1. **Data Monitoring**: The DHT sensor connected to the ESP microcontroller measures the humidity and temperature. The ESP microcontroller sends this data to Home Assistant, which displays it on the dashboard.
2. **LED Control**: The LED can be switched on or off using the GUI, with commands sent from Home Assistant to the ESP microcontroller.

## Demo

Below is a GIF demonstrating the project in action:

![Project Demo](Demo.gif)