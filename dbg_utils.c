#include <stdio.h>
#include <stdlib.h>

#include "dbg_utils.h"

void dbg_stop(void) {
	printf("dbg: stoped\n");
	getchar();
	getchar();
}