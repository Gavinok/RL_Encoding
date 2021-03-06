#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* The encoded string must at most contain half digits and half alphas.
 * the digits have a maximum of 9. 9*20 is 180 ( chars in a sequence ),
 * and with the extra 20 alphas an extra for the \0 we get 201 */
#define MAX_DECODED_SIZE 201
/* buffer needs to be 41 since we need and extra character for \0 */
#define BUFFERSIZE 41
#define DEBUG

void encode( char buffer[] );
void decode( char buffer[] );
int isvalid( char letter );	

int main(int argc, char *argv[])
{
	/* check for 2 commandline arguments
	 * check that the 2nd arg is either e or d */
	if ( (argc != 3)  || ((strcmp(argv[2], "e")) && (strcmp(argv[2], "d"))) ) {
		fprintf(stderr,"Invalid Usage, expected: RLE {filename} [e | d]\n");
		exit(4);
	}

	/* OPEN FILE  */
	const char *filename = argv[1];
	/* check if the filename is completely empty*/
	if ( !strcmp(filename, "") ) {
		printf("Error: No input file specified!\n");
		exit(1);
	}
	FILE *file_pointer = fopen(filename, "r");
	if (file_pointer == NULL) {
		printf("Read error: file not found or cannot be read\n");
		exit(2);
	}
	/* FILE IS NOW OPEN */
	char buffer[BUFFERSIZE]; /* buffer for storing the string from the file  */
	char place_holder; /* char used to hold the current character for checking its value */
	int length = BUFFERSIZE;

	int i = 0;
	while ( i <= length ) {
		place_holder = fgetc(file_pointer);
		if ( place_holder == EOF ){
			buffer[i] = '\0';
			break;
		}
		if ( isupper(place_holder) || isdigit(place_holder) ){
			buffer[i] = place_holder;
			i++;
		} else {
			/* make sure the rest of the fomating is correct*/
			while ( place_holder != EOF ) {
				if ( !isspace(place_holder) ) {
					printf("Error: Invalid format\n");
					exit(3);
				}
				place_holder = fgetc(file_pointer);
			}
			buffer[i] = '\0';
			break; /* formatting is correct so exit loop */
		}
	}
	fclose(file_pointer);
	/* FILE IS NOW CLOSED */
	/* STRING FROM FILE IS NOW STORED IN BUFFER*/

	/* Check If Encoding*/
	if ( !strcmp(argv[2], "e") ) {
		encode(buffer);
	} else {
		decode(buffer);
	}
	return 0;
}

/* check that the letter is valid for encodeing and decoding */
int isvalid( char letter )
{
	switch ( letter ) {
		case 'A':
			return 1;
		case 'C':
			return 1;
		case 'T':
			return 1;
		case 'G':
			return 1;
		default:
			return 0;
	}
}

void encode( char buffer[] )
{
	int length = strlen(buffer);    /* length of the given buffer */
	int sequence_counter = 0;	    /* keeps track of the repeated characters */
	int encoded_str_pos = 0;	    /* keeps track of the resulting string position */
	char encoded_str[ length + 1 ]; /* resulting string */
	char last_char = buffer[0];	    /* last char spotted in original string*/
	int i;
	for ( i = 0; i <= length; ++i) {
		if ( !isvalid(last_char) ) {
			printf("Error: String could not be encoded\n");
			exit(5);
		}
		if ( last_char == buffer[i] ) {
			sequence_counter++;
		} else {
			/* add the next sequence to string */
			encoded_str[encoded_str_pos] = last_char;
			encoded_str[encoded_str_pos + 1] = (sequence_counter + '0');
			encoded_str_pos += 2;
			sequence_counter = 1;
		}
		last_char = buffer[i];
	}
	encoded_str[encoded_str_pos] = '\0';
	printf("%s\n", encoded_str);
}

void decode( char buffer[] )
{
	int decoded_str_pos = 0;	    /* keeps track of the resulting string position */
	char decoded_str [ MAX_DECODED_SIZE ]; /* resulting string */
	char last_char = '0';	    /* last char spotted in original string*/
	int i;
	for ( i = 0; buffer[i] != '\0'; ++i) {
		if ( isalpha(buffer[i]) && isvalid(buffer[i]) && isdigit(last_char)  ) {
			last_char = buffer[i];
		} else if ( isdigit(buffer[i]) && isalpha(last_char)) {
			/* add the sequence to the string */
			int j;
			for ( j = 0; j < ( buffer[i] - '0' ); j++) {
				decoded_str[decoded_str_pos] = last_char;
				decoded_str[decoded_str_pos + 1] = '\0';
				decoded_str_pos++;
			}
			last_char = buffer[i];
		} else {
			/* the this the string is invalid and does not follow
			 * the expected order */
			printf("Error: String could not be decoded\n");
			exit(5);
		}
		last_char = buffer[i];
	}
	decoded_str[decoded_str_pos] = '\0';
	printf("%s\n", decoded_str);
}
