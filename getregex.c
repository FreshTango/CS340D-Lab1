#include <stdio.h>
#include <stdlib.h>
#include "mypattern.h"

// Gets the regular expression to prepare for parsing.
void getRegex(char *pattern_file, bool useFile)
{

	FILE *fp = fopen(pattern_file, "r");

	if (fp == NULL) {
		printf("Error: File not valid.\n");
		exit(-1);
	}

	char c;
	patSize = 0;

	while ((c = getc(fp)) != EOF) {
		patSize++;
	}

	if (patSize == 0) {
		printf("Error: No pattern found in provided file.\n");
		exit(-1);
	}

	rewind(fp);

	size_t index = 0;
	pattern = malloc(patSize + 1);

	while ((c = getc(fp)) != EOF) {
		pattern[index++] = c;
	}
	pattern[index] = '\0';
}