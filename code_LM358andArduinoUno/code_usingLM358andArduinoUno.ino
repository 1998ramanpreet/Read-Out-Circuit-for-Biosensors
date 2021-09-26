
/**********************************************************************
* Project: Read-Out circuit for biosensors
* Devices: Arduino Uno 
* Authors: Ramanpreet Kaur, Shikha Singhal and Trishna Aryal
* This is the program written to run the cTni detection device
***********************************************************************/
#include <LiquidCrystal.h>
#include <Wire.h>                                                 //This library allows you to communicate with I2C / TWI devices.

//**********************************************************************
//--- Declarations---
//**********************************************************************
const int rs = 13, en = 12, d4 = 11, d5 = 8, d6 = 9, d7 = 10;     // initialize the library with the numbers of the interface pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                        // REGISTER SELECT PIN,ENABLE PIN,D4 PIN,D5 PIN, D6 PIN, D7 PIN
int Rs =100;                                                      // feedback resistance 
int RawValue;
int ACSoffset = 500;                                              // Voltage across inverting and non-inverting pins of OP-Amp
double Ik;                                                        // current measuring 
float Voltage = 0;                                                //voltage measuring 
double Voltage2 = 0;
double DV;                                                        // Voltage difference 
double R;
double milliVolt;                                                 // voltage measuring
const int analogIn = 0;                                           //Connect current sensor with A0 of Arduino
//**********************************************************************
//--- Void Setup---
//**********************************************************************
void setup() {
Serial.begin(9600);                                               // to set speed(baud rate) for serial communication i.e. 9600 
lcd.begin(16, 2);
Wire.begin();
}
//**********************************************************************
//--- Void Loop---
//**********************************************************************
void loop()
{
lcd.setCursor(0, 0);                                              //set the cursor to column 0, line 1
lcd.print("Apply Sample");
delay(2000);
lcd.clear();
lcd.setCursor(0, 0);                                              // set the cursor to column 0, line 1 
lcd.print("Calculating"); 
delay(2000);
lcd.clear();
RawValue = analogRead(analogIn);                                  //reading the value from the analog pin
Voltage = (RawValue / 1023) *1085;                                // gets you mV
milliVolt = (Voltage-Voltage2);
DV= milliVolt-ACSoffset;
Ik= DV/Rs;
R=ACSoffset/Ik;
lcd.clear();                                                      //clears the display of LCD 
lcd.setCursor(0,0); 
lcd.print(Ik); 
lcd.setCursor(4,0); 
lcd.print("uA");
lcd.setCursor(0,1); 
lcd.print(R); 
lcd.setCursor(6,1); 
lcd.print("k0hm");
lcd.setCursor(10,0);
lcd.print(milliVolt);                                             // output voltage
delay(15000); 
lcd.clear();
lcd.setCursor(0,0);                                               // set the cursor to column 0, line 1 
lcd.print("Rem0ve Strip");
}
