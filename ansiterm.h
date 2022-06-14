#ifndef _ANSITERM_H_
#define _ANSITERM_H_

#ifdef NO_ANSITERM

#define ANSIRED	
#define ANSIGREEN
#define ANSIYELLOW
#define ANSIBLUE
#define ANSIRESET
#define ANSIBOLD

#else

#define ANSIRED		"\e[0;1;31m"
#define ANSIGREEN	"\e[0;1;32m"
#define ANSIYELLOW	"\e[0;1;33m"
#define ANSIBLUE	"\e[0;1;34m"
#define ANSIRESET	"\e[0m"
#define ANSIBOLD	"\e[1m"

#endif

#endif
