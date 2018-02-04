#include <iostream>
#include <stdio.h>

#define STRING_ARRAY_SIZE 16

/*
 * Example program for parsing strings using sscanf
 * http://www.manpages.info/linux/scanf.3.html
 */
int main() {
	unsigned char string_array[STRING_ARRAY_SIZE];
	unsigned int team_number;

	/* Stores the first word of text_string into an array and prints to console */
	char text_string[] = "Bob Ross";
	sscanf(text_string,"%s",string_array);
	std::cout << "Text example" << std::endl;
	std::cout << string_array << std::endl;
	std::cout << std::endl;

	/* Stores the first word of text_and_integer_string into an array
	 * Stores the second word into team_number integer variable */
	char text_and_integer_string[] = "DERT 2040";
	sscanf(text_and_integer_string,"%s %d",string_array, &team_number);
	std::cout << "Text and integer example" << std::endl;
	std::cout << string_array << std::endl;
	std::cout << team_number << std::endl;
	std::cout << std::endl;

	/* Stores the third number of integer_string into team_number
	 * "%*" is used to bypass parts of the string that
	 * do not need to be processed */
	char integer_string[] = "1000 1001 2001 3003 5005 8008 13013";
	sscanf(integer_string,"%*d %*d %d",&team_number);
	std::cout << "Integer example" << std::endl;
	std::cout << team_number << std::endl;
	std::cout << std::endl;

	return 0;
}
