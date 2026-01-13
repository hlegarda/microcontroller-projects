## nRF24L01 ↔ ESP32 Pin Summary (Expanded)

| nRF24 Pin | Function | ESP32 GPIO (VSPI) | Simple description / why it’s needed |
|----------|---------|------------|--------------------------------------|
| **VCC** | Power (3.3 V) | **3V3** | Powers the nRF24. Must be **3.3 V only**; higher voltage will damage it. A capacitor is needed because the radio draws short current spikes during transmission. |
| **GND** | Ground | **GND** | Common electrical reference so both devices agree on voltage levels. Without this connection, nothing works. |
| **SCK** | SPI Clock | **GPIO 18** | Clock signal from the ESP32 (VSPI). It defines *when* each bit is transferred so both sides stay synchronized. |
| **MOSI** | SPI Data (ESP32 → nRF24) | **GPIO 23** | Data line used by the ESP32 to send commands and configuration data to the nRF24 (register writes, payloads). |
| **MISO (MSO)** | SPI Data (nRF24 → ESP32) | **GPIO 19** | Data line used by the nRF24 to send responses back to the ESP32 (status flags, register reads). |
| **CSN** | SPI Chip Select (active LOW) | **GPIO 21** | Selects the nRF24 on the SPI bus. Pulled LOW during SPI transfers so the radio knows the data is meant for it. |
| **CE** | Radio Enable | **GPIO 22** | Controls the radio’s operating mode. LOW = standby/configuration. HIGH = start transmitting or receiving RF signals. This pin is **not part of SPI**. |
| **IRQ** | Interrupt Output | *(not connected)* | Optional interrupt line used to notify the ESP32 of events like packet sent or received. Not required if polling is used. |


## (HSPI)
| Signal | Pin |
|--------|-----|
| SCK    | 14  |
| MISO   | 12  |
| MOSI   | 13  |
| CS     | 15  |
| CE     | 16  |


## SWITCH PIN (OPTIONAL)

    PIN 33 OF YOUR ESP32 
