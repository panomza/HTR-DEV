
void powerset(){
  // check if previous state is different from current state, current state is 0 and powercount=0

  if ((Bp != Lp) && (Bp == 0) && (currenttime-powert0 > buttondelay) && powercount==0&&plays==0){
      Lp=Bp;
      powert0 = currenttime;  
      powercount = 1;
  } // else if Bp is back to 1, reset the powercount

  else if ((Bp != Lp) && (Bp == 1)&& (currenttime-powert0 > buttondelay)&& powercount == 1&&plays==0){
        stateP=!stateP;
        if(stateP==0){
          beeppowervar=1;
          songindex=0;
          index=5;   
        time_filter = EEPROM.get(0,time_update);
        Serial.println(time_filter);
        } 
        
        if(stateP==1){
          beeppowervar=1;
          songindex=1;
          index=0;
          stateA=0;   
          EEPROM.put(0, time_update);
        }
        
        applythespeedswitch(); // apply the switch for speed when turning on
        Serial.print("Power to : ");
        Serial.println(stateP); 
        
        Lp=Bp;
        powercount = 0;
  }
  
}
