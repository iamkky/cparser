#include <string.h>
#include <stdlib.h>

void *memdup_safe(void *src, int size)
{
void *dst;

	if((dst=malloc(size))==NULL) return NULL;
	if(src==NULL)
		memset(dst, 0, size);
	else
		memcpy(dst, src, size);
	return dst;
}

void *memdup(void *src, int size)
{
void *dst;

	if(src==NULL) return NULL;
	if((dst=malloc(size))==NULL) return NULL;
	memcpy(dst, src, size);
	return dst;
}


