#ifndef _TREE_H_
#define _TREE_H_

typedef struct tree *Tree;

struct tree{
	int	type;
	char	*value;
	Tree	child[128];
	int	n_child;
};

Tree treeNew(int type, char *value);
int treeAddChild(Tree t, Tree child);
Tree treeReduceToMinimal(Tree t, int nt_start);
int treePrint(Tree t, FILE *fp, int level);
int treePrintToken(Tree t, FILE *fp, int level, int non_terminal_start);

#endif
