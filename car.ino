#define enB 10
#define in3 9
#define in4 8
#define enA 11  
#define in1 4
#define in2 5

#define enC 3
#define in5 2
#define in6 1 

#define enD 6
#define in7 7 
#define in8 A5 

#define transistor A3 

const int button =13; 
const int LED=12; 
bool arm_on=false; 

int  xAxis, yAxis;
int motorSpeedA = 0;
int motorSpeedB = 0;
int motorSpeedC =0; 
 
void setup() {
  //Motor Code 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(enC, OUTPUT); 
  pinMode(enD, OUTPUT); 


  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT); 
  pinMode(in6, OUTPUT); 
  pinMode(in7, OUTPUT); 
  pinMode(in8, OUTPUT); 
  
  Serial.begin(9600);
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);

  //Button Code
  pinMode(LED, OUTPUT);
  pinMode(button, INPUT);

  //transistor code
  pinMode(transistor, OUTPUT); 


  Serial.begin(9600); 
}

void loop() {
  yAxis = analogRead(A1);
  xAxis = analogRead(A0); 
  //Serial.println(yAxis);
  //Serial.println(xAxis);

  Serial.println(digitalRead(button)); 
  if(digitalRead(button)==1){
    if(arm_on==false){


      digitalWrite(LED, HIGH); 
      arm_on = true; 
      delay(500); 
    }
    else{
      digitalWrite(LED, LOW); 
      arm_on=false; 
      delay(500); 
    }
  }

  if(!arm_on){
      //Turn pylley motor off 
      digitalWrite(in5, LOW);
      digitalWrite(in6, LOW);
      analogWrite(enC, 0);
      //Turn Magnet off
      digitalWrite(in7, LOW);
      digitalWrite(in8, LOW);
      analogWrite(enD, 0);

    if (yAxis < 470) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW);
      motorSpeedA = map(yAxis, 470, 0, 0, 255);
      motorSpeedB = map(yAxis, 470, 0, 0, 255);
    }
    else if (yAxis > 550) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, LOW);
      digitalWrite(in4, HIGH);
      motorSpeedA = map(yAxis, 550, 1023, 0, 255);
      motorSpeedB = map(yAxis, 550, 1023, 0, 255);
    }
    else {
      motorSpeedA = 0;
      motorSpeedB = 0;
    }
    if (xAxis > 550) {
      int xMapped = map(xAxis, 550, 0, 0, 255);
      motorSpeedA = motorSpeedA + xMapped;
      motorSpeedB = motorSpeedB - xMapped;
      // Confine the range from 0 to 255
      if (motorSpeedA < 0) {
        motorSpeedA = 0;
      }
      if (motorSpeedB > 255) {
        motorSpeedB = 255;
      }
    }
    if (xAxis < 470) {
      int xMapped = map(xAxis, 470, 1023, 0, 255);
      motorSpeedA = motorSpeedA - xMapped;
      motorSpeedB = motorSpeedB + xMapped;
      if (motorSpeedA > 255) {
        motorSpeedA = 255;
      }
      if (motorSpeedB < 0) {
        motorSpeedB = 0;
      }
    }
    if (motorSpeedA < 70) {
      motorSpeedA = 0;
    }
    if (motorSpeedB < 70) {
      motorSpeedB = 0;
    }
    analogWrite(enA, motorSpeedA); // Send PWM signal to motor A
    analogWrite(enB, motorSpeedB); // Send PWM signal to motor B
  }


  else{
    Serial.println("joystick controlling pulley and magnet is on");
    //power the EM
    digitalWrite(6, HIGH); 
    delay(1000); 
    digitalWrite(6, LOW); 
    delay(1000); 


    //Turn Magnet on 
    digitalWrite(in7, LOW);
    digitalWrite(in8, HIGH);
    analogWrite(enD, 255);

    if (yAxis < 470) {
      digitalWrite(in5, HIGH);
      digitalWrite(in6, LOW);
      analogWrite(enC, 255);
      //motorSpeedA = map(yAxis, 470, 0, 0, 255);
    }
    else if (yAxis > 550) {
      digitalWrite(in5, LOW);
      digitalWrite(in6, HIGH);
      analogWrite(enC, 255); 
      //motorSpeedA = map(yAxis, 550, 1023, 0, 255);
    }
    if(yAxis>470 && yAxis<550){
      digitalWrite(in5, LOW);
      digitalWrite(in6, LOW);
      analogWrite(enC, 0);
    }
  }
  
}

