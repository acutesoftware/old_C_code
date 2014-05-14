/* Binary Tree functions used for SpellChecker for ASSIGNMENT3 ADVC	*/
/*		Duncan Murray	16/5/94					*/

#include <stdio.h>
#include <alloc.h>
#include <string.h>
#include <ctype.h>
#include "dflat.h"
#include "speller.h"

static FILE *logfile;	/* file pointer of the testing log */
static FILE *op;	/* output file to save tree to 			*/
int LeftRight(void);	/* declaration for DEBUG */


Node_type *GetNode(FILE *fp)	/* get a new node with data for BTree	*/
{
	Node_type *pp = NULL;
	extern int howmany;
	int i = 0;
	int lenword;
	char tmpword[30];
	char word[15];
	char *letter;
	word[0] = NULL;

	if((pp = (Node_type *) malloc(sizeof(Node_type))) == NULL)
		ErrorMessage("Cannot allocate any more Nodes");
	fgets(tmpword, 30 , fp); /* read a word from disk */

	lenword = strlen(tmpword);
	while(isalpha(tmpword[i]) && i < 15) {
		letter = &tmpword[i];
		strncat(word, letter, 1);
		i++;
	}
	word[i] = NULL;
	strcpy(pp->info.word, word); /* assign Node to word from disk */
	pp->left=pp->right=NULL;
	return pp;
}


Node_type *BuildTree(void)	/* build nodes from GetNode into a BTree*/
{
	int count = 0;	/* number of nodes so far	*/
	int level;	/* level of current node 	*/
	FILE *fp;	/* file pointer of the words */
	logfile = fopen("C:\debug.as3", "a");   /* open the DEBUG file */
	fprintf(logfile, "\n\nStarted Buildtree--------------\n\n");

	for( level = 0; level < MAXHEIGHT; level++)
		lastnode[level] = NULL;   /* clear lastnodes to NULL */

	if (( fp = fopen("WORDS.DAT", "rt")) != NULL) {  /* open the word file */
	  while(!feof(fp))	 {	/* if file has not finished (ie not NULL) */
		p = GetNode(fp);		/* get new node from disk */
		Insert(p, ++count, lastnode);   /* insert node into Btree */
		}
	  fclose(fp);	/* close the file with words in it */
	}
	else {
		ErrorMessage("Input File could not be opened");
		return NULL;
	}
	p = FindRoot(lastnode);
	ConnectSubtrees(lastnode);
	p = FindRoot(lastnode);
	totcount = count;	/* assign total nodes entered to static var. */
	return p;		/* return Root*/

}

void Insert(Node_type *insp, int count, Node_type *lastnode[]) /* insert node as RHS of partial Btree */
{
	int level;
	if(count == 0)
		count = 7;

	level = Power2(count) + 1;

	insp->right = NULL;
	insp->left = lastnode[level - 1];
	lastnode[level] = insp;

	if(lastnode[level + 1] && !lastnode[level + 1]->right)
		lastnode[level + 1]->right = insp;

}

int Power2( int count)	/* find the highest power of 2 that divides count */
{
	int level;

	for(level = 0; !ODD(count); level++ )
		count /= 2;
	return level;
}

void Delete(Node_type **p)/* delete node, reattach left & right subtrees	*/
{
	Node_type *q;		/* used to find place for sub entries */

	if(*p == NULL)
		ErrorMessage("Cannot delete empty Node");
	else if((*p)->right == NULL) {
		q = *p;
		*p = (*p)->left;	/* reattach left subtree 	*/
		free(q);		/* release Node space		*/
	} else if ((*p)->left == NULL) {
		q = *p;
		*p = (*p)->right;	/* reattach right subtree	*/
		free(q);
	} else {		/* Neither sub tree is empty		*/
		for( q = (*p)->right; q->left; q = q->left)
			;		/*right, then to the left	*/
		q->left = (*p)->left;	/* reattach left subtree	*/
		q = *p;
		*p = (*p)->right;	/*reattach right subtree	*/
		free(q);
	}

}

Node_type *FindRoot(Node_type *lastnode[])	/* find root of Btree		*/
{
	int level;

	for(level = MAXHEIGHT - 1; level > 0 && !lastnode[level]; level--)
		;
	if(level <= 0)
		return NULL;
	else    {
		root = lastnode[level];
		return lastnode[level];
	}
}

void ConnectSubtrees(Node_type *lastnode[])	/* connect subtrees from lastnode */
{
	Node_type *cp;
	int level, templevel;

	for(level = MAXHEIGHT - 1; level > 2 && !lastnode[level]; level--)
		;		/* levels 1 and 2 are already OK.	*/
	while(level > 2) {
		if(lastnode[level]->right)
			level--;	/* search for highest dangling node */
		else {			/* right subtree is undefined	*/
			cp = lastnode[level]->left;
			templevel = level - 1;
			do {		/*find highest entry not in left subtree */
				cp = cp->right;
			} while(cp&&cp==lastnode[--templevel]);
			lastnode[level]->right = lastnode[templevel];
			level = templevel;
		}
	}
}

void Inorder(Node_type *IOroot)	/* visit each node of the tree in order */
{
	if(IOroot) {
		Inorder(IOroot->left);
		Visit(IOroot);
		Inorder(IOroot->right);
	}
}

void Visit(Node_type *proot)		/* function to write node data to disk	*/
{
     char report[256];

     sprintf(report, "%s\n", proot->info.word);
     fputs(report, op);
}


int LeftRight(void)	/* debug - asks to move to left or right node */
{
	char *ch = NULL;
	printf("Do you want to move <L>eft or <R>ight");
	fflush(stdin);  /* flush the input stream in case of bad input */

	ch = getc(stdin);
	printf("The character input was: '%c'\n", ch);
	if(ch == 'r')
		return 2;
	if(ch == 'l')
		return 1;
	return 0;

}


int TreeSearch(Node_type *p, char *testword)/* search the Btree for 'testword' */
{
	int found = 0;	/* tells if testword was found in the Btree 'root' */

	while(p && (testword != p->info.word)) {

		found = strcmp(testword, p->info.word);
		if(found == 0)
			return 1;
		if(found < 0)
			p = p->left;
		else
			p = p->right;
		}
	return 0;


}


int SaveTree(Node_type *proot)	/* save Binary Tree to disk */
{
	if (( op = fopen("WORDS.DAT", "w+")) != NULL) { /* open the word file */
		Inorder(root);
		fclose(op);	/* close the file with words in it */
		return 1;
	}
	else {
		ErrorMessage("I cannot open the WORDS.DAT file for writing");
		return 0;
	}
}