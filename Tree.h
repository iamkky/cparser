#ifndef _TREE_H_
#define _TREE_H_

#include <stdio.h>

typedef struct tree *Tree;

struct tree{
	void	*nodevalue;
	Tree	*child;
	int	n_child;
	int	n_child_allocated;
	Tree	parent;
};

Tree	treeNew(void *nodevalue);
int	treeAddChild(Tree t, Tree child);

Tree	treeGetFirstChild(Tree self);
int	treeIsLastChild(Tree self, Tree child);
Tree	treeGetNextChild(Tree self, Tree child);

int	treeFixParents(Tree self, Tree parent);

int	treeGetChildCount(Tree self);
Tree	treeGetChild(Tree self, int n);
void	*treeGetNodeVata(Tree self);

int	treeSetParent(Tree self, Tree parent);

Tree	treeReduceToMinimal(Tree t, int (*isRemovable_fn)(void *nodevalue));
int	treePrintChildreenCount(Tree t, FILE *fp, int level, int (*print_fn)(void *, FILE *, int));
int	treePrint(Tree t, FILE *fp, int level, int (*print_fn)(void *, FILE *, int));

#endif
