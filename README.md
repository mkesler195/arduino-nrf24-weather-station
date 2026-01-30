# Arduino nRF24 Wireless Weather Station

This repository documents a modular Arduino-based wireless weather station built using nRF24L01 radios. The project is being developed incrementally, starting with a fully implemented and documented base station.

## Current Status

- Base station hardware + firmware implemented ✅
- Remote Station 1 (BMP280) implemented + diagram ✅
- Remote Station 2 (thermistor) implemented ✅
- Base display alternates Node 1 / Node 2 every ~5s ✅

## Lessons Learned and Reminders
- nRF24L01 power: VCC must be from Nano 3.3V (not breadboard 3.3V rail), with 100µF across VCC/GND at the radio.
- Node ID + ACK: I'm using NRFLite with ACKs and seq counters (great for debugging).

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

## Build & Run Notes
- Install libraries (NRFLite, RTClib, Adafruit SSD1306/GFX, etc.)
- Flash base-station/firmware/...
- Flash remote-station-1/Firmware/...
- Power notes (USB vs MB102 vs battery)

## Repository Structure

- base-station/firmware/ – Arduino Uno RX + OLED + DS3231
- remote-station-1/Firmware/ – Nano TX + BMP280
- remote-station-2/Firmware/ – Nano TX + thermistor (coming soon)
- docs/diagrams/ – Fritzing diagrams + photos

