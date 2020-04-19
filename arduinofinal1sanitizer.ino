
#include <VarSpeedServo.h>
VarSpeedServo myservo1;  // create servo object to control a servo 
const int servoPin1 = 9; // the digital pin used for the first servo
#define trigPin 13
#define echoPin 12
int dist1=0;
void setup() {
  myservo1.attach(servoPin1);  // attaches the servo on pin 9 to the servo object
  myservo1.write(0,200); // set the intial position of the servo, as fast as possible
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance >= 22 || distance <= 0){ // you can make adjustments here depending on reading of your ultrasonic sensor
    Serial.println("Out of range");
    Serial.println();
    dist1=1;
    myservo1.write(0,255,false);
    Serial.print("servo pos :");
    Serial.println(myservo1.read());
    Serial.println();
   }
  else {
    Serial.print(distance);
    Serial.println(" cm");
    if (distance <=20 && dist1==1) { // distance you want your servo to rotate
      if(myservo1.read()==0){
           dist1=0;
           myservo1.write(60,255,true); //angle you tell your servo to rotate
           delay(200); // delay to stabilize your servo      
           Serial.println(myservo1.read());
           myservo1.write(0,255,false); //zero position
           delay(50);
       }
     }
      delay(100);
  }
  //delay(100);
  
}
