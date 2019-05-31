/*
* Sumo Program 
* Jacob Pitzer
* RET 160 
* Created: 4/4/17
* Edited: 4/27/17
* Description: 
* Program that uses sensors an motors to move boe-bot
* through a sumo ring and force out another object 
* while following the rules of sumo wrestling
*/

#include <Servo.h> //include servo library 

Servo servoLeft; //declare left servo
Servo servoRight;  //declare right servo

const int pingPin = 7; //attach PING to digiral pin 7  

void setup() 
{
  Serial.begin(9600); //initialize communication between board and computer
  servoLeft.attach(13); //attach left servo to board
  servoRight.attach(12); //attach right servo to board
}

void loop() //main program loop 
{
  long duration, inches, cm; //declare PING sensor values

  duration = scan(duration); //scan for object 
  
  inches = microsecondsToInches(duration); //convert distance to inches
  cm = microsecondsToCentimeters(duration); //convert remaining distance to centimeters  

  if(inches < 10) //if object detected, move toward it
  {
    forward(); 
    delay(100); //move machine forward 
  }
  else //if object not found, search for it 
  {
    left();  
    delay(100); //when found, move forward 
  }
  
}//end main loop

long scan(long duration) //function to use PING to search
{
  pinMode(pingPin, OUTPUT); //set pin 7 to output
  digitalWrite(pingPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(pingPin, HIGH); 
  delayMicroseconds(5); 
  digitalWrite(pingPin, LOW); 
  pinMode(pingPin, INPUT); 
  duration = pulseIn(pingPin, HIGH);

  return duration; 
}

long microsecondsToInches(long microseconds) //function to convert distance to inches
{
  return microseconds / 74 / 2; 
}

long microsecondsToCentimeters(long microseconds) //function to convert distance to cm
{
  return microseconds / 29 / 2; 
}

void forward() //function to move forward
{
  servoLeft.writeMicroseconds(1700); 
  servoRight.writeMicroseconds(1300);   
}

void right() //function to move 90 degrees right
{
  servoLeft.writeMicroseconds(1700); 
  servoRight.writeMicroseconds(1700); 
}

void backward() //function to move backwards
{
  servoLeft.writeMicroseconds(1300); 
  servoRight.writeMicroseconds(1700); 
}

void left() //function to move left 90 degrees
{
  servoLeft.writeMicroseconds(1300); 
  servoRight.writeMicroseconds(1300);  
}

void cease() //function to stop motors
{
  servoLeft.detach(); 
  servoRight.detach();   
}





