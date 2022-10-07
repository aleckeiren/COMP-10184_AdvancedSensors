/**
  I, Alec Pasion, 000811377 certify that this material is my original work. No other person's work has been used
  without due acknowledgement.
**/

// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 
DeviceAddress deviceAddress;
boolean sensorFound = false;
boolean disMsgShown = false;
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
  if(DS18B20.getAddress(deviceAddress,0)){
    sensorFound = true;
    Serial.print("\nDS18B20 sensor with address: ");

    for (uint8_t i = 0; i < 8; i++) {
      Serial.print(deviceAddress[i],HEX);
    }

    // Start the DS18B20 sensor 
    Serial.println(" \n");
    DS18B20.begin(); 
  }else{
    Serial.println("\nNo DS18B20 sensors found.");
  }
} 
 
void loop() {
  if(!DS18B20.getAddress(deviceAddress,0)){
    sensorFound = false;
    if(!disMsgShown){
      Serial.println("Sensor Disconnected");
      disMsgShown = true;
    }
  }else{
    sensorFound = true;
    if(disMsgShown){
      Serial.println("Sensor Reconnected");
      disMsgShown = false;
    }
  }
  if(sensorFound){
    float fTemp;
    // ask DS18B20 for the current temperature 
    DS18B20.requestTemperatures(); 
    // fetch the temperature.  We only have 1 sensor, so the index is 0. 
    fTemp = DS18B20.getTempCByIndex(0);
    String statement = "";
    if(fTemp < 10){
      statement = "cold!";
    }else if (fTemp <15 && fTemp >= 10)
    {
      statement = "cool!";
    }else if (fTemp <25 && fTemp >=15)
    {
      statement = "perfect!";
    }else if (fTemp <30 && fTemp >=25)
    {
      statement = "warm!";
    }else if (fTemp <35 && fTemp >= 30)
    {
      statement = "hot!";
    }else {
      statement = "too hot!";
    }
    Serial.println("Current temperature is: " + String(fTemp) + "°C or " +statement);
    // wait 5s (5000ms) before doing this again 
    delay(5000);
  }
}