// screen and display functions of the weather program
// DJMURRAY  6-3-99

#include <conio.h>

#include "WTHR_SCN.HH"



void Log( char filename[80], char msg[80])   // Function to log data to disk
{
    FILE *logfileptr;
    logfileptr = fopen(filename, "a");
    if (logfileptr == NULL) {
	Message("Cant open %s for output", 1);
    } /* end if */
    else {
	fprintf(logfileptr, "%s  ", msg);
	// now log all settings
	fprintf(logfileptr, "%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
				valueAnalog[0],
				valueAnalog[1],
				valueAnalog[2],
				valueAnalog[3],
				valueInput[0],
				valueInput[1],
				valueInput[2],
				valueInput[3],
				valueOutput[0]);


	fclose(logfileptr);
    } /* end elseif */
} // end Log






void InitDisplay(void)	/* set up the main autolog screen		    */
{
   //   int i = 0;	 /* general counter */
   /*	int tmp;	      /* used to count vert. steps	    */
 //      unsigned long int dfree = 0;	  /* disk space free		*/
 /* char dspace[25];	/* amount of free disk space	    */
      //char *currenttime;
      // _clearscreen( _GCLEARSCREEN );
      //color(BLACK, LIGHTGRAY);
      color(CF_INPUT,CB_INPUT);
//      color(BLUE, CYAN);
      ClearScreen();
      //currenttime = thetime();	/* get the current time	*/
      color(WHITE, BLUE);
     // 	color(CF_TITLE,GS);

      cprintf(" WEATHER CONTROLLER %s                                         D.J.Murray     ",gVERSION);
    //  DisplaySettings(XSETTINGS,YSETTINGS);

      /*------------------ SETUP THE OUTPUT BOX------------*/
      //DrawOutputPort(XOUTPUT,YOUTPUT);
      //DisplayPort(0,XOUTPUT,YOUTPUT);
      /*------------------ SETUP THE Input BOX------------*/
  //    color(BLUE,CYAN);
      DrawAnalogPort(XANALOG,YANALOG);
    //  DrawInputPort(XINPUT,YINPUT);
    //  DrawEventsBox(XEVENT,YEVENT);
     //locate(stat_y + 4, stat_x + 33);
      //printf("Disk Space Free =          ");
     // dfree = GetDiskSpace();		/* get free disk space	    */
     // PrintDspace();

      /*-------------------Function Key Settings------------*/
      color(CF_SETTINGS,CB_SETTINGS);
      DrawBox(1, 22, 7, 24);	    /* draw ESC key	*/
      locate( 22, 3 );
      cprintf("ESC");
      locate( 23, 2 );
      cprintf("Exit");

      DrawBox(9, 22, 15, 24);	    // F1
      locate( 22, 11 );
      cprintf("F1");
      locate( 23, 10 );
      cprintf("....");

      DrawBox(16, 22, 22, 24);	    // F2 - pulse
      locate( 22, 18 );
      cprintf("F2");
      locate( 23, 17 );
      cprintf("....");




}


void DisplaySettings(int x, int y)	// show the parameters
{       // 58,y=10
	color(CF_SETTINGS,CB_SETTINGS);
  //	color(BLUE,CYAN);
	DrawBox(x, y, x+25, y+9);
	color(CF_TITLE,CB_SETTINGS);
	locate(y,x+1);
	//color(BLUE,CYAN);
	cprintf("Settings");
	color(CF_SETTINGS,CB_SETTINGS);

	locate(y+1,x+2); cprintf("                  ");
	locate(y+2,x+2); cprintf("PORT       = %d  ",gPORT);
	locate(y+3,x+2); cprintf("Counter    = %d  ",gCounter);
	locate(y+4,x+2); cprintf("Speed      = %d  ",gSpeed);
	locate(y+5,x+2); cprintf("Fast Pulse = %d  ",gPulse_fast);
	locate(y+6,x+2); cprintf("Slow Pulse = %d  ",gPulse_slow);
	locate(y+7,x+2); cprintf("Iterations = %d  ",gIterations);
}


void DrawOutputPort(int x, int y)
{
     // color(YELLOW,LIGHTGRAY);
      color(CF_OUTPUT,CB_OUTPUT);
      DrawBox(x,y,x+25,y+12);
      color(CF_TITLE,CB_OUTPUT);
      locate(y,x+2);
      cprintf("Digital Outputs");
      color(CF_OUTPUT,CB_OUTPUT);
      locate(y+1, x+16); cprintf("DEC  HEX");
     // locate(y+3,x+4);	cprintf("³³³³³³³³   ");
     // locate(y+4,x+4);	cprintf("³³³³³³³ÀÄ  ");
     // locate(y+5,x+4);	cprintf("³³³³³³ÀÄÄ  ");
     // locate(y+6,x+4);	cprintf("³³³³³ÀÄÄÄ  ");
     // locate(y+7,x+4);	cprintf("³³³³ÀÄÄÄÄ  ");
     // locate(y+8,x+4);	cprintf("³³³ÀÄÄÄÄÄ  ");
     // locate(y+9,x+4);	cprintf("³³ÀÄÄÄÄÄÄ  ");
     // locate(y+10,x+4);	cprintf("³ÀÄÄÄÄÄÄÄ  ");
     // locate(y+11,x+4);	cprintf("ÀÄÄÄÄÄÄÄÄ  ");


}


void DrawAnalogPort(int x, int y)
{

      color(CF_ANALOG,CB_ANALOG);
      DrawBox(x,y,x+57,y+10);	    /* draw the main status box */
      color(CF_TITLE,CB_ANALOG);
      locate(y,x+2 );
      cprintf("Analog Inputs");
      color(CF_ANALOG,CB_ANALOG);
      locate(y+1,x+1);	cprintf(" Port Value   Min   Max   Range");
      locate(y+3,x+1);	cprintf("   0    0     x   x ");
      locate(y+5,x+1);	cprintf("   1    0     x   x ");
      locate(y+7,x+1);	cprintf("   2    0     x   x ");
      locate(y+9,x+1);	cprintf("   3    0     x   x ");


}


void DisplayAnalogValues(int num)
{
   //color(CF_ANALOG,CB_ANALOG);
   //color(LIGHTGREEN,CYAN);
   for (int i=0;i<=num;i++)
   {
	color(LIGHTRED,BLACK);
	locate(YANALOG+3+(i*2),XANALOG+7);
	cprintf(" %5.1f ",valueAnalog[i]);
	color(CF_ANALOG,CB_ANALOG);
      //	color(LIGHTGREEN,CYAN);
	locate(YANALOG+3+(i*2),XANALOG+14);
	cprintf("%5.1f %5.1f %5.1f",valueAnalogMin[i],valueAnalogMax[i],valueAnalogMax[i]-valueAnalogMin[i]);

   }

}

void DisplayDigitalInputs(int num)
{
   // int temp = ~valueInput[0];
    //cprintf(" %d  ",temp & 0x2);

    //locate(YINPUT+6,XINPUT+10);
    //cprintf(" %d  ",temp);        // display decimal value
   // num++;

   //color(CF_INPUT,CB_INPUT);
 //  color(BLUE,LIGHTGRAY);
    for(int i=0;i<=num;i++)
    {
	locate(YINPUT+2+i,XINPUT+8);
	color(LIGHTRED,BLACK);
	cprintf(" %1.1d ", valueInput[i]);
	color(CF_INPUT,CB_INPUT);
      //	color(BLUE,LIGHTGRAY);
	locate(YINPUT+2+i,XINPUT+12);
	cprintf("%4.4d",valueInputCount[i]);
	locate(YINPUT+2+i,XINPUT+18);
	cprintf("%2.2d:",valueInputTimeHour[i]);
	locate(YINPUT+2+i,XINPUT+21);
	cprintf("%2.2d:",valueInputTimeMin[i]);
	locate(YINPUT+2+i,XINPUT+24);
	cprintf("%2.2d",valueInputTimeSec[i]);
	//if(valueInputOld[i] != 1)
	//{
	//	valueInputCount[i]++;
	//	valueInputOld[i] = 0;
	//}
       //	;
    }


}





void DisplayPort(int value, int xx, int y)
{
	int i = xx + 4;
	int j = y + 3;
      //	char str[3];
      //	char bin_str[1 + 8 * sizeof(int)];
       //	static int size = 8 * sizeof(int);
	locate(j - 1, i);
       //	itoa(x, str, 10);
	color(CF_OUTPUT,CB_OUTPUT);
//	color(DARKGRAY,LIGHTGRAY);
    //	color(YELLOW,LIGHTGRAY);
       //	color( BLACK, LIGHTGRAY);
       value = valueOutput[0];
	//cprintf("01234567");
	locate(j, i +10);cprintf("  %3.3d  %2.2X", value,value);
	//for (int x = size - 1; x>=0; x--, value >>= 1)
	color(LIGHTRED,BLACK);

	for (int x = 7; x>=0; x--, value >>= 1)
	{
		//bin_str[x] = (01 & value) + '0';
		//bin_str[size] = '\0';
	//	color(CYAN,LIGHTGRAY);
		color(CF_OUTPUT,CB_OUTPUT);
	//	color(DARKGRAY,LIGHTGRAY);
		locate(j+x,i); cprintf("%1.1d",x);
		color(LIGHTRED,BLACK);

		locate(j+x,i+4);

		if(value & 1)
		{
			cprintf(" 1 ");
		}
		else
		{
 //			color(BLACK, LIGHTGRAY);

			cprintf(" 0 ");
		}
	}
	//gotoxy(10,10);
	//cprintf(bin_str);
	valueInput[0] = value;

}



