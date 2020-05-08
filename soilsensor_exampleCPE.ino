/*

Works with the following materials:
Adafruit Circuit Playground Express : http://adafru.it/333
Adafruit Soil Sensor : http://adafru.it/4026 (Install Adafruit_seesaw library via Arduino Library Manager)
JST 4PH to fe/male header cable : http://adafru.it/3950 or http://adafru.it/3955
*/

#include "Adafruit_seesaw.h"
#include <Adafruit_CircuitPlayground.h>

Adafruit_seesaw ss;
boolean blinkState;
int i; //generic counter needed


/*
Global Variables for Soil Moisture.
This is being used for soil moisture and not tempature due to the use of the map() function.
*/

uint16_t MinCap = 200;       //From Sensor datasheet
uint16_t MinWet = 600;       //From Data  TEST VALUE
uint16_t MinOptimal = 800;   //from data  TEST VALUE
uint16_t MaxOptimal = 1000;  //from data  TEST VALUE
uint16_t MaxWet = 1350;      //from data  TEST VALUE
uint16_t MaxCap = 2000;      //from Sensor datasheet

void setup() {
  CircuitPlayground.begin();

  //pins, if necessary
  pinMode(13, OUTPUT);

  //Variable Setup
  blinkState = true;
  i = 0;
  
  Serial.begin(115200);
  Serial.println("HELLO WORLD");
  Serial.println("seesaw Soil Sensor example!");

  //Show a boot up LED event, then clear them
  bootLEDs();

  //check to see if seesaw is there
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    //set all NEOPIXELS to red then play bad tone
    redLEDs();
    CircuitPlayground.playTone(5000,500,0);
    while(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
    //play you win, set all NEOPIXELS GREEN
    greenLEDs();
    CircuitPlayground.playTone(750,500,0);
  }
  
  delay(500);
  CircuitPlayground.clearPixels();
}


void loop() {
  //Retrive Stemma Info
  float tempC = ss.getTemp();
  uint16_t capread = ss.touchRead(0);
  Serial.print("Temperature: "); Serial.print(tempC); Serial.println("*C");
  Serial.print("Capacitive: "); Serial.println(capread);
  
  //show that I'm cycyling through the code
  if(blinkState == true) {
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }
  blinkState = !blinkState;

 //if A pressed, then Tempature, if B pressed then Moisture
 if(CircuitPlayground.leftButton()){
    displayTemp(tempC);
  }
  if(CircuitPlayground.rightButton()) {
    displaySoil(capread);
  }  
  delay(1000);  
  CircuitPlayground.clearPixels();
}

void bootLEDs(){
  //description
  for(int j=0; j<10; j++){
    CircuitPlayground.setPixelColor(j,0,0,255);
      delay(100);
  }
}

void redLEDs() {
    CircuitPlayground.setBrightness(30);
    for(int j=0; j<10; j++){
      CircuitPlayground.setPixelColor(j,255,0,0);
    }
}

void greenLEDs() {
  CircuitPlayground.setBrightness(30);
  for(int j=0; j<10; j++){
      CircuitPlayground.setPixelColor(j,0,255,0);
    } 
}

void blueLEDs(){
  CircuitPlayground.setBrightness(30);
  for(int j=0; j<10; j++){
    CircuitPlayground.setPixelColor(j,0,0,255);
  }
}


//display the soil tempature via the neopixels
void displayTemp(float tempC) {
  //testing values of tempC, comment out when done
  //tempC = 25;
  CircuitPlayground.setBrightness(30);
  CircuitPlayground.clearPixels();

   if(tempC <= 0){
    //way too cold, full blue
    blueLEDs();
   }
   if(tempC >=45) {
    //way too hot, full red
    redLEDs(); 
   }

  //In version 2, migrate this to a switch statement like tha moisture values.

   //freezing to optimal
   if(tempC>0 && tempC<=2){
    blueLEDs();
    CircuitPlayground.setPixelColor(9,0,255,0);
    }
   if(tempC>2 && tempC<=4){
    blueLEDs();
    CircuitPlayground.setPixelColor(9,0,255,0);
    CircuitPlayground.setPixelColor(8,0,255,0);
    }
    if(tempC>4 && tempC<=6){
      blueLEDs();
      CircuitPlayground.setPixelColor(9,0,255,0);
      CircuitPlayground.setPixelColor(8,0,255,0);
      CircuitPlayground.setPixelColor(7,0,255,0);
    }
    if(tempC>6 && tempC<=8){
      blueLEDs();
      CircuitPlayground.setPixelColor(9,0,255,0);
      CircuitPlayground.setPixelColor(8,0,255,0);
      CircuitPlayground.setPixelColor(7,0,255,0);
      CircuitPlayground.setPixelColor(6,0,255,0);
    }
    if(tempC>8 && tempC<=10){
      blueLEDs();
      CircuitPlayground.setPixelColor(9,0,255,0);
      CircuitPlayground.setPixelColor(8,0,255,0);
      CircuitPlayground.setPixelColor(7,0,255,0);
      CircuitPlayground.setPixelColor(6,0,255,0);    
      CircuitPlayground.setPixelColor(5,0,255,0);
    }
    if(tempC>10 && tempC<=12){
      greenLEDs();
      CircuitPlayground.setPixelColor(0,0,0,255);
      CircuitPlayground.setPixelColor(1,0,0,255);
      CircuitPlayground.setPixelColor(2,0,0,255);
      CircuitPlayground.setPixelColor(3,0,0,255);    
    }
    if(tempC>12 && tempC<=14){
      greenLEDs();
      CircuitPlayground.setPixelColor(0,0,0,255);
      CircuitPlayground.setPixelColor(1,0,0,255);
      CircuitPlayground.setPixelColor(2,0,0,255);    
    }
    if(tempC>14 && tempC<=16){
      greenLEDs();
      CircuitPlayground.setPixelColor(0,0,0,255);
      CircuitPlayground.setPixelColor(1,0,0,255);    
    }
    if(tempC>16 && tempC<=18){
      greenLEDs();
      CircuitPlayground.setPixelColor(0,0,0,255);    
    }

    //optimal range 18-24  //testing here
    if(tempC>18 && tempC<=24){
      greenLEDs();
      }
    if(tempC>18 && tempC<=19){
      CircuitPlayground.setPixelColor(9,0,255,128);
      //CircuitPlayground.setPixelColor(8,0,255,128);
      }
    if(tempC>19 && tempC<=20){
      CircuitPlayground.setPixelColor(8,0,255,128);
      CircuitPlayground.setPixelColor(7,0,255,128);
      }
    if(tempC>20 && tempC<=21){
      CircuitPlayground.setPixelColor(6,0,255,128);
      CircuitPlayground.setPixelColor(5,0,255,128);
      }
    if(tempC>21 && tempC<=22){
      CircuitPlayground.setPixelColor(4,128,255,0);
      CircuitPlayground.setPixelColor(3,128,255,0);
      }
    if(tempC>22 && tempC<=23){
      CircuitPlayground.setPixelColor(2,128,255,0);
      CircuitPlayground.setPixelColor(1,128,255,0);
      }
    if(tempC>23 && tempC<=24){
      //CircuitPlayground.setPixelColor(1,128,255,0);
      CircuitPlayground.setPixelColor(0,128,255,0);
      }

    //optimal to too hot 25-45
    if(tempC>24 && tempC<=27){
      greenLEDs();
      CircuitPlayground.setPixelColor(9,255,0,0);
    }
    if(tempC>27 && tempC<=29){
      greenLEDs();
      CircuitPlayground.setPixelColor(9,255,0,0);
      CircuitPlayground.setPixelColor(8,255,0,0);
    }
    if(tempC>29 && tempC<=31){
      greenLEDs();
      CircuitPlayground.setPixelColor(9,255,0,0);
      CircuitPlayground.setPixelColor(8,255,0,0);
      CircuitPlayground.setPixelColor(7,255,0,0);
    }
    if(tempC>31 && tempC<=33){
      greenLEDs();
      CircuitPlayground.setPixelColor(9,255,0,0);
      CircuitPlayground.setPixelColor(8,255,0,0);
      CircuitPlayground.setPixelColor(7,255,0,0);
      CircuitPlayground.setPixelColor(6,255,0,0);
    }
    if(tempC>33 && tempC<=35){
      greenLEDs();
      CircuitPlayground.setPixelColor(9,255,0,0);
      CircuitPlayground.setPixelColor(8,255,0,0);
      CircuitPlayground.setPixelColor(7,255,0,0);
      CircuitPlayground.setPixelColor(6,255,0,0);
      CircuitPlayground.setPixelColor(5,255,0,0);
    }
    if(tempC>35 && tempC<=37){
      redLEDs();
      CircuitPlayground.setPixelColor(0,0,255,0);
      CircuitPlayground.setPixelColor(1,0,255,0);
      CircuitPlayground.setPixelColor(2,0,255,0);
      CircuitPlayground.setPixelColor(3,0,255,0);
    }
    if(tempC>37 && tempC<=39){
      redLEDs();
      CircuitPlayground.setPixelColor(0,0,255,0);
      CircuitPlayground.setPixelColor(1,0,255,0);
      CircuitPlayground.setPixelColor(2,0,255,0);
    }
    if(tempC>39 && tempC<=42){
      redLEDs();
      CircuitPlayground.setPixelColor(0,0,255,0);
      CircuitPlayground.setPixelColor(1,0,255,0);
    }
    if(tempC>42 && tempC<=45){
      redLEDs();
      CircuitPlayground.setPixelColor(0,0,255,0);
    }
}


void displaySoil(uint16_t soilCap){
    //Test to make sure I'm in the correct function
    /*
    for (i=0; i<11; i++) {
      CircuitPlayground.setPixelColor(i,25,25,25);
    }
    */
    CircuitPlayground.clearPixels();
    int switchCase = soilCap;
    
    //testing of switch cases
    //soilCap = 

    if(soilCap < MinWet){
      //too dry
      redLEDs();
    }
    if(soilCap >= MinWet && soilCap < MinOptimal){
      switchCase = map(switchCase,MinWet,MinOptimal,0,8);
      Serial.println("Soil Moisture Switch Case between MinWet and MinOptimal");
      Serial.println(switchCase);
    }
    if(soilCap >= MinOptimal && soilCap < MaxOptimal){
      switchCase = map(switchCase,MinOptimal,MaxOptimal,9,17);
      Serial.println("Soil Moisture Switch Case between MinOptimal and MaxOptimal");
      Serial.println(switchCase);
    }
    if(soilCap >= MaxOptimal && soilCap < MaxWet){
      switchCase = map(switchCase,MinOptimal,MaxOptimal,18,26);
      Serial.println("Soil Moisture Switch Case MaxOptimal and MaxWet");
      Serial.println(switchCase);
    }
    if(soilCap >= MaxWet){
      //too wet
      blueLEDs();
    } 
    
    switch(switchCase) {
      //0 to 8 too dry, red, add green 9 to 0
      case 0:
        redLEDs();
        CircuitPlayground.setPixelColor(9,0,255,0);
        break;
      case 1:
        redLEDs();
        CircuitPlayground.setPixelColor(9,0,255,0);
        CircuitPlayground.setPixelColor(8,0,255,0);
        break;
      case 2:
        redLEDs();
        CircuitPlayground.setPixelColor(9,0,255,0);
        CircuitPlayground.setPixelColor(8,0,255,0);
        CircuitPlayground.setPixelColor(7,0,255,0);
        break;
      case 3:
        redLEDs();
        CircuitPlayground.setPixelColor(9,0,255,0);
        CircuitPlayground.setPixelColor(8,0,255,0);
        CircuitPlayground.setPixelColor(7,0,255,0);
        CircuitPlayground.setPixelColor(6,0,255,0);
        break;
      case 4:
        redLEDs();
        CircuitPlayground.setPixelColor(9,0,255,0);
        CircuitPlayground.setPixelColor(8,0,255,0);
        CircuitPlayground.setPixelColor(7,0,255,0);
        CircuitPlayground.setPixelColor(6,0,255,0);
        CircuitPlayground.setPixelColor(5,0,255,0);
        break;
      case 5:
        greenLEDs();
        CircuitPlayground.setPixelColor(0,255,0,0);
        CircuitPlayground.setPixelColor(1,255,0,0);
        CircuitPlayground.setPixelColor(2,255,0,0);
        CircuitPlayground.setPixelColor(3,255,0,0);
        break;
      case 6:
        greenLEDs();
        CircuitPlayground.setPixelColor(0,255,0,0);
        CircuitPlayground.setPixelColor(1,255,0,0);
        CircuitPlayground.setPixelColor(2,255,0,0);
        break;
      case 7:
        greenLEDs();
        CircuitPlayground.setPixelColor(0,255,0,0);
        CircuitPlayground.setPixelColor(1,255,0,0);
        break;
      case 8:
        greenLEDs();
        CircuitPlayground.setPixelColor(0,255,0,0);
        break;
      //9 to 17 Optimal Range See notes
      case 9:
        greenLEDs();
        CircuitPlayground.setPixelColor(9,128,128,0);
        break;
      case 10:
        greenLEDs();
        CircuitPlayground.setPixelColor(8,128,128,0);
        break;
      case 11:
        greenLEDs();
        CircuitPlayground.setPixelColor(7,128,128,0);
        break;
      case 12:
        greenLEDs();
        CircuitPlayground.setPixelColor(6,128,128,0);
        break;
      case 13:
        greenLEDs();
        CircuitPlayground.setPixelColor(5,128,128,0);
        CircuitPlayground.setPixelColor(4,0,128,128);
        break;
      case 14:
        greenLEDs();
        CircuitPlayground.setPixelColor(3,0,128,128);
        break;
      case 15:
        greenLEDs();
        CircuitPlayground.setPixelColor(2,0,128,128);
        break;
      case 16:
        greenLEDs();
        CircuitPlayground.setPixelColor(1,0,128,128);
        break;
      case 17:
        greenLEDs();
        CircuitPlayground.setPixelColor(0,0,128,128);
        break;
      //18 to 26 too wet, green add blue, 9 to 0
      case 18:
        greenLEDs();
        CircuitPlayground.setPixelColor(9,0,0,255);
        break;
      case 19:
        greenLEDs();
        CircuitPlayground.setPixelColor(9,0,0,255);
        CircuitPlayground.setPixelColor(8,0,0,255);
        break;
      case 20:
        greenLEDs();
        CircuitPlayground.setPixelColor(9,0,0,255);
        CircuitPlayground.setPixelColor(8,0,0,255);
        CircuitPlayground.setPixelColor(7,0,0,255);
        break;
      case 21:
        greenLEDs();
        CircuitPlayground.setPixelColor(9,0,0,255);
        CircuitPlayground.setPixelColor(8,0,0,255);
        CircuitPlayground.setPixelColor(7,0,0,255);
        CircuitPlayground.setPixelColor(6,0,0,255);
        break;
      case 22:
        greenLEDs();
        CircuitPlayground.setPixelColor(9,0,0,255);
        CircuitPlayground.setPixelColor(8,0,0,255);
        CircuitPlayground.setPixelColor(7,0,0,255);
        CircuitPlayground.setPixelColor(6,0,0,255);
        CircuitPlayground.setPixelColor(5,0,0,255);
        break;
      case 23:
        blueLEDs();
        CircuitPlayground.setPixelColor(0,0,255,0);
        CircuitPlayground.setPixelColor(1,0,255,0);
        CircuitPlayground.setPixelColor(2,0,255,0);
        CircuitPlayground.setPixelColor(3,0,255,0);
        break;
      case 24:
        blueLEDs();
        CircuitPlayground.setPixelColor(0,0,255,0);
        CircuitPlayground.setPixelColor(1,0,255,0);
        CircuitPlayground.setPixelColor(2,0,255,0);
        break;
      case 25:
        blueLEDs();
        CircuitPlayground.setPixelColor(0,0,255,0);
        CircuitPlayground.setPixelColor(1,0,255,0);
        break;
      case 26:
        blueLEDs();
        CircuitPlayground.setPixelColor(0,0,255,0);
        break;                                                              
      default:
        //doNothing
        break;
       
    }
      
    
}
