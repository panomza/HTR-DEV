

void Auto(){
   
    if(currenttime-autotime>3000 && stateA==1 && stateP==0){
//        Serial.println("Auto");
      
        if(averagedust>=100){clearspeed();digitalWrite(M4,motor_on);}
        if(averagedust>=75 && averagedust<100){clearspeed();digitalWrite(M3,motor_on);}
        if(averagedust>=35 && averagedust<70){clearspeed();digitalWrite(M2,motor_on);}
        if(averagedust<35){clearspeed();digitalWrite(M1,motor_on);}
        
        autotime=currenttime;

    }
    
if ((Ba != La) && (Ba == 0)&& (currenttime-auto0 > buttondelay)&&autocount==0 && stateP==0){  
     La=Ba;
     stateA=!stateA;
     autocount=1;

     
     clearspeed();
     if(stateA==0){index=1;}
     if(stateA==1){index=5;}
     auto0=currenttime;      // get the current time
     beepvarB=1;
//     Serial.print("Auto is :");
//     Serial.print(stateA);
 }
   else if ((Ba != La) && (Ba == 1)&& (currenttime-auto0 > buttondelay)&&autocount==1 && stateP==0){
      La=Ba;
      autocount=0;
  }
    
}
