#include <stdlib.h>
#include <stdio.h>
#include "Type.h"

Type typeNew(int basic_type, int primitive_subtype, int dimension, int bsize)
{
Type self;

        if((self = malloc(sizeof(*self)))==NULL) return NULL;

	self->basic_type = basic_type;
	self->primitive_subtype = primitive_subtype;
	self->dimension = dimension;
	self->bsize = bsize;

	return self;
}

void typePrint(Type self, FILE *fp)
{

	if(self==NULL){
		fputs("(NULL)", fp);
		return;
	}

	fputs("(", fp);
	switch(self->basic_type){
	case TYPE_PRIMITE:
		switch(self->primitive_subtype){
		case PSTYPE_INT:   fputs("INT", fp); break;
		case PSTYPE_FLOAT: fputs("FLOAT", fp); break;
		case PSTYPE_CHAR:  fputs("CHAR", fp); break;
		default:           fputs("UNKNOW PRIMITIVE SUBTYPE", fp); break;
		}
		break;
	case TYPE_ARRAY:
		fputs("ARRAY OF", fp);
		typePrint(self->next, fp);
		break;
	case TYPE_POINTER:
		fputs("POINTER TO", fp);
		typePrint(self->next, fp);
		break;
	default:
		fputs("UNKNOW TYPE", fp);
		break;
	}
	fputs(")", fp);
}
