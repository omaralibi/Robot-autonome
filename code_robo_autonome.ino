#define enA 10
#define in1 9 
#define in2 8 
#define in3 7 
#define in4 6 
#define enB 5  
#define L_S A0 
#define R_S A1
#define echo A2    
#define trigger A3 
#define servo A4
int va=0,vt=0;
int rodbelek=15;
int distance_L, distance_F, distance_R; 

void servoPulse (int pin, int angle){
int pwm = (angle*11) + 500;    
 digitalWrite(pin, HIGH);
 delayMicroseconds(pwm);
 digitalWrite(pin, LOW);
 delay(50); }

void compareDistance(){
    if(distance_L > distance_R){
  turnLeft();
  delay(500);
  forword();
  delay(200);
  turnRight();
  delay(500);
  forword();
  delay(200);
  turnRight();
  delay(500);
  }
  else{
  turnRight();
  delay(500);
  forword();
  delay(200);
  turnLeft();
  delay(500);
  forword();
  delay(200);  
  turnLeft();
  delay(500);
  }
}

void Check_side(){
    stop();
    delay(100);
 for (int angle = 70; angle <= 140; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    distance_R = Ultrasonic_read();
    delay(100);
  for (int angle = 140; angle >= 0; angle -= 5)  {
   servoPulse(servo, angle);  }
    delay(500);
    distance_L = Ultrasonic_read();
    delay(100);
 for (int angle = 0; angle <= 70; angle += 5)  {
   servoPulse(servo, angle);  }
    delay(300);
    compareDistance();
}

void forword(){  
analogWrite(enA, va);  
analogWrite(enB, va);
digitalWrite(in1, LOW); 
digitalWrite(in2, HIGH);
digitalWrite(in3, HIGH);
digitalWrite(in4, LOW); }

void backword(){
analogWrite(enA, va);
analogWrite(enB, va);
digitalWrite(in1, HIGH);
digitalWrite(in2, LOW); 
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}

void turnRight(){ 
analogWrite(enA, vt); 
analogWrite(enB, 0); 
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);

}
void turnLeft(){ 
analogWrite(enA, 0); 
analogWrite(enB, vt); 
digitalWrite(in1, HIGH); 
digitalWrite(in2, LOW); 
digitalWrite(in3, HIGH);  
digitalWrite(in4, LOW);  
}
void stop(){
analogWrite(enA, 0); 
analogWrite(enB, 0); 
digitalWrite(in1, LOW); 
digitalWrite(in2, LOW); 
digitalWrite(in3, LOW);  
digitalWrite(in4, LOW);  
}

long Ultrasonic_read(){
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  long time = pulseIn (echo, HIGH);
  return time / 29 / 2;
}
void setup(){
  
Serial.begin(9600);
pinMode(R_S, INPUT);
pinMode(L_S, INPUT); 
pinMode(echo, INPUT );
pinMode(trigger, OUTPUT); 
pinMode(enA, OUTPUT); 
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
pinMode(enB, OUTPUT); 
pinMode(servo, OUTPUT);

for (int angle = 70; angle <= 140; angle += 5)  {servoPulse(servo, angle);  }
for (int angle = 140; angle >= 0; angle -= 5)  {servoPulse(servo, angle);  }
for (int angle = 0; angle <= 70; angle += 5)  {servoPulse(servo, angle);  }
distance_F = Ultrasonic_read();

delay(1000);
}
void loop(){  
va=100;
vt=140; 
distance_F = Ultrasonic_read();

 if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 0)){
  if(distance_F > rodbelek){forword();}
                  else{Check_side();}  
 }  

else if((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 0)){stop();delay(150);while((digitalRead(R_S) == 0)&&((digitalRead(L_S) == 0))){backword();delay(80);}do{turnLeft();delay(50);}while(digitalRead(R_S) == 1);} 
else if((digitalRead(R_S) == 0)&&(digitalRead(L_S) == 1)){stop();delay(150);while((digitalRead(L_S) == 0)&&((digitalRead(L_S) == 0))){backword();delay(80);}do{turnRight();delay(50);}while(digitalRead(L_S) == 1);}
 else if ((digitalRead(R_S) == 1)&&(digitalRead(L_S) == 1)){forword();delay(350);}
 
}