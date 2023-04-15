#include <Arduino.h>
#include <Witsanu.h>

#define CS 0x0A
#define DIN 0x0B
#define CLK 0x0D

const byte c[] = {0, 0, 0, 0, 0, 0, 0, 0};
const byte tri[] = {0x80, 0xC0, 0xA0, 0x90, 0x88, 0x84, 0x82, 0xFF};
const byte PIC[5][9] = {
  {0xc7, 0x89, 0x09, 0x0E, 0x7E, 0x99, 0x99, 0xE7}, //0,5
  {0x18, 0x24, 0x42, 0x99, 0x99, 0x42, 0x24, 0x18}, //1,6
  {0xF8, 0xF0, 0xF0, 0xF8, 0x9C, 0x0E, 0x07, 0x02}, //2,7
  {0xC3, 0x89, 0x18, 0x38, 0x78, 0x00, 0x83, 0xC3}, //3,8
  {0xFE, 0x80, 0xA0, 0x92, 0x8B, 0x87, 0x9F, 0x0F}  //4,9
};
const byte Char[27][9] = {
  { //A
    B00111100,
    B01111110,
    B01100110,
    B01100110,
    B01111110,
    B01111110,
    B01100110,
    B01100110
  },

  { //B
    B01111100,
    B01100110,
    B01100110,
    B01111110,
    B01111110,
    B01100110,
    B01100110,
    B01111100
  },

  { //C
    B00011100,
    B00111110,
    B01100110,
    B01100000,
    B01100000,
    B01100110,
    B00111110,
    B00011100
  },

  { //D
    B01111100,
    B01111110,
    B01100111,
    B01100011,
    B01100011,
    B01100111,
    B01111110,
    B01111100
  },

  { //E
    B01111110,
    B01111110,
    B01100000,
    B01111110,
    B01111110,
    B01100000,
    B01111110,
    B01111110
  },

  { //F
    B01111110,
    B01111110,
    B01100000,
    B01111100,
    B01111100,
    B01100000,
    B01100000,
    B01100000
  },

  { //G
    B00011100,
    B00111110,
    B01100110,
    B01100000,
    B01100000,
    B01100111,
    B00111111,
    B00011101
  },


  { //H
    B01100110,
    B01100110,
    B01100110,
    B01111110,
    B01111110,
    B01100110,
    B01100110,
    B01100110
  },

  { //I
    B00111100,
    B00111100,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00111100,
    B00111100
  },

  { //J
    B00011110,
    B00011110,
    B00001100,
    B00001100,
    B00001100,
    B01101100,
    B01111100,
    B00111000
  },

  { //K
    B01100011,
    B01100110,
    B01101100,
    B01111000,
    B01111000,
    B01101100,
    B01100110,
    B01100011
  },

  { //L
    B00110000,
    B00110000,
    B00110000,
    B00110000,
    B00110000,
    B00110000,
    B00111110,
    B00111110
  },

  { //M
    B01111110,
    0377,
    B11011011,
    B11011011,
    B11011011,
    B11011011,
    B11011011,
    B11011011
  },

  { //N

    B11000011,
    B11100011,
    B11110011,
    B11011011,
    B11001111,
    B11000111,
    B11000011,
    B11000001
  },

  { //O
    B00111100,
    B01111110,
    B11100111,
    B11000011,
    B11000011,
    B11100111,
    B01111110,
    B00111100
  },

  { //P
    B01111100,
    B01111110,
    B01100011,
    B01100011,
    B01111110,
    B01111100,
    B01100000,
    B01100000
  },

  { //Q
    B00111100,
    B01111110,
    B11100111,
    B11000011,
    B11001011,
    B11100111,
    B01111110,
    B00111101
  },

  { //R
    B01111100,
    B01111110,
    B01100110,
    B01100110,
    B01111100,
    B01111000,
    B01101100,
    B01100110
  },


  { //S
    B00111100,
    B01100110,
    B01110010,
    B00111000,
    B00011100,
    B01001110,
    B01100110,
    B00111100
  },

  { //T
    B01111110,
    B01111110,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000
  },

  { //U
    B01100110,
    B01100110,
    B01100110,
    B01100110,
    B01100110,
    B01100110,
    B01111110,
    B00111100
  },

  { //V
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B11000011,
    B01100110,
    B00111100,
    B00011000
  },

  { //W
    B11000011,
    B11000011,
    B11000011,
    B11011011,
    B11011011,
    B11011011,
    B11111111,
    B0111110
  },

  { //X
    B01000010,
    B01100110,
    B00111100,
    B00011000,
    B00011000,
    B00111100,
    B01100110,
    B01000010
  },

  { //Y
    B01100110,
    B01100110,
    B01111110,
    B00111100,
    B00011000,
    B00011000,
    B00011000,
    B00011000
  },

  { //Z
    B01111110,
    B01111110,
    B00000100,
    B00001000,
    B00010000,
    B00100000,
    B01111110,
    B01111110
  }
};

const byte NUM[][9] = {
  { //0
    B00111100,
    B01111110,
    B01100110,
    B01100110,
    B01100110,
    B01100110,
    B01111110,
    B00111100
  },
  { //1
    B00011000,
    B00111000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00111100,
    B00111100
  },
  { //2
    B00111100,
    B01100110,
    B01000110,
    B00001100,
    B00011000,
    B00110000,
    B01111110,
    B01111110
  },
  { //3
    B00111100,
    B01111110,
    B01000110,
    B00001100,
    B00001100,
    B01000110,
    B01111110,
    B00111100
  },
  { //4
    B00000100,
    B00001100,
    B00010100,
    B00100100,
    B01111110,
    B01111110,
    B00000100,
    B00000100
  },
  { //5
    B01111110,
    B01111110,
    B01100000,
    B01111100,
    B01111110,
    B00000110,
    B01100110,
    B00111100
  },
  { //6
    B00111100,
    B01100110,
    B01100000,
    B01111100,
    B01111110,
    B01100110,
    B01100110,
    B00111100
  },
  { //7
    B01111110,
    B01111110,
    B00000110,
    B00001100,
    B00001100,
    B00011000,
    B00011000,
    B00011000
  },
  { //8
    B00111100,
    B01100110,
    B01100110,
    B00111100,
    B00111100,
    B01100110,
    B01100110,
    B00111100
  },
  { //9
    B00111100,
    B01100110,
    B01100110,
    B01111110,
    B00111110,
    B00000110,
    B01100110,
    B00111100
  }
};
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
  SendPackets(0x0A, 0);//light intensity (0-15)
  SendPackets(0x0B, 7);         //scan limit: all digits ON
  SendPackets(0x0C, 1);         //turn ON MAX7219
}
void Witsanu::Brightness(byte brightness) {
  SendPackets(0x0A, brightness);//light intensity (0-15)
}
//-------------------------------------------------------------
void Witsanu::Clear()
{
  for (byte i = 0; i < 8; i++) SendPackets(i + 1, 0);
}
//--------------------------------------------------------------
void Witsanu::Clear(int TimeDelay) {
  for (int j = 0; j < 8; j++) {
    SendPackets(j + 1, c[j]);
  }
  delay(TimeDelay);
}
//--------------------------------------------------------------
void Witsanu::Triangle(int TimeDelay) {
  for (int j = 0; j < 8; j++) {
    SendPackets(j + 1, tri[j]);
  }
  delay(TimeDelay);
}
//--------------------------------------------------------------
void Witsanu::Text(char text[], int TimeDelay) { //text,time
  for (int i = 0; i < str_length(text); i++) { //loop word

    for (int j = 0; j < 8; j++) {
      if (text[i] > 90)text[i] -= 32;
      SendPackets(j + 1, Char[text[i] - 65][j]);
    }
    delay(TimeDelay);
    Clear(5);
  }
}
void Witsanu::NumberAndPic(int number, int TimeDelay) { //number
  char cstr[4];
  sprintf(cstr, "%04d", number);
  for (int i = 0; i < 4; i++) { //loop word

    for (int j = 0; j < 8; j++) SendPackets(j + 1, NUM[cstr[i] - '0'][j]);
    delay(TimeDelay);
    Clear(5);
  }
  for (int j = 0; j < 8; j++) SendPackets(j + 1, PIC[(cstr[3] - '0') % 5][j]);
  delay(TimeDelay);
}
//--------------------------------------------------------------
void Witsanu::FullCombo(char Name[], int pa) {
  Triangle(1000);
  Clear(1);
  Text(Name, 1000);
  NumberAndPic(pa, 1000);
}
//--------------------------------------------------------------
// Debug
//--------------------------------------------------------------
void Witsanu::CheckChar() {
  for (byte i = 0; i < 27; i++) { //loop word
    for (byte j = 0; j < 8; j++) {
      SendPackets(j + 1, Char[i][j]);
    }
    delay(1000);
    Clear(5);
  }
}
//-------------------------------------------------------------
void Witsanu::CheckChar(int index) {
  for (byte j = 0; j < 8; j++) {
    SendPackets(j + 1, Char[index - 1][j]);
  }
  delay(1000);
}
//-------------------------------------------------------------
void Witsanu::CheckNumber() {
  for (byte i = 0; i < 10; i++) { //loop word

    for (byte j = 0; j < 8; j++) {
      SendPackets(j + 1, NUM[i][j]);
    }
    delay(1000);
    Clear(5);
  }
}
//-------------------------------------------------------------
void Witsanu::CheckNumber(int index) {
  for (byte j = 0; j < 8; j++) {
    SendPackets(j + 1, NUM[index][j]);
  }
  delay(1000);
  Clear(5);

}
//-------------------------------------------------------------
void Witsanu::CheckPic() {
  for (byte i = 0; i < 5; i++) { //loop word
    for (byte j = 0; j < 8; j++) {
      SendPackets(j + 1, PIC[i][j]);
    }
    delay(1000);
  }
}
//-------------------------------------------------------------
void Witsanu::CheckPic(int index) {

  for (int j = 0; j < 8; j++) {
    SendPackets(j + 1, PIC[index][j]);
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
    digitalWrite(CLK, LOW);                  //CLK low pulse

    if (data & 0x80) digitalWrite(DIN, HIGH); //o/p high if MSB = 1
    else digitalWrite(DIN, LOW);             //o/p low if MSB = 0

    digitalWrite(CLK, HIGH);                 //CLK high pulse
    data = data << 1;                         //shift data left one bit
  }
}
//--------------------------------------------------------------
int Witsanu::str_length(char str[]) {
  int count;
  for (count = 0; str[count] != '\0'; ++count);
  return count;
}
