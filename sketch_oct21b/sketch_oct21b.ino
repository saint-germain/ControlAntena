/* Analog Read to LED
 * ------------------ 
 *
 * turns on and off a light emitting diode(LED) connected to digital  
 * pin 13. The amount of time the LED will be on and off depends on
 * the value obtained by analogRead(). In the easiest case we connect
 * a potentiometer to analog pin 2.
 *
 * Created 1 December 2005
 * copyleft 2005 DojoDave <http://www.0j0.org>
 * http://arduino.berlios.de
 *
 */
// sudo chmod a+rw /dev/ttyACM0 
// in case there are problems with ubuntu
// also, delete preferences.txt if there are problems with baud rate
// vcc and ground from arduino

int potPin = 3;    // select the input pin for the sensor
int ledPin = 5;   // select the pin for relays 1 and 4 (26 pb)
int ledPin2 = 6;   // select the pin for relays 2 and 3 (25 pb)

float val = 0;       // variable to store the value coming from the sensor
int valcont = 0;     // state of the motor, 0, 3, 5
int valold = 0;      // dummy for delay after state change
float vref = 2.5;    // reference voltage
float eps = 0.1;     // tolerance

void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  pinMode(ledPin2, OUTPUT);  // declare the ledPin as an OUTPUT
// protection from short-circuiting the motor
  digitalWrite(ledPin, HIGH);  // turn the ledPin on
  digitalWrite(ledPin2, HIGH);  // turn the ledPin on
  Serial.begin(9600);
}

void loop() {
 
  val = (float)analogRead(potPin)*5./1024.;
//((int)(val*10))/10.;
  if (val < vref - eps){
    valcont = 5;
  }
  if (val > vref + eps){
    valcont = 3;
  }
  if (val >= vref - eps && val <= vref + eps){
    valcont = 0;
  }  
  
//(int)((float)val*5./1023.);
  if( valold != valcont && valcont != 0 ){
    delay(1500);
    digitalWrite(ledPin, HIGH);  // turn the ledPin on
    digitalWrite(ledPin2, HIGH);  // turn the ledPin on
  }
  valold = valcont;
  Serial.print(val);
  Serial.print("\t");
  Serial.print(analogRead(potPin));
  Serial.print("\t");
  Serial.print(valcont);
  Serial.print("\n");

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

}
