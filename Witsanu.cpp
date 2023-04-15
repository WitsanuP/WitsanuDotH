#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include <Witsanu.h>
#include "font.h"

#define CS 0x0A
#define DIN 0x0B
#define CLK 0x0D
#define LEDR 4  //can't pwm
#define LEDY 5  //can pwm
#define LEDG 6  //can pwm
#define BUTTON1 2
#define BUTTON2 3

//-------------------------------------------------------------
// Constructor
//-------------------------------------------------------------
Witsanu::Witsanu()
{
  pinMode(DIN, OUTPUT);
  pinMode(CS, OUTPUT);
  pinMode(CLK, OUTPUT);
}

//-------------------------------------------------------------
// Methods
//-------------------------------------------------------------
void Witsanu::Set()
{
  SendPackets(0x09, 0);         //decoding mode OFF
  SendPackets(0x0A, 0);         //light intensity (0-15)
  SendPackets(0x0B, 7);         //scan limit: all digits ON
  SendPackets(0x0C, 1);         //turn ON MAX7219
  Clear();
}
void Witsanu::Brightness(byte brightness) {
  SendPackets(0x0A, brightness);//light intensity (0-15)
}
//-------------------------------------------------------------
void Witsanu::Clear()           //clear display
{
  for (byte i = 0; i < 8; i++) SendPackets(i + 1, 0);
}
//--------------------------------------------------------------
void Witsanu::Clear(int TimeDelay) {//clear display <TimeShow>
  for (int j = 0; j < 8; j++) {
    SendPackets(j + 1, c[j]);
  }
  delay(TimeDelay);
}
//--------------------------------------------------------------
void Witsanu::Triangle(int TimeDelay) {//show triangle <TimeShow>
  for (int j = 0; j < 8; j++) {
    SendPackets(j + 1,  tri[j]);
  }
  delay(TimeDelay);
}
//--------------------------------------------------------------
void Witsanu::Text(char text[], int TimeDelay) { //show text <"text"><TimeShow>
  for (int i = 0; i < strlen(text); i++) { //loop word  

    for (int j = 0; j < 8; j++) {
      if (text[i] > 90)text[i] -= 32;
      SendPackets(j + 1, CapLetter[text[i] - 65][j]);
    }
    delay(TimeDelay);
    Clear(5);
  }
}
//--------------------------------------------------------------
void Witsanu::NumberAndPic(int number, int TimeDelay) { //display number and sign <number><TimeShow>
  char cstr[4];
  sprintf(cstr, "%04d", number);
  for (int i = 0; i < 4; i++) { //loop word

    for (int j = 0; j < 8; j++) SendPackets(j + 1, Num[cstr[i] - '0'][j]);
    delay(TimeDelay);
    Clear(5);
  }
  for (int j = 0; j < 8; j++) SendPackets(j + 1, Sign[(cstr[3] - '0') % 5][j]);
  delay(TimeDelay);
}
//--------------------------------------------------------------
void Witsanu::FullCombo(char Name[], int Num) {//display All(triangle,text,number,sign) <text><number>
  Triangle(1000);
  Clear(1);
  Text(Name, 1000);
  NumberAndPic(Num, 1000);
}
//--------------------------------------------------------------
void Witsanu::TextScrolling(int TimeDelay, const char *text, ...) {//scrolling text<TimeShow><text> <format, ... >
  //byte ArrayText[CountRealLetter(text)][8];
  //resize array
  ArrayText = (byte**)malloc(CountRealLetter(text) * sizeof(byte*));
  for (int i = 0; i < CountRealLetter(text); i++) {
    ArrayText[i] = (byte*)malloc(8 * sizeof(byte));
  }

  if (text == NULL) return 0; //check case without text

  va_list valist;
  va_start(valist, text);

  int num = 0;

  int i = 0; //index รวม%
  int j = 0;//index ไม่รวม%_
  int len = strlen(text);
  int found = 0;
  while ( text[i] != NULL)
  {
    num = 0;
    found = 0;

    if ( ( text[i] == '%' ) && ( ( i + 1 ) < len ) ) {
      switch ( text[i + 1] ) {
        case 's': {//sign 0-4
            found = 1;
            num = va_arg(valist, int);
            CopyArray(j, num, Sign);
            j++;
          }
          break;

        case 'p': {//pic 0-10
            found = 1;
            num = va_arg(valist, int);
            CopyArray(j, num, Pic);
            j++;
          }
          break;

        case 't': {//triagle
            found = 1;
            for (int i = 0; i < 8; i++) {
              ArrayText[j][i] = tri[i];
            }
            j++;
          }
          break;

      }
      if ( found != 0 ) {
        i += 2;
        continue;
      }
    }
    if (( 'a' <= text[i]) && ('z' >= text[i])) {
      CopyArray(j, text[i] - 'a', SmallLetter);
    }
    else if (( 'A' <= text[i]) && ('Z' >= text[i])) {
      CopyArray(j , text[i] - 'A', CapLetter);
    }
    else if (( '0' <= text[i]) && ('9' >= text[i])) {
      CopyArray(j , text[i] - '0', Num);
    }
    else if (text[i] == ' ') {
      for (int i = 0; i < 8; i++) {
        ArrayText[j][i] = c[i];
      }
    }
    j++;
    i++;
  }
  va_end(valist);
  //display scrolling text
  byte tmp[8];

  for (int i = 0; i < CountRealLetter(text) ; i++) { //loop word

    for (int j = 0; j < 8; j++) {
      for (int m = 0; m < 8; m++) {
        if (i + 1 >= CountRealLetter(text))
          tmp[m] = (ArrayText[i][m] << j) | (ArrayText[0][m] >> (8 - j)); //make frame
        else
          tmp[m] = (ArrayText[i][m] << j) | (ArrayText[i + 1][m] >> (8 - j)); //make frame
      }
      for (int k = 0; k < 8; k++) {
        SendPackets(k + 1, tmp[k]);// show each frame
      }
      delay (TimeDelay);
    }
    Clear();
  }
  //free mem
  for (int i = 0; i < CountRealLetter(text); i++)
    free(ArrayText[i]);
  free(ArrayText);
}
//--------------------------------------------------------------
void Witsanu::CopyArray(const int a, const int b, byte a2[][8]) //copy from SomeFont to ArrayText(variable) <ArrayText[a]> <SomeFont[b]><SomeFont>
{
  for (int i = 0; i < 8; i++) {
    ArrayText[a][i] = a2[b][i];
  }
}
//--------------------------------------------------------------
int Witsanu::CountRealLetter(char *text) {//dont count %_

  int len = strlen(text);
  int count = 0;
  for (int i = 0; i < strlen(text); i++) {
    if (text[i] == '%') {
      count += 1;
    }
  }
  return len - count;
}

//--------------------------------------------------------------
// Debug
//--------------------------------------------------------------
void Witsanu::CheckCapLetter() {
  for (byte i = 0; i < 26; i++) { //loop word
    for (byte j = 0; j < 8; j++) {
      SendPackets(j + 1, CapLetter[i][j]);
    }
    delay(1000);
    Clear(5);
  }
}
//-------------------------------------------------------------
void Witsanu::CheckCapLetter(int index) {
  for (byte j = 0; j < 8; j++) {
    SendPackets(j + 1, CapLetter[index - 1][j]);
  }
  delay(1000);
}
//-------------------------------------------------------------
void Witsanu::CheckNumber() {
  for (byte i = 0; i < 10; i++) { //loop word

    for (byte j = 0; j < 8; j++) {
      SendPackets(j + 1, Num[i][j]);
    }
    delay(1000);
    Clear(5);
  }
}
//-------------------------------------------------------------
void Witsanu::CheckNumber(int index) {
  for (byte j = 0; j < 8; j++) {
    SendPackets(j + 1, Num[index][j]);
  }
  delay(1000);
  Clear(5);

}
//-------------------------------------------------------------
void Witsanu::CheckSign() {
  for (byte i = 0; i < 5; i++) { //loop word
    for (byte j = 0; j < 8; j++) {
      SendPackets(j + 1, Sign[i][j]);
    }
    delay(1000);
  }
}
//-------------------------------------------------------------
void Witsanu::CheckSign(int index) {

  for (int j = 0; j < 8; j++) {
    SendPackets(j + 1, Sign[index][j]);
  }
  delay(1000);
}
//-------------------------------------------------------------
void Witsanu::CheckSmallLetter() {
  for (byte i = 0; i <26; i++) { //loop word
    for (byte j = 0; j < 8; j++) {
      SendPackets(j + 1, SmallLetter[i][j]);
    }
    delay(1000);
  }
}
//-------------------------------------------------------------
void Witsanu::CheckSmallLetter(int index) {

  for (int j = 0; j < 8; j++) {
    SendPackets(j + 1, SmallLetter[index][j]);
  }
  delay(1000);
}


//-------------------------------------------------------------
// Functions
//-------------------------------------------------------------
void Witsanu::SendPackets(byte cmd, byte data)
{
  digitalWrite(CS, LOW);   //CS low pulse to enable MAX7219

  SPI_send(cmd);       //send command byte to MAX7219
  SPI_send(data);      //send data byte to MAX7219

  digitalWrite(CS, HIGH);  //CS high pulse to disable MAX7219
}
//--------------------------------------------------------------
void Witsanu::SPI_send(byte data)
{
  for (byte i = 0; i < 8; i++)
  {
    digitalWrite(CLK, LOW);                   //CLK low pulse

    if (data & 0x80) digitalWrite(DIN, HIGH); //o/p high if MSB = 1
    else digitalWrite(DIN, LOW);              //o/p low if MSB = 0

    digitalWrite(CLK, HIGH);                  //CLK high pulse
    data = data << 1;                         //shift data left one bit
  }
}
