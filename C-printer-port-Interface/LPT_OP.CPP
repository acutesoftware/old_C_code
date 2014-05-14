// LPT_OP.CPP
// written by Duncan Murray 4/3/1999  (c) Acute Software 1999
//  This program is part of a test suite to enable the LPT port of
//  of a PC to control the gadgets designed by Acute Software.

#include "LPT_OP.HH"

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


#include "USER_IF.hh"
#include "PCIO_SCN.hh"
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
	    ReadDigitalInputs(3);
	    DisplayDigitalInputs(3);
	    locate( 25, 56);
	    color(CF_SETTINGS,CB_SETTINGS);
	    cprintf(currenttime);	/* update current time on screen	*/
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
		WritePort(16);
		DisplayPort(16,XOUTPUT,YOUTPUT);
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

		case 59: {		/* F1	*/
		    Message("Initialising",0);
		    Message("Fast Pulse", 0);
		    Pulse(255, gPulse_fast);
		}
		break;

		case 60: {		/* F2	*/
		    Message("Storage CRO - enter settings", 0);
		    //getch();
		    gotoHiResMode();
		    DrawOscilliscopeScreen(50,0,550,255,50,51);
		    StorageOscilliscope("waiting for trigger", 1, 0, 220, 40, 0, 499);
		    InitDisplay();

		}
		break;

		case 61: {		/* F3	*/
		    gotoHiResMode();
		    DrawOscilliscopeScreen(100,100,355,355,20,32);
		    Oscilliscope();

		    InitDisplay();
		    Message("Oscilliscope", 0);
		     Pulse(255, gPulse_slow);
		}
		break;

		case 62: {		/* F4	*/
		    Message("BinaryCount", 0);
		    BinaryCount(gCounter);
		}
		break;

		case 63: {		/* F5	*/
		    Message("Chase Multiple", 0);
		    ChaseMultiple(gIterations, gSpeed);

		}
		break;
		case 64: {		/* F6	*/
		    Message("Chase Up", 0);
		    Chase(gSpeed, 0, 7);

		}
		break;
		case 65: {		/* F7	*/
		    Message("Chase Down", 0);
		    Chase(gSpeed, 7,0);

		}
		break;
		case 66: {		/* F8	*/
		    Message("Reading Analog inputs", 0);
		    ReadAnalogInputs(3);
		    DisplayAnalogValues(3);
		    ReadDigitalInputs(3);
		    DisplayDigitalInputs(3);
		}
		break;
		case 67: {		/* F9	*/
		    Message("Logging - PRESS A KEY TO STOP", 0);
		    FastAcquisition("e:\\user\\c\\a_pcio\\fastlog.log", currenttime);
		    Message("Done Logging to e:\user\c\a_pcio\fastlog.log", 0);
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
   // calculate mask return
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

void BinaryCount(int num)
{
 for (int i=0; i<=num; i++)
	{
	WritePort(++valueOutput[0]);
       //	DisplayPort(i);
	wait(gSpeed);
	}
}


void Chase(int speed, int startbit, int stopbit)
{
	int value = 0;
	if(startbit > stopbit) {     // CHASE DOWN
		//value = 2^(startbit); //128;
		switch(startbit) {
		  case 7:		value = 128; break;
		  case 3:		value =8;	break;
		  default:	value =1;
		}
		for (int i=startbit; i>=stopbit; i--)
		{
			//gotoxy(10, 10+i);
			//printf("start=%d  stop=%d, i=%d, value=%d",startbit,stopbit,i,value);
			WritePort(value);
			value >>= 1;
			wait(speed);
		}
	}
	else
	{      // Chase Up
		switch(startbit) {
		  case 0:		value = 1; break;
		  case 3:		value =8;	break;
		  default:	value =1;
		}



	//	value = 2^(startbit);
		for (int i=startbit; i<=stopbit; i++)
		{
			WritePort(value);
			value <<= 1;
			wait(speed);
		}
	}

	WritePort(0);
}


void ChaseMultiple(int speed, int iterations)
{
	for (int i=0; i<=iterations; i++)
	{

		Chase(speed, 0, 3);
		Chase(speed, 3, 0);
	}

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
 DisplayPort(255,XOUTPUT,YOUTPUT);
 WritePort(255);
 wait(100);
 DisplayPort(0,XOUTPUT,YOUTPUT);
 WritePort(0);
 for(int i=0;i<4;i++)
 {
	valueAnalogMin[i]=255;   // set min value to half
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

void Pulse(int value, int len) 	// pulse output port for x milliseconds
{


    WritePort(0);    	// turn ports off
    WritePort(value);	// start pulse
    for (int i=0; i<len; i++)
	wait(1);
    WritePort(0);




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
	valueAnalog[0] = regs.x.ax;
	valueAnalog[1] = regs.x.bx;
	valueAnalog[2] = regs.x.cx;
	valueAnalog[3] = regs.x.dx;


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


void FastAcquisition(char filename[80], char msg[80])
{
    char *currenttime;	    /* current time/date string	*/

    long count = 0;
    FILE *logfileptr;
    logfileptr = fopen(filename, "w");
    if (logfileptr == NULL)
    {
	Message("Cant open %s for output", 1);
    } /* end if */
    else
    {

	fprintf(logfileptr, "Started Logging on %s \n", msg);
	fprintf(logfileptr, "count,hh,mm,ss,AD1,AD2,AD3,AD4,IP1,IP2,IP3,IP4\n", msg);

	while(1)
	{
		ReadAnalogInputs(3);
		ReadDigitalInputs(3);
		fprintf(logfileptr, "%6.6u,",count);
		fprintf(logfileptr, "%2.2d,%2.2d,%2.2d,",cur_hour,cur_min,cur_sec);
		fprintf(logfileptr, "%3.3d,",valueAnalog[0]);
		fprintf(logfileptr, "%3.3d,",valueAnalog[1]);
		fprintf(logfileptr, "%3.3d,",valueAnalog[2]);
		fprintf(logfileptr, "%3.3d,",valueAnalog[3]);
		fprintf(logfileptr, "%1.1d,",valueInput[0]);
		fprintf(logfileptr, "%1.1d,",valueInput[1]);
		fprintf(logfileptr, "%1.1d,",valueInput[2]);
		fprintf(logfileptr, "%1.1d\n",valueInput[3]);
		count++;

		if( kbhit() ) break;
		if(count % 100 == 0)	// every 100 readings, update time
		{
			fprintf(logfileptr, "updating time (100 readings since last time update)\n");
			currenttime = thetime();    /* get the current time	*/
			cur_sec = extract_num(currenttime, 18, 2); /* extract minute	*/
			cur_min = extract_num(currenttime, 15, 2); /* extract minute	*/
			cur_hour = extract_num(currenttime, 12,2); /* extract hour	*/
		}

	}

	fprintf(logfileptr, "Logging stopped at %s \n", msg);

	fclose(logfileptr);
    } /* end elseif */





}


void Oscilliscope(void)
{

	//getviewsettings

	union REGS regs;
	void far *ptr[4];
	char tmp[6];

	/* draw a line */
   //	int xx = getmaxx();
    //	int yy = getmaxy();
	int x = 1;
	int y = 1;
	settextstyle(4,0,20);
	outtextxy(100,30,"Digital Oscilliscope");
	settextstyle(4,0,10);
	outtextxy(400,150,"ADC1=");
	outtextxy(400,200,"ADC2=");
	outtextxy(400,250,"ADC3=");
	outtextxy(400,300,"ADC4=");

	save_screen(ptr);    /* save the current screen */

	setcolor(0);

	while(1)	// as long as user doesnt press a key
	{
	       //	cleardevice();
		for(x=100; x<355; x=x+2)
		{
			regs.x.dx = 1;	// read analog port settings
			regs.h.ah = 0x84;
			int86(0x15,&regs,&regs);

			//if(regs.x.cflag)  Message("Error calling int15",0);

		       //	ReadAnalogInputs(3);
			//y = valueAnalog[0] * 1.5 + 10;
			//if(y>yy) y=yy;
			//if(x>xx) x=xx;
			//putpixel(x,y-1, 3);
			//setlinestyle(1, 1, 1);
			//setcolor(7);
			line(x+1,100,x+1,355);   // clear old point
			setfillstyle(0,0);
			bar(500,140,540,350);

			setcolor(10);
			y = regs.x.ax;
			itoa(y,tmp,10);
			outtextxy(507,150,tmp);
			setcolor(0);
			putpixel(x+1,y+50,10);
			setcolor(11);

			y = regs.x.bx;  itoa(y,tmp,10);
			outtextxy(507,200,tmp);
			setcolor(0);
			putpixel(x+1,y+100,11);

			setcolor(12);

			y = regs.x.cx;  itoa(y,tmp,10);
			outtextxy(507,250,tmp);
			setcolor(0);
			putpixel(x+1,y+150,12);

			setcolor(14);

			y = regs.x.dx;  itoa(y,tmp,10);
			outtextxy(507,300,tmp);
			setcolor(0);

			putpixel(x+1,y+200,14);

			//putpixel(x-1,y, 4);
			//putpixel(x,y+1, 7);
		       //	outtextxy(507,200,);
		       //	outtextxy(507,250,);
		       //	outtextxy(507,300,);

		}
		if( kbhit() )
		{
			save_screen(ptr);
			getch();
			break;
		}


		//wait(600);
       //		restore_screen(ptr); /* restore the screen */

	       //	sound(7);

	}

	/* clean up */
	closegraph();

//	textmode(C80);


}

int gotoHiResMode(void)
{
	/* request auto detection */
	int gdriver = DETECT, gmode, errorcode;


	//cout << "gdriver = " << gdriver << endl;
	//cout << "gmode  = " << gmode << endl;
	//getch();
	/* initialize graphics mode */
	//initgraph(VGA);
	initgraph(&gdriver, &gmode, "");
	/* read result of initialization */
	errorcode = graphresult();

	if (errorcode != grOk)  /* an error occurred */
	{
	   printf("Graphics error: %s\n", grapherrormsg(errorcode));
	   printf("Press any key to halt:");
	  // getch();
	   exit(1);             /* return with error code */
	}


 return 0;
}

void DrawOscilliscopeScreen(int x, int y, int xx, int yy, int xgrid,int ygrid)
{
	setcolor(LIGHTGRAY);   // draw grid
	setlinestyle(0x1111, 1, 1);
	for (int a=x; a<xx; a+=xgrid)
	{
		line(a, y, a, yy); //draw vert line

	}
	line(x, yy, xx, yy); //draw vert line
	for(int b=y; b<yy; b+=ygrid)
	{
		line(x, b, xx, b); //draw horiz line
	}

	line(xx+1, y, xx+1, yy); //draw vert line

	setcolor(3);
	outtextxy(1,0,"+5.0V");
	outtextxy(1,50,"+4.0V");
	outtextxy(1,100,"+3.0V");
	outtextxy(1,150,"+2.0V");
	outtextxy(1,200,"+1.0V");
	outtextxy(1,250," 0.0V");




}

void StorageOscilliscope(char* msg,
			int channel,	// which channel to read
			int trigChannel,// which channel will do trigger
			int trigHI,	// how HI before reading starts
			int trigLO,	// how LO before reading starts
			int timebase,	// pause between readings
			int numScans)	// number of readings to do
{
     union REGS regs;
     union REGS regT;
     char message[80];
     int result = 0;
     int keepgoing=1;
     int startSec = 0;
     int startMs = 0;
     int startMin = 0;
     int stopMin = 0;
     int stopSec = 0;
     int stopMs = 0;
     int stopHr = 0;
     int startHr = 0;
     long temp = 0;		// elapsed time in milliseconds
     long mS_START = 0;
     long mS_STOP = 0;
     long uS_per_div = 0;
 //	settextstyle(4,0,10);
 //	outtextxy(400,150,"ADC1=");
     nosound();
     while(keepgoing == 1)
     {


	  ReadAnalogInputs(3);
	  if (valueAnalog[trigChannel] < trigLO || valueAnalog[trigChannel] > trigHI)
	  {
		// triggered, first recordd the time and do a FAST scan
		regT.h.ah =0x2c;
		int86(0x21,&regT,&regT);
		startMs = regT.h.dl;  	// record start time
		startSec = regT.h.dh;
		startMin = regT.h.cl;
		startHr = regT.h.ch;
		mS_START = (startMin*60)+(startSec*100)+startMs;

		settextstyle(4,0,20);
		message[0] = '\0';
		sprintf(message,"started %02.2d:%02.2d:%02.2d\.%02.2d",startHr,startMin,startSec,startMs);
		setcolor(12);
		outtextxy(30,290,message);


		for(int i=0;i<numScans;i++)
		{
			regs.x.dx = 1;	// read analog port settings
			regs.h.ah = 0x84;
			int86(0x15,&regs,&regs);
			scans[i] = regs.x.ax;
			//scans[i][1] = regs.x.bx;
			//if(timebase>0) wait(timebase);
		}
		//break;
	       //	setcolor(10);

		regT.h.ah =0x2c;  		// record stop time
		int86(0x21,&regT,&regT);
		stopMs = regT.h.dl;
		stopSec = regT.h.dh;
		stopMin = regT.h.cl;
		stopHr = regT.h.ch;

		mS_STOP = (stopMin*60)+(stopSec*100)+stopMs;


		//temp=351;
		message[0] = '\0';
		sprintf(message,"stopped %02.2d:%02.2d:%02.2d\.%02.2d",stopHr,stopMin,stopSec,stopMs);
		setcolor(12);
		outtextxy(30,330,message);



		setcolor(2);

		for(int j=1;j<numScans;j++)
		{
		//putpixel(j+1,scans[j]+200,11);

			line(j+49,255-scans[j-1],j+50,255-scans[j]);

		}
		//getch();
		temp = mS_STOP - mS_START;
		uS_per_div = ((temp*100000) / numScans)/100;

		setcolor(12);
		message[0] = '\0';
		sprintf(message,"Elapsed Time     = %5.5u mS",temp);
		outtextxy(300,290,message);
		sprintf(message,"Number of Pixels = %d",numScans+1);
		outtextxy(300,310,message);
		sprintf(message,"%u uS per pixel",uS_per_div);
		outtextxy(300,330,message);

	  }
	  if( kbhit() )
	  {
		result = getkeypressed();	/* get a single keypress    */
		switch (result)  		/* perform task user pressed	*/
		{
		  case 27: { keepgoing=0; } break;	// user pressed ESC
		  case 60:
		  {		// F2
			cleardevice();
			DrawOscilliscopeScreen(50,0,550,255,50,51);
			//StorageOscilliscope("waiting for trigger...", 1, 0, 220, 40, 0, 549);
		  }
		  break;
		  default: sound(300);

		}
	   }

     }

     /* clean up */
     closegraph();
     nosound();


}




void save_screen(void far *buf[4])
{
   unsigned size;
   int ystart=0, yend, yincr, block;

   yincr = (maxy+1) / 4;
   yend = yincr;
   size = imagesize(0, ystart, maxx, yend);
/* get byte size of image */

   for (block=0; block<=3; block++)
   {
      if ((buf[block] = farmalloc(size)) == NULL)
      {
	 closegraph();
         printf("Error: not enough heap space in save_screen().\n");
	 exit(1);
      }

      getimage(0, ystart, maxx, yend, buf[block]);
      ystart = yend + 1;
      yend += yincr + 1;
   }
}

void restore_screen(void far *buf[4])
{
   int ystart=0, yend, yincr, block;

   yincr = (maxy+1) / 4;
   yend = yincr;

   for (block=0; block<=3; block++)
   {
      putimage(0, ystart, buf[block], OR_PUT);
      farfree(buf[block]);
      ystart = yend + 1;
      yend += yincr + 1;
   }
}

