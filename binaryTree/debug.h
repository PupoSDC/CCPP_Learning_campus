#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG
	#define _DEBUG(exp) exp
#else
	#define _DEBUG(exp) ;
#endif

#endif