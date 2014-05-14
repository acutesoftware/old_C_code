
//   USER_IF.CPP		modified D.J.Murray 5/3/1999
//  Uses generic screen and utilities to be used for ALL programs

#include "USER_IF.HH"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <graphics.h>
#include <time.h>
#include <bios.h>
#include <fcntl.h>
#include <sys\types.h>
#include <sys\stat.h>

extern char ms[80];	/* message text declared in DECENTOC.C	*/
extern char logfile[80];
extern char date[26];	    /* date time stuff	*/
extern int box_x;	    /* starting 'x' pos of data box		*/
extern int box_y;	    /* starting 'y' pos of data box		*/
extern int stat_x;     /* starting point for status box		*/
extern int stat_y;	    /* starting point for status box		*/
extern int gDelay;

void ClearScreen(void)
{
 clrscr();
}



void Message( char *mes, int log)/* print a message to the message box. clear first	*/

   /* the message will also log to disk file if int=1	*/
{
      FILE *mp;
      locate( 25, 1 );
      printf("                                                     ");
      locate( 25, 1 );
      //color(BLACK, LIGHTGRAY);
      cprintf("%s", mes);

      if (log == 1) {	/* if user chose to log this message to disk	    */
	  mp = fopen(logfile, "at");	/* open the log file for append     */
	  if (mp == NULL) {
	    locate( 25, 1 );
	    printf("Cant open %s (log file)", logfile);
	    exit (0);
	  }
	  fprintf(mp, mes);
	  fprintf(mp, "\n");
	  fclose(mp);
      }

}
void ClearDataArea(void)	/* clear the data area	*/
{
    int i = 0;	/* general counter  */
    for (i=box_y + 1; i < (box_y + 9); i++) {
	locate( i, box_x + 1);
	printf("                                                                ");
    }
}

void PrintData( int i, int dat) /* print data group # 'i' as value 'dat' */
{
 /* This function prints the data 'dat' from the group 'i' (0 > 128) to
    the correct position on the screen (groups of 16). The box has already
    been drawn
  */

    int rem = 0 ;	 /* varaible for the remainder	*/
    int x = 0;	    /* x co-ord for screen		*/
    int y = 0;	    /* y co-ord for screen		*/

    rem = (i % 16); /* how much remainder is from i if divided by 16	*/

    x = rem * 4;    /* get 'x'	= remainder after / 16		*/
    y = i / 16;     /* get 'y'	= num. times i divides into 16	*/
    if ((x + box_x) > 80) {
	Message("X too big", 0);
	x = 80 - box_x;
    }
    if ((y + box_y) > 25) {
	Message("Y too big", 0);
	y = 25 - box_y;
    }
    locate( y + box_y + 1, x + box_x + 1);
    printf("%3d", dat);



}




void DrawBox(int x1, int y1, int x2, int y2)
{
    /* This function draws a box in text mode on the screen using ASCII chars
       It can be used as a general purpose function. If the co-ords are out of
       bounds then they will be moved to the nearest border. ie -3=0 83=80
     */
    int i = 0;		    /* general counter				*/
    //color(BLACK, LIGHTGRAY);
    char spaces[80];
    if (x1 < 1) x1 = 1;     /* make sure all co-ords are within range */
    if (x2 > 80) x2 = 80;
    if (y1 < 1) y1 = 1;
    if (y2 > 24) y2 = 24;

    // first clear the background , so its all the same color
    for(i=0;i<(x2-x1);i++)
    {
	spaces[i]= ' ';	// make the correct spaced out line to clear
    }
    spaces[i+1]='\0';
    for(i=y1;i<=y2;i++)
    {
	locate(i,x1);
	cprintf("%s",spaces);
    }

    locate( y1, x1 ); /* print top left corner		*/
    printf("Ú");

    locate( y1, x2 ); /* print top right corner		*/
    printf("¿");

    locate( y2, x1 ); /* print bottom left corner		*/
    printf("À");

    locate( y2, x2 ); /* print bottom right corner		*/
    printf("Ù");

    for (i = x1 + 1; i < x2; i++){	/* print horizontal lines		*/
	 locate( y1, i );
	 printf("Ä");
	 locate( y2, i );
	 printf("Ä");
    }

    for (i = y1 + 1; i < y2; i++){	/* print vertical lines			*/
	 locate( i, x1 );
	 printf("³");
	 locate( i, x2 );
	 printf("³");
    }



    /*Pause(); */

}

int Question(char *mesg)	  /* Function to print question and return answer */
{
    char answer[80];	   /* initialise answer to NULL  */
    int ans;
    printf("%s ?\t", mesg);    /* print the question	    */
    gets( answer );
    if (*answer > '0' && *answer < '9') {
	 ans = atoi( answer );
	 answer[0] = '\0';	    /* clear pointer to NULL	*/
	 if (ans > 0 && ans < 10)
	    return ans;
    }
    return 0;
} /* end Question */


void Pause(void)    /* Pauses until <<Enter>> key is pressed */
{
    char *c = NULL;
    Message("Press <<Enter>> ", 0);
    gets(c);
}





int getkeypressed(void)	/* returns the ascii value of key pressed */
    /* This general purpose function checks the keyboard (once only)
     * and returns the value of the key pressed as an INT
     */

{
    int key = 0;
    /* If first key is 0, then get second extended. */
    key = getch();
    if( (key == 0) || (key == 0xe0) )
    {
	key = getch();
      /*	Message( "ASCII: no\tChar: NA\t" );*/
    }

    /* Otherwise, there's only one key. */

    sprintf(ms, "ASCII:yes  Char: %c Decimal: %d  Hex: %X", isgraph( key ) ? key : ' ', key, key );
    Message(ms, 0);


    /* Echo character response to prompt. */
 /*   if( key == 27) return ESC; */
    return key;
}




void locate( int y, int x)  /* function to locate text on screen    */
{
    short y_s = 0;	/* short int for function   */
    short x_s = 0;	/* short int for function   */


    if (x > 80) x = 80;
    if (y > 25) y = 25;
    if (x < 1) x = 1;
    if (y < 1) y = 1;

    y_s = (short)y;
    x_s = (short)x;
    //_settextposition( y_s, x_s );
    gotoxy(x_s, y_s);

}


void color(int cf, int cb)  /* sets screen color		*/
{
    short cf_s = 0;	/* short int for function   */
    long cb_l = 0;	/* long int for function	*/

    if (cf > -1) {		/* if the foreground color parameter was valid	*/
       cf_s = (short)cf;	/* cast int to short		*/
       textcolor( cf_s );	/* set the text color		*/
       //_settextcolor( cf_s );	/* set the text color		*/
    }

    if (cb > -1) {		/* if the background color parameter was valid	*/
       cb_l = (long)cb; 	/* cast the int to long 	*/
       textbackground( cb_l );	/* set the back color		*/
    }


}

char *thetime(void)	    /* returns the character array as the date	*/
{
    struct tm *newtime;
    time_t long_time;

    time( &long_time );     /* Get time as long int */
    newtime = localtime( &long_time );       /* Convert to local time */

    sprintf(date, "%s", asctime( newtime )); /* put converted time into date */
    date[24] = '\0';	    /* overwrite newline in date with a null */
    return date;	    /* return the character array of the date */
}




void wait(int ms)
{
	for(int j=0; j<ms; j++)
	{
	  ;
	  for(int i=0; i<(gDELAY * 1000); i++)
	  {
	     ;
	  }
	}
	;

}


int extract_num(char *string, int start, int len)  /* extracts num from char	*/
{
    /* This general purpose function extracts a number from string 'string'
       starting at position 'start' for length 'len'
       written by Duncan Murray 23/8/94
     */

    char tmp[256];	 /* tempory chars to put characters */
    int val;		 /* value to be returned	    */

    strncpy(tmp, string + start - 1, len);
    tmp[len++] = '\0';		/* NULL terminate the tmp char pointer	*/
    val = atoi(tmp);		/* convert the tmp string to an integer */
    return val; 		/* return the integer value		*/
}
