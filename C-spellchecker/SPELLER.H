/* Header file for Spell Checking Functions for DFLAT		*/
/* written by Duncan Murray for ADVC, ASSIGN3 on 14/5/94	*/

/* Declarations */
typedef struct item_tag {
	char word[30];		/* word in the Binary tree		*/
} Item_type;

typedef struct node_tag {
	Item_type info;		/* word in the Binary tree		*/
       /*	char *word;		/* modified struct 30/5/94		*/
	struct node_tag *left;	/* branch pointing to LEFT		*/
	struct node_tag *right;	/* branch pointing to RIGHT		*/
} Node_type;


#define ODD(x) ((x)/2*2 != (x))

static int MAXHEIGHT = 13;

static Node_type *p;	/* Tempory pointer for the tree			*/
static char *target;	/* key for which we search			*/

static Node_type *root;/* pointer to the root of the Binary Tree 	*/
static Node_type *lastnode[12];	/*pointers to last node on each level */
static int totcount = 0;/* total number of nodes in the Btree */


/* function prototypes */
void MainSpell(WINDOW);	/* main spelling routine */
void Spell(WINDOW, char *);  	/* function to handle the main spell check facilities */
void checkword(WINDOW, char *);	/* function to test a single word		*/
static int SpellCheckProc(WINDOW, MESSAGE, PARAM, PARAM); /* spellcheck processor for dialogbox */


void Changeword(void);
void AddwordtoDic(void);
void Ignoreword(void);


void Visit(Node_type *);	/* function to display node info	*/
void Inorder(Node_type *root);	/* visit each node of the tree in order	*/
Node_type *GetNode(FILE *);	/* get a new node with data for BTree	*/
Node_type *BuildTree(void);		/* build nodes - uses GLOBAL *root	*/
/*Node_type *BuildTree(void);	/* build nodes from GetNode into a BTree*/
void Insert(Node_type *p, int count, Node_type *lastnode[]); /* insert node as RHS of partial Btree */
int Power2( int);	/* find the highest power of 2 that divides count */
void Delete(Node_type **p);/* delete node, reattach left & right subtrees	*/
Node_type *FindRoot(Node_type *lastnode[]);	/* find root of Btree		*/
void ConnectSubtrees(Node_type *lastnode[]);	/* connect subtrees from lastnode */

int TreeSearch(Node_type *, char *); /* search the Btree for 'testword' */


