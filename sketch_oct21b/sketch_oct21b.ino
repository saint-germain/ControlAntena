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

int potPin = 3;    // select the input pin for the potentiometer
int ledPin = 5;   // select the pin for the LED
int ledPin2 = 6;   // select the pin for the LED

int val = 0;       // variable to store the value coming from the sensor
int valcont = 0;
int valold = 0;

void setup() {
  pinMode(ledPin, OUTPUT);  // declare the ledPin as an OUTPUT
  pinMode(ledPin2, OUTPUT);  // declare the ledPin as an OUTPUT

  Serial.begin(9600);
}

void loop() {
  val = analogRead(potPin);    // read the value from the sensor
  valcont = (int)((float)val*5./1023.);
  if( valold != valcont && valcont != 0 ){
     delay(1500);
  }
  valold = valcont;
  Serial.print((float)val*5./1023.);
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
