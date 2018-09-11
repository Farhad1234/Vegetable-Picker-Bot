const int L1 = 2;
const int L2 = 4;
const int R1 = 8;
const int R2 = 7;

const int ctrl = 5;       //PWM FOR LEFT
const int ctrl2= 6;       //PWM FOR RIGHT

int pace=100;         //DEFAULT MOTION SPEED
int pace2=100;        //DEFAULT MOTION SPEED
void setup() {
    Serial.begin(9600);
    pinMode(L1,OUTPUT);
    pinMode(L2,OUTPUT);
    pinMode(R1,OUTPUT);
    pinMode(R2,OUTPUT);
    pinMode(ctrl,OUTPUT);
    pinMode(ctrl2,OUTPUT);

  digitalWrite(L1,LOW);
  digitalWrite(L2,LOW);
  digitalWrite(R1,LOW);
  digitalWrite(R2,LOW);
  analogWrite(ctrl,100);
  analogWrite(ctrl2,100);
 
}

void loop() {
  
  if(Serial.available()>0){
    int val = Serial.read();
      
      if(val=='8')                      //frwd
          updateValue(1,0,1,0);

      else if(val=='6')                 //right turn
          updateValue(1,0,0,1);
            
      else if(val=='4')                 //left turn
          updateValue(0,1,1,0);
            
      else if(val=='7')                 //left frwd
          LF();
      
      else if(val=='9')                 //right frwd  
          RF();
      
      else if(val=='5')                 //STOP
          updateValue(0,0,0,0);

      
  }
}

void updateValue(int a, int b, int c, int d)
{
  digitalWrite(L1,a);digitalWrite(L2,b);
  digitalWrite(R1,c);digitalWrite(R2,d);
  analogWrite(ctrl,100);
  analogWrite(ctrl2,100);
  
}
void LF()
{
  
  digitalWrite(L1,HIGH);digitalWrite(L2,LOW);
  digitalWrite(R1,HIGH);digitalWrite(R2,LOW);
  
  analogWrite(ctrl,50);
  analogWrite(ctrl2,150);
  
}

void RF()
{ 
  
  digitalWrite(L1,HIGH);digitalWrite(L2,LOW);
  digitalWrite(R1,HIGH);digitalWrite(R2,LOW);
  
  analogWrite(ctrl,150);
  analogWrite(ctrl2,50);
}
