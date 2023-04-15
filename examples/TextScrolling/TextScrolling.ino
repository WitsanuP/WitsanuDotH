#include <Witsanu.h>
Witsanu disp;

void setup()
{
  disp.Set();//required in setup
  //disp.Brightness(3);//Brightness level 0-15
}
//------------------------------------------------------------
void loop()
{
  disp.TextScrolling(100, "%tHello1234%s", 4);//<time><text><...>
  //disp.TextScrolling(100, "I%pYou ", 0);
}
