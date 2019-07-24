#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3);   
int STBY = 10; //standby

//Motor A
int PWMA = 4; //Speed control+ 
int AIN1 = 9; //Direction
int AIN2 = 8; //Direction

//Motor B
int PWMB = 5; //Speed control
int BIN1 = 11; //Direction
int BIN2 = 12; //Direction

void setup() {  
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(STBY, OUTPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(PWMB, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

void loop() {
  while (BTSerial.available()){
    int data = BTSerial.read();
    BTSerial.print("statr");
    switch(data){
      case 0:
        Serial.println("front");
        stop();
        move(1, 255, 1); //motor 1, full speed, front
        move(2, 255, 0); 
        break;
      case 1:
        Serial.println("back");
        stop();
        move(1, 255, 0); //motor 1, full speed, back
        move(2, 255, 1); 
        break;
      case 2:
        Serial.println("right");
        stop();
        move(1, 200, 1); //motor 1, full speed, right
        move(2, 130, 1); 
        break;
      case 3:
        Serial.println("left");
        stop();
        move(1, 130, 0); //motor 1, full speed, left
        move(2, 200, 0); 
        break;
      case 4:
        Serial.println("stop");
        stop();
        break;
    }
  }
    
  if (Serial.available())
    BTSerial.write(Serial.read());
}


//motor A connected between A01 and A02
//motor B connected between B01 and B02

void move(int motor, int speed, int direction){
//Move specific motor at speed and direction
//motor: 0 for B 1 for A
//speed: 0 is off, and 255 is full speed
//direction: 0 clockwise, 1 counter-clockwise

  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

  if(motor == 1){
    digitalWrite(AIN1, inPin1);
    digitalWrite(AIN2, inPin2);
    analogWrite(PWMA, speed);
  }else{
    digitalWrite(BIN1, inPin1);
    digitalWrite(BIN2, inPin2);
    analogWrite(PWMB, speed);
  }
}

void stop(){
//enable standby  
  digitalWrite(STBY, LOW); 
  delay(100);
}
