typedef enum {false, true} bool;

struct row{
	char ascii[130];
	struct row *next;
	struct row *prev;
};

struct row *first;
struct row *last;
size_t patSize;
char *pattern;
void getRegex(char *pattern_file, bool useFile);
void freeMemory();
void errorMessage();
void makeTable();