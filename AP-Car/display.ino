
#define CLK_PIN (4)
#define DIO_PIN (3)

#define bit_delay_125ns_4clk_of_8Mhz() asm("nop\n nop\n nop\n nop\n")
#define TM1637_CMD1_write_auto_inc_addr (0x40)
#define TM1637_CMD2_1st_mem_addr_7seg_1xxx (0xC0)   
#define TM1637_CMD3_ctrl_screen_head (0x80)         
byte k1=0;
byte k2=0;
byte k3=0;
byte d1=0;
byte d2=0;
byte d3=0;

     const uint8_t SEVEN_SEG_DIGITS[] = {
           // gfedcba
           0b00111111, // 0
           0b00000110, // 1
           0b01011011, // 2
           0b01001111, // 3
           0b01100110, // 4
           0b01101101, // 5
           0b01111101, // 6
           0b00000111, // 7
           0b01111111, // 8
           0b01101111, // 9

          
           0b00000000, // 10

           0b00110111, // 11 is N
           0b00111111, // 12 is O
           0b00111111, // 13 is O
           0b01110001, // 14 is F
           0b01101101, // 15 is S
           0b01110011, // 16 is P
           0b01110111, // 17 is A
           
           0b00000000, // 18
           0b00000001, // 19
           0b00000011, // 20
           0b00000101, // 21
           0b00001001, // 22
           0b00010001, // 23
           0b00100000, // 24
           0b01000000, // 25

           0b00000000, // 26
           0b00100000, // 27

           0b01111111, // 28

//           0b00000000, // 29
//           0b01000000, // 30
           

           
   };

    void tm1637_init_pin_for_sent_I2C() {
       pinMode( CLK_PIN, OUTPUT );
       pinMode( DIO_PIN, OUTPUT );
       digitalWrite( CLK_PIN, HIGH );
       digitalWrite( DIO_PIN, HIGH );
     }

    void tm1637_start_bit_I2C() {
         digitalWrite( DIO_PIN, LOW );
         bit_delay_125ns_4clk_of_8Mhz();
         digitalWrite( CLK_PIN, LOW );
         bit_delay_125ns_4clk_of_8Mhz();
     }

     void tm1637_stop_bit_I2C() {
          digitalWrite( CLK_PIN, HIGH );
          bit_delay_125ns_4clk_of_8Mhz();
          digitalWrite( DIO_PIN, HIGH );
          bit_delay_125ns_4clk_of_8Mhz();
      }

    int tm1637_send_1byte_I2C_ack( uint8_t data ) {
         uint8_t ack;
         for( uint8_t i = 0; i < 7; i++ ) {           // Send 8-bit data, LSB first
            digitalWrite( CLK_PIN, LOW );
            digitalWrite( DIO_PIN, ( data & 0x01 ) ? HIGH : 0 ); // ????????????????
            digitalWrite( CLK_PIN, HIGH );
            data >>= 1;                                    // shift bit to the right
           }
         digitalWrite( CLK_PIN, LOW );
             // I2C acknowledgement process , read ack in clolck9
         pinMode( DIO_PIN, INPUT );      // make DIO pin floating (input)
         digitalWrite( DIO_PIN, HIGH );   // enable pull-up
         digitalWrite( CLK_PIN, HIGH );   // start clock9
         ack = digitalRead( DIO_PIN );    // read ACK bit 
            // make DIO pin to output again
         digitalWrite( DIO_PIN, LOW );
         pinMode( DIO_PIN, OUTPUT );
         digitalWrite( CLK_PIN, LOW );
         return (ack==0);                                    
      }

   boolean showDigits( uint8_t digits[], boolean colon=false, uint8_t brightness=7) {
       // send the first command-----------------------
         tm1637_start_bit_I2C();
         tm1637_send_1byte_I2C_ack( TM1637_CMD1_write_auto_inc_addr );
         tm1637_stop_bit_I2C();
       // send the second command-------------------
         tm1637_start_bit_I2C();
         tm1637_send_1byte_I2C_ack( TM1637_CMD2_1st_mem_addr_7seg_1xxx );
         for ( uint8_t i=0, value; i <15; i++ ) {
           value = SEVEN_SEG_DIGITS[ digits[i] ];
           if ( (i == 1) && colon ) {
              value |= 0x80; // turn on the colon on the display ,x1xx digit ,hundreds digit
             }
           tm1637_send_1byte_I2C_ack( value );
         }
        tm1637_stop_bit_I2C();
      // send the third command---------------------- option send only 1 time is OK---- 
        tm1637_start_bit_I2C();
        tm1637_send_1byte_I2C_ack( TM1637_CMD3_ctrl_screen_head | (brightness & 7) | 0x08 );
             // brightness [0-7] , &0x07 filter to correct brightness value (before OR with CMD3)
            // 0x08 (0b00001000) , 1 is bit cmd for open 7seg screen ,0= close screen
        tm1637_stop_bit_I2C();
     }

////////////////////////////////////////////////////////////////////////

     
      // show time (hour and minute)
    void showdisplay(uint16_t ds) {
         static uint8_t data[15];

         k3=ds%10;
         k2=ds/10%10;
         k1=ds/100;
         
    if (Speed>0 && swdisplay==0 && on==1){
        /////////RED   
        if(ds>=56) {
         data[0] = k1;   
         data[3] = k2;    
         data[6] = k3;
        }else{
         data[0] = 10;   
         data[3] = 10;    
         data[6] = 10;
        }
        /////////Orenge
        if(ds>=36&&ds<=55) {
         data[2] = k1;  
         data[5] = k2;    
         data[8] = k3;
         }else{ 
         data[2] = 10;  
         data[5] = 10;    
         data[8] = 10;
         }
        /////////Green 
        if(ds<=35) {
         data[1] = k1;
         data[4] = k2; 
         data[7] = k3;
         }else{ 
         data[1] = 10;
         data[4] = 10; 
         data[7] = 10; 
         }
    }else{         
         data[0] = 10;   
         data[3] = 10;    
         data[6] = 10;

         data[2] = 10;  
         data[5] = 10;    
         data[8] = 10;
         

         data[1] = 10;
         data[4] = 10; 
         data[7] = 10; 
         }
    

    if(swdisplay==1){
        if(Speed==1 && on==1 && off==0){d1=10;d2=17;d3=10;    data[1] = d1;data[4] = d2;data[7] = d3;}
        if(Speed==2 && on==1 && off==0){d1=15;d2=16;d3=1;     data[1] = d1;data[4] = d2;data[7] = d3;}
        if(Speed==3 && on==1 && off==0){d1=15;d2=16;d3=2;     data[1] = d1;data[4] = d2;data[7] = d3;}
        if(Speed==4 && on==1 && off==0){d1=15;d2=16;d3=3;     data[1] = d1;data[4] = d2;data[7] = d3;}      
        if(Speed>=1 && on==1 && off==1){d1=10;d2=12;d3=11;    data[1] = d1;data[4] = d2;data[7] = d3; next=1;}//on
        
        if(Speed==0 && on==0 && off==1){d1=13;d2=14;d3=14;data[0] = d1;data[3] = d2; data[6] = d3;}//off        
         }

         showDigits( data); 
     }
unsigned int tts;

    void Display() {                       

         static uint16_t ds=0;   
        

         if ( currenttime - tts > 50 ) {                 
            showdisplay(ds); 
            
              ds=amphenoldust;  
                        
             tts = currenttime;

           }
     }
