#ifndef Witsanu_h
#define Witsanu_h

//class definition
class Witsanu
{
  public:
    //constructor
    Witsanu(void);
    
    //setup
    void Set();
    void Brightness(byte brightness);
    void Clear();
    void Clear(int TimeDelay);
    
    //methods
    void Triangle(int TimeDelay);
    void Text(char text[], int TimeDelay);
    void NumberAndPic(int number, int TimeDelay);
    void FullCombo(char Name[], int Num);
    void TextScrolling(int TimeDelay, const char *text, ...);
    
    //debug
    void CheckCapLetter();
    void CheckCapLetter(int index);
    void CheckNumber();
    void CheckNumber(int index);
    void CheckSign();
    void CheckSign(int index);
    void CheckSmallLetter();
    void CheckSmallLetter(int index);
    
    //Feature in Future
    //void Byte(byte row, byte value);
  private:
    //fucntion commutication
    void SendPackets(byte cmd, byte data);
    void SPI_send(byte data);
    
    //function 
    //int str_length(char str[]) ;//deleted
    
    //use in TextScrolling()
    byte **ArrayText;//use in Funcion CopyArray, CreartArray
    void CopyArray(const int a, const int b, byte a2[][8]);
    int CountRealLetter(char *text);
};
#endif
