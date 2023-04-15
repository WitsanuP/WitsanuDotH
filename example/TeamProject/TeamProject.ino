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
  disp.Triangle(1000);
  disp.Text("Hello", 1000);
  disp.NumberAndPic(1234, 1000);
}
