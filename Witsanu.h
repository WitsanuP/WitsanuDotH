#ifndef Witsanu_h
#define Witsanu_h
//--------------------------------------------------------
//class definition
class Witsanu
{
  public:
    //constructor
    Witsanu(void);
    //methods
    void Set();
    void Brightness(byte brightness);
    void Clear();
    void Clear(int TimeDelay);
    void Triangle(int TimeDelay);
    void Text(char text[], int TimeDelay);
    void NumberAndPic(int number, int TimeDelay);
    void FullCombo(char Name[], int pa);
    //debug
    void CheckChar();
    void CheckChar(int index);
    void CheckNumber();
    void CheckNumber(int index);
    void CheckPic();
    void CheckPic(int index);
    
    //Feature in Future
    //void Number(byte n);
    //void Letter(char l);
    //void Byte(byte row, byte value);
  private:
    //fucntion
    void SendPackets(byte cmd, byte data);
    void SPI_send(byte data);
    int str_length(char str[]) ;
};
#endif
