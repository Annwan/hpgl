#include "log.h"
#include <stdio.h>

void log_error(const char* msg){
	fprintf(stderr, "[ERROR] %s\n", msg);
}

void log_notice(const char* msg){
#ifdef DEBUG
	fprintf(stderr, "[NOTICE] %s\n", msg);
#endif
}
