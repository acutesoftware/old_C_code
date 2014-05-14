/*		Text Utitlity - FINDAT
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
#include <ctype.h>

/* Function Prototypes */
int FindAt(char *Data, int pos, char *word);
int WildCompare(char *line, char *word);

int main( int argc, char *argv[])
{
    int linenum = 0;/* current line number (used as count)	    */
    int good = 0;   /* number of good lines			    */
    int bad  = 0;   /* number of bad lines			    */
    int startpos;   /* starting position in line to search	    */
    char Line[256]; /* the line itself , as read in from disk/stdin */
    char Text[256]; /* text to find at startpos		    */
    FILE *fp;	    /* filename being read in			    */

    Text[0] = '\0';
    Line[0] = '\0';
    if(argc < 3) {  /* incorrect arguments entered		    */
	printf("\n\tFINDAT.EXE - Duncan Murray 20/6/94\n");
	printf("This program reads in a text file and outputs any line which contains\n");
	printf("the text 'TEXT' starting at line position 'n'.\n");
	printf("The format for command line parameters is :-\n\n");
	printf("\tFINDAT n TEXT filename /L /S\n");
	printf("where :-\n");
	printf("\tn        = position to find text\n");
	printf("\tTEXT     = text to find at that position\n");
	printf("\tfilename = filename to search\n");
	printf("\t/L       = output Line numbers\n");
	printf("\t/S       = totals at end\n");
	printf("\n The TEXT can contain the following Wildcards :-\n");

	printf( "\t* = any number of characters\n");
	printf( "\t? = any ASCII character\n");
	printf( "\t$ = any digit      ( 0-9 )\n");
	printf( "\t@ = any alpha char.( a-Z )\n");
	printf( "\t# = anything BUT digits\n");
	printf( "\t! = anything BUT aplha.\n");
	return 1;
    }
    else {
	startpos = atoi(argv[1]);/* get the starting position	    */
	strcat(Text, argv[2]);	/* text to find  */
	if( (fp = fopen( argv[3], "rt" )) == NULL ) {
	    printf("Error - cant open input file %s\n\n",argv[3]);
	    return 2;
	}

	else {			/* The file has been opened	    */
	   /* printf("startpos = %d   Text = %s  Filename = %s\n", startpos, Text, argv[3]);*/
	    while(!feof(fp)) {	/* As long as there are more lines  */
		linenum++;	/* update the line number count     */
		Line[0] = '\0';
		fgets( Line, 80, fp );
	       /*	printf("%d,%s,_%s_", linenum, Text, Line); */
		if(FindAt(Line, startpos, Text)) {	/* if text is found in pos */
		    good++;
		    if (strcmp(argv[4], "/L") == 0 || strcmp(argv[4], "/l") == 0 )	/* output Line num */
			printf("%5d,%s", linenum, Line);
		    else
			printf("%s", Line);
		}   /*----------------------------end If (FindAt found match)----*/

		else
		    bad++;
	    }	/*-------end While (NOT end of file)---------------------*/

	    fclose( fp );
	} /*--------------- end else (cant open input file)-------------*/
	if (strcmp(argv[4], "/S") == 0 || strcmp(argv[4], "/s") == 0 || strcmp(argv[5], "/S") == 0 || strcmp(argv[5], "/s") == 0 ) {	/* output Line num */
	    printf("There were %d lines in the file %s\n", linenum, argv[3]);
	    printf("There were %d lines which contained '%s' at position %d\n\n", good, Text, startpos);
	}
    }	/*---------end else (incorrect arg[]s--------------*/

    return 0;
}   /*------end function main()-----------*/



int FindAt(char *Data, int pos, char *word)
/* Function to find the word 'word' at position 'pos' in the buffer 'Data'  */
/* returns 0 if not found or 1 if found 				    */
{
    int lenline;    /* length of the text				    */
    int lenword;    /* length of the line				    */
    int i = 0;	    /* general counter					    */
    int j = 0;	    /* general counter					    */
    char postext[256];	/* temp line to find text   */
    char tmp[2];    /* general var for char	    */

    postext[0] = '\0';	/* clear the postext var    */
    lenline = strlen(Data);	/* find the length of the line		    */
    lenword = strlen(word);	/* find the length of the word		    */

    if(lenline < lenword)	/* If the line is shorter than the word     */
	return 0;
    j = 0;
    for ( i = pos - 1; i < pos - 1 + lenword; i++) {	/* for each character in the word   */
	j++;
	tmp[0] = Data[i];
	tmp[1] = '\0';
	strcat(postext, tmp);	/* add a char to the temp var.	*/

       //	if(*(word++) != *(Data + i)) {			/* if the letters are the same	    */
       //	    return 0;
       //	}
    }
  //  printf("(WC)-postext=_%s_ word=_%s_  ", postext, word);
    if (WildCompare(postext, word) == 1)    /* if it matches wildcards	*/
	return 1;
    else
	return 0;
}



/****************************************************************
 *								*
 *	W I L D C O M P A R E	      (c) Duncan Murray 19/1/95	*
 *								*
 * Finds the string 'word' in the string 'text' using Wildcards *
 * and returns 1 = found, or 0 = not found.			*
 *								*
 * Wildcards are :- * any number of characters			*
 *		    ? any single character			*
 *		    @ any alpha character   ( a - Z )		*
 *		    $ any number	    ( 0 - 9 )		*
 *		    # any NON number	    ( NOT 0-9 ) 	*
 *		    ! any NON letter	    ( NOT a-Z ) 	*
 *								*
 *								*
 ****************************************************************/

int WildCompare(char *line, char *word)
{
    int i = 0;		/* General Counter			*/
    int j = 0;		/* General Counter			*/
    int lenline = 0;	/* Length of the entire line		*/
    int lenword = 0;	/* Length of the entire word		*/
    int test = 0;	/* flag showing if word is found ot not */
    int found = 0;	/* flag showing if word is found ot not */
    int success = 0;	/* flag showing if word is found ot not */
    char letter = '\0'; /* letter currently being tested	*/
    char letter2 = '\0'; /* letter currently being tested	*/
    lenline = strlen( line );
    lenword = strlen( word );

    for ( i = 0; i < lenline; i++ )	{ /* for each letter in line*/
	test = 0;	    /* clear test for each pos in line	    */
	for ( j = 0; j < lenword; j++ ) { /* for each letter in word*/
	  letter2 = word[j];	/* current letter in the word */
	  letter  = line[i + j];	/* current letter in the line */


	  switch ( letter2 ) {
	    case '*': {
		if ( test == j ) {	    /* if all letters so far, have passed */
		    i = lenline;	    /* Dont test any more chars in line */
		    success = 1;	    /* WE FOUND THE WORD		    */
		}
		j = lenword;	    /* test no more chars in word */
		}
		break;
	    case '?': {
		if ( isalnum(letter))
		    test++;
		}
		break;
	    case '@': {
		if ( isalpha(letter))
		    test++;
		}
		break;
	    case '$': {
		if ( isdigit(letter))
		    test++;
		}
		break;
	    case '#': {
		if ( !isdigit(letter))
		    test++;
		}
		break;
	    case '!': {
		if ( !isalpha(letter))
		    test++;
		}
		break;
	    default :
	      /*	if ( word[i] == line[j] )	/* letter in word matchs letter in line */
		if ( letter == letter2 )	    /* letters are same */
		    test++;
		break;
	  }	/* END switch  */
	}	/* END for - j */

	if ( test >= lenword && success == 0){	/* if all letters in word are in line */
	    success = 1;	/*  WE FOUND THE WORD		    */
	}	/* END IF      */

    }		/* END for - i */

    return success;	/* return the flag to calling function	*/

} /* END FUNCTION - WildCompare */
