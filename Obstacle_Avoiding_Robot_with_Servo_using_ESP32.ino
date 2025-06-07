#include <ESP32Servo.h>

#define distanceMin 20

Servo myservo;              // define object for servo motor
int i;
int j;

#define trigPin 4
#define echoPin 2
#define leftSensorPin 34
#define rightSensorPin 35
#define ENA 25
#define IN1 23
#define IN2 33
#define ENB 26
#define IN3 21
#define IN4 22

int duration, distance, dist_fromfunction, dist_left, dist_right;
unsigned long previousMillis = 0;

void setup()
{
  Serial.begin(9600);
  myservo.attach(18);

  myservo.write(90);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(leftSensorPin, INPUT);
  pinMode(rightSensorPin, INPUT);
}

void loop()
{
  myservo.write(90);
  waitMillies(1000);
  dist_fromfunction = calculateDistance();
  if ( dist_fromfunction < distanceMin) {
    stopMoving();
    if (dist_fromfunction <= distanceMin) {
   
      myservo.write(180);
      waitMillies(1000);
      dist_left = calculateDistance();

      myservo.write(0);
      waitMillies(1000);
      dist_right = calculateDistance();

      if (dist_right > distanceMin || dist_left > distanceMin) {
        if (dist_right < dist_left) {
          Serial.println("Spinning left");
          spinL();
          waitMillies(500);
        } else if (dist_right == dist_left) {
          Serial.println("Spinning right because both distances are the same");
          spinR();
          waitMillies(500);
        } else if (dist_right > dist_left) {
          Serial.println("Spinning right");
          spinR();
          waitMillies(500);
        }
      }
      else {
        moveBackward();
        waitMillies(500);
      }
    }
  }

  else {
    moveForward();
//    waitMillies(1000);
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  Serial.println(distance);
  return distance;
}

void waitMillies(unsigned long duration) {
  unsigned long startMillis = millis();
  while (millis() - startMillis < duration) {
  }
}

void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void spinR() {
  Serial.println("Spin Right rotating...");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void spinL() {
  Serial.println("Spin Left rotating...");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

void stopMoving() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
}

