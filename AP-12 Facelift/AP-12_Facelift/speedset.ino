

void speedset(){

 if ((Bs != Ls) && (stateP==0) && (Bs == 0)&& (currenttime-speedt0 > buttondelay)&&speedcount==0){  
     Ls=Bs;
     speedcount=1;
     index++;
     speedt0=currenttime;      // get the current time
     beepvarB=1;
     if(index>5){index=1;}
     Serial.print("Speed is : ");
     Serial.println(index);
     applythespeedswitch();
 }
 
 else if ((Bs != Ls) && (Bs == 1)&& (currenttime-speedt0 > buttondelay)&&speedcount==1){
      Ls=Bs;
      speedcount=0;
  }
  
}

void applythespeedswitch(){
  
    switch (index) {
    case 0:
      clearspeed();
      stateA=0;
      break;
    case 1:
      clearspeed();
      digitalWrite(M1,motor_on);  
      stateA=0;
      break;
    case 2:
      clearspeed();
      digitalWrite(M2,motor_on);
      stateA=0;
      break;
    case 3:
      clearspeed();
      digitalWrite(M3,motor_on);
      stateA=0;
      break;
    case 4:
      clearspeed();
      digitalWrite(M4,motor_on);
      stateA=0;
      break;
     case 5:
      clearspeed();
      stateA=1;
      break;
  }
  
}

void clearspeed(){
      
      digitalWrite(M1,motor_off);  
      digitalWrite(M2,motor_off);
      digitalWrite(M3,motor_off);
      digitalWrite(M4,motor_off);

}
