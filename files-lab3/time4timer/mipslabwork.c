/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define timeP ((80000000/256) /10) //100 ms 
int mytime = 0x5957;

volatile int* trisE = (volatile int*) 0xbf886100;

char textstring[] = "text, more text, and even more text!";
int timeoutcount = 0;
/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  *trisE &= ~0xff;

  PORTD = (PORTD & 0xfffff00f) | 0xfe0;


  TMR2 = 0; //Initalize timer 2
  T2CONSET = 0x0070; //Set to prescale 1:256
  PR2 = timeP; 
  T2CONSET = 0x8000;
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  // delay( 1000 );
  if (IFS(0) & 0x100)
  {
    IFS(0) = 0;
    timeoutcount++;

    if (timeoutcount == 10)
    {
      time2string( textstring, mytime );
      display_string( 3, textstring );
      display_update();
      tick( &mytime );
      *trisE += 0x1;
      timeoutcount = 0; 
    }

      display_image(96, icon);

  int btnValue = getbtns();
  int swValue = getsw();

  if (btnValue == 4)
  {
    mytime = (swValue << 12) | (mytime & 0x0fff);
  }

    if (btnValue == 2)
  {
    mytime = (swValue << 8) | (mytime & 0xf0ff);
  }

    if (btnValue == 1)
  {
    mytime = (swValue << 4) | (mytime & 0xff0f);
  }
  if (btnValue == 6)
  {
    mytime = (swValue << 12) | (mytime & 0x00ff) | (swValue << 8);

  }
  if (btnValue == 5)
  {
    mytime = (swValue << 12) | (mytime & 0x0f0f) | (swValue << 4);
  }

  if (btnValue == 3)
  {
    mytime = (swValue << 4) | (mytime & 0xf00f) | (swValue << 8);
  }
  if (btnValue == 7)
  {
    mytime = (swValue << 4) | (mytime & 0x000f) | (swValue << 8) | (swValue << 12);
    
  } 

  }
  

}
