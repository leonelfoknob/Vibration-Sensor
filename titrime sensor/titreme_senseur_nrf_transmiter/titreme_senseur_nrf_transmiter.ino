
/*titremer cihazı transmitter
 * 3.3v and gnd use 10 nanofarad condansator and if you want change ce and cns pin
 * NRF24L01  PNA/LNA Arduino uno and Arduino nano connection pin
     ----------------
GND |GND         VCC | 3.3V        
7   |CE          CNS | 8    ---------   
13  |SCK         MOSI| 11      ANTEN  |
12  |MISO        IRQ |      ---------
     ----------------

* NRF24L01 Arduino uno and Arduino nano connection pin
     ----------------
GND |GND         VCC | 3.3V        
7   |CE          CNS | 8    ---  
13  |SCK         MOSI| 11     | ANTEN
12  |MISO        IRQ |      ---
     ----------------
*/

//verici
#include <Adafruit_MPU6050.h> //don't forget to download this library
#include <Adafruit_Sensor.h> //don't forget to download this library
#include <Wire.h>
Adafruit_MPU6050 mpu;
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

float data[1];

void setup() {
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);

  mpu.setGyroRange(MPU6050_RANGE_500_DEG);

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  delay(100);

  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}
void loop() {
  
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float Acc_x = a.acceleration.x;
  float Acc_y = a.acceleration.y;
  float Acc_z = a.acceleration.z;
  float Gy_x = g.gyro.x;
  float Gy_y = g.gyro.y;
  float Gy_z = g.gyro.z;
  
  data[0] = Acc_z;
  
  Serial.print(data[0]);
  
  radio.write(&data, sizeof(data));
  //delay(1000);
  delay(20);
  Serial.println("data sended...");
}
