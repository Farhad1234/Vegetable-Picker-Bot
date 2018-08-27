//unsigned char hello[] = {'H','e','l','l','o',' ',
  ///                       'R','a','s','p','i','\n'};
char marker,tem;
//int ss=10;
void setup() {
 // pinMode(MISO,OUTPUT);
  //pinMode(ss,INPUT);
  SPCR |= _BV(SPE);
  Serial.begin(9600);
  // put your setup code here, to run once:

}
void loop (void)
{
    //digitalWrite(ss,LOW);
  if((SPSR & (1 << SPIF)) != 0)
  {tem=/*(char)*/SPDR;
   // if(tem=='w' || tem=='d' || tem=='s' || tem=='a')  
  marker = tem;
  }Serial.print(marker); 
  
  
}

/*void loop() {
  
   if((SPSR & (1 << SPIF)) != 0)
  {
//    SPDR = hello[marker];
//    marker++;
    marker = SPDR;
    //marker= (char)marker;
    //if(marker > sizeof(hello))
    //{
     // marker = 0;
    //}  
  //while(marke
  Serial.println((char)marker);
  }
  // put your main code here, to run repeatedly:

}*/

