#include <Witsanu.h>

Witsanu disp;

void setup()
{
    disp.Set(); //set brightness level 1 (1-->15)
    disp.Brightness(1);
}
//------------------------------------------------------------
void loop()
{
    disp.FullCombo("witsanu",1005);
}
