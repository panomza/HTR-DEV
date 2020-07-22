
///////////////////////////Amphinol//////////////////////

void amphenol()
{
  if (millis() >= (sampleRate + sampleTime) && Bs==1)
  {
    sampleTime = millis();  //resets timer before printing output

    if (GetSerialData()) {  //request to get data, if CRC OK, then print and display
//      Serial.print(( data[4] & 0x3F ) << 8 | data[5]); Serial.print(", "); //PM1 Standard Smoke

      amphenoldust = ( data[6] & 0x3F ) << 8 | data[7];
      Serial.println(amphenoldust);
    }else{Serial.print(F("No data"));}
  }
}


bool GetSerialData() {  //get lots - post sort method
  byte message[64];
  int CRC = 0;
  pmsSerial.readBytes(message, 64);

  for ( byte i = 0 ; i < 32 ; i++ ) {
    if ( message[i] == 0x42 && message[i + 1] == 0x4D ) {
      for ( byte j = 0 ; j < 32 ; j++ ) {
        data[j] = message[i];
        i++;
      }
      break;
    }
  }

  if ((data[30] * 256 + data[31]) == getCS(30)) {
    return true;
  }
  else {
    return false;
  }
}

unsigned int getCS(byte len)     // Compute the checksum
{
  unsigned int var = 0;
  for (int i = 0; i < len; i++) {
    var += data[i];
  }
  return var;
}
