/* 
Lab 1
Name: Khiem Tang
UTEID: KLT2399

ATTRIBUTION NOTE: Given the difficulty of the lab, I worked with a fellow 340D classmate,
David Chavarria, to create a detailed implementation approach and solution for the function.
While still missing some functionality, we worked together to formulate the strategy of creating
a table to interpret each character of the regex expression, and a defined set of rules
and cases to take into consideration when implementing the expression parsing.
*/

/*
						mygrep Command Overview

!!		Read USAGE NOTES below for formatting necessary for correct working of program.

NAME
       mygrep - searches the input (from an input file or standard input), for lines that
       contain a match based on the inputted pattern file. 

SYNOPSIS
		mygrep [options]... [-f file] [file]...

DESCRIPTION
       The mygrep function parses a given regular expression provided in the pattern file,
       and searches the given inputted file for matches of that given pattern. The function
       will return any lines that have a valid match of the pattern.

       The compatible regular expression symbols available in the function are:

       GENERAL SYMBOL FUNCTIONS
		
	   All printable and nonprintable ASCII characters (further detailed below).
	   	
       + Searches for one or more occurrences of a character.
       * Searches for zero or more occurrences of a character.
       \ Utilized as an escape character and provides alternate meaning to certain symbols.
       		Example: Characters such as '+' and '*', displayed above, with a preceding '\'
       		character will search simply for the literal symbol itself rather than the 
       		special definition.

       SET SYMBOL FUNCTIONS

       [] Utilized to denote a character set, useful for finding multiple possible values for
       one character within the given sequence.
       - Searches for a range of characters. Requires either a hexidecimal (@xx), decimal, or 
       alphanumeric character before and after the '-' to create a valid range.
       		Example: a-z, @00-@02
       ^ Searches for the complement of the characters following the symbol in a given set.
       To evoke the special definition, character must be at the beginning of a set.
       		Example: [^abc]

       SPECIAL FUNCTIONS

       @ Reads in a hexidecimal value and interprets the value as a specific ASCII character.
       Must be printed in the format 'xx' (xx being a valid hexidecimal number within the
	   the standard ASCII table), following the '@' symbol.
	   		Example: @41, @2B

		Examples of calling the mygrep command include:

		mygrep -f regex.txt test.txt
			Utilizes the regular expression found in regex.txt and searches the file test.txt
			for appropriate matches. Returns the lines with found matches.
		mygrep --file= regex.txt test.txt
			dumps the character from a file beginning from the second character, offset
			placed as a decimal representation. Prints out only after one character.
			Another possible flag interpretation.

USAGE NOTES (!!!IMPORTANT!!!)
		In its current state, the mygrep function will only be able to accept the search file if
		there is a blank line as the last line of the file. An example would be reaching the final
		character of the input file and simply performing a carriage return.
		This is due to the implementation of the function using getline(). 

		In addition, cases that involve redundant (or poorly written) regular expressions are not
		covered by the mygrep function. An example includes: 'ab+bc' or 'ab*bc' (the 'b' following
		the '+' or '*' in this case is not required, and can simply be omitted).

IMPLEMENTATION
		The implementation of mygrep follows a streamlined flow from mygrep.c -> mypattern.c -> myfilter.c.
		The program begins by accepting the command line input and parsing the input for the respective
		pattern and search file, searching for any flags. The program then parses the regular expression 
		provided that the expression is valid within the grammar of the function, and proceeds to create a
		table. This table allows the function to specifically search for ASCII values corresponding to each
		character in the inputted expression. In addition, the table tells the function whether to look 
		for a certain amount of the same character, as is required for symbols like '+' and '*'. Finally, after
		the creation of the table, the function searches line by line to find matches of the given regular
		expression using the information from the table. Matched lines are returned.

*/

#include <stdio.h>
#include <stdlib.h>
#include "mypattern.h"
#include "myfilter.h"

// String comparator function
bool strCmp(char *a, char *b)
{
    int i = 1;
    for (i = 0; a[i] != '\0' || b[i] != '\0'; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return true;
}

int main(int argc, char *argv[], char *envp[])
{
	char *pattern_file = NULL;
	char *file = NULL;
	bool useFile = false;

	if (argc < 4) {
		printf("Incorrect number of arguments. Example: mygrep -f <pattern> <file>\n");
		exit(-1);
	}

	// Flags for file input.
	if (strCmp(argv[1], "-f") || strCmp(argv[1], "--file=")) {
		pattern_file = argv[2];
		file = argv[3];
	} else {
		useFile = true;
	}

	if (useFile == false) {
		getRegex(pattern_file, useFile);
	} else {
		getRegex(argv[1], useFile);
	}
	makeTable();
	searchFile(file);
	freeMemory();
	return 0;
}