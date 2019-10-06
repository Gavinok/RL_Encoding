#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* buffer needs to be 41 since we need and extra character for \0 */
#define BUFFERSIZE 41
#define DEBUG

void encode( char buffer[] );
void decode( char buffer[] );

/* TODO ask if we can use seperate functions to make main more readable*/
int main(int argc, char *argv[])
{
    /* check for 2 commandline arguments
     * check that the 2nd arg is either e or d */
    if ( (argc != 3)  || ((strcmp(argv[2], "e")) && (strcmp(argv[2], "d"))) ) {
	fprintf(stderr,"Invalid Usage, expected: RLE {filename} [e | d]\n");
	exit(4);
    }

    /* TODO ASK A QUESTION ABOUT 
     * i.  If there is no filename specified: 
     *	    1.  print “Error: No input file specified!” to the console 
     *	    2.  terminate the program with exit code 1.  */

    /* OPEN FILE  */
    const char *filename = argv[1];
    FILE *file_pointer = fopen(filename, "r");
    if (file_pointer == NULL) {
	fprintf(stderr, "Read error: file not found or cannot be read\n");
	exit(2);
    }
    /* FILE IS NOW OPEN */

    char buffer[BUFFERSIZE]; /* buffer for storing the string from the file  */
    char place_holder; /* char used to hold the current character for checking its value */
    int length = BUFFERSIZE;

    /* printf("isupper for 1 is %d\n", isupper('1')); */
    int i = 0;
    while ( i <= length ) {
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
	    while ( place_holder != EOF ) {
		/* if the the next char from the file is 
		 * not whitespace or the formatting is Invalid*/
		if ( place_holder != ' ' ) {
		    /* formatting is incorrect so exit program */
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
    /* FILE IS NOW CLOSED */
    /* STRING FROM FILE IS NOW STORED IN BUFFER*/

    /* check if encoding*/
    if ( !strcmp(argv[2], "e") ) {
	encode(buffer); 
    } else {
	decode(buffer); 
    }
    return 0;
}

void encode( char buffer[] )
{

    int length = strlen(buffer); /* length of the given buffer */
    char encoded_str[ length + 1 ];
    char last_char = buffer[0];
    printf("length is %d\n", length);
    int sequence_counter = 0;
    int encoded_str_pos = 0;
    for (int i = 0; i <= length; ++i) {
	if ( last_char == buffer[i]) {
	    printf("last_char is %c\n", last_char);
	    printf("matches last char\n");
	    sequence_counter++; 
	    printf("sequence_counter is %d\n", sequence_counter);
	}else{
	    /* add the next sequence to string */
	    encoded_str[encoded_str_pos] = last_char;
	    encoded_str[encoded_str_pos + 1] = (sequence_counter + '0');
	    encoded_str_pos += 2;
	    printf("encoded_str is %s\n", encoded_str);
	    sequence_counter = 1;
	    printf("sequence_counter is %d\n", sequence_counter);
	}
	    printf("i is %d\n", i);
	    printf("sequence_counter is %d\n", sequence_counter);
	    printf("encoded_str_pos is %d\n", encoded_str_pos);
	last_char = buffer[i];
    }
    encoded_str[encoded_str_pos] = '\0';
    printf("%s\n", encoded_str);

    /* errors */
    printf("Error: String could not be encoded\n");
    exit(5);
}

void decode( char buffer[] )
{
    int length = strlen(buffer);
    char encoded_str[ length + 1 ];
    char last_char = '\0';
    char place_holder = 0;
    int sequence_counter = 0;
    for (int i = 0; place_holder != '\0'; ++i) {
	place_holder = buffer[i];
	if ( last_char == place_holder) {
	    sequence_counter++; 
	}else{
	    encoded_str[ i - sequence_counter ];
	    sequence_counter = 0;
	}
	last_char = place_holder;
    }
    printf("%s\n", encoded_str);
}
