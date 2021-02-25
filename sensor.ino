//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
const int led=2;
int sensorpir=14;

void setup() {
  pinMode(sensorpir,INPUT);
  
  Serial.begin(115200);
  //nombre y conxion bt
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  pinMode(led,OUTPUT);
}

void loop() {
  //controla las conexiones bt disponibles
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  if (SerialBT.available()) {
    Serial.write(SerialBT.read());
  }
  //controla el parpadeo del led una vvez que se detecta el movimiento
  if(digitalRead(sensorpir) == HIGH)
  {
    Serial.println("Detectando movimiento por el sensor pir");
    digitalWrite(led,HIGH);
    delay(1000);
    digitalWrite(led,LOW);
    delay(1000);
    
  }

}
