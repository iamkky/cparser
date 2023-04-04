#ifndef _TYPES_H_
#define _TYPES_H_

enum basic_types {TYPE_PRIMITE=1, TYPE_ARRAY, TYPE_POINTER};
enum primitive_subtypes {PSTYPE_INT=1, PSTYPE_FLOAT, PSTYPE_CHAR};

typedef struct type *Type;

struct type {
	int	basic_type;
	int	primitive_subtype;
	int	dimension;
	int	bsize;
	Type	next;
};

#endif
