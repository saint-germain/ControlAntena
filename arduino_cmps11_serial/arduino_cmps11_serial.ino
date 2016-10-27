/*****************************************
*   CMPS11 Serial example for Arduino    *
*        By James Henderson, 2014        * 
*****************************************/
// 1 - vcc ; 2 - tx ; 3 - rx ; 4 - mode ; 5 - noconnect ; 6 - gnd

#include <SoftwareSerial.h>

#define CMPS_GET_ANGLE8 0x12
#define CMPS_GET_ANGLE16 0x13
#define CMPS_GET_PITCH 0x14
#define CMPS_GET_ROLL 0x15

SoftwareSerial cmps11 = SoftwareSerial(2,3);

unsigned char high_byte, low_byte, angle8;
char pitch, roll;
unsigned int angle16;
int ledPin = 5;   // select the pin for relays 1 and 4 (26 pb)
int ledPin2 = 6;   // select the pin for relays 2 and 3 (25 pb)
float val = 0;       // variable to store the value coming from the sensor
int valcont = 0;     // state of the motor, 0, 3, 5
int valold = 0;      // dummy for delay after state change
float vref = 90;    // reference value (angle)
float eps = 2;     // tolerance
float azold = 0.;



void setup()
{
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  pinMode(ledPin2, OUTPUT);  // declare the ledPin as an OUTPUT
// protection from short-circuiting the motor
  digitalWrite(ledPin, HIGH);  // turn the ledPin on
  digitalWrite(ledPin2, HIGH);  // turn the ledPin on
  
  Serial.begin(9600);              // Start serial ports
  cmps11.begin(9600);
}

void loop()
{
  cmps11.write(CMPS_GET_ANGLE16);  // Request and read 16 bit angle
  while(cmps11.available() < 2);
  high_byte = cmps11.read();
  low_byte = cmps11.read();
  angle16 = high_byte;                // Calculate 16 bit angle
  angle16 <<= 8;
  angle16 += low_byte;
  
  cmps11.write(CMPS_GET_ANGLE8);  // Request and read 8 bit angle
  while(cmps11.available() < 1);
  angle8 = cmps11.read();
  
  cmps11.write(CMPS_GET_PITCH);   // Request and read pitch value
  while(cmps11.available() < 1);
  pitch = cmps11.read();
  
  cmps11.write(CMPS_GET_ROLL);    // Request and read roll value
  while(cmps11.available() < 1);
  roll = cmps11.read();
  
  Serial.print("roll: ");            // Display roll data
  Serial.print(roll, DEC);
  
  Serial.print("    pitch: ");          // Display pitch data
  Serial.print(pitch, DEC);
  
  Serial.print("    angle full: ");       // Display 16 bit angle with decimal place
  Serial.print(angle16 / 10, DEC);
  Serial.print(".");
  Serial.print(angle16 % 10, DEC);
  Serial.print("  ");
  Serial.print((float)angle16/10.);
  
  Serial.print("    angle 8: ");        // Display 8bit angle
  Serial.println(angle8, DEC);
  
  val=(float)angle16/10.;
  if (val < vref - eps){
     valcont = 5;
  }
  if (val > vref + eps){
     valcont = 3;
  }
  if (val >= vref - eps && val <= vref + eps){
    valcont = 0;
  }  
  
  if( valold != valcont && valcont != 0){
    delay(1500);
    digitalWrite(ledPin, HIGH);  // turn the ledPin on
    digitalWrite(ledPin2, HIGH);  // turn the ledPin on
  }
  
  valold = valcont;
  if(valcont == 0){
    digitalWrite(ledPin, HIGH);  // turn the ledPin on
    digitalWrite(ledPin2, HIGH);  // turn the ledPin on
  }
  if(valcont == 3){
    digitalWrite(ledPin, HIGH);  // turn the ledPin on
    digitalWrite(ledPin2, LOW);  // turn the ledPin on
  }
  if(valcont == 5){
    digitalWrite(ledPin, LOW);  // turn the ledPin on
    digitalWrite(ledPin2, HIGH);  // turn the ledPin on
  }       
  
  
  
  delay(10);                           // Short delay before next loop
}




