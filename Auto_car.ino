#include <SoftwareSerial.h>
#include <Servo.h> 
#include <NewPing.h>
#define TRIGGER_PIN  A3
#define ECHO_PIN     A4
#define MAX_DISTANCE 500
SoftwareSerial hc06(2,3);

//L298N motor control pins
int left_r = 7;
int left_f = 8;
int right_r = 9;
int right_f = 10;
//L298N speed pins
int left_s = 5;
int right_s = 6;
// speed leds
int green = 13;
int  speed1 = 170; 
// Create a servo object 
int servoPin = A5;
Servo servo1; 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int distance; 
int dis_l;
int dis_r;
void setup() 
{
  //Initialize Serial Monitor
  Serial.begin(9600);
  //Initialize Bluetooth Serial Port
  hc06.begin(9600); 
  pinMode(left_r, OUTPUT);
  pinMode(left_f, OUTPUT);
  pinMode(right_r, OUTPUT);
  pinMode(right_f, OUTPUT);
  pinMode(left_s, OUTPUT);
  pinMode(right_s, OUTPUT);
  //led
  pinMode(green, OUTPUT);
  servo1.attach(servoPin);
int dis_l =0;
int dis_r =0;

}
void loop(){
 
look();
 
if (distance<30 && distance>0 ){
  stop();
  delay(100);
  backward();
  delay(400);
  stop();
  lookleft();
  delay(500);
  lookright();
  delay(500);
    if (dis_l >= dis_r){
      left();
      delay(500);
      stop();
      delay(500);
    }
    else{
      right();
      delay(500);
      stop();
      delay(500);
     }
}
  else{
    forward();
  }
//set speed
analogWrite(left_s, speed1);
analogWrite(right_s, speed1);
}


int look(){
  servo1.write(90);
  delay(50);                       // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping();  // Send ping, get ping time in microseconds (uS).
  distance = sonar.convert_cm(uS);
  return distance;
  }
int lookleft(){
  servo1.write(140);
  delay(300);
  unsigned int uS = sonar.ping();
  dis_l = sonar.convert_cm(uS);
  return dis_l;
  delay(100);
  servo1.write(90);
  delay(100);
  }
int lookright(){
  servo1.write(40);
  delay(300);
  unsigned int uS = sonar.ping();
  dis_r = sonar.convert_cm(uS);
  return dis_r;
  delay(100);
  servo1.write(90);
  delay(100);
  }

int forward(){ 
  digitalWrite(right_f, HIGH);
  digitalWrite(left_f, HIGH);
  digitalWrite(right_r, LOW);
  digitalWrite(left_r, LOW);
  }
int backward(){
  digitalWrite(right_f, LOW);
  digitalWrite(left_f, LOW);
  digitalWrite(right_r, HIGH);
  digitalWrite(left_r, HIGH);
  }
int right(){
  digitalWrite(right_f, LOW);
  digitalWrite(left_f, HIGH);
  digitalWrite(right_r, LOW);
  digitalWrite(left_r, LOW);
  }
int left(){
  digitalWrite(right_f, HIGH);
  digitalWrite(left_f, LOW);
  digitalWrite(right_r, LOW);
  digitalWrite(left_r, LOW);
  }
int stop(){
  digitalWrite(right_f, LOW);
  digitalWrite(left_r, LOW);
  digitalWrite(right_r, LOW);
  digitalWrite(left_f, LOW);
  }
