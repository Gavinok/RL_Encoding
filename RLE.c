#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    /*
     * check for 2 commandline arguments
     * check that the 2nd arg is either e or d
     */
    if ( (argc != 3)  || ((strcmp(argv[2], "e")) && (strcmp(argv[2], "d"))) ) {
	fprintf(stderr,"Invalid Usage, expected: RLE {filename} [e | d]\n");
	exit(4);
    }
    /*
     * ASK A QUESTION ABOUT 
     * i.  If there is no filename specified: 
     *	    1.  print “Error: No input file specified!” to the console 
     *	    2.  terminate the program with exit code 1. 
     */

    /* open file  */
    const char *filename = argv[1];
    FILE *file_pointer = fopen(filename, "r");
    if (file_pointer == NULL) {
	fprintf(stderr, "Read error: file not found or cannot be read\n");
	exit(2);
    }
    /* File is now open */

    //buffer needs to be 41 since we need and extra character for \0
    char buffer[41]; //buffer for storing the string from the file 
    char place_holder; //char used to hold the current character for checking its value
    /* int length = sizeof(buffer); */
    int length = 41;

    /* printf("isupper for 1 is %d\n", isupper('1')); */
    int i = 0;
    while (i <= length) {
	place_holder = fgetc(file_pointer); 
	if ( place_holder == EOF ){
	    buffer[i] = '\0';
	    printf("break\n");
	    printf("buffer is %s\n", buffer);
	    break; 
	}
	printf("place_holder is %c\n", place_holder);
	if ( isupper(place_holder) || isdigit(place_holder) ){
	    buffer[i] = place_holder;
	    i++;
	} else { 
	    printf("non digit of uppercase letter found");
	    /* make sure the rest of the fomating is correct*/
	    while (place_holder != EOF) {
		/* if the the next char from the file is 
		 * not whitespace or the formatting is Invalid*/
		if (place_holder != ' ') {
		    printf("Error: Invalid format\n");
		    exit(3);
		}
		place_holder = fgetc(file_pointer); 
	    }
	    buffer[i] = '\0';
	    break; /* formatting is correct so exit loop */
	}
	printf("buffer is %s\n", buffer);
	printf("i is %d\n", i);
    }
    fclose(file_pointer);
    /* File is now closed */

    /* string from file is now stored in buffer*/
    return 0;
}
