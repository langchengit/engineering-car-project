/*
some function names might sound redundant, since I did the line tracing and obtacle detecting in two separate files
and combined them together. 
*/

/*
motor pins
*/
int motor2pin2 = 4;
int motor2pin1 = 5;

int motor1pin2 = 2;
int motor1pin1 = 3;

int irsensor1pin = 12; //right
int irsensor2pin = 13;//left

int pin1speed = 10; //right
int pin2speed = 9; //left

//booleans to keep track of turning states
bool rightturning = false;
bool leftturning  = false;

//ultrasonic sensor
const int trigPin = 7;
const int echoPin = 6;

// duration for the sound to echo back, and distance calculated based on duration
float duration, distance;

int delaytime = 115;
//potential different speed for two motors because the motor has different efficiency
int speed = 65; // speed for motor right
int speed2 = 65; // speed for motor left

// booleans to update states (might not be used)
bool isObstacle = false;
bool otherWay = false;

void setup() {

  
  /*
  motordriver
  */
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  //(Optional)
  pinMode(pin1speed, OUTPUT); 
  pinMode(pin2speed, OUTPUT);
  //(Optional)
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, LOW);
  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, LOW);

  
  pinMode(irsensor1pin, INPUT);
  pinMode(irsensor2pin, INPUT);

  //ultrasonic sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.begin(9600);
  
  delay(5);
}

void moveForward() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(pin1speed, speed);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  analogWrite(pin2speed, speed2);
}

// ----- ultrasonic sensor functions ------
void left() {
  //left
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(pin1speed, 90);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  analogWrite(pin2speed, 0);
}

void right() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(pin1speed, 0);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  analogWrite(pin2speed, 90);

}

void straight() {
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(pin1speed, 90);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  analogWrite(pin2speed, 90);
}

void back() {
  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);
  analogWrite(pin1speed, 90);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  analogWrite(pin2speed, 90);
}

void straightLeft() {
  
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(pin1speed, 85);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  analogWrite(pin2speed, 50);
}

void straightRight() {
  
  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, LOW);
  analogWrite(pin1speed, 50);

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  analogWrite(pin2speed, 100);
}

// -----------------------

void loop() {
  
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); // send out ultrasonic sound waves
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); // wait for the returning echo

  duration = pulseIn(echoPin, HIGH); // measure the pulse (time takes for the sound wave from out to back)
  distance = (duration*.0343)/2; // convert to distance
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(25);   

  //distance is 20, start turning
  if (distance <= 20) {
    delay(750);

    back();
    delay(400);

    right();
    delay(425);

    straight();
    delay(575);

    left();
    delay(600);

    straightLeft();

    otherWay = true;

    //back off; turn right 90 degrees and move forward a little bit; then do an arch path to go back on track
  }

  // if (otherWay && distance <= 20) {
  //   delay(750);
  //   straight();
  //   // back();
  //   // delay(400);

  //   // left();
  //   // delay(500);

  //   // straight();
  //   // delay(450);

  //   // right();
  //   // delay(675);

  //   // straight();
  //   // delay(300);

  //   // straightRight();

  //   otherWay = false;
  // }

  /* 
  read values from the sensors
  */
  
  int sensor1Value = digitalRead(irsensor1pin);
  int sensor2Value = digitalRead(irsensor2pin);


  if (sensor1Value == LOW && sensor2Value == HIGH) { // right turn

    leftturning = false;

    //if changes turning state, move forward a little bit first before turning
    if(rightturning == false){
      moveForward();
      delay(delaytime);
    }
    rightturning = true;
    
    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    analogWrite(pin1speed, speed);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    analogWrite(pin2speed, 0);

    delay(delaytime);
  }

  if (sensor1Value == HIGH && sensor2Value == LOW) { // left turn

    rightturning = false;

    //if changes turning state, move forward a little bit first before turning
    if (leftturning == false) {
      moveForward();
      delay(delaytime);
    }

    leftturning = true;

    digitalWrite(motor1pin1, HIGH);
    digitalWrite(motor1pin2, LOW);
    analogWrite(pin1speed, 0);

    digitalWrite(motor2pin1, HIGH);
    digitalWrite(motor2pin2, LOW);
    analogWrite(pin2speed, speed2);

    delay(delaytime);
  }

}
