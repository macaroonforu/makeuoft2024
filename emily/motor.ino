
int enaA = 5;
int in1 = A0;
int in2 = A1;

int enaB = 3; //10 got fried!
int in3 = A2;
int in4 = A3;

void setup() {
  //yellow wheel 
  pinMode(enaA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  //black wheel 
  pinMode(enaB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //Serial.begin(9600);
}

void loop(){
    start(); //Start the motors 
    delay(3000); 
    stop(); 
}

//turn both motors off
void stop(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

//start both motors 
void start(){
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(enaA, 127);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enaB, 127);
}
