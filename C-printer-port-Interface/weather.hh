// LPT_OP.HH
// written by Duncan Murray 4/3/1999  (c) Acute Software 1999
//  This program is part of a test suite to enable the LPT port of
//  of a PC to control the 'gadgets' designed by Acute Software.
#define PROGNAME "WEATHER    written by Duncan Murray.   (c) Acute Software 1999"
#define PROGDESC "Program to measure temperatures,light levels and control things"
#include "USER_IF.HH"
#include "WTHR_SCN.HH"
//#define PORT 0x378	// LPT1
//#define PORT 0x3BC	// LPT2
//#define PORT 0x278	// LPT3

// COLOUR SETTINGS
//#define CF_INPUT BLUE;
//BLACK        ³  0  ³ Yes ³ Yes
//BLUE         ³  1  ³ Yes ³ Yes
//GREEN        ³  2  ³ Yes ³ Yes
//CYAN         ³  3  ³ Yes ³ Yes
//RED          ³  4  ³ Yes ³ Yes
//MAGENTA      ³  5  ³ Yes ³ Yes
//BROWN        ³  6  ³ Yes ³ Yes
//LIGHTGRAY    ³  7  ³ Yes ³ Yes
//DARKGRAY     ³  8  ³ No  ³ Yes
//LIGHTBLUE    ³  9  ³ No  ³ Yes
//LIGHTGREEN   ³ 10  ³ No  ³ Yes
//LIGHTCYAN    ³ 11  ³ No  ³ Yes
//LIGHTRED     ³ 12  ³ No  ³ Yes
//LIGHTMAGENTA ³ 13  ³ No  ³ Yes
//YELLOW       ³ 14  ³ No  ³ Yes
//WHITE        ³ 15  ³ No  ³ Yes

int CF_TITLE = 14;
int CF_INPUT = 1;
int CB_INPUT = 7;
int CF_ANALOG = 1;
int CB_ANALOG = 7;
int CF_OUTPUT = 0;
int CB_OUTPUT = 7;
int CF_SETTINGS = 0;
int CB_SETTINGS = 7;
int CF_EVENT = 8;
int CB_EVENT = 7;

//int DELAY = 40;
char gVERSION[6] = "V0.1";
int gPORT = 888;
int gDELAY = 351;
int gSpeed = 100;
int gPulse_fast = 50;
int gPulse_slow = 300;
int gIterations = 10;
int gValue = 0;
int gCounter = 15;


int cur_sec = 0;	    /* current second			*/
int cur_min = 0;	    /* current minute			*/
int cur_hour = 0;	    /* current minute			*/


int XOUTPUT = 30;
int YOUTPUT = 2;
int XANALOG = 2;
int YANALOG = 3;
int XINPUT = 1;
int YINPUT = 2;
int XEVENT = 1;
int YEVENT = 16;
int XSETTINGS = 58;
int YSETTINGS = 10;





int valueOutput[8];
int valueInput[4];
int valueInputOld[4];
long valueInputCount[4];
int valueInputTimeMin[4];
int valueInputTimeSec[4];
int valueInputTimeHour[4];

float valueAnalog[4];
float valueAnalogMin[4];
float valueAnalogMax[4];


//int value

int WritePort(int);            	// actual ASM function to write to port
void OutputBit(int bit,int val);// turns o/p bit on or off;

void Initialise(void);		// turn outputs on and off for 1 second
void Pulse(int, int);		// pulse output port for x milliseconds
void TestMaxSpeed(int);		// see how fast it can pulse
void BinaryCount(int);
void Chase(int, int, int);
void ChaseMultiple(int, int);

int ReadAnalogInputs(int);

void ReadDigitalInputs(int);


float ConvertToTemperature(int);