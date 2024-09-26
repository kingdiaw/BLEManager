# BLEManager Library for Dabble Gamepad

## Overview
The `BLEManager` library simplifies the process of creating a Bluetooth Low Energy (BLE) server to communicate with the Dabble app’s gamepad. It handles BLE initialization, communication, and decoding of gamepad actions (e.g., UP, DOWN, LEFT, RIGHT, buttons like TRIANGLE, CIRCLE, CROSS, etc.).

## Features
- Initializes BLE with a custom device name.
- Handles communication using BLE Characteristics.
- Decodes Hex values received from Dabble’s gamepad to corresponding button presses and actions.
- Allows sending custom messages via BLE notifications.
- Custom callback support for processing received data.

## API Reference

### Class: `BLEManager`

### Constructor
`cpp
BLEManager();
`

Initializes the BLEManager instance and sets up internal callback handling.

### Public Methods
`void init(const char* deviceName)`

Initializes the BLE device with the specified deviceName, sets up a BLE server, service, and characteristic.

**Parameters:**
**deviceName** - The name of the BLE device as it will appear to clients.
**void notifyHelloWorld()**
Sends a "Hello World" message over the BLE connection to connected clients.

`void sendString(const String &value)`
Sends a custom string message over BLE to connected clients.

**Parameters:**
**value** - The custom string message to send.
`void setOnDataReceivedCallback(OnDataReceivedCallback callback)`
Sets the callback function that will be triggered when data is received from the BLE characteristic.

**Parameters:**
**callback** - A function pointer of type OnDataReceivedCallback, which takes an Arduino String parameter.
`OnDataReceivedCallback getOnDataReceivedCallback()`
Returns the current callback function for handling received data.

Callback Type: `OnDataReceivedCallback`
```cpp
typedef void (*OnDataReceivedCallback)(String);
```
The custom callback that processes the received data. It takes an Arduino String as an argument.

### Example Usage
Initialize and Send Custom Data
```cpp
#include "BLEManager.h"

BLEManager bleManager;

void setup() {
  Serial.begin(115200);
  
  // Initialize the BLEManager with a device name
  bleManager.init("DabbleGamepad");
  
  // Set up a callback to handle received data
  bleManager.setOnDataReceivedCallback(onDataReceived);
}

void loop() {
  // Send "Hello World" periodically
  bleManager.notifyHelloWorld();
  delay(1000);
}

void onDataReceived(String data) {
  Serial.println("Received from Gamepad: " + data);
}
```
### How Data is Decoded
When receiving data from the Dabble app’s gamepad, the library decodes the Hex values based on button actions and translates them into the following commands:

**UP, DOWN, LEFT, RIGHT**
**TRIANGLE, CIRCLE, CROSS, SQUARE**
**START, SELECT**
Default action: IDLE

The decoding is handled in the callback within the BLEManager class, and the decoded action is passed to the user’s custom callback.

### Dependencies
This library depends on the following:

`ESP32 BLE Arduino Library`
