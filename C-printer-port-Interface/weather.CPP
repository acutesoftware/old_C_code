// LPT_OP.CPP
// written by Duncan Murray 4/3/1999  (c) Acute Software 1999
//  This program is part of a test suite to enable the LPT port of
//  of a PC to control the gadgets designed by Acute Software.

#include "WEATHER.HH"

#include <graphics.h>
//#include <stdlib.h>
//#include <conio.h>
//#include <iostream.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#include <iostream.h>
//#include <stddef.h>
#include <dos.h>
#include <stdio.h>
#include <alloc.h>
#include <math.h>


#include "USER_IF.hh"
#include "WTHR_SCN.hh"
int box_x = 12;	    /* starting 'x' pos of data box		*/
int box_y = 11;	    /* starting 'y' pos of data box		*/
int stat_x = 2;     /* starting point for status box		*/
int stat_y = 3;	    /* starting point for status box		*/
char ms[80];	/* message text declared in DECENTOC.C	*/
char logfile[80];
char date[26];	    /* date time stuff	*/
int maxx, maxy;

//int scans[2000][4];
int scans[2000];



int main(void)
{
    char *currenttime;	    /* current time/date string	*/
    int	old_sec = 0;
//    int cur_hour = 0;	    /* current hour			*/
//    int cur_day = 0;	    /* current current day		*/
    int result = 0;
    int key = 0;
    Initialise();		// turn outputs on and off for 1 second
    InitDisplay();
    int keepgoing = 1;	    /* tells program to keep running until ESC pressed */
    while ( keepgoing == 1 )
    {

	currenttime = thetime();    /* get the current time	*/
	cur_sec = extract_num(currenttime, 18, 2); /* extract minute	*/
	cur_min = extract_num(currenttime, 15, 2); /* extract minute	*/
	cur_hour = extract_num(currenttime, 12,2); /* extract hour	*/
	//cur_day = extract_num(currenttime, 9, 2);  /* extract day	*/

	if(old_sec != cur_sec) {	/* only update screen once per second	*/
	    ReadAnalogInputs(3);
	    DisplayAnalogValues(3);
 //	    ReadDigitalInputs(3);
      //	    DisplayDigitalInputs(3);
	 //   locate( 25, 56);
	    color(CF_SETTINGS,CB_SETTINGS);
//	 //   cprintf(currenttime);	/* update current time on screen	*/
	    //locate(20,1);cprintf("cur_min=%d",cur_min);
	    old_sec = cur_sec;
	    //  EVENTS (new function)
	    //OutputBit(0,valueInput[0]);
	    //OutputBit(1,valueInput[1]);
	    //OutputBit(2,valueInput[2]);
	    //OutputBit(3,valueInput[3]);

	    if (valueInput[1] == 1) {
		WritePort(1);
		DisplayPort(1,XOUTPUT,YOUTPUT);
	    }
	    if (valueAnalog[0] < 50) {
	       //	WritePort(16);
	       //	DisplayPort(16,XOUTPUT,YOUTPUT);
	    }
	Log("e:\\user\\c\\a_pcio\\logfile.log", currenttime);
	}

	if( kbhit() ) {
	    result = getkeypressed();	/* get a single keypress    */

	    switch (result)  {		/* perform task user pressed	*/
		case 27: {		/* ESC	*/
		    Message( "Do you really want to quit? (Y/n) " , 0);
		    key = getch();
		    if( ( key  == 'Y') || (key =='y') || (key == 13) )
			keepgoing = 0;	/* stop program execution	*/
		    Message("", 0);
		}
		break;
		case 68: {		/* F10	*/
		    Message("Setup", 0);
		    //locate(12,65); scanf("%d", &gPORT);   // port change
		    locate(11, 62);
		    color(CF_SETTINGS,CB_SETTINGS);
	//	    color(YELLOW,BLACK);
		    cprintf("Enter new settings");
		    locate(13,75); scanf("%d", &gCounter);   // port change
		    if(gCounter<0||gCounter>999) gCounter=10; else fflush(stdin);
		    locate(14,75); scanf("%d", &gSpeed);   // port change
		    if(gSpeed<0||gSpeed>999) gSpeed=10; else fflush(stdin);
		    locate(15,75); scanf("%d", &gPulse_fast);   // port change
		    if(gPulse_fast<0||gPulse_fast>999) gPulse_fast=10; else fflush(stdin);
		    locate(16,75); scanf("%d", &gPulse_slow);   // port change
		    if(gPulse_slow<0||gPulse_slow>999) gPulse_slow=10; else fflush(stdin);
		    locate(17,75); scanf("%d", &gIterations);   // port change
		    if(gIterations<0||gIterations>999) gIterations=10; else fflush(stdin);

		    DisplaySettings(XSETTINGS,YSETTINGS);
		}
		break;
		case 48: { OutputBit(0,2); DisplayPort(1,XOUTPUT,YOUTPUT); } break;
		case 49: { OutputBit(1,2); DisplayPort(2,XOUTPUT,YOUTPUT); } break;
		case 50: { OutputBit(2,2); DisplayPort(4,XOUTPUT,YOUTPUT); } break;
		case 51: { OutputBit(3,2); DisplayPort(16,XOUTPUT,YOUTPUT); } break;
		case 52: { OutputBit(4,2); DisplayPort(32,XOUTPUT,YOUTPUT); } break;
		case 53: { OutputBit(5,2); DisplayPort(64,XOUTPUT,YOUTPUT); } break;
		case 54: { OutputBit(6,2); DisplayPort(128,XOUTPUT,YOUTPUT); } break;
		case 55: { OutputBit(7,2); DisplayPort(255,XOUTPUT,YOUTPUT); } break;

		case 43: { WritePort(++valueOutput[0]); } break;
		case 45: { WritePort(--valueOutput[0]); } break;

	    }

	}
    }
 return 0;

}




void OutputBit(int bit,int val)
{
   // calculate mask
   int mask = 0;
   for(int i=0; i<=bit; i++)
   {
	mask = mask * 2+1;    //almost works
   }
   mask++;
   mask=mask/2;

   locate(25,1);
   cprintf("bit=%d mask=%d val=%d",bit,mask,val);
   switch (val)
   {
	case 2:	// toggle output bit
	{
	   valueOutput[0] = valueOutput[0] ^ mask;
	}
	break;
	case 1:	// turn BIT ON
	{
	   valueOutput[0] = valueOutput[0] ^ mask;

	}
	break;

	case 0: // turn BIT OFF
	{
	   mask = ~mask;
	   valueOutput[0] = valueOutput[0] ^ mask;

	}
	break;
   }
   WritePort(valueOutput[0]);

}

int  WritePort(int value)
{
 //cout << "Outputting : " << value << endl;
   ;
   asm  {   // taken from book 'The C Toolbox, page 264
	mov	dx, gPORT
	mov	ax, value
	out dx,al
   }
   if(value < 0) value = 255;
   if(value >255) value = 0;
   valueOutput[0] = value;
   DisplayPort(value,XOUTPUT,YOUTPUT);
 return 0;
}


void Initialise(void)		// turn outputs on and off for 1 second
{
 for(int i=0;i<4;i++)
 {
	valueAnalogMin[i]=1000000000;   // set min value to half
	valueAnalogMax[i]=0;   // set max value to half
 }
// color(BLUE,CYAN);
 color(CF_SETTINGS,CB_SETTINGS);

}

void TestMaxSpeed(int)		// see how fast it can pulse
{
 DisplayPort(1,XOUTPUT,YOUTPUT);
 while(1)  {
	WritePort(1);
	WritePort(0);   // test max freq
	if( kbhit() ) break;

 }

 DisplayPort(0,XOUTPUT,YOUTPUT);

}




void ReadDigitalInputs(int num)
{

	union REGS regs;
	int val;
	regs.x.dx = 0;	// read digital port settings from Joystick
	regs.h.ah = 0x84;
	int86(0x15,&regs,&regs);

	val = regs.h.al;
	val = ~val;
	//locate(24,10); cprintf("INPUT VAL = %d",val);
	val>>=1;   // shift to the last 4 bits
	val>>=1;
	val>>=1;
	val>>=1;
	for(int i=num; i>=0; i--,val>>=1)
	{
		valueInputOld[i] = valueInput[i];
		if(val & 1)
		{
			valueInput[i] = 1;
			if (valueInputOld[i] == 0) // if changed
			{                         // clock on RISING pulse
				valueInputCount[i]++;
				valueInputOld[i] = 1; //valueInput[i];
				valueInputTimeHour[i]=cur_hour;
				valueInputTimeMin[i]=cur_min;
			     //cout << valueInputTimeMin[i] << endl;
				valueInputTimeSec[i]=cur_sec;
			}

		}
		else
		{
			valueInput[i] = 0;
		}



		//val>>=1;
	}
	//valueInput[1] = val &1; val>>=1;
	//valueInput[2] = val &1; val>>=1;
	//valueInput[3] = val &1; val>>=1;

}


int ReadAnalogInputs(int num)
{

	union REGS regs;

	regs.x.dx = 1;	// read analog port settings
	regs.h.ah = 0x84;
	int86(0x15,&regs,&regs);

	if(regs.x.cflag)  Message("Error calling int15",0);
       //	switch (port)
       //	{
       //		case 1: result = regs.h.ah;	break;
       //		case 2: result = regs.h.bh;	break;
       //		case 3: result = regs.h.ch;	break;
       //		case 4: result = regs.h.dh;	break;
       //		default: result =351;		break;
       //	}
	locate (15, 1);
	valueAnalog[0] = ConvertToTemperature(regs.x.ax);
	locate (16, 1);
	valueAnalog[1] = ConvertToTemperature(regs.x.bx);
	locate (17, 1);
	valueAnalog[2] = regs.x.cx;
	locate (18, 1);
	valueAnalog[3] = regs.x.dx;
	//----------------- added for temp. conversion



	for(int i=0; i<=num; i++)
	{
		if(valueAnalog[i] < valueAnalogMin[i])
		{
			valueAnalogMin[i]=valueAnalog[i]; //new MIN
		}
		if(valueAnalog[i] > valueAnalogMax[i])
		{
			valueAnalogMax[i]=valueAnalog[i]; //new MAX
		}

	}
	return 0;

}



float ConvertToTemperature(int val)
{
	// main routine to convert the int from the joystick port
	// into a temperature
	float result =0;

	float RESISTANCE = 0;
	float VOLTAGE_RESOLUTION = 0.0195312;
    //	cprintf( "nVOLTAGE_RESOLUTION=%f",VOLTAGE_RESOLUTION );
	// first calculate the resistance from the value read by port
	// 0V = 0
	// 5V = 256  in 3.9062mV resolutions

	float VOLTS = val * VOLTAGE_RESOLUTION ;
	float CURRENT = ( 5 - VOLTS ) / 2136;
	RESISTANCE = VOLTS / CURRENT;

       //	RESISTANCE = 256 / log(val) ;

	result=4500/(log((RESISTANCE/0.0277))) - 273.14;
	cprintf("\nvalue=%d VOLTS=%f CURRENT=%f RESISTANCE=%f TEMP=%f",val,VOLTS,CURRENT,RESISTANCE,result);

	// now convert resistance of thermistor to Degrees
	result = RESISTANCE;





	return result;



}