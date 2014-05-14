/*	SPELL CHECKER using a Binary Tree		Duncan Murray	*/
/*	first created Monday 9/5/94					*/

/*	This file is merged with the MEMOPAD application using DFLAT	*/


#include <stdio.h>
#include <alloc.h>
#include <string.h>
#include <ctype.h>
#include "dflat.h"
#include "speller.h"


extern int howmany = 100;
extern DBOX SpellCheckDB;
extern DBOX SpellMaintainDB;

/* GLOBAL VARIABLES */
static int totalwords;		/* total number of words checked	*/
static int badwords = 0;	/* number of mispelt words		*/
static int finishedDB = 0;	/* flag to show if Dbox has been checked*/
static char *testword = NULL;	/* current word being spellchecked	*/
static WINDOW textwnd;		/* permanent reference to TEXT window	*/
static int treeloaded = 0;	/* flag true if binary tree has been loaded */
static char *newword = NULL;    /* edited word entered into DialogBox	*/

/* -------------- the SPELLCHECKER Dialog box --------------- */
DIALOGBOX( SpellCheckDB )
    DB_TITLE(        "Spell Check has found a misspelt word",    -1,-1,12,48)
    CONTROL(BUTTON, "~Add Word", 	       	3,  3, 1, 10, ID_SPELLADDWORD)
    CONTROL(EDITBOX, NULL,         	       	3,  1, 1, 22, ID_SPELLADDWORD)
    CONTROL(BUTTON, " ~Ignore",		       	15, 3, 1, 10, ID_SPELLIGNORE)
    CONTROL(TEXT, " Maintain the Btree ",      	10, 6, 1, 25, ID_SPELLREPLACE)
    CONTROL(BUTTON, "~Modify a word ",     	2,  8, 1, 15, ID_SPELLMODIFY)
    CONTROL(BUTTON, "~Delete a word ",     	23, 8, 1, 15, ID_SPELLDELETE)
    CONTROL(BUTTON, " ~Cancel ",           	33, 1, 1, 10, ID_SPELLCANCEL)
    CONTROL(BUTTON, "  ~Help  ",           	33, 3, 1, 10, ID_SPELLHELP)
ENDDB


void MainSpell(WINDOW wnd)	/* main spelling routine called from memopad */
{
	char *spelltext = NULL;	/*pointer to text to be checked */
	Node_type *treeroot;
	textwnd = wnd;		/* assign text window to static variable */

	ClearClipboard();	/* clear the Clipboard */
	CopyToClipboard(wnd);	/* copy marked text to clipboard */
	if(ClipboardLength == 0)
		spelltext = GetText(wnd); /* get full window text */
	else
		spelltext = Clipboard;	/* spell check marked text only */
	if(treeloaded == 0) {	/* if the Btree has not yet been loaded */
		root = BuildTree(); 	/* Load Btree from disk to RAM	*/
		if (root != NULL)	/* check that 'root' to Btree exists */
			treeloaded = 1;	/* set flag to show tree is loaded */
		else
			ErrorMessage("Binary Tree could not be built");
	}
	Spell(wnd, spelltext);	/* send pointer to spelling routine 	*/
	ClearClipboard();	/* clear the clipboard before returning	*/

	/* SAVE the Binary Tree back to Disk */
	if(SaveTree(root) != 1)
		ErrorMessage("Warning... Binary Tree not saved");

     /*	free(spelltext);	/* free memory used by pointer to text	*/
}


void Spell(WINDOW wnd, char *text)	/* spell checks the entire text after splitting words */
{
	int i;				/* general counter 		*/
	int lentext = 0;		/* length of the text passed in	*/
	char word[25];			/* pointer to each word in text	*/
	char report[256];		/* text on report at end of check */

	totalwords = 0;			/* total number of words checked*/
	badwords = 0;			/* number of mispelt words	*/
	word[0] = NULL;			/* clear word to NULL		*/

	lentext = strlen(text);		/* get length of text passed in	*/
	for(i = 0; i < lentext; i++)	/* for each letter in the text  */
	{
		if(isalpha(*text))	/* dont add punctuation characters */
		    if(strlen(word) < 25)	/* for long stupid words */
			strncat(word, text, 1);	/* get the current letter of text */
		text++;				/* increment to next letter	*/
		if(isspace(*text)) {	/* when space, line feed etc encounted */
			if(strlen(word) > 0) {	/* if word is not just LF etc */
				word[strlen(word) + 1] = NULL;
				checkword(wnd, word);	/* call function to check word */
			}
			word[0] = NULL;		/* clear space for next word	*/
			text++; 		/* skip the space between words	*/
		}
	}
	/* Now we need to spell check the last word in the document */
	if(strlen(word) > 0) {			/* if LAST word is not just LF etc */
		word[strlen(word) + 1] = NULL;	/* add NULL char to end of word */
		checkword(wnd, word);	/* call function to check the last word */
	}
	sprintf(report, "There where %d incorrectly spelt words\nof the %d words checked\n", badwords, totalwords);
	ErrorMessage(report);  /* causes lockups when adding 'fp' */
	totalwords = 0;
}


void checkword(WINDOW wnd, char *testingword)
{
	int result = 1;		/* result of the spellchecker 		*/

	totalwords++;		/* increment total number of words check*/
	result = TreeSearch(root, testingword);
	if (result != 1)  {	/* word is misspelt  			*/
		badwords++;	/* increment total misplelt words so far*/
		SetEditBoxText( &SpellCheckDB, ID_SPELLADDWORD, testingword);
		/* set the editbox in DB to current missplet word */
		result = DialogBox(wnd, &SpellCheckDB, TRUE, SpellCheckProc);
		/* call the Dialog Box */
		newword = GetEditBoxText( &SpellCheckDB, ID_SPELLADDWORD);
		/* get the new text from the editbox as entered by user */
	}
}

void Changeword(void)
{
	/* edit the Btree - modify a word */
	char report[256];
	int tmp;

	testword = newword;
	newword = GetEditBoxText( &SpellCheckDB, ID_SPELLADDWORD);
	sprintf(report, "Changing word '%s' to '%s'\n", testword, newword);
	ErrorMessage(report);
	if(TreeSearch(root, testword) == 1)	/* if newword is in Btree */
		strcpy(p->info.word, newword);	/* change the text 	  */
	else
		ErrorMessage("I cannot modify a word which doesnt exist");
}

void AddwordtoDic(void)
{
	/* add the current word 'newword' in the dialog box to the dictionary */
	Node_type *pp = NULL;
	Node_type *tmpp = root;	/* tempory Node for inserting */
	int i = 0;
	int lenword;
	char report[256];
	char word[15];
	char *letter;
	word[0] = NULL;

	newword = GetEditBoxText( &SpellCheckDB, ID_SPELLADDWORD);
	sprintf(report, "Adding new word '%s'\n", newword);
	ErrorMessage(report);

	if((pp = (Node_type *) malloc(sizeof(Node_type))) == NULL)
		ErrorMessage("Cannot allocate any more Nodes");

	lenword = strlen(newword);
	while(isalpha(newword[i]) && i < 15) {
		letter = &newword[i];
		strncat(word, letter, 1);
		i++;
	}
	word[i] = NULL;  		/* NULL terminate the word   	*/
	strcpy(pp->info.word, word); 	/* assign Node to word from disk*/
	pp->left=pp->right=NULL;

	/*--------------------- function to insert new node ------ */
	while(tmpp != NULL) {
		if(strcmp(pp->info.word, tmpp->info.word) < 0)
			if(tmpp->left)
				tmpp = tmpp->left;
			else {
				tmpp->left = pp;
				break;
			}
		else if(strcmp(pp->info.word, tmpp->info.word) > 0)
			if(tmpp->right)
				tmpp = tmpp->right;
			else {
				tmpp->right = pp;
				break;
			}
		else
			ErrorMessage("Duplicate word entered into Btree");
	}
	pp->left = pp->right = NULL;
	if(root == NULL)
		root = pp;

}

void Ignoreword(void)   /*  DEBUG PURPOSES ONLY !!! */
{
    int x = 1;
    char report[512];
   sprintf(report, "L=%p R=%p, word=%p _%s_\n", p->left, p->right, p->info.word, p->info.word);
   printf(report);

   while(x != 0) {
	   x = LeftRight();
	   if(x == 1)
		if(p->left) {
			p = p->left;
			printf("Moving to Left\n");
			}
		else
			printf("Cant move Left into NULL\n");
	   if(x == 2)
		if(p->right) {
			p = p->right;
			printf("Moving to Right\n");
			}
		else
			printf("Cant move Right into NULL\n");

    sprintf(report, "L=%p R=%p, word=%p _%s_\n", p->left, p->right, &p->info.word, p);
    printf(report);
    p = FindRoot(lastnode);
   }
   printf("Finished DEBUG");

}


/* window processing module for the Spell Checker Dialog Box */
int SpellCheckProc(WINDOW wnd,MESSAGE msg,PARAM p1,PARAM p2)
{
	int answer = 0;
	char report[256];
	int rtn;	/* return message procedure */

    switch (msg)    {

	case COMMAND:

		if(p2 > 0)
		return;

	    switch ((int) p1)    {

		case ID_SPELLADDWORD:
			AddwordtoDic();
			break;

		case ID_SPELLIGNORE:
			break;


		case ID_SPELLREPLACE:
			break;


		case ID_SPELLHELP:
			MessageBox(
			 "Binary Tree Spell Checker using DFLAT",
			"This is a modification to MEMOPAD\n"
			"which incorporates a Spell Checker\n"
			"You can check the entire document\n"
			"by selecting Spell Check from the\n"
			"Utilities Menu, or check selected\n"
			"text by marking it first.\n\n"
			"When a misplect word is encountered\n"
			"You have the option of Adding it to\n"
			"the dictionary or Ignoring it. You\n"
			"can also Modify or Delete a words in\n"
			"the dictionary by entering them into\n"
			"the EDITBOX before selecting the\n"
			"appropriate button on the Dialog Box\n"
			"editor that demonstrates D-Flat");

			break;

		case ID_SPELLCANCEL:
			break;


		case ID_SPELLMODIFY:

			Changeword(); /* change name to Modifyword() */
			break;

		case ID_SPELLDELETE:
			sprintf(report, "About to delete word %s",newword);
			ErrorMessage(report);

			if(TreeSearch(root, testword) == 1)	/* if newword is in Btree */
				Delete(p); 		/* MAJOR LOCKUPS !!!! */
			else
				ErrorMessage("I cannot delete a word which doesnt exist");
			break;

		default:
		    break;
	    }
	    break;


	default:
	    break;
    }
   rtn = DefaultWndProc(wnd, msg, p1, p2);
   return rtn;

}



