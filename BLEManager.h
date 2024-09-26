#ifndef BLEMANAGER_H
#define BLEMANAGER_H

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

typedef void (*OnDataReceivedCallback)(String);  // Use Arduino String for the callback

class BLEManager {
  public:
    BLEManager();                           // Constructor
    void init(const char* deviceName);      // Init method to set device name
    void notifyHelloWorld();                // Method to send "Hello World"
    void sendString(const String &value);   // Method to send a custom string
    void setOnDataReceivedCallback(OnDataReceivedCallback callback); // Set custom data received callback

    OnDataReceivedCallback getOnDataReceivedCallback();  // Public getter for the callback

  private:
    BLECharacteristic *pCharacteristic;     // BLE Characteristic
    BLEServer *pServer;                     // BLE Server
    BLEService *pService;                   // BLE Service

  protected:
    OnDataReceivedCallback onDataReceived;  // Custom callback for data received
};

#endif
