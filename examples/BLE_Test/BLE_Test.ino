#include <BLEManager.h>

BLEManager bleManager;

// Custom callback to handle data received over BLE
void onDataReceived(String data) {
  Serial.print("Received data: ");
  Serial.println(data);
}

void setup() {
  // Initialize the BLE Manager with a custom device name
  bleManager.init("MyESP32Device");
  
  // Set the custom callback for when data is received
  bleManager.setOnDataReceivedCallback(onDataReceived);
}

void loop() {
  delay(2000);
  
  // Send a custom message every 2 seconds
  bleManager.sendString("Custom Message");
}
