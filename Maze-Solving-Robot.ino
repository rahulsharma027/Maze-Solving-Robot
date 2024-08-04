#define DIS 5
int trigger_front = A0;  //front
int echo_front = A1;
int trigger_left = A2;  //left
int echo_left = A3;
int trigger_right = A4;  //right
int echo_right = A5;
int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;

void setup() {
  pinMode(trigger_front, OUTPUT);
  pinMode(echo_front, INPUT);
  pinMode(trigger_left, OUTPUT);
  pinMode(echo_left, INPUT);
  pinMode(trigger_right, OUTPUT);
  pinMode(echo_right, INPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right;

  //Calculating distance

  digitalWrite(trigger_front, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_front, LOW);
  duration_front = pulseIn(echo_front, HIGH);
  distance_front = duration_front * 0.034 / 2;

  digitalWrite(trigger_left, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_left, LOW);
  duration_left = pulseIn(echo_left, HIGH);
  distance_left = duration_left * 0.034 / 2;

  digitalWrite(trigger_right, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_right, HIGH);

  delayMicroseconds(10);
  digitalWrite(trigger_right, LOW);
  duration_right = pulseIn(echo_right, HIGH);
  distance_right = duration_right * 0.034 / 2;


  Serial.print("front = ");
  Serial.println(distance_front);
  Serial.print("Left = ");
  Serial.println(distance_left);
  Serial.print("Right = ");
  Serial.println(distance_right);
  delay(500);

      if (distance_front > 20) {
        forward();
        if (distance_left > 10 && distance_left < 20) {
          forward();
        }
        if (distance_right > 10 && distance_left < 20) {
          forward();
        }
        if (distance_left < 10 && distance_right > 10) {
          right();
          delay(35);
          forward();
        }
        if (distance_right < 10 && distance_left > 10) {
          left();
          delay(35);
          forward();
        }
      }
      if (distance_front <= 20 && distance_right > 20 && distance_left < 20) {
        stop();
        reverse();
        delay(200);
        right();
        delay(680);
        forward();
      }
      if (distance_front <= 20 && distance_left > 20 && distance_right < 20) {
        stop();
        reverse();
        delay(200);
        left();
        delay(640);
        forward();
      }
      if (distance_front <= 10 && distance_right < 20 && distance_left < 20) {
        stop();
        reverse();
        delay(1240);
        right();
        delay(620);
        forward();
      }
    

  if (Serial.available()) {
    String Command = Serial.readString();
    
    if (Command == "L") {
      stop();
    }

    else if (Command == "F") {
      Serial.print("FORWARD");
      Serial.print("\n");
      forward();
      delay(500);
      stop();
    }


    else if (Command == "S") {
      Serial.print("STOP");
      Serial.print("\n");
      stop();
    }


    else if (Command == "B") {
      Serial.print("BACKWARD");
      Serial.print("\n");
      reverse();
      delay(500);
      stop();
    }


    else if (Command == "L") {
      Serial.print("LEFT");

      Serial.print("\n");
      left();
      delay(620);
      forward();
    }


    else if (Command == "R") {
      Serial.print("RIGHT");
      Serial.print("\n");
      right();
      delay(620);
      forward();
    }



    else if (Command == "U") {
      Serial.print("U-TRUN");
      Serial.print("\n");
      forward();
      delay(3000);
      right();
      delay(620);
      forward();
      delay(1000);
      right();
      delay(620);
      forward();
      delay(3000);
      stop();
    }


    else if (Command == "E") {
      Serial.print("START-TO-END");
      Serial.print("\n");
    }


    else if (Command == "3") {
      Serial.print("END-TO-START");
      Serial.print("\n");
    }
  }
}



  void forward() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }

  void reverse() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  void right() {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }

  void left() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
  }



  void stop() {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
