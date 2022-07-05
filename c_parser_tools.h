#ifndef _C_PARSER_TOOLS_H_
#define _C_PARSER_TOOLS_H_

int printNodeValueOnlyToken(void *nodevalue, FILE *fp, int level);
int printNodeValue(void *nodevalue, FILE *fp, int level);
int isRemovable(void *nodevalue);

#endif
