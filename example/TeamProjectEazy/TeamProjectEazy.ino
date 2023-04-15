#include <Witsanu.h>
Witsanu disp;

void setup()
{
  disp.Set();//required in setup
  disp.Brightness(3);//Brightness level 0-15
}
//------------------------------------------------------------
void loop()
{
  disp.FullCombo("Hello",1234);//<name><number>
}
