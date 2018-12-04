#include <DHT_U.h>
#include "Relay.h"
#include <SimpleDHT.h>
#include <SoftwareSerial.h>

// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
// for relay
//      GND: GND
//      VCC: 5V
//      DATA: 3


int pinDHT11 = 2;
SimpleDHT11 dht11;
SoftwareSerial BLU(9, 8);
String state;
Relay light(3, true);

void setup() {
  Serial.begin(9600); 
  BLU.begin(9600);
  light.begin();
  Serial.print("Begin");
  //state="t";
}

void loop() {
  while (BLU.available()){  // Check if there is an available byte to read
    delay(10); // Delay added to make thing stable 
    //char c = BLU.read(); // Conduct a serial read
    //state = c; // build the string- either "On" or "off"
  }   
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); 
    Serial.println(err);
    delay(1000);
    return;
  }
  
 /* if (state.length() > 0) {
    if (state == "t"){
      BLU.print((int)temperature);
      // Serial.print((int)temperature);
    }
    else if(state == "h"){
      BLU.print((int)humidity);
      // Serial.print((int)humidity);
    }
  }
*/

  int out = light.getState();
  String outS = "";
  switch(out) {
    case 0: outS = "Off"; break;
    case 1: outS = "On"; break;
    default: outS = "N/A"; 
  }
  String tempS = temperature + "";
  String humS = humidity + "";
  String output = String(temperature) + "#" + String(humidity) + "#" + outS;
  if (temperature > 23 && humidity > 50) {
     light.turnOn();
     BLU.print(output);
  }
  else {
    light.turnOff();
    BLU.print(output);
    }
  
 delay(500);
}
  
