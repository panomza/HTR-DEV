

void speedset(){
 
   if ((Bs != Ls)  && (Bs == 0) && (currenttime-speedt0 > 100)&&speedcount==0){  
       Ls=Bs;
       speedt0=currenttime; 
       speedcount=1; 
       if(Speed==0 && off==1){on=1;}
       Serial.print("Speed is set to: ");
      nextauto=0;
   }
   else if ((Bs != Ls) && (Bs == 1)&& (currenttime-speedt0 > 300)&&speedcount==1){
      Ls=Bs;
      speedcount=0;
      countbutton=0;
      Speed++;
      swdisplay=1;
      trigdisplay=0;
       if(Speed==5){Speed=1;}
       Serial.print("Speed is set to: ");
       Serial.println(Speed);
    }

//       Serial.print(speedcount);
    if (currenttime-timedisplay>100 && Bs == 0){
        timedisplay=currenttime;
        countbutton++;
    }else if (Bs==1){countbutton=0;}
    
    if (countbutton==20){swdisplay=1;countbutton=0;speedcount=0; Speed=0;off=1;on=0;}
//    Serial.println(nextauto);
    if (currenttime-timedisplay>100 && swdisplay == 1){
        timedisplay=currenttime;
        trigdisplay++;
        if(trigdisplay==20){trigdisplay=0;swdisplay=0;speedcount=0;Ls=Bs;
        
            nextauto++;
            if(Speed>0){off=0;
              if(next==1){swdisplay=1;}
              }
              if(nextauto==2){swdisplay=0;nextauto=0;next=0;}
            }
            
    }
    
}
