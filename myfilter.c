#include <stdio.h>
#include <stdlib.h>
#include "mypattern.h"
#include "myfilter.h"

// Uses created table to search input file for matches.
void searchFile(char *filename)
{

	FILE *fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Error: File not valid.\n");
		freeMemory();
		exit(-1);
	}

	char *line = NULL;
	ssize_t lineSize = 0;
	ssize_t maxSize = 0-1;

	while (lineSize != maxSize) {
		struct row *curr = first;
		ssize_t index = 0;
		size_t placeVal = 0;
		line = malloc(sizeof(char));
		lineSize = getline(&line, &placeVal, fp);
		while (index < lineSize) {
			if (curr == NULL){
				// Prints the line.
				printf("%s", line);
				break;
			}
			if (curr->ascii[line[index]] == 1) {
				index++;
				if (curr->ascii[128] == 1 || curr->ascii[129] == 1) {
					while (curr->ascii[line[index]] == 1) {
						index++;
					}
				}
				curr = curr->next;
			}else{
				if (curr->ascii[128] == 1) {
					curr = curr->next;
				} else {
					curr = first;
					if (curr->ascii[line[index]] == 1) {
						curr = curr->next;
					}
					index++;
				}
			}
		}
		free(line);
	}

}