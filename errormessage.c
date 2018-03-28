#include <stdio.h>
#include <stdlib.h>
#include "mypattern.h"

// Used to print general error message and to free/exit properly.
void errorMessage()
{
	printf("Error: Invalid pattern syntax.\n");
	freeMemory();
	exit(-1);
}