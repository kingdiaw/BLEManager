#include "BLEManager.h"

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Custom BLECharacteristicCallbacks to handle data writes
class MyCallbacks: public BLECharacteristicCallbacks
{
  BLEManager *bleManager;  // Reference to the BLEManager to access the callback
  
  public:
    MyCallbacks(BLEManager *manager) {
      bleManager = manager;
    }

    void onWrite(BLECharacteristic *pCharacteristic) {
      String rawData = pCharacteristic->getValue();  // Get raw data as String

  if (rawData.length() > 0) {
    // Print raw hex values for debugging
    Serial.print("Received HEX data: ");
    for (size_t i = 0; i < rawData.length(); i++) {
      Serial.printf("%02X ", (uint8_t)rawData[i]);
    }
    Serial.println();

    if (rawData.length() >= 7) { // Ensure we have enough data to check
      // Extract the relevant parts of the data for button press/release
      uint8_t highByte = static_cast<uint8_t>(rawData[5]); // The 6th byte for action
      uint8_t lowByte = static_cast<uint8_t>(rawData[6]); // The 7th byte for action
      
      // Decode the action based on highByte and lowByte
      if (highByte == 0 && lowByte == 1) rawData = "UP";
      else if (highByte == 0 && lowByte == 4) rawData = "LEFT";
      else if (highByte == 0 && lowByte == 8) rawData = "RIGHT";
      else if (highByte == 0 && lowByte == 2) rawData = "DOWN";
      else if (highByte == 4 && lowByte == 0) rawData = "TRIANGLE";
      else if (highByte == 8 && lowByte == 0) rawData = "CIRCLE";
      else if (highByte == 0x10 && lowByte == 0) rawData = "CROSS";
      else if (highByte == 0x20 && lowByte == 0) rawData = "SQUARE";
      else if (highByte == 0x01 && lowByte == 0) rawData = "START";
      else if (highByte == 0x02 && lowByte == 0) rawData = "SELECT";
      else rawData = "IDLE"; // Default case

      // Print decoded action
      Serial.println("Decoded Data: " + rawData);
}

        // Trigger the custom callback if it's set
        OnDataReceivedCallback callback = bleManager->getOnDataReceivedCallback();  // Use the public getter
        if (callback != nullptr) {
          callback(rawData);  // Pass value as Arduino String
        }
      }
    }
};

BLEManager::BLEManager() {
  onDataReceived = nullptr;  // Initialize the callback as null
}

void BLEManager::init(const char* deviceName) {

  // Initialize BLE device with the provided name
  BLEDevice::init(deviceName);
  
  // Create server, service, and characteristic
  pServer = BLEDevice::createServer();
  pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE
                    );

  pCharacteristic->setCallbacks(new MyCallbacks(this));  // Pass BLEManager instance to MyCallbacks
  pCharacteristic->setValue("Hello World");

  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
}

void BLEManager::notifyHelloWorld() {
  pCharacteristic->setValue("Hello World");
  pCharacteristic->notify();
}

void BLEManager::sendString(const String &value) {  // Use String instead of std::string
  pCharacteristic->setValue(value);  // Send custom string over BLE
  pCharacteristic->notify();
}

void BLEManager::setOnDataReceivedCallback(OnDataReceivedCallback callback) {
  onDataReceived = callback;  // Set the callback function
}

OnDataReceivedCallback BLEManager::getOnDataReceivedCallback() {
  return onDataReceived;  // Provide access to the callback function
}
