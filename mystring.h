/****************************** myString.h ***********************************
Student Name: Marshall Aaron Asch            Student Number:  0928357
Date: January 29, 2017                    	 Course Name: CIS*2750
Assignment: A1

Version 2

Part of the library of functions that contain the functions to deal
with strings
****************************************************************************/

#ifndef __MY_STRING_H__
#define __MY_STRING_H__


/**
 * toLowerStr
 * Takes a string as input and returns a new string that is a copy
 * of the origonal but is in lowercase. The caller mist free the string.
 *
 * IN:	str, the sring that it is going to make lowercase
 * OUT: pointer to the new string on success
 *		NULL on failure
 * POST: a new string is created in memory
 * ERROR: NULL if the parameter is invalid or mem could not be allocated
 */
char* toLowerStr(const char* str);

/**
 * toUpperStr
 * Takes a string as input and returns a new string that is a copy
 * of the origonal but is in uppercase. The caller mist free the string.
 *
 * IN:	str, the sring that it is going to make uppercase
 * OUT: pointer to the new string on success
 *		NULL on failure
 * POST: a new string is created in memory
 * ERROR: NULL if the parameter is invalid or mem could not be allocated
 */
char* toUpperStr(const char* str);

/**
 * join
 * Joins 2 strings together. src is put after
 * dest, src needs to be freed by the caller.
 * dest is destroyed.
 *
 * IN:	dest, the string that is being added to
 *		src, the string that is being added
 * OUT: NULL, on failure
 *		pointer to the new string on success
 * POST: the old dest gets freed and the new string is created
 * ERROR: NULL if something goes wrong.
 */
char* join(char* dest, const char* src);

/**
 * joinC
 * Joins a character to the end of the string
 *
 * IN:	dest, the string that is being added to
 *		src, the character that is being added
 * OUT: a new string that contains both the old and the new
 * POST: makes a string
 * ERROR: NULL if something goes wrong
 */
char* joinC(char* dest, char src);

/**
 * strduplicate
 * Copies a sting into a new string
 *
 * IN: 	str, the sting to duplicate
 * OUT: NULL, on failure
 *		returns a pointer to the new string
 * POST: creates a new string in memory
 * ERROR: NULL if mem can not be allocated
 */
char* strduplicate(const char* str);

/**
 * substring
 * Creates a new string from the old string.
 * ranges from start inclusive to end exclusive.
 *
 * IN: 	input, the base string
 *		start, the start index
 *		end, the end index of the substring
 * OUT: a pointer to the new string on success
 *		NULL pointer on failure
 * POST: a new smaller string is created
 * ERROR: NULL if parameters are not valid or
 *		  mem can not be allocated
 */
char* substring(const char* input, unsigned long start, unsigned long end);

/**
 * lastIndex
 * Gets the last index of the given character in the string.
 *
 * IN:	str, the string that is being searched
 *		ch, the char that it is searching for
 * OUT: returns the index of last time the character apears
 *		-1 on failure or if the characer is not in the string
 * POST: none
 * ERROR: -1 if the string does not exist
 */
long int lastIndex(const char* str, char ch);

/**
 * firstIndex
 * Gets the index of the first occurance of the given
 * character in the string.
 *
 * IN:	str, the string that is being searched
 *		ch, the char that it is searching for
 * OUT: returns the index of first time the character apears
 *		-1 on failure or if the characer is not in the string
 * POST: none
 * ERROR: -1 if the string does not exist
 */
long int firstIndex(const char* str, char ch);

/**
 * firstIndexOffset
 * Gets the index of the first occurance of the given
 * character in the string after the offset index
 *
 * IN:	str, the string that is being searched
 *		ch, the char that it is searching for
 *		offset, how far into the string to start the search
 * OUT: returns the index of first time the character apears
 *		-1 on failure or if the characer is not in the string
 * POST: none
 * ERROR: -1 if the string does not exist
 */
long int firstIndexOffset(const char* str, char ch, unsigned long offset);

/**
 * trim
 * Removes any leading or trailing white space characters
 * Makes a copy and destroyes the origonal.
 *
 * IN: 	input, the string that is being trimmed
 * OUT: NULL on failure
 *      a pointer the the new string that has been trimmed
 * POST: origonal memory is freed, new memory is allocated
 * ERROR: if input does not exist returns NULL
 */
char* trim(char* input);

/**
 * strcmp_nocase
 * Does a case insensitive string comparison.
 * If ether paramater is NULL then it segfaults.
 *
 *	if Return value < 0 then it indicates str1 is less than str2.
 *	if Return value > 0 then it indicates str2 is less than str1.
 *	if Return value = 0 then it indicates str1 is equal to str2.
 *
 * IN: 	str1, This is the first string to be compared.
 *		str2, This is the second string to be compared.
 * OUT: number
 * POST: none
 * ERROR: SEGFAULT on error
 */
int strcmp_nocase(const char* str1, const char* str2);


long int strSearchOffset(const char* haystack, const char* needle, long int offset);
long int strSearch(const char* haystack, const char* needle);

void sortStr(char* str);

#endif
