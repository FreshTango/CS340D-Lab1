#include <stdio.h>
#include <stdlib.h>
#include "mypattern.h"

// Method to free used memory. 
void freeMemory()
{
	free(pattern);
	// Iterates through struct to free memory.
	while(first->next != NULL){
		first = first->next;
		free(first->prev);
	}
	free(first);
	pattern, first, last = NULL;

}
