#ifndef _TREE_H_
#define _TREE_H_

typedef struct tree *Tree;

struct tree{
	int	type;
	char	*value;
	Tree	*child;
	int	n_child;
	int	n_child_allocated;
	char	*file;
	int	lnumber;
};

Tree treeNew(int type, char *value, char *file, int lnumber);
int treeAddChild(Tree t, Tree child);
Tree treeReduceToMinimal(Tree t, int nt_start);
int treePrint(Tree t, FILE *fp, int level);
int treePrintToken(Tree t, FILE *fp, int level, int non_terminal_start);

#endif
