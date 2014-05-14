/*	    REMBLANK.C	    written by Duncan Murray	15/6/95
 *
 *  Utility to remove blank lines from a Text file. Usage is
 *  REMBLANK [infile] [opfile]
 *
 */

#include <stdio.h>
#include <string.h>



void main(int argc, char *argv[])
{
    int i = 0; /* general counter */
    char infile[255];	/* input filename   */
    char opfile[255];	/* output filename  */
    char line[255];	/* line currently being read in */
    char prevline[255];	/* previous line read in */
    FILE *in;		/* pointer to input file */
    FILE *op;		/* pointer to output file */
    int result; 	/* result of blank line compare */
    int lines_read = 0;	/* num lines read in	*/
    int lines_outp = 0;	/* num lines output	*/
    int lines_blnk = 0; /* total blank lines	*/
    int lines_leng = 0;	/* lines of length less than 2 */
    int lines_CRLF = 0; /* lines containing a \n */
    int total_blank = 0;/* total blank lines removed */


    if (argc < 3) {
	printf("\n\nREMBLANK V1.0         written by Duncan Murray  15/6/95\n\n");
	printf("This program simply removes blank lines from a text file\n\n");
	printf("It only removes blank lines which arent in a block - ie only removes blanks between text\n");
	printf("usage REMBLANK [inputfile] [outputfile]\n");
	printf("where [inputfile]  = input file to has its blank lines removed\n");
	printf(" and  [outputfile] = output file to save the modified file\n\tNote:-inputfile cant be the same as outputfile\n");
	exit(0);
    }
    strcpy(infile, argv[1]);	/* get the input file from the command line */
    strcpy(opfile, argv[2]);	/* get the output file from the command line */
    if (strcmp(infile, opfile) == 0)	{
	printf("The input file cannot be the same same as the output file\n");
	exit(0);
    }

    if ((in = fopen(infile, "r")) == NULL) {  /* open the input file  */
	printf("Cannot open the input file %s\n", infile);
	exit(0);
    }
    if ((op = fopen(opfile, "w")) == NULL) {  /* open the output file	*/
	printf("Cannot open the output file %s\n", opfile);
	exit(0);
    }

    printf("Remblank    written by Duncan Murray 1/1/96\n\n");

    /********************************************** Main Function Here ****/
    while(!feof(in)) {	    /* while not at the end of the file */
	strcpy(prevline, line);
	fgets( line, 255, in);	  /* get a line of data		*/
	lines_read = lines_read + 1;	/* num lines read in	*/

     /*	result = strcmp(line, "\n") || !strcmp(line, prevline);	/* only output if not CRLF and it is only a single blank line */
	result = 0;
	if (strcmp(line, "\n") == 0)	{				/* is it a blank line	*/
	    result = 1;
	    lines_CRLF = lines_CRLF + 1;
	}
	if (strlen(line) < 2)	{
	    result = 1;
	    lines_leng = lines_leng + 1;

	}
	if (strcmp(line, prevline) == 0)	{
	    result = 0;
	    lines_blnk = lines_blnk + 1;
	}
	if (result == 0 || (strcmp(line, prevline) == 0))	{	   /* means lines passed all tests */
	    fputs(line, op);		   /* output that line */
	    lines_outp = lines_outp + 1;   /* num lines output	*/
	    strcpy(line, "");		   /* clear var, to stop last line repeating */
	}
	else {
	    total_blank = total_blank + 1;
	  /*  printf("%s", line); /* print the removed line for now */
	}
	/* now update stats on screen.............................. */
    }
    fclose(in); /* close the input file */
    fclose(op); /* close the output file */

    printf("Total Lines Read in     = %d\n\n", lines_read);
    printf("Lines less than 2 bytes = %d\n", lines_leng);
    printf("Lines with CRLF only    = %d\n", lines_CRLF);
    printf("Lines with same prev.   = %d\n\n", lines_blnk);
    printf("Total Lines Removed     = %d\n\n", total_blank);




}
