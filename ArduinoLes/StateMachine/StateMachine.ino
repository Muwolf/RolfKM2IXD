#include <Servo.h>

#define STEP_FORWARD 1
#define STEP_BACK -1

volatile byte state = LOW; 
int ledState = LOW;
long ledChangeTime = 0L;

Servo myServo;
int servoState = STEP_FORWARD;
int servoPos = 0;
long servoStepTime = 0L;

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT); // LDR

  pinMode(11, OUTPUT); // LED
  pinMode(13, OUTPUT); //ISRLED
  pinMode(2, INPUT_PULLUP); //Button
  attachInterrupt(digitalPinToInterrupt(2), buttonISR, CHANGE); 

  myServo.attach(9);
  myServo.write(servoPos);
}

void loop() {
  digitalWrite(13, state); 
  int value = analogRead(A0);
  Serial.print("value=");
  Serial.print(value);
  Serial.print("       ISR Button: ");
  Serial.println(digitalRead(2)); 

  long currentTimeMS = millis();

  if (currentTimeMS - ledChangeTime > 500) { // time to change the led?
    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    ledChangeTime = currentTimeMS;
    digitalWrite(11, ledState);
  }

  if (currentTimeMS - servoStepTime > 200) { // time to move the servo?
    myServo.write(servoPos);
    servoStepTime = currentTimeMS;

    if (servoState == STEP_FORWARD) {
      servoPos += 10;    
    } else {
      servoPos -= 10;
    }

    if (servoPos > 180) {
      servoPos = 180;
      servoState = STEP_BACK;
    } else if (servoPos < 0) {
      servoPos = 0;
      servoState = STEP_FORWARD;
    }
  }
}

void buttonISR() {
  state = !state;
}


