#include <SoftwareSerial.h>
#include "EBYTE.h"

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

int Chan;
DATA MyData;
unsigned long Last;

SoftwareSerial ESerial(PIN_RX, PIN_TX);
EBYTE Transceiver(&ESerial, PIN_M0, PIN_M1, PIN_AX);

void setup() {
  Serial.begin(9600);
  ESerial.begin(9600);
  //Serial.println("Starting Reader");
  Transceiver.init();
  //Transceiver.PrintParameters();
}

void loop() {
  if (ESerial.available()) {
    Transceiver.GetStruct(&MyData, sizeof(MyData));
    /*Serial.print("ID: ");Serial.println(MyData.id);
    Serial.print("durum: ");Serial.println(MyData.durum);
    Serial.print("sicaklik: ");Serial.println(MyData.sicaklik);
    Serial.print("CO2 Val: ");Serial.println(MyData.duman_val);*/
    Serial.print(MyData.id);Serial.print(",");Serial.print(MyData.durum);Serial.print(",");
    Serial.print(MyData.sicaklik);Serial.print(",");Serial.print(MyData.duman_val);//Serial.print(",");
    Last = millis();
  }
  else {
    if ((millis() - Last) > 1000) {
      //Serial.println("No Data Comming...");
    Serial.print(0);Serial.print(",");Serial.print(0);Serial.print(",");
    Serial.print(0);Serial.print(",");Serial.print(0);//Serial.print(",");
      Last = millis();
    }

  }
}
