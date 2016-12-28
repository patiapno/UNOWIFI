#include <Wire.h>
#include <Ciao.h>
#include <UNOWIFI.h>

#define Thing_key "++++++++"
UNOWiFi_Thingspeak Uno(Thing_key);
float data[2]={13.4,15.5};
void setup() {
  Ciao.begin();
}

void loop() {
  Uno.MutiplePublish(data,2);
  delay(20*1000);
}
