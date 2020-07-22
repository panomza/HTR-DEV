unsigned int motortime = 0;
unsigned int autotime = 0;
unsigned AutoPwm = 80;

void motor(){
  if (currenttime-motortime>1000){
      motortime=currenttime;
      PWM_control();
  }

  switch (Speed) {
      case 0:    
//        Serial.println("Off");
        Auto = 0;
        PWM = 0;
        break;
      case 1:    
        Auto = 1;
        AutoPwm=amphenoldust*3.57;
        break;
      case 2:   
        PWM = 100;
        Auto = 0;
        break;
      case 3:    
        PWM = 150;
        Auto = 0;
        break;
      case 4:    
        PWM = 200;
        Auto = 0;
        break;
  }

    if(currenttime-autotime>700 && Auto==1){
      autotime=currenttime;
       
        if (AutoPwm<80){ PWM=80;}
        if (AutoPwm>200){ PWM=200;}
        if (AutoPwm>50 && AutoPwm<200){PWM=AutoPwm;}
       
       Serial.print("AutoPwm="); Serial.print(AutoPwm);Serial.print("\t"); 
       Serial.print("Pwm=");  Serial.println(PWM);
   }
   
    if(Serial.available()>0){
    text=Serial.read();
   
    Serial.println(amphenoldust);

    if(text=='1'){amphenoldust=amphenoldust+1;}
    if(text=='2'){amphenoldust=amphenoldust-1;}
    }
}


void PWM_control(){
  
  TCCR1A = 0;            //clear timer registers
  TCCR1B = 0;
  TCNT1 = 0;

  TCCR1B |= _BV(CS10);   //no prescaler
  ICR1 =200;            //PWM mode counts up 320 then down 320 counts (25kHz)
 
  OCR1A = PWM;          //0-320 = 0-100% duty cycle
  TCCR1A |= _BV(COM1A1); //output A clear rising/set falling

  TCCR1B |= _BV(WGM13);  //PWM mode with ICR1 Mode 10
  TCCR1A |= _BV(WGM11);  //WGM13:WGM10 set 1010

}
