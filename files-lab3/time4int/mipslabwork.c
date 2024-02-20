/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog

   For copyright and licensing, see file COPYING */

#include <stdint.h>  /* Declarations of uint_32 and the like */
#include <pic32mx.h> /* Declarations of system-specific addresses etc */
#include "mipslab.h" /* Declatations for these labs */

#define timeP ((80000000 / 256) / 10) // 100 ms
int mytime = 0x5957;
int prime = 1234567;

volatile int *trisE = (volatile int *)0xbf886100;
volatile int* portE = (volatile int*) 0xbf886110;


char textstring[] = "text, more text, and even more text!";
int timeoutcount = 0;
int count = 0; 

/* Interrupt Service Routine */
void user_isr(void)
{

  if (IFS(0) & 0x100)
  {
    IFS(0) = 0; 
    timeoutcount++;     

    if (timeoutcount == 10)
    {
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);
      timeoutcount = 0; 

    }
  }
//lab3
  // if (IFS(0) & 0x00080000)
  // {
  //   IFS(0) = 0; 

  // }

//lab2 delay

}

/* Lab-specific initialization goes here */
void labinit(void)
{
  *trisE = ~0xff & *trisE;

  PORTD = (PORTD & 0xfffff00f) | 0xfe0;

  TMR2 = 0;          // Initalize timer 2
  T2CONSET = 0x0070; // Set to prescale 1:256
  PR2 = timeP;
  T2CONSET = 0x8000;

  IPCSET(2) = 6; //Priority 
  IECSET(0) = 0x100; //Enable interrupt

  IPCSET(4) = 0x10000000; // Prioierty
  IECSET(0) = 0x00080000; //

  enable_interrupt();
  return;
}

/* This function is called repetitively from the main program */
void labwork(void)
{
  prime = nextprime(prime);
  display_string(0, itoaconv(prime));
  display_update();
}
