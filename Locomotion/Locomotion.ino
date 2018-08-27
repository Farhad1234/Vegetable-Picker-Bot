#define L1 1
#define L2 2
#define R1 3
#define R2 4
#define RPWM 5
#define LPWM 6

void setup() {
pinMode(L1,LOW)    ;
pinMode(L2,LOW)    ;
pinMode(R2,LOW)    ;
pinMode(R1,LOW)    ;
pinMode(RPWM,OUTPUT);
pinMode(LPWM,OUTPUT);
pinMode(A0,INPUT); //ch3
pinMode(A1,INPUT); //ch2

}

void loop() {
  
int leftin,rightin;
rightin=pulseIn(A0,HIGH);
leftin=pulseIn(A1,HIGH);

rightin=map(rightin,1023,1850,-200,200);
leftin=map(leftin,1017,1845,-200,200);

Write(rightin,leftin);

}
void Write(int right, int left)
{
  if(right>-20 && right <20)       
      pass(R1,LOW,R2,LOW);
  
  else {
    if(right>=20)
    {
      pass(R1,LOW,R2,HIGH);
      analogWrite(RPWM,right);
    }
    else
      {
        pass(R1,HIGH,R2,LOW);
        analogWrite(RPWM,-right);
      }
  }

if(left>-20 && left <20)       
      pass(L1,LOW,L2,LOW);
  
  else {
    if(left>=20)
    {
      pass(L1,LOW,L2,HIGH);
      analogWrite(LPWM,left);
    }
    else
      {
        pass(L1,HIGH,L2,LOW);
        analogWrite(LPWM,-left);
      }
  }

}
void pass(int p1, int a, int p2, int b)
{
  digitalWrite(p1,a);
  digitalWrite(p2,b);
}
