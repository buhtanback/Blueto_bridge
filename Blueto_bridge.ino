#include "painlessMesh.h"
#include "BluetoothSerial.h"

#define MESH_PREFIX     "buhtan"
#define MESH_PASSWORD   "buhtan123"

painlessMesh mesh;
BluetoothSerial SerialBT;

void receivedCallback(uint32_t from, String &msg) {
  String str1 = msg.c_str();
  SerialBT.print(str1);
}

void setup() {
  Serial.begin(115200);

  mesh.init(MESH_PREFIX, MESH_PASSWORD);
  mesh.onReceive(&receivedCallback);

  SerialBT.begin("pies'MASH'");
  Serial.println("The device started, now you can pair it with Bluetooth!");
}

void loop() {
  mesh.update();

  // Передача даних з Bluetooth в mesh
  if (SerialBT.available()) {
    String str = SerialBT.readString();
    str.trim();
    mesh.sendBroadcast(str);
  }
}
