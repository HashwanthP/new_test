#include <xc.h>

void init_config()
{
    TRISB = 0X00;
    PORTB = 0x00;
    TRISC = TRISC | 0X0F;
}

unsigned char read_dkp_edge()
{
    static unsigned char once = 1;
    if(((PORTC & 0x0F) != 0x0F) && once)
    {
        once = 0;
        return (PORTC & 0x0F);
    }
    else if((PORTC & 0x0F) == 0x0F)
    {
        once = 1;
    }
    return 0x0F;
}

void main(void)
{   
    init_config();
    unsigned int pattern = 0;
    unsigned int delay = 0;
    unsigned char i = 0;
    unsigned int key;
    while(1)
    {
    /*    if(RC0 == 0)
        {
            PORTB = 0x00;
            pattern = 1;
            delay = 0;
            i = 0;
        }
        else if(RC1 == 0)
        {
            PORTB = 0x00;
            pattern = 2;
            delay = 0;
            i = 0;
        }
        else if(RC2 == 0)
        {
            PORTB = 0x00;
            pattern = 3;
            delay = 0;
            i = 0;
        }
        else if(RC3 == 0)
        {
            PORTB = 0x00;
            pattern = 4;
            delay = 0;
            i = 0;
        }*/        
        key = read_dkp_edge();
        if(key != 0x0F)
        {
            pattern = key;
            PORTB = 0x00;
            i = 0;
        }
        
        if(pattern == 0x0E)
        {
            if(delay++ == 5000)
            {
                delay = 0;
                
                if(i <=7)
                {
                    PORTB = (PORTB << 1) | 1 ;
                }
                else if(i <=15)
                {
                    PORTB = PORTB << 1;
                }
                else if(i <=23 )
                {
                    PORTB = (PORTB >> 1) | (1 << 7);
                }
                else if(i <=31)
                {
                    PORTB = PORTB >> 1;
                }
                else
                {
                    i = 0;
                }
                i++;
            }
        }
        else if(pattern == 0x0D)
        {
           if(delay++ == 5000)
            {
                delay = 0;
                
                if(i <=7)
                {
                    PORTB = (PORTB << 1) | 1 ;
                }
                else if(i <=15)
                {
                    PORTB = PORTB << 1;
                }
                else
                {
                    i = 0;
                }
                i++;
            }
        }
        else if(pattern == 0x0B)
        {
            if(delay++ <= 10000)
            {
                PORTB = 0xAA;
            }
            else if(delay <= 20000)
            {
                PORTB = 0x55;
            }
            else
            {
                delay = 0;
            }
        }
        else if(pattern == 0x07)
        {
            if(delay++ <= 10000)
            {
                PORTB = 0x0F;
            }
            else if(delay <= 20000)
            {
                PORTB = 0xF0;
            }
            else
            {
                delay = 0;
            }
        }
    }
}
