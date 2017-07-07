#include "SdFat.h"
SdFat SD;

File myFile;

void Save(String text, String label = ""){

//  if(label != ""){
//      Serial.print(label);
//      Serial.print(F(": "));
//      Serial.println(text);
//  }

  //if the file opened okay, write to it
  if (myFile) {
  
    myFile.print(text);
    
    //close the file
    myFile.flush();
  
  }
}

// using a macro to join the seperating character to make it easier to change and not take up memory
#define SEP( val ) val + ","

void Save_sensor(String data, const __FlashStringHelper* label){
  Save(SEP(data), label);
}

bool SD_available = true;

void Save_sensors(String Time, bool PIR, String Temp, int CO2, String Dust){

    if(SD_available){
      
      Save_sensor(Time, F("Time"));
      Save_sensor(String(PIR), F("PIR"));
      Save_sensor(Temp, F("Temp"));
      Save_sensor(String(CO2),F("CO2"));
      Save_sensor(Dust, F("Dust"));
      Save(F("\n"));
    }

//   Wifi_send(Time, PIR, Temp, CO2, Dust);
    WIFI_send(Time, PIR, Temp, CO2, Dust);
   
}

void SD_setup(){
//  Serial.println(F("Init SD"));
  
  if (!SD.begin(10)) {
//    Serial.println(F("Init failed!"));
    SD_available = false;
    return;
  }

//  oled.clear();
//  oled.print(F("Initializing SD"));

  show(F("Initializing SD"));
  // print the headings for our data in the txt file
   myFile = SD.open(F("Box" BOX_ID ".csv"), FILE_WRITE);

   // Print the headings in the csv file
   // please note these do not use the SEP macro because they get converted to Flashstrings which are stored in program memory to save SRAM
   // as a result we can't use dynamic concatenation I don't think
   Save(F("Time,"));
   Save(F("Moving,"));
   Save(F("Temp,"));
   Save(F("Humid,"));
   Save(F("CO2,"));
   Save(F("Dust 1.0,"));
   Save(F("Dust 2.5,"));
   Save(F("Dust 10\n"));

   show(F("SD initialized"));
   
//   Serial.println(F("init done"));
}
