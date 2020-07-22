

void wifi_set(){
  
  if (Bt==0 && (currenttime-wifitrig > 100)&&stateP==0){
      Lt=Bt;
      wifitrig = currenttime;
      wifibutton++; 
//      Serial.println(wifibutton);        
    } 
   
   if (wifibutton==15){
      beepvarB=1;
      statewifi =! statewifi;
      wifibutton = 0;
      timercount=0;
   }

   if(statewifi==1){ledwifi=30;}else{ledwifi=29;}


   
   if (Bt == 1 ){wificount++; wifibutton=0;
      if (wificount==400){wificount = 0; Lt=1;}
   }
}
