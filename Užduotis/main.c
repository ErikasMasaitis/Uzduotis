// Erikas Masaitis
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ftw.h>
#include <argp.h>
#include <dirent.h>
#include <unistd.h>

#include "lib/dynamiclibrary.h"

static char doc[] =
  "Argp example #3 -- a program with options and arguments using argp";

static char args_doc[] = "ARG1 [OPTION....] ARG2";

static struct argp_option options[] = {
  {"verbose",  'f', 0,      0,  "Priverstinis" },
  {"quiet",    't', 0,      0,  "Priverstinis" },
  { 0 }
};

struct arguments
{
  char *args[2]; 
  int FirstArg, SecondArg;
};
/** For parsing arguments.
We check for argument count
also we check if first option argument 
and third option argument is the ones
we need (-f and -t)
*/
error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;
	switch (key) {
	case 'f':
	if (state->next == 2)
	arguments->FirstArg = 1;
	break;
	case 't':
	if (state->next == 4)
	arguments->SecondArg = 1;
	break;
	
	case ARGP_KEY_INIT:
	//printf("INIT");
	break;
	case ARGP_KEY_SUCCESS:
		//printf("SUCCESS");
		break;
	case ARGP_KEY_ERROR:
		//printf("ERROR");
		break;

	case ARGP_KEY_ARG:
      if (state->arg_num >= 2)
      argp_usage (state);
      arguments->args[state->arg_num] = arg;

      break;

    case ARGP_KEY_END:
      if (state->arg_num < 2)
        argp_usage (state);
      break;
	default:
	return ARGP_ERR_UNKNOWN;
	}
	if (state->next > 5)
	{
		printf ("./telt --usage\n");
		abort();
	}
	return 0;
}

/** method for checking if arg[2] is directory
*/
void CheckDirectory(char *arg) {
	struct stat st;
	stat(arg, &st);
	
	if ((S_ISDIR(st.st_mode) == 0)) {
		printf("Program should be used: ./programa -f [DIRECTORY<----] -t [TEXT]\n");
		exit(230);
	}
}
/** Count symbols
Count every symbol in file
and return value
*/
int SymbolsCount(const char *p)
{
	FILE *fp;
	int count = 0;
	char c;
	
	    if ((fp = fopen(p, "r")) == NULL) {
        perror(p);
    }
	for (c = getc(fp); c != EOF; c = getc(fp)) {
        // Increment count for this character 
        count = count + 1; 
	}
//	printf("%d\n", count);
	return count;
}
/** Check every file
If file meets all the conditions
(permissions, non-directory, arguments)
then fgets method reads file line by line,
counting all lines and when match is found,
method prints file name and line where it was found
*/
void ScrollingThroughFiles(const char *p, char *text)
{
	
	int Symbols = 0;
	FILE *fp;
	int line = 1;
	int rv;
	Symbols = SymbolsCount(p);
	char str[Symbols+10];
    if ((fp = fopen(p, "r")) == NULL) {
        perror(p);
    }
	while (fgets(str, Symbols+10, fp) != NULL) {
		//puts(str);
      if (strstr(str, text) != NULL)
       {
            printf("Text is in file: %s line: %d\n", p, line);
        }
        line++;
    }
	   rv = fclose( fp );
	   if( rv != 0 )
	   perror ( "fclose() failed" );
   
}

/** Method for list library
Method to push few elements to list,
printing list and checking its length.
*/
void ListCommands() {
	printf("-------Linked List information-------\n");
    push("a");
    push("b+580");
    push("c");
	push("Threesad5648...");
	push("++--++");
    printList();
	printf("Length of list: %d\n", length());
}
/** Recursively go through all folders/files
First of all we need to check if we can open directory,
then we check for all non-regular files (with dots infront).
If we find folder we go into it and call dirwalk again with
that folder path. If we find regular file we call ScrollingThroughFiles
method to find our match.
*/
void dirwalk(const char *name, char *string)
{
    DIR *dir;
    struct dirent *entry;
	char path[1024];
	
    if ((dir = opendir(name)) == NULL){
		fprintf(stderr, "dirwalk: can't open %s\n", name);
        return;
	}

    while ((entry = readdir(dir)) != NULL) {
		snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
				dirwalk(path, string);
		//printf("%*s[%s]\n", entry->d_name);
        }
		if (entry->d_type == DT_REG)
		{
			ScrollingThroughFiles(path, string);
        }
    }
    closedir(dir);
}

static struct argp argp = { options, parse_opt, args_doc, doc };
/** Main method
To call other methods
*/
int main(int argc, char *argv[])  {
	struct arguments arguments;
	
    arguments.FirstArg = 0;
    arguments.SecondArg = 0;
	
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	
	if (arguments.FirstArg != 0 && arguments.SecondArg != 0)
	{
	CheckDirectory(arguments.args[0]);
	dirwalk(arguments.args[0], arguments.args[1]);
	ListCommands();
	}
	else
	{
		printf ("./telt --usage\n");
		abort();
	}	

    return 0;
}