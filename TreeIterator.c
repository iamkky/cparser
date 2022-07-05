#include <stdlib.h>
#include "Tree.h"

typedef struct treeIterator_struct *TreeIterator;
struct treeIterator_struct{
	Tree    last;
	int	level;
};

TreeIterator treeIteratorNew()
{
TreeIterator self;
	
	if((self=malloc(sizeof(struct treeIterator_struct)))==NULL) return NULL;
	
	self->last = NULL;
	self->level = 0;

	return self;
}

Tree treeIteratorBeginPreorder(TreeIterator self, Tree root)
{
	self->last = root;
	return self->last;
}

Tree treeIteratorNextPreorder(TreeIterator self)
{
Tree parent, current;

	if(self->last->n_child>0) {
		self->level = self->level + 1;
		return self->last = treeGetFirstChild(self->last);
	}

	parent = self->last->parent;

        while(treeIsLastChild(parent, self->last)){
		self->level = self->level - 1;
		self->last = parent;
		parent = self->last->parent;
	}

	return self->last = treeGetNextChild(parent, self->last);
}
