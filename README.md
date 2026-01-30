# Arduino nRF24 Wireless Weather Station

This repository documents a modular Arduino-based wireless weather station built using nRF24L01 radios. The project is being developed incrementally, starting with a fully implemented and documented base station.

## Current Status

- Base station hardware + firmware implemented ✅
- Remote Station 1 (BMP280) implemented + diagram ✅
- Remote Station 2 (thermistor) implemented ✅
- Base display alternates Node 1 / Node 2 every ~5s ✅

## System Overview

The weather station system is designed around a simple architecture:

### Base Station
- Arduino Uno
- nRF24L01 radio
- OLED display
- DS3231 real-time clock (RTC)

### Remote Sensor Nodes (planned)
- Battery-powered Arduino-compatible boards
- Environmental sensors
- nRF24L01 radios

## Repository Structure

