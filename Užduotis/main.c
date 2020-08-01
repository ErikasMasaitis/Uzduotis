// Erikas Masaitis
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ftw.h>

#include "lib/dynamiclibrary.h"

char *text;

/** Method for checking possible arguments
Method to find how much arguments we use
and do they meets requirements:
Program should be used: ./programa -f [DIRECTORY] -t [TEXT].
*text is global pointer variable where we put text of what
we want to find in files
*/
void Arguments(char * arg[], int argc, char **text_temp) {
	
	if 	(argc > 5 || argc < 5) {
		printf("Program should be used: ./programa -f [DIRECTORY] -t [TEXT]\n");
		exit(210);
	}
	else if (strcmp(arg[1], "-f") != 0 || strcmp(arg[3], "-t") != 0) {
		printf("Program should be used: ./programa -f [DIRECTORY] -t [TEXT]\n");
		exit(220);
	}
	*text_temp = arg[4];
	text = *text_temp;
}
/** method for checking if arg[2] is directory
*/
void CheckDirectory(char *arg[]) {
	struct stat st;
	stat(arg[2], &st);
	
	if ((S_ISDIR(st.st_mode) == 0)) {
		printf("Program should be used: ./programa -f [DIRECTORY<----] -t [TEXT]\n");
		exit(230);
	}
}
/** Check every file
If file meets all the conditions
(permissions, non-directory, arguments)
then fgets method reads file line by line,
counting all lines and when match is found,
method prints file name and line where it was found
*/
void ScrollingThroughFiles(const char *p)
{
	FILE *fp;
	int line = 1;
	int rv;
	char str[60];
		
    if ((fp = fopen(p, "r")) == NULL) {
        perror(p);
    }
	while (fgets(str, 60, fp) != NULL) {
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
/** 
Method for checking if every found file
is a non-directory file and checking
if that file has read permission
*/
int kp_ftwinfo(const char *p, const struct stat *st, int fl, struct FTW *fbuf) {	
	if (fl == FTW_F && (st->st_mode & S_IRUSR)){
		ScrollingThroughFiles(p);
		//perror(p);
	}
	else
	{
		// printf("%s is not file or has no read permission\n", p);
	}
	return 0;
}
/** Method for execute of NFTW.
Method for executing NFTW (walk a file tree) method.
If NFTW fails (no permissions), method prints "Failed".
*/
	void FileSearch(char *arg[]) {
	int rv;
	rv = nftw(arg[2], kp_ftwinfo, 500, 0);
	if (rv == -1)
	{
		fprintf(stderr, "Failed.\n");
		abort();
	}
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
/** Main method
To call other methods
*/
int main(int argc, char *argv[])  {
	char *text_temp = NULL;
    Arguments(argv, argc, &text_temp);
	CheckDirectory(argv);
	FileSearch(argv);
	ListCommands();

    return 0;
}