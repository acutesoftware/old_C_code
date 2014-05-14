// PCIO_SCN.hh


#include <stdio.h>
#include "USER_IF.hh"
//#include "LPT_OP.hh"




void InitDisplay(void);		// set up the main screen
void DisplayPort(int,int,int);
void DrawOutputPort(int,int);
void DrawAnalogPort(int x, int y);
void DrawInputPort(int x, int y);
void DisplayDigitalInputs(int);
//int Log(char*, int);
void Log( char filename[], char msg[]);
void DisplaySettings(int,int);
 void DisplayAnalogValues(int num);

void DrawEventsBox(int,int);
extern char gVERSION[];
extern int gPORT ;
extern int gDELAY;
extern int gSpeed;
extern int gPulse_fast;
extern int gPulse_slow;
extern int gIterations;
extern int gValue;
extern int gCounter;


extern int XOUTPUT;
extern int YOUTPUT;
extern int XANALOG;
extern int YANALOG;
extern int XINPUT;
extern int YINPUT;
extern int XEVENT;
extern int YEVENT;
extern int XSETTINGS;
extern int YSETTINGS;


extern int CF_TITLE;
extern int CF_INPUT;
extern int CB_INPUT;
extern int CF_ANALOG;
extern int CB_ANALOG;
extern int CF_OUTPUT;
extern int CB_OUTPUT;
extern int CF_SETTINGS;
extern int CB_SETTINGS;
extern int CF_EVENT;
extern int CB_EVENT;


extern int valueOutput[];
extern int valueInput[];
extern int valueInputOld[];
extern long valueInputCount[];
extern int valueInputTimeHour[];
extern int valueInputTimeMin[];
extern int valueInputTimeSec[];


extern int valueAnalog[];
extern int valueAnalogMin[];
extern int valueAnalogMax[];

	      //	array
