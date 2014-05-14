/*		USER_IF.H	written by Duncan Murray 11/8/94

    This header file contains the function prototypes and structure
    declarations for the USER_IF functions.
*/

/* type declarations-----------------------------------*/



/*------------------- Function Prototypes---------------------------------*/
void wait(int); 		/* Wait for 'int' milliseconds		*/
void Log(char[80], char[80]);	/* Function to log data to disk 	*/
void NewFilename(char *name, int day);	/* Get a new filename based on current day */
int ReadConfigFile(char name[80]);	    /* read the external configuration file */
char *thetime(void);		    /* returns the character array of the current date	*/
void TestMenu(void);		    /* display the test menu	*/


/*--------------User IO Functions--------------*/
int Question(char *msg);	/* Function to print question and return answer */
/*void UpdateScreen(void);			/* update the current screen values	*/
void DrawBox(int x1, int y1, int x2, int y2);	/* Draw a box on screen */
void Message( char *mes, int log);		/* print a message to the message box. clear first */
void PrintData( int i, int dat);		/* print data group # 'i' as value 'dat' */
void ClearDataArea(void);			/* clear the data area	*/
void locate( int y, int x);			/* function to locate text on screen	*/
//void setupscreen(void);		/* set up the main autolog screen		    */
int getkeypressed(void);			/* returns the ascii value of key pressed */
int extract_num(char *string, int start, int len);  /* extracts num from char	*/
void Pause(void);		/* stops execution until key pressed	*/
void color(int cf, int cb);	/* sets screen color		*/


void ClearScreen(void);
/*------------------FILE_IO Functions------------------*/
void PrintDspace(void);	  /* get and print the free disk space	*/
unsigned long int GetDiskSpace(void);	/* returns the amount of free disk space    */



extern int gDELAY;

/*--------------EXTERNAL PROTOYPES------------ */
extern int _kbhit(void);
extern int _getch(void);
//extern int gotoxy(int, int);
//extern int textbackground(int);
//extern int textcolor(int);

