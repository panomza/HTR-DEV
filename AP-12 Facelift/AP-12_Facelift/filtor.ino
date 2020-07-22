

byte count_filter = 0;
unsigned long puttime = 0;

unsigned int trig_filter = 0;

unsigned int show_filter = 0;
unsigned int time_fil = 0;
bool filon = 0;



void filter(){
  
  if (stateP==1){count_filter=0; min_filter=0;}
  
  if (currenttime-trig_filter>1000 && stateP==0){
      trig_filter=currenttime;  
      count_filter++;    
      if(count_filter==60 ){
         count_filter=0;
         min_filter++;  
        
         if(min_filter-puttime>30){ 
            EEPROM.put(0, time_update);
            Serial.print("time_update = ");
            Serial.println(time_update);
            puttime=0;
            puttime=min_filter;
            }
      }    
      
    time_update = time_filter + min_filter; 
      
    if (time_update>=270000){filon = 1;}
    if (time_update>=258000&&time_update<=269999){show_filter = 200;}
    if (time_update>=240000&&time_update<=257999){show_filter = 1000;}
    if (time_update<240000&&stateP==0){filon = 0;}
//    Serial.println(time_update);
  }
  
    if (currenttime-time_fil>show_filter&&(time_update>=4000&&time_update<=4500)&&stateP==0){
        time_fil=currenttime;
        filon=!filon;   
    }
    if (filon == 1&&stateP==0){alarm = 27;}else{alarm = 26;}


  if ((Bf != Lf) && (Bf == 0)&& (currenttime-filter0 > buttondelay)&&filtercount==0 && stateP==0){  
     Lf=Bf;
     filtercount=1;
     filter0=currenttime;      // get the current time
     beepvarB=1;
     time_update=0;
     min_filter=0;
     EEPROM.put(0, time_update);
 }
   else if ((Bf != Lf) && (Bf == 1)&& (currenttime-filter0 > buttondelay)&&filtercount==1 && stateP==0){
      Lf=Bf;
      filtercount=0;
      time_filter = EEPROM.get(0,time_update);
      Serial.println(time_filter);
  }
}
