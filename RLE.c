#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* The encoded string must at most contain half digits and half alphas.
 * the digits have a maximum of 9. 9*20 is 180 ( chars in a sequence ), 
 * and with the extra 20 alphas an extra for the \0 we get 201 */
#define MAX_DECODEDSIZE 201
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
						/* make sure the rest of the fomating is correct*/
						printf("make sure the rest of the fomating is correct\n");
						while ( place_holder != EOF ) {
								if ( !isspace(place_holder) ) {
										printf("place_holder is not Whitespace it is %c\n", place_holder);
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
		int length = strlen(buffer);    /* length of the given buffer */
		int sequence_counter = 0;	    /* keeps track of the repeated characters */
		int encoded_str_pos = 0;	    /* keeps track of the resulting string position */
		char encoded_str[ length + 1 ]; /* resulting string */
		char last_char = buffer[0];	    /* last char spotted in original string*/
		for (int i = 0; i <= length; ++i) {
				/* print error if the sequence is a double digit 
				 * or contains a non alpha */
				if (( sequence_counter <= 10 ) && ( !isalpha(last_char) )) { 
						printf("sequence_counter is %d\n", sequence_counter);
						printf("Error: String could not be encoded\n");
						exit(5);
				}
				if ( last_char == buffer[i]) {
						printf("last_char is %c\n", last_char);
						printf("matches last char\n");
						sequence_counter++; 
						printf("sequence_counter is %d\n", sequence_counter);
				} else {
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
}

/* TODO: complete decode */
void decode( char buffer[] )
{
		int decoded_str_pos = 0;	    /* keeps track of the resulting string position */
		char decoded_str [ MAX_DECODEDSIZE ]; /* resulting string */
		char last_char = '0';	    /* last char spotted in original string*/
		for (int i = 0; buffer[i] != '\0'; ++i) {
				if ( isalpha(buffer[i]) && isdigit(last_char) ) {
						printf("alpha found\n");
						printf("buffer[i] is %c\n", buffer[i]);
						last_char = buffer[i]; 
				} else if ( isdigit(buffer[i]) && isalpha(last_char)) {
						printf("digit found\n");
						printf("buffer[i] is %c\n", buffer[i]);
						for (int j = 0; j < ( buffer[i] - '0' ); j++) {
								printf("j is %d\n", j);
								printf("buffer[i] is %c\n", buffer[i]);
								decoded_str[decoded_str_pos] = last_char;
								decoded_str[decoded_str_pos + 1] = '\0';
								printf("last_char is %c\n", last_char);
								printf("decoded_str is %s\n", decoded_str);
								decoded_str_pos++;
						}
						last_char = buffer[i];
						printf("digits finished\n");
				} else {

								printf("Error: String could not be decoded\n");
								exit(5);
				}
				printf("i is %d\n", i);
				printf("decoded_str_pos is %d\n", decoded_str_pos);
				printf("decoded_str is %s\n", decoded_str);
				last_char = buffer[i];
		}
		decoded_str[decoded_str_pos] = '\0';
		printf("%s\n", decoded_str);
}
