// Software Serial Library to communicate between the Primary and Secondary Controller.
#include<SoftwareSerial.h>

// To operate Sabertooth Drivers Servo library is used.
#include <Servo.h>

// 10 - RX, 11 - TX
SoftwareSerial s(10, 11); 

// Initialize the front left, front right, back left and back right motors.
Servo fr, fl, bl, br;

// forward pwm
int pf = 75;

// reverse pwm
int pb = 105;

// front ultrasonic sensor pins
const int frontEchoPin = A0;
const int frontTriggerPin = A1;

// left ultrasonic sensor pins
const int leftEchoPin = A2;
const int leftTriggerPin = A3;

// right ultrasonic sensor pins
const int rightEchoPin = A4;
const int rightTriggerPin = A5;

// Distance to object which front ultrasonic sensor considers as an obstacle in cms.
volatile float maxFrontDistance = 25.00;

// Variables to record the distance and duration for the ultrasonic sensor array.
volatile float  frontDuration, frontDistanceCm, leftDuration, leftDistanceCm, rightDuration, rightDistanceCm;

// Distance to object which right ultrasonic sensor considers as an obstacle in cms.
volatile float maxRightDistance = 15.00;

// Distance to object which left ultrasonic sensor considers as an obstacle in cms.
volatile float maxLeftDistance = 15.00;

void setup() 
{
  // Serial baud rate to recieve data from NodeMCU
  s.begin(115200);
  
  // Bauu rate to match the data input serially
  Serial.begin(115200);
  
  // setup the pins as output or input
  pinMode(frontEchoPin, INPUT);
  pinMode(frontTriggerPin, OUTPUT);
  pinMode(leftEchoPin, INPUT);
  pinMode(rightEchoPin, INPUT);
  pinMode(rightTriggerPin, OUTPUT);
  pinMode(leftTriggerPin, OUTPUT);
  
  // Attach the digital pins to the respctive motors
  fr.attach(3); fl.attach(2); bl.attach(4); br.attach(5);
  
  // PWM value to set the motor speed as 0
  fr.write(90);
  fl.write(90);
  bl.write(87);
  br.write(86.5);
}

void loop() 
{
  // Write 's' as a notifier to Secondary Controller to send the data.
  s.write('s');
  
  if (s.available() >= 0)
  {
    char drive = s.read();
    // Check the data and call the respective functions.
    if (drive == 1)
    {
      Serial.println("Forward");
      moveForward();
    }
    else if (drive == 2)
    {
      Serial.println("Backward");
      moveBackward ();
    }
    else if (drive == 3)
    {
      Serial.println("Left");
      moveLeft();
    }
    else if (drive == 4)
    {
      Serial.println("Right");
      moveRight();
    }
    else if (drive == 5)
    {
      Serial.println("Forward-right");
      forwardright();
    }
    else if (drive == 6)
    {

      Serial.println("Backward-right");
      backwardright ();
    }

    else if (drive == 7)
    {
      Serial.println("Backward-left");
      backwardleft ();
    }
    else if (drive == 8)
    {
      Serial.println("Forward-left");
      forwardleft ();
    }
    else if (drive == 9)
    {
      Serial.println("Rotate-left");

      turnLeft () ;

    }
    else if (drive == 10)
    {
      Serial.println("Rotate-right");

      turnRight ();
    }
    else if (drive == 0)
    {
      Serial.println("Halt");
      stp();
    }
  }
  else 
  {
    stp();
  }
}

// Move Forward Function
void moveForward() 
{
  digitalWrite(frontTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(frontTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(frontTriggerPin, LOW);
  frontDuration = pulseIn(frontEchoPin, HIGH);
  frontDistanceCm = frontDuration * 10 / 292 / 2;
  Serial.println( frontDistanceCm);
  if ( frontDistanceCm < maxFrontDistance) 
  {
    Serial.println("st");
    fr.write(90);
    fl.write(90);
    bl.write(87);
    br.write(86.5);
  }
  else 
  {
    fr.write(pf);
    fl.write(pf);
    bl.write(pf);
    br.write(pf);
  }
  
// Move backward Function
}
void moveBackward () 
{
  fr.write(pb);
  fl.write(pb);
  bl.write(pb);
  br.write(pb);
}

// Move right Fucntion
void moveRight() {

  digitalWrite(rightTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rightTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(rightTriggerPin, LOW);
  rightDuration = pulseIn(rightEchoPin, HIGH);
  rightDistanceCm = rightDuration * 10 / 292 / 2;
  if (rightDistanceCm < maxRightDistance) {
    Serial.println("st");
    fr.write(90);
    fl.write(90);
    bl.write(87);
    br.write(86.5);
  }
  else {
    fr.write(pb);
    fl.write(pf);
    bl.write(pb);
    br.write(pf);;

  }
}

// Move left Function
void moveLeft() {
  digitalWrite(leftTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(leftTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(leftTriggerPin, LOW);
  leftDuration = pulseIn(leftEchoPin, HIGH);
  leftDistanceCm = leftDuration * 10 / 292 / 2;
  Serial.println(leftDistanceCm);
  if ( leftDistanceCm < maxLeftDistance) {
    Serial.println("st");
    fr.write(90);
    fl.write(90);
    bl.write(87);
    br.write(86.5);
  }
  else {
    fr.write(pf);
    fl.write(pb);
    bl.write(pf);
    br.write(pb);

  }
}

// Move Back Right Function
void backwardright () {
  digitalWrite(rightTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rightTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(rightTriggerPin, LOW);
  rightDuration = pulseIn(rightEchoPin, HIGH);
  rightDistanceCm = rightDuration * 10 / 292 / 2;
  if (rightDistanceCm < maxRightDistance) {
    Serial.println("st");
    fr.write(90);
    fl.write(90);
    bl.write(87);
    br.write(86.5);
  }
  else {
    fr.write(pb);
    fl.write(90);
    bl.write(pb);
    br.write(90);
  }
}

// Move Backward Left Function
void backwardleft () {
  digitalWrite(leftTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(leftTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(leftTriggerPin, LOW);
  leftDuration = pulseIn(leftEchoPin, HIGH);
  leftDistanceCm = leftDuration * 10 / 292 / 2;
  if ( leftDistanceCm < maxLeftDistance) {
    Serial.println("st");
    fr.write(90);
    fl.write(90);
    bl.write(87);
    br.write(86.5);
  }
  else {
    fr.write(90);
    fl.write(pb);
    bl.write(90);
    br.write(pb);
  }
}

// Move Forward Right Function
void forwardright () {
  digitalWrite(frontTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(frontTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(frontTriggerPin, LOW);
  frontDuration = pulseIn(frontEchoPin, HIGH);
  frontDistanceCm = frontDuration * 10 / 292 / 2;
  digitalWrite(rightTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rightTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(rightTriggerPin, LOW);
  rightDuration = pulseIn(rightEchoPin, HIGH);
  rightDistanceCm = rightDuration * 10 / 292 / 2;
  if ( frontDistanceCm < maxFrontDistance && rightDistanceCm < maxRightDistance ) {
    Serial.println("st");
    fr.write(90);
    fl.write(90);
    bl.write(87);
    br.write(86.5);
  }
  else {
    fr.write(90);
    fl.write(pf);
    bl.write(90);
    br.write(pf);
  }
}

// Move Forward Left Function
void forwardleft () {
  digitalWrite(frontTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(frontTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(frontTriggerPin, LOW);
  frontDuration = pulseIn(frontEchoPin, HIGH);
  frontDistanceCm = frontDuration * 10 / 292 / 2;
  digitalWrite(leftTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(leftTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(leftTriggerPin, LOW);
  leftDuration = pulseIn(leftEchoPin, HIGH);
  leftDistanceCm = leftDuration * 10 / 292 / 2;
  if ( frontDistanceCm < maxFrontDistance && leftDistanceCm < maxLeftDistance) {
    Serial.println("st");
    fr.write(90);
    fl.write(90);
    bl.write(87);
    br.write(86.5);
  }
  else {
    fr.write(pf);
    fl.write(90);
    bl.write(pf);
    br.write(90);
  }
}

// Move Right Function
void turnRight () {
  digitalWrite(rightTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(rightTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(rightTriggerPin, LOW);
  rightDuration = pulseIn(rightEchoPin, HIGH);
  rightDistanceCm = rightDuration * 10 / 292 / 2;
  if (  rightDistanceCm < maxRightDistance ) {
    Serial.println("st");
    fr.write(90);
    fl.write(90);
    bl.write(87);
    br.write(86.5);
  }
  else {
    fr.write(pb);
    fl.write(pf);
    bl.write(pf);
    br.write(pb);
  }
}

// Move Left Function
void turnLeft () {
  digitalWrite(leftTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(leftTriggerPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(leftTriggerPin, LOW);
  leftDuration = pulseIn(leftEchoPin, HIGH);
  leftDistanceCm = leftDuration * 10 / 292 / 2;
  if (  leftDistanceCm < maxLeftDistance) {
    Serial.println("st");
    fr.write(90);
    fl.write(90);
    bl.write(87);
    br.write(86.5);
  }
  else {
    fr.write(pf);
    fl.write(pb);
    bl.write(pb);
    br.write(pf);
  }
}

// Stop Function
void stp() {
  Serial.println("i");
  fr.write(90);
  fl.write(90);
  bl.write(87);
  br.write(86.5);
}
