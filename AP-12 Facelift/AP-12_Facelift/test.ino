void test ()
{
  
  if ((B_test != L_test) && (B_test == 0)&& (currenttime-test0 > buttondelay)&&testcount==0 && stateP==1&&state_test==0&&plays==0){  
     L_test=B_test;
     testcount=1;
     test0=currenttime;      // get the current time
     beepvarB=1;   
     No_test=1;
     state_test=1;
     averagedust= 0;
     index  = 255;
     timer_led = 18;
     alarm =26;
 }
   else if ((B_test != L_test) && (B_test == 1)&& (currenttime-test0 > buttondelay)&&testcount==1 && stateP==1&&state_test==0&&plays==0){
      L_test=B_test;
      testcount=0;
  }


  if (No_test == 1){averagedust++;delay(40);      if (averagedust==120){averagedust=0;   No_test = 2;}    Serial.println(averagedust);}
  if (No_test == 2){index++;      delay(500);     if (index==8)        {index=0;         No_test = 3;}    Serial.println(index);}
  if (No_test == 3){timer_led++;  delay(500);     if (timer_led==25)   {timer_led=18;    No_test = 4;}    Serial.println(Settime);}
  if (No_test == 4){alarm++;      delay(500);     if (alarm==29)       {alarm=26;        No_test = 5;}    Serial.println(alarm);}
  if (No_test == 5){ledwifi++;    delay(500);     if (ledwifi==31)     {ledwifi=29;      No_test = 6;}    Serial.println(ledwifi);}
  if (No_test == 6){averagedust=888; index=17; timer_led=28; alarm=28; ledwifi=30; No_test = 7; bright7=0;}
  if (No_test == 7){bright7++;    delay(500);     if (bright7>=7)      {No_test = 7;     delay(1000);}}

  if (No_test == 0){state_test=0;}
  
}
