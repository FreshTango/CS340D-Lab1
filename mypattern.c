#include <stdio.h>
#include <stdlib.h>
#include "mypattern.h"

// Creates table based on regular expression for filtering.
void makeTable()
{
	size_t index = 0;

	if (pattern[index] == '+' || pattern[index] == '*') {
		printf("Error: Invalid pattern syntax.\n");
		exit(-1);
	}

	first = NULL;
	last = NULL;
	struct row *curr = NULL;

	while (index < patSize) {
		if (pattern[index] == '*') {
			curr->ascii[128] = 1;
			index++;
			continue;
		}
		if (pattern[index] == '+') {
			curr->ascii[129] = 1;
			index++;
			continue;
		}
		if (curr == NULL) {
			curr = malloc(sizeof(struct row));
			for (int i = 0; i < 130; i++) {
				curr->ascii[i] = 0;
			}
			curr->prev = NULL;
			curr->next = NULL;
			first = curr;
		} else {
			curr->next = malloc(sizeof(struct row));
			for (int i = 0; i < 130; i++) {
				curr->next->ascii[i] = 0;
			}
			curr->next->prev = curr;
			curr->next->next = NULL;
			curr = curr->next;
		}
		if (pattern[index] == '\\') {
			if (index + 1 < patSize) {
				curr->ascii[pattern[index+1]] = 1;
				index += 2;
				continue;
			} else {
				errorMessage();
			}
		}
		if (pattern[index] == '.') {
			for(int i = 0; i < 128; i++) {
				curr->ascii[i] = 1;
			}
			index++;
			continue;
		}
		if (pattern[index] == '@') {
			if (index + 2 < patSize){
				// Hexadecimal formatting and validity checks.
				if ('0' <= pattern[index+1] && pattern[index+1] <= '7') {
					if ('0' <= pattern[index+2] && pattern[index+2] <= '9') {
						// Converts the hexadecimal value to respective ASCII.
						char c = ((pattern[index+1] - 48) * 16) + (pattern[index+2] - 48);
						curr->ascii[c] = 1;
						index += 3;
						continue;
					} else if ('A' <= pattern[index+2] && pattern[index+2] <= 'F') {
						char c = ((pattern[index+1] - 48) * 16) + (pattern[index+2] - 65 + 10);
						curr->ascii[c] = 1;
						index += 3;
						continue;
					} else if ('a' <= pattern[index+2] && pattern[index+2] <= 'f') {
						char c = ((pattern[index+1] - 48) * 16) + (pattern[index+2] - 97 + 10);
						curr->ascii[c] = 1;
						index += 3;
						continue;
					} else {
						errorMessage();
					}
				} else {
					errorMessage();
				}
			} else {
				errorMessage();
			}
		}
		if (pattern[index] == '[') {
			if (index + 1 < patSize){
				if (pattern[index+1] == ']') {
					errorMessage();
				}
				bool complement = false;
				if (pattern[index+1] == '^') {
					if (index + 2 < patSize) {
						if (pattern[index+2] == ']') {
							errorMessage();
						}
						complement = true;
						index += 2;
					} else {
						errorMessage();
					}
				} else {
					index++;
				}
				while (index < patSize) {
					if (pattern[index] == ']') {
						index++;
						break;
					}
					if (pattern[index] == '\\') {
						if (index + 1 < patSize) { 
							curr->ascii[pattern[index+1]] = 1;
							index += 2;
							continue;
						} else {
							errorMessage();
						}
					}
					if (pattern[index] == '@') {
						if (index + 2 < patSize) {
							if ('0' <= pattern[index+1] && pattern[index+1] <= '7') {
								char c;
								if ('0' <= pattern[index+2] && pattern[index+2] <= '9') {
									c = ((pattern[index+1] - 48) * 16) + (pattern[index+2] - 48);
									curr->ascii[c] = 1;
									index += 3;
								} else if ('A' <= pattern[index+2] && pattern[index+2] <= 'F') {
									c = ((pattern[index+1] - 48) * 16) + (pattern[index+2] - 65 + 10);
									curr->ascii[c] = 1;
									index += 3;
								} else if ('a' <= pattern[index+2] && pattern[index+2] <= 'f') {
									c = ((pattern[index+1] - 48) * 16) + (pattern[index+2] - 97 + 10);
									curr->ascii[c] = 1;
									index += 3;
								} else {
									errorMessage();	
								}
								if (index < patSize) {
									if (pattern[index] == '-') {
										if (index + 3 < patSize) {
											if (pattern[index+1] == '@') {
												if ('0' <= pattern[index+2] && pattern[index+2] <= '7') {
													char c2;
													if ('0' <= pattern[index+2] && pattern[index+2] <= '9') {
														c2 = ((pattern[index+2] - 48) * 16) + (pattern[index+3] - 48);
														curr->ascii[c2] = 1;
														index = index + 4;
													} else if ('A' <= pattern[index+2] && pattern[index+2] <= 'F') {
														c2 = ((pattern[index+2] - 48) * 16) + (pattern[index+3] - 65 + 10);
														curr->ascii[c2] = 1;
														index = index + 4;
													} else if ('a' <= pattern[index+2] && pattern[index+2] <= 'f') {
														c2 = ((pattern[index+2] - 48) * 16) + (pattern[index+3] - 97 + 10);
														curr->ascii[c2] = 1;
														index = index + 4;
													} else {
														errorMessage();	
													}
													if (c <= c2) {
														while(c <= c2) {
															curr->ascii[c++] = 1;
														}
														continue;
													} else {
														errorMessage();
													}
												} else {
													errorMessage();
												}
											} else {
												errorMessage();
											}
										} else {
											errorMessage();
										}
									}
								}
								continue;
							} else {
								errorMessage();
							}
						} else {
							errorMessage();
						}
					}
					curr->ascii[pattern[index]] = 1; 
					index++;
				}
				if (complement) {
					for (int i = 0; i < 128; i++) {
						if (curr->ascii[i] == 1)
							curr->ascii[i] = 0;
						else
							curr->ascii[i] = 1;
					}
				}
				continue;
			} else {
				errorMessage();
			}
		}
		curr->ascii[pattern[index]] = 1;
		index++;
	}

	last = curr;

}
