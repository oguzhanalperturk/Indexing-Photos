

struct node{    /* For TreeNode->next, I made linked list for the countries which has the same name with the country in the treenode. I connect this linked list to treeNode->next.  */
	int balancefactor;
	char Name[20];
	char Dimension[20];
	char Size[20];
	char City[20];
	char Country[20];
	int Year;
	struct node *next;
};

struct TreeNode{       /* The node's of the tree.  */
	int balancefactor;
	char Name[20];
	char Dimension[20];
	char Size[20];
	char City[20];
	char Country[20];
	int Year;
	struct TreeNode *left;
	struct TreeNode *right;
	struct node *next;

};
typedef struct TreeNode *Tree;

struct stacknode{   /* Node of stack. I store tree nodes in data and link them with next pointer.  */
	Tree data;
	struct stacknode *next;
};

struct StackRecord{
 	struct stacknode *bottom;
 	struct stacknode *top;
 	int size;
};
typedef struct StackRecord *Stack;

struct yearnode{       /*   Using in the popularyear function.  */
	int year;
	int numberofphoto;
	struct yearnode *next;
};

struct ListRecord{
	struct yearnode *head;
	struct yearnode *tail;
	int size;
};
typedef struct ListRecord *List;


Tree pop(Stack temp);	

void push(Tree t,Stack temp);

Tree IterativeInsertBinarySearchTree(Tree t,struct node *x);

int IsAvlTree(Tree t);  /* 1 AVL Tree, 0 Not AVL Tree  */

int TreeHeight(Tree t);   /* For adding t == NULL condition  */

int Height(Tree t);   /* not include t == NULL condition  */

Tree CopyTree(Tree t);

Tree FindUnbalancedTree(Tree t);

void BalanceFactorCalculator(Tree t);

Tree LeftRotate(Tree t);
	
Tree RightRotate(Tree t);

Tree LeftRight(Tree t);

Tree RightLeft(Tree t);

Tree InsertTree(Tree insert, Tree t,char country[20]);    /* Inserting tree to tree, value is the root node's value of insert tree, so that I can find the insertion location. */

Tree insertPhoto(Tree t,struct node *n);

Tree IterativeInsertBinarySearchTree(Tree t,struct node *x);

Tree readData(char filename[20]);
	
void displayIndex(Tree t);

Tree FindMaXPopularCountry(Tree t,char maxcountryname[20]);

void popularCountry(Tree t); 

Tree FindMaXPopularCountry(Tree t,char maxcountryname[20]);

void displayMaxYearPhotos(Tree t,int year);

void popularYear(Tree t);
	
char *parseInput(int argc,char *argv[]);



