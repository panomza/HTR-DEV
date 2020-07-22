

#include <SoftwareSerial.h>
#include <ArduinoJson.h>
#include <avr/wdt.h>
#include <EEPROM.h>
#include <TimerOne.h>
#include <Wire.h>

SoftwareSerial NodeSerial(20, 21); // RX | TX

///////////////////////////////////////////////////////////////////////////

#include <IRremote.h>
int RECV_PIN = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;
#define OUTPUT_COUNT 5
unsigned long last = millis();
long remote_key[] = {0xDF40BF, 0xDF609F, 0xDF08F7, 0xDF50AF, 0xDF30CF
};
const byte outputPins[OUTPUT_COUNT] = {0, 1, 2, 3, 4};
bool status1[5] = {0, 0, 0, 0, 0};
struct keypad {
boolean state;
};
keypad output[OUTPUT_COUNT];

///////////////////////////////////////////////////////////////////////////


// input pins

const short int Bpow    = 14;    // power button input pin
const short int Bspeed  = 15;    // speed input pin
const short int Btimer  = 16;    // Timer button input pin
const short int Bfilter = 10;    // filter button input pin
const short int Btest   = 11;    // filter button input pin
bool buttonchack = 0;

const short int BUZ    = 9;         // buzzer output pin
const short int M1     = 4;         // motor output pin
const short int M2     = 5;         // motor output pin
const short int M3     = 6;         // motor output pin
const short int M4     = 7;         // motor output pin



//////////////////////////////////////////////////////////////////////////
// state variables

//////////////////////power//////////////////////

bool Bp         = 1;         //power button state
bool Lp         = 1;         //previous power button state
byte stateP     = 1;         //power output state
bool powercount = 0;         // count if the power button is pushed
unsigned int powert0 = 0;


/////////////////////speed////////////////////

bool Bs         = 1;           // speed input state
bool Ls         = 1;           // previous speed input state
bool speedcount = 0;           // check if button is pressed in the last loop
byte index = 0;                // case counter
unsigned int speedt0 = 0;
byte speed_led = 10;
bool motor_on = 0;
bool motor_off = 1;

////////////////////Timer////////////////////

bool Bt         = 1;
bool Lt         = 1;
bool timercount = 0;
byte Settime = 0;
unsigned int timer0;
unsigned int timedown = 0;        

byte timer_led = 10;
unsigned int timetrig = 0;
unsigned int runtime = 0;


/////////////////Auto////////////////////

bool Ba         = 1;
bool La         = 1;
bool stateA     = 0;    //auto state
bool autocount  = 0;
unsigned int autotime = 0;
unsigned int auto0 = 0;

/////////////////Reset filter////////////////////

bool Bf         = 1;
bool Lf         = 1;
bool filtercount  = 0;
unsigned int filtertime = 0;
unsigned int filter0 = 0;

/////////////////test////////////////////

bool B_test         = 1;
bool L_test         = 1;
bool state_test     = 0;   
byte No_test        = 0;
bool testcount      = 0;
unsigned int testtime = 0;
unsigned int test0  = 0;

///////////////delays////////////////////

unsigned int buttondelay = 50; // delay between each button press in ms
unsigned int currenttime = 0;


//////////////dust sensor///////////////

const short int measurePin = 17;
const short int ledPower = 12;
//const short int numaverage = 100; ///number of values for taking average
//unsigned int count;
//unsigned int dust[numaverage];
unsigned int averagedust = 0;
//unsigned int panadust = 0;

/////////////////////amphenol////////////////////////

SoftwareSerial pmsSerial(18,19);
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


///////////////beep///////////////////

bool songindex = 0;
bool beepvarB = 0;
bool beepvarS = 0;
bool beepstarted = 0;
bool beepstartedS = 0;
byte beeppowervar = 0;
unsigned int beeptime = 0;
unsigned int beeptimeS = 0;
int plays = 0;
int soundtime = 0;
unsigned int bwf = 0;
byte bnum = 0;

///////////////Bright////////////////

byte bright7 = 7;
byte brightdim = 30;
bool ck = 1;
bool Rd         = 1;           // speed input state
bool Ld        = 1;           // previous speed input state

//////////////dimmer////////////////
bool dimcount = 0;               
unsigned int Rdim0 = 0;
bool lastD = 0;
bool dimcheck = 0;
unsigned int trigdim=0;

//////////////filter///////////////

unsigned long time_filter = 0;
unsigned long time_update = 0;
unsigned long min_filter = 0;
byte alarm = 0;

////////////////wifi//////////////
byte ledwifi = 29;
bool statewifi =0;
unsigned int wifitrig =0;
byte wifibutton =0;
unsigned wificount =0;



////////////////////////////////////VOID/////////////////////////////////////////////////
///////////////////////////////////SETUP/////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);

//   Wire.begin();  // Connection start
//   Wire.setClock(60000L);

  pmsSerial.begin(9600);  //baud rate, configuration
  sampleTime = millis();
  
  tm1637_init_pin_for_sent_I2C();
  
  irrecv.enableIRIn(); // Start the receiver

  for (int i=0;i<OUTPUT_COUNT;i++) {
       pinMode(outputPins[i], OUTPUT);
       output[i].state = 0;
  }
   
  wdt_enable(WDTO_2S); // Watch dog function start

  int inputpins[6] = {Bpow, Bspeed, Btimer, Bfilter, Btest,measurePin};
  
  int outputpins[6] = { M1, M2, M3, M4, BUZ,ledPower };

  for (int j = 0; j < sizeof(inputpins) / sizeof(1); j++) {
    pinMode(inputpins[j], INPUT);
  }

  for (int j = 0; j < sizeof(outputpins) / sizeof(1); j++) {
    pinMode(outputpins[j], OUTPUT);
  }

  digitalWrite(outputpins[6],1);
  
  beepvarS = 1;

  clearspeed();
  
  pinMode(RECV_PIN, INPUT);   // IR receive
  pinMode(2, OUTPUT); // DIO (Display)
  pinMode(3, OUTPUT); // CLK (Display)

//  NodeSerial.begin(57600);
  pinMode(20, INPUT);    // Smart bord
  pinMode(21, OUTPUT);   // Smart bord
  
    pinMode(18, INPUT);

}

//////////////////////////////////////VOID////////////////////////////////////
//////////////////////////////////////LOOP////////////////////////////////////


void loop() {

  currenttime = millis();

  if (state_test==0){Dimmer();}

  beep();

  if (state_test==0){statebutton();}

  Remote();

  Display();

  if (state_test==0){amphenol();}

  if (state_test==0){powerset();}

  if (state_test==0){speedset();}

  if (state_test==0){TIMER();}

  if (state_test==0){Auto();}

  if (state_test==0){filter();}

  test();
  
  if (state_test==0){wifi_set();}

  read_smart();

  send_smart();

//  simulate_hang(); //stalls if timedown > 35 and stateA ==1

  wdt_reset(); // Watch dog reset

}
