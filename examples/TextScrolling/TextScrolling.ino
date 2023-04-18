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
/*
  TextScrolling(TimeDelay, text[], ...);

    TimeDelay   : Time per frame(ms)
    text[]      : "text" //can use %s, %p %t
            mean        value
        %t  triangle    None
        %s  sign        0-4
        %p  picture     0-10
         +-----------------------------------+
         |  <value>     <picture>            |   
         |     0          Heart              |    
         |     1          Apple              |     
         |     2          Moon               |    
         |     3          Cat                |   
         |     4          Pumpkin head       |            
         |     5          Smile circle       |            
         |     6          Flat circle        |           
         |     7          Sad circle         |          
         |     8          Smile square       |            
         |     9          Flat square        |           
         |     10         Sad square         |           
         +-----------------------------------+
        
        Ex.
            TextScrolling(150,"Hello ");
                scrolling "Hello " with 150 time per frame(ms)
                
            TextScrolling(100, "%tHello1234%s", 4);
                scrolling "<triangle>Hello<sign4>" with 100 time per frame(ms)
                
            TextScrolling(150, "I%pYou", 0);
                scrolling "I<heart>You" with 150 time per frame(ms)
       */
