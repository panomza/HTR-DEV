#include <Arduino.h>
#include <TM1637Display.h>


unsigned int currenttime = 0;
bool speedcount = 0;
bool Bs = 1;
bool Ls = 1;
unsigned int speedt0 = 0 ;
byte Speed = 0;
const short int Bspeed = 2;
unsigned int countbutton = 0;
bool off = 1;
bool on = 0;
unsigned int timedisplay = 0;
unsigned int trigdisplay = 0;
byte swdisplay = 0;
bool next = 0;
byte nextauto = 0;
byte PWM = 0;
bool Auto = 0;
char text;


/////////////////////Amphinol////////////////////////

#include <SoftwareSerial.h>
SoftwareSerial pmsSerial(19,18);
int sampleRate = 2000; //sample rate in mS

#define fwVersion "SM_UART_04L_v1.2"
//Define Global Variables excluding CRC and 0x42, 0x4D prefix
const byte mode1[]   =    {0XE1, 0X00, 0X01}; //direct output (default)
const byte mode0[]   =    {0XE1, 0X00, 0X00}; //change to ask answer mode
const byte standby[] =    {0XE4, 0X00, 0X00}; //put into standby
const byte working[] =    {0XE4, 0X00, 0X01}; //put to working mode
const byte readPM[]  =    {0XE2, 0X00, 0X00}; //get reading

byte data[32] ; //create an array to store the response
unsigned long sampleTime;         // variable to monitor time of each sample start
unsigned int amphenoldust = 0;

void setup() {
  Serial.begin(9600);

  pinMode(Bspeed,INPUT); //button input
  pinMode(9,OUTPUT);//motor control

tm1637_init_pin_for_sent_I2C();
  

  ////////////////////////amphenol//////////////////////////

  pmsSerial.begin(9600);  //baud rate, configuration
  sampleTime = millis();
  
}

bool pou = 1;

void loop() {

currenttime = millis();

speedset();

motor();

Display();

if (text=='n'){pou = 1; }
if (text=='o'){pou = 0;}

if (pou==1){amphenol();}

Bs = digitalRead(Bspeed);


}
