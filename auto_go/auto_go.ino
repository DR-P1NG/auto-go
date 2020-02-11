//www.elegoo.com
#include <Servo.h>
Servo ulserv;
Servo ulserv2;
Servo ulserv3;
Servo ulservU;

//    The directio` ` ` qwedfghgfewrfvciujyt IN1   IN2   IN3   IN4   Description
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car is runing forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car is runing back
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car is turning left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car is turning right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Car is stoped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car is stoped
//  LOW   LOW   N/A   N/A   N/A   N/A   Car is stoped

//define L298n module IO Pin
#define ENB 5
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11
#define ENA 6


//define Ultrasonic Sensor
const int trigPin = A5;
const int echoPin = A4;
const int trigPin2 = A2;
const int echoPin2 = A3;
const int trigPin3 = A0;
const int echoPin3 = A1;
int distance;
int distance2;
int distance3;

float duration;

void forward(){
  analogWrite(ENA, 255);    //enable L298n A channel
  analogWrite(ENB, 255);    //enable L298n B channel
  digitalWrite(IN1, HIGH);    //set IN1 high level
  digitalWrite(IN2, LOW);     //set IN2 low level
  digitalWrite(IN3, LOW);     //set IN3 low level
  digitalWrite(IN4, HIGH);    //set IN4 high level
  ulserv.write(60);
  ulserv2.write(80);
  ulserv3.write(100);
  Serial.println("Forward");  //send message to serial monitor
}

void back(){
  analogWrite(ENA, 255);     //enable L298n A channel
  analogWrite(ENA, 255);       //enable L298n B channel
  digitalWrite(IN1, LOW);     //set IN1 low level
  digitalWrite(IN2, HIGH);    //set IN2 high level
  digitalWrite(IN3, HIGH);    //set IN3 high level
  digitalWrite(IN4, LOW);     //set IN4 low level
  ulserv.write(60);
  ulserv2.write(80);
  ulserv3.write(100);
  Serial.println("Backward"); //send message to serial monitor
}

void left(){
  analogWrite(ENA, 255);     //enable L298n A channel
  analogWrite(ENA, 255);      //enable L298n B channel
  digitalWrite(IN1, LOW);    //set IN1 low level
  digitalWrite(IN2, HIGH);   //set IN2 high level
  digitalWrite(IN3, LOW);    //set IN3 low level
  digitalWrite(IN4, HIGH);   //set IN4 high level
  //SPAS Code
  //ulserv.write(120);
  //Normal Code
  ulserv.write(60);
  ulserv2.write(80);
  ulserv3.write(100);
  Serial.println("Left");    //send message to serial monitor
}

void right(){
  analogWrite(ENA, 255);    //enable L298n A channel
  analogWrite(ENA, 255);    //enable L298n B channel
  digitalWrite(IN1, HIGH);   //set IN1 high level
  digitalWrite(IN2, LOW);    //set IN2 low level
  digitalWrite(IN3, HIGH);   //set IN3 high level
  digitalWrite(IN4, LOW);    //set IN4 low level
  //SPAS Code
  //ulserv.write(0);
  ulserv.write(60);
  ulserv2.write(80);
  ulserv3.write(100);
  Serial.println("Right");   //send message to serial monitor
}

void stop() {
  analogWrite(ENB, 255);     //enable L298n A channel
  analogWrite(ENB, 255);     //enable L298n B channel
  digitalWrite(IN1, LOW);    //set IN1 low level
  digitalWrite(IN2, LOW);    //set IN2 low level
  digitalWrite(IN3, LOW);    //set IN3 low level
  digitalWrite(IN4, LOW);    //set IN4 low level
  ulserv.write(60);
  ulserv2.write(80);
  ulserv3.write(100);
  Serial.println("Stop");    //send message to serial monitor
}

int acquireDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH) / 58;
  Serial.print("duration1:" + String(duration));
  return duration;
}

int acquireDistance2() {
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  duration = pulseIn(echoPin2, HIGH) / 58;
  Serial.print("duration2:" + String(duration));
  return duration;
}

int acquireDistance3() {
  digitalWrite(trigPin3, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin3, LOW);
  duration = pulseIn(echoPin3, HIGH) / 58;
  Serial.print("duration3:" + String(duration));
  return duration;
}

void leftServo() {
  ulserv3.write(145);
  delay(800);
  distance3 = acquireDistance3();
  delay(100);
  ulserv3.write(100);
  return;
}

void rightServo() {
  ulserv2.write(35);
  delay(800);
  distance2 = acquireDistance2();
  delay(100);
  ulserv2.write(90);
  return;
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(IN1, OUTPUT);   //before useing io pin, pin mode must be set first 
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  ulserv.attach(3);   
  ulserv2.attach(13); 
  ulserv3.attach(12);      
  Serial.begin(9600);     //open serial and set the baudrate             
}


void loop() {  
  distance = acquireDistance();
  distance2 = acquireDistance2();
  distance3 = acquireDistance3();
  delay(1);
  forward();
  delay(10);
  
  if (distance < 45) {
    stop(); 
    leftServo();
    delay(500);
    rightServo();
    delay(500);
    if (distance2 > distance3) {
      while (distance < 45) {
        distance = acquireDistance();
        delay(1);
        Serial.print(distance);
        right();
        delay(5);
      }
      forward();
      delay(200);
    } else if (distance3 > distance2) {
      while (distance < 45) {
        distance = acquireDistance();
        delay(1);
        Serial.print("Hi");
        Serial.print(distance);
        left();
        delay(5);
      }
      forward();
      delay(200);
    } else {
      forward();
      delay(100);
    }
  }

  if (distance2 < 45) {
     while (distance2 < 45) {
        distance2 = acquireDistance2();
        delay(1);
        Serial.print("Hi: ");
        Serial.print(distance);
        left();
        delay(5);
      }
  }

  if (distance3 < 45) {
     while (distance3 < 45) {
        distance3 = acquireDistance3();
        delay(1);
        Serial.print("Hi: ");
        Serial.print(distance);
        right();
        delay(5);
      }
  }
}
