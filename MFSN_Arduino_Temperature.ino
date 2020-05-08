/*
Using an Arduino Uno, a 16x2 LCD, a button, and a thermoresistor, display the air tempature in F on the LCD screen.

code modified from p03_LoveOMeter and Scroll LCD Library
*/

//LCD Setup
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Temp and button setup
const int tempPin = 0;  //confirm   this is an analog pin ()
const int buttonPin = 8; //confirm  this is a digital pin
int buttonState = 0;
float tempC = 0;
float tempF = 0;

void setup() {
  // put your setup code here, to run once:
  //button and sensor setup
  pinMode(tempPin, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);

  //LCD setup and show LCD is active
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16,2);
  lcd.setCursor(0,1);
  // Print a message to the LCD.
  lcd.print("hello mars!");
  delay(3000);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:

  /*
  if button pressed
    get tempature sensor value
    convert to C 0.0 and F 0
    display on LCD then wait for 3 seconds
  else, do nothing and save power
  */
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    int sensorVal = analogRead(tempPin);
    float voltage = (sensorVal / 1024.0) * 5.0;
    tempC = (voltage - .5) * 100;
    tempF = ((tempC * 9)/5) + 32;
    /*Confirm data is correct if connected to serial output*/
    Serial.print("Temp in F " );
    Serial.println(tempF);
    //display scrolling to LCD
    lcd.setCursor(0,1);
    lcd.print(tempF);
    lcd.print(" F     ");
    delay(3000);
  } 
  else {
    //do nothing
  }
}
