#include "i7188.h" 
int quit = 0;    
int LedMode = 0;  
int data;           
unsigned long time; 

int main(void) 
{
    
    TimerOpen();       
    StopWatchStart(0); 
    LedOff();          

    while (!quit)
    {
        StopWatchReadValue(0, &time); 
        if (LedMode == 0 && time >= 2000) 
        {
            LedOn();
            LedMode = 1; 
            StopWatchStart(0); 
        }
        else if (LedMode == 1 && time >= 3000) 
        {
            LedOff();
            LedMode = 0; 
            StopWatchStart(0); 
        }
        
        if (Kbhit())
        {                   
            data = Getch(); 
            if (data == 'q' || data == 'Q')
                quit = 1; 
            else
            {
                Putch(data);
                if (data == '\r')
                    Putch('\n');
            }
        }
    }
    
    TimerClose(); 
}

