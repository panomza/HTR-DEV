
unsigned int tc=0;
unsigned int returnbutton = 0;
byte countbuttonchack = 0;

void checkbuttons(){
  Bp      =  digitalRead(Bpow);
  Bs      =  digitalRead(Bspeed);
  Bt      =  digitalRead(Btimer); 
  Bf      =  digitalRead(Bfilter); 
  B_test  =  digitalRead(Btest); 
  
// Serial.println(Btest);
}

void statebutton(){

  if (digitalRead(Bpow)==0 || digitalRead(Bspeed)==0 || digitalRead(Btimer)==0 || digitalRead(Bfilter)==0) {
      checkbuttons();
  }
  
  if (Bp==0 || Bs==0 || Bt==0 || Ba==0 || Rd==0){buttonchack=1;countbuttonchack=0;}
  
  if (currenttime-returnbutton>10&&buttonchack==1){
      returnbutton=currenttime;
      countbuttonchack++;
      Serial.println(countbuttonchack);
      if (countbuttonchack==250){buttonchack=0;countbuttonchack=0;}
     }

//if(NodeSerial.available()>0){}else{
  if(currenttime-tc>100){
      checkbuttons();
      tc=currenttime;
  }
// }
}
