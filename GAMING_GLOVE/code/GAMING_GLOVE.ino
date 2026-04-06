#include <Wire.h>
#include <MPU6050.h>
#include <BleKeyboard.h>

MPU6050 mpu;
BleKeyboard bleKeyboard("ESP32 Gaming Glove", "ESP32", 100);

int16_t ax, ay, az;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  mpu.initialize();
  if (!mpu.testConnection()) {
    Serial.println("MPU6050 not connected");
    while (1);
  }

  bleKeyboard.begin();
  Serial.println("Bluetooth Keyboard Started");
}

void loop() {
  if (bleKeyboard.isConnected()) {

    mpu.getAcceleration(&ax, &ay, &az);

    // RELEASE ALL FIRST
    bleKeyboard.releaseAll();

    if (ay > 8000) {
      bleKeyboard.press('w');
    }
    else if (ay < -8000) {
      bleKeyboard.press('s');
    }
    else if (ax > 8000) {
      bleKeyboard.press('d');
    }
    else if (ax < -8000) {
      bleKeyboard.press('a');
    }

    delay(70);
  }
}
