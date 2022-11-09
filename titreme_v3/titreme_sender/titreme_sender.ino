// 
#include <SoftwareSerial.h>
#include "EBYTE.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
Adafruit_MPU6050 mpu;
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 20, 4);

#define PIN_RX 2
#define PIN_TX 3
#define PIN_M0 4
#define PIN_M1 5
#define PIN_AX 6


struct DATA {
  float durum;
  float sicaklik;
  int duman_val;
  int id;
};

int ID = 1; //motor and sensor id
int Chan;
DATA MyData;

SoftwareSerial ESerial(PIN_RX, PIN_TX);
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {
  ESerial.begin(9600);
  Transceiver.init();
  Transceiver.PrintParameters();

  lcd.init();
  lcd.backlight();
  lcd.begin (20, 4);
      
  if (!mpu.begin()) {
    while (1) {
      delay(10);
      }
     }
     
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);
}

void loop() {
 // smoke sensor data
  int duman_sensor = analogRead(A0);
//mpu6050 data and temperature
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float Acc_x = a.acceleration.x;
  float Acc_y = a.acceleration.y;
  float Acc_z = a.acceleration.z;
  float Gy_x = g.gyro.x;
  float Gy_y = g.gyro.y;
  float Gy_z = g.gyro.z;
  float sicak = temp.temperature;
  
//struct data will send
  MyData.durum = Acc_z;
  MyData.sicaklik = sicak;
  MyData.duman_val = duman_sensor;
  MyData.id = ID;
  
//lcd show motor id
  lcd.setCursor(0, 0);
  lcd.print("----> MOTOR");
  lcd.setCursor(12, 0);
  lcd.print(MyData.id);
  lcd.setCursor(14, 0);
  lcd.print("<----");
//lcd show vibration
  lcd.setCursor(0, 1);
  lcd.print("Durum :");
  lcd.setCursor(7, 1);
  lcd.print(MyData.durum);
  lcd.print("       ");
// lcd show temperaure
  lcd.setCursor(0, 2);
  lcd.print("Sicaklik :");
  lcd.setCursor(10, 2);
  lcd.print(MyData.sicaklik);
  lcd.print("     ");
//lcd show logo
  lcd.setCursor(0, 3);
  lcd.print("CO2 Val :");
  lcd.setCursor(10, 3);
  lcd.print(MyData.duman_val);
  lcd.print("     ");
  Transceiver.SendStruct(&MyData, sizeof(MyData));
  delay(10);  
}
