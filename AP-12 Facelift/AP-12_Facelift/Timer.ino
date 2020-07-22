bool out = 0;


void TIMER(){
    if ( Bp == 0 ) {Settime=0;}

    if ((Bt != Lt) && Bt == 0  && (currenttime-timer0 > buttondelay)&&timercount==0){
        Lt=Bt;
        timer0 = currenttime;
        timercount=1;
    } 
    else if ((Bt != Lt) && (Bt == 1)&& (currenttime-timer0 > buttondelay)&&timercount==1){
              Lt=Bt;
              timer0 = currenttime;
              beepvarB=1;
              Settime++;
              if(Settime==5){Settime=0;}
              selecttime();
              out = 0; 
              timercount=0;
              Serial.print("Timer to : ");
              Serial.println(Settime); 
    }
  
    

///////////////////////////////////////////////////////////////////////////////.

      runtime=millis();
      
            if(runtime - timetrig >1000 && selecttime>0){
                     timetrig = runtime;
                     timedown=timedown-1;   
                     out = 0; 
             }
 
      if (Settime==0){timedown=0;}

      if (timedown == 28800 && out == 0 ){Settime=4;out =1;}
      if (timedown == 14400 && out == 0 ){Settime=3;out =1;}
      if (timedown == 7200 && out == 0 ){Settime=2;out =1;}
      if (timedown == 3600 && out == 0 ){Settime=1;out =1;}
      if (timedown == 0 && out == 0 && Settime >0){Settime=0;Bp = 0;out =1;}
      if (stateP==0&&timedown==0){timer_led=19;}
      if (stateP==1&&timedown==0){timer_led=18;}

      if (Settime==1){timer_led=20;}
      if (Settime==2){timer_led=21;}
      if (Settime==3){timer_led=22;}
      if (Settime==4){timer_led=23;}
//      Serial.println(timedown); 

 }

void selecttime(){
  switch(Settime){
    
    case 1:
    timedown=3600;
    break;
    case 2:
    timedown=7200;
    break;
    case 3:
    timedown=14400;
    break;
    case 4:
    timedown=28801;
    break;
  }
}
