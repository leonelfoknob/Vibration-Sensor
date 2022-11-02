#include <Adafruit_MPU6050.h> //don't forget to download this library
#include <Adafruit_Sensor.h> //don't forget to download this library
#include <Wire.h>
#include "DHT.h"
Adafruit_MPU6050 mpu;
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  for(int i =2;i<9;i++){
    pinMode(i,OUTPUT);
  }

  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println(F("DHTxx test!"));
  dht.begin();
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);
}

void loop() {
  /***********************dht11 temp***************************************/
  delay(10);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  /***********************mpu***************************************/
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float Acc_x = a.acceleration.x;
  float Acc_y = a.acceleration.y;
  float Acc_z = a.acceleration.z;
  float Gy_x = g.gyro.x;
  float Gy_y = g.gyro.y;
  float Gy_z = g.gyro.z;
  /*Serial.print("Acc_x: ");
  Serial.print(Acc_x);
  Serial.print(" | ");
  Serial.print("Acc_y: ");
  Serial.print(Acc_y);
  Serial.print(" | ");*/
  Serial.print("Acc_z ");
  Serial.print(Acc_z);
  Serial.print(" m/s^2");
  Serial.print(" | ");
  /*Serial.print("Gy_x: ");
  Serial.print(Gy_x);
  Serial.print(" | ");
  Serial.print("Gy_y");
  Serial.print(Gy_y);
  Serial.print(" | ");
  Serial.print("Gy_z: ");
  Serial.print(Gy_z);
  Serial.print(" rad/s");
  Serial.print(" | ");
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temp: "));
  Serial.println(t);*/
 float temperature_t = t;//*************************************temp
  Serial.print(F(" Temp: "));//ajouter moi mm
  Serial.println(temperature_t);
  /*Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));*/
}
