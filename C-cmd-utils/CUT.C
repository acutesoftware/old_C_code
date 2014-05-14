/*		Text Utitlity - CUT
	   written by Duncan Murray 20/6/94
   This program reads in a filename and outputs the lines which contain
   the text at a specific line position.

    Program returns 0 = successful operation
		    1 = incorrect number of parameters on command line
		    2 = cant find filename
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Prototypes */

int main( int argc, char *argv[])
{
    int linenum = 0;/* current line number (used as count)	    */
    int good = 0;   /* number of good lines			    */
    int bad  = 0;   /* number of bad lines			    */
    int startpos;   /* starting position in line to search	    */
    int endpos;     /* end position in line to search		    */
    char Line[256]; /* the line itself , as read in from disk/stdin */
    char Text[256]; /* text to output				    */
    FILE *fp;	    /* filename being read in			    */
    int i=0, j=0;   /* general counters 			    */
    int length = 0; /* length of the current line being read in     */

    Text[0] = '\0';
    Line[0] = '\0';
    if(argc < 3) {  /* incorrect arguments entered		    */
	printf("\n\n\tCUT  - Duncan Murray 21/6/94\n\n");
	printf("This program reads in a text file and outputs the columns ");
	printf("selected by the user.\n\n");
	printf("The format for command line parameters is :-\n");
	printf("\tCUT sss fff filename /L /S\n\n");
	printf("where :-  sss      = starting column to output text\n");
	printf("          fff      = end column to output text\n");
	printf("          filename = filename to search\n\n");
	printf("          /L       = output line numbers\n");
	printf("          /S       = show stats at end\n");
	return 1;
    }
    else {
	startpos = atoi(argv[1]);/* get the starting position	    */
	endpos = atoi(argv[2]);  /* get the end position	    */
	if (strcmp(argv[5], "/S") == 0 || strcmp(argv[5], "/s") == 0 )	/* output Line num */
	    printf("startpos = %d\tendpos = %d\n", startpos, endpos);

	if( (fp = fopen( argv[3], "rt" )) == NULL ) {
	    printf("Error - cant open input file %s\n\n",argv[3]);
	    return 2;
	}
	else {			/* The file has been opened	    */
	    while(!feof(fp)) {	/* As long as there are more lines  */
		linenum++;	/* update the line number count     */
		fgets( Line, 80, fp );	/* get the line from input file */
		j = 0;
		length = strlen( Line );    /* get the length of the line */
		if (startpos > length) {    /* if line is shorter than startpos */
		  if (strcmp(argv[4], "/L") == 0 || strcmp(argv[4], "/l") == 0 )	/* output Line num */
		    printf("%5d,%s\n", linenum, Text);
		  else
		    printf("%s\n", Text);
		}
		else {
		  for ( i = startpos; i < endpos + 1; i++ ) {	/* for each char in output */
		    if (Line[i - 1] != '\0') {	/* as long as line is not too long  */
			Text[j] = Line[i - 1];	  /* add to output	*/
			j++;
		    }
		    else
			i = endpos + 1; /* end of line	*/

		  }
		  Text[j] = '\0';	/* Null terminate the string	*/
		  if (strcmp(argv[4], "/L") == 0 || strcmp(argv[4], "/l") == 0 )	/* output Line num */
		    printf("%5d,%s\n", linenum, Text);
		  else
		    printf("%s\n", Text);
		}
	    }
	}
	fclose( fp );
	if (strcmp(argv[5], "/S") == 0 || strcmp(argv[5], "/s") == 0 )	/* output Line num */
	    printf("There were %d lines in the file %s\n", linenum, argv[3]);
    }
    return 0;
}
