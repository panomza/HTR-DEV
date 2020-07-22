unsigned countcheck = 0;
byte dimbutton = 0;

void Dimmer(){

  if (Bp==0 && (currenttime-trigdim > 100)){
      dimbutton++;  
//      Serial.println(dimbutton);
      trigdim = currenttime;
      
    if (dimbutton==10){
        beepvarB=1;
        ck=!ck; 
        dimbutton=0;
        if (ck==1){bright7=7;}else{bright7=0;}    
        dimcheck = 1;  
        powercount = 0;
      }
  }
  if (dimcheck==1&&Bp==1){countcheck++;if(countcheck==500){dimcheck = 0;countcheck=0;Lp=1;}
//      Serial.println(countcheck);
      }
  
if (Bp==1){dimbutton=0;}
  
  
  if ((Rd != Ld) && (Rd == 0)&& (currenttime-Rdim0 > buttondelay)&&dimcount==0){  
     Ld=Rd;     
     ck=!ck;
     dimcount=1;
     Rdim0=currenttime;      // get the current time
     beepvarB=1;
     if (ck==1){bright7=7;}else{bright7=0;}
  }
   else if ((Rd != Ld) && (Rd == 1)&& (currenttime-Rdim0 > buttondelay)&&dimcount==1){
      Ld=Rd;
      dimcount=0;
  }
}
