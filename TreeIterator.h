#ifndef _TREEITERATOR_H_
#define _TREEITERATOR_H_

#include "Tree.h"

typedef struct treeIterator_struct *TreeIterator;

struct treeIterator_struct{
	Tree    last;
	int	level;
};

TreeIterator treeIteratorNew();
Tree treeIteratorBeginPreorder(TreeIterator self, Tree root);
Tree treeIteratorNextPreorder(TreeIterator self);

#endif
