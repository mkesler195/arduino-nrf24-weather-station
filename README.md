# Arduino nRF24 Wireless Weather Station

This repository documents a modular Arduino-based wireless weather station built using nRF24L01 radios. The project is being developed incrementally, with a fully implemented and documented base station and multiple working remote sensor nodes.

The emphasis of this project is on reliability, clear documentation, and capturing real-world lessons learned while building a small multi-node wireless system.

## Current Status

- Base station hardware + firmware implemented ✅
- Remote Station 1 (BMP280) implemented + diagram ✅
- Remote Station 2 (thermistor) implemented ✅
- Base display alternates Node 1 / Node 2 every ~5 seconds ✅

## Lessons Learned and Reminders

These are the practical details that mattered most during development:

- **nRF24L01 power stability**  
  Radio VCC must be powered from the Nano’s **3.3V pin** (not a breadboard 3.3V rail), with a **100 µF electrolytic capacitor placed directly across VCC/GND at the radio**.

- **Reliable packet delivery**  
  The project uses **NRFLite with ACKs and sequence counters**, which greatly simplifies debugging and confirms link reliability.

## System Overview

The weather station follows a simple, extensible architecture.

### Base Station
- Arduino Uno
- nRF24L01 radio
- OLED display
- DS3231 real-time clock (RTC)

The base station listens for data from multiple remote nodes and automatically alternates the display between active nodes.

### Remote Sensor Nodes
- Battery-powered Arduino-compatible boards (Nano-class)
- Environmental sensors (BMP280, thermistor, etc.)
- nRF24L01 radios

Each node transmits environmental data to the base station using a unique node ID.

## Build & Run Notes

- Install required libraries:
  - NRFLite
  - RTClib
  - Adafruit SSD1306
  - Adafruit GFX
- Flash the base station firmware:
  - `base-station/firmware/`
- Flash remote node firmware:
  - `remote-station-1/Firmware/`
  - `remote-station-2/Firmware/`
- Power considerations:
  - USB is convenient for development
  - MB102 breadboard supply or battery power is used for remote nodes
  - Do not power the Nano from USB and external 5V at the same time

## Repository Structure

- `base-station/firmware/`  
  Arduino Uno RX + OLED + DS3231 firmware

- `remote-station-1/Firmware/`  
  Nano TX + BMP280 sensor

- `remote-station-2/Firmware/`  
  Nano TX + thermistor-based temperature sensor

- `docs/diagrams/`  
  Fritzing diagrams and build photos
