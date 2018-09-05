#include<Servo.h>
#define L1 2
#define L2 3
#define R1 5
#define R2 6
#define RPWM 7
#define LPWM 4

#define THRESHOLD 200
int pos[]={90,135,90,135};
int leftin,rightin;
int x,y,SIZE;
int start=-1,i=0;

Servo S1,S2,S3,S4;


void setup() {
  pinMode(L1,OUTPUT)    ;
  pinMode(L2,OUTPUT)    ;
  pinMode(R2,OUTPUT)    ;
  pinMode(R1,OUTPUT)    ;
  pinMode(RPWM,OUTPUT);
  pinMode(LPWM,OUTPUT);
  pinMode(A0,INPUT); //ch3
  pinMode(A1,INPUT); //ch2

  S1.attach(8);
  S2.attach(9);
  S3.attach(10);
  S4.attach(11);
  armreset();

}

void armreset()         // PUTS THE ARM IN DEFAULT POSITION
{
  
  S1.write(90);
  S2.write(135);
  S3.write(90);
  S4.write(135);
  pass(L1,LOW,L2,LOW);
  pass(R1,LOW,R2,LOW);
  
}


void allMotions()   
{
  
  loco();
  
  if( abs(x) <5 && abs(y)<5)    //radius of 5 pixels is excluded for arm motion
      forward(SIZE);
  else
  {
    if(x>0 && y>0)
      armMotion(1,1,1,0);
    
    if(x<0 && y>0) 
      armMotion(0,1,1,0);
  
    if(x<0 && y<0)
      armMotion(0,0,0,1);
      
    if(x>0 && y<0)
      armMotion(1,0,0,1);
  } 
  
}

void armMotion(int a,int b,int c, int d)
{
  

  
  
//  WRITING TO ARM NOW --------------->  
  if(a==1)
    S1.write(++pos[0]);
  else
    S1.write(--pos[0]);
  
  if(b==1)
  
    S2.write(++pos[1]);
   else
    S2.write(--pos[1]);
    
  if(c==1)
    S3.write(++pos[2]);
  else
    S3.write(--pos[2]);
    
  if(d==1)
    S4.write(++(++pos[3]));
   else
    S4.write(--(--pos[3]));



//    <------------ ARM CONTROL ENDs
}

void forward(int SIZE)
{
  if(SIZE>THRESHOLD)
    cut();
  else
    {
      S2.write( --pos[1] );
      S3.write( ++pos[2] );
    }
}

void loco()
{
  //  REMOTE CONTROLS START HERE -------->
  if(rightin>-20 && rightin <20)       
      pass(R1,LOW,R2,LOW);
  
  else {
    if(rightin>=20)
    {
      pass(R1,LOW,R2,HIGH);
      analogWrite(RPWM,rightin);
    }
    else
      {
        pass(R1,HIGH,R2,LOW);
        analogWrite(RPWM,-rightin);
      }
  }

if(leftin>-20 && leftin <20)       
      pass(L1,LOW,L2,LOW);
  
  else {
    if(leftin>=20)
    {
      pass(L1,LOW,L2,HIGH);
      analogWrite(LPWM,leftin);
    }
    else
      {
        pass(L1,HIGH,L2,LOW);
        analogWrite(LPWM,-leftin);
      }
  }

//  <-------------- REMOTE CONTROLS ENDS HERE  
}
void pass(int p1, int a, int p2, int b)
{
  digitalWrite(p1,a);
  digitalWrite(p2,b);
}
void cut()
{
//  calibrate cutting 
}
void readData()
{
//  READING PI DATA --------------->
  char arr[20];
  if(Serial.available() > 0 )
    {
      char ch=Serial.read();
      
      if(ch=='$')
        start=1;
      if(start==1)
      {
          arr[i]=ch;
          i++;
      }
      if(ch=='*')
      {
        arr[i]='\0';
        start=-1;
        i=0;
      }
      
    }
//    <-------------- PI DATA READ
//EXTRACTING VALUES FROM PI DATA --------------->


  x= (arr[1]*100) + (arr[2]*10) + arr[3];
  y= (arr[5]*100) + (arr[6]*10) + arr[7];
  SIZE= (arr[9]*100) + (arr[10]*10) + arr[11];
//  <---------------------------  VALUES EXTRACTED

}


void loop (){
                        
    
// ALL INPUTS HERE ------------------------------->
// REMOTE INPUT HERE ----->
  rightin=pulseIn(A0,HIGH);
  leftin=pulseIn(A1,HIGH);

  rightin=map(rightin,1023,1850,-230,230);
  leftin=map(leftin,1017,1845,-230,230);
// <------- REMOTE INPUT ENDS

  readData();             // INPUT FROM PI 


// <------------------------------------- ALL INPUT ENDS
    
    allMotions();   //ALL MOTIONS ARE TRIGGERED
}
