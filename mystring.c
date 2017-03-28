/****************************** mysting.c ***********************************
Student Name: Marshall Aaron Asch            Student Number:  0928357
Date: January 29, 2017                    	 Course Name: CIS*2750
Assignment: A1

Version 2

Part of the library of functions that contain the functions to deal
with strings


changeLog
	-March 15, 2017
		- made strcmp_nocase() use constant strings
		- made return types long int so it can be positive or negative
		- added a search function with a start offset

		- need to imporve strsearch so there are no string copies

	-March 25, 2017
		- Added a string sort function uses merge sort using O(n) space
		- I belive it is stable not inplace

	-March 28, 2017
		- removed the mybool.h

****************************************************************************/



#include <string.h>
#include <ctype.h>
#include <signal.h>

#include <stdlib.h>
#include <stdio.h>

#include "mystring.h"



static long int boyer_moore(const char* text, const char* search, long int offset);

static void mergeSort(char* str, long int start, long int end);
static void merge(char* str, long int start, long int middle, long int end);



/**
 * toLowerStr
 * Takes a string as input and returns a new string that is a copy
 * of the origonal but is in lowercase. if overwrite is set to TRUE (1)
 * then the origonal is freed, otherwise the caller mist free the string.
 *
 * IN:	str, the sring that it is going to make lowercase
 *		overwrite, wether or not the orgional gets destroyed
 * OUT: pointer to the new string on success
 *		NULL on failure
 * POST: a new string is created in memory
 * ERROR: NULL if the parameter is invalid or mem could not be allocated
 */
char* toLowerStr(const char* str)
{
	char * new;
	unsigned long i;			/*   loop variable */
	unsigned long length;

	new = strduplicate(str);

	/* make sure that string duplicate was successfull */
	if (new == NULL)
	{
		return NULL;
	}

	length = strlen(new);

	/* loop through entire string */
	for (i = 0; i < length; i++)
	{
		new[i] = tolower(new[i]);
	}

	return new;
}

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
char* join(char* dest, const char* src)
{
	char* new;

	/* make sure that there is a source to add */
	if (src == NULL)
	{
		return dest;
	}

	/* if dest is NULL then make a copy of the sorce to return */
	if (dest == NULL)
	{
		new = malloc (sizeof(char) * (strlen(src) + 2));

		if (new == NULL)
		{
			return NULL;
		}

		/* put into new string */
		strcpy(new, src);
		return new;
	}

	/* join the 2 strings*/
	new = malloc (sizeof(char) * (strlen(dest) + strlen(src) + 2));

	if (new == NULL)
	{
		return dest;
	}

	/* put into new string */
	sprintf(new, "%s%s", dest, src);

	free(dest);

	return new;
}

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
char* joinC(char* dest, char src)
{
	char* new;

	/* if dest is NULL then make a copy of the sorce to return */
	if (dest == NULL)
	{
		new = malloc (sizeof(char) * 2);

		if (new == NULL)
		{
			return NULL;
		}

		/* put into new string */
		sprintf(new, "%c", src);

		return new;
	}

	new = malloc (sizeof(char) * (strlen(dest) + 2));

	if (new == NULL)
	{
		return dest;
	}

	/* put into new string */
	sprintf(new, "%s%c", dest, src);

	free(dest);

	return new;
}

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
char* strduplicate(const char* str)
{
	char* new;

	/* make sure that the parameter is valid */
	if (str == NULL)
	{
		return NULL;
	}

	/* allocate new memory for the string */
	new = malloc(sizeof(char) * (strlen(str) + 1));
	if (new == NULL)
	{
		return NULL;
	}

	strcpy(new, str);

	return new;
}

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
char* substring(const char* input, unsigned long start, unsigned long end)
{
	char* temp;
	unsigned long i;			/* loop variable */
	unsigned long j;			/* loop variable */

	/* check the parameters */
	if (input == NULL || end > strlen(input) || end < start)
	{
		return NULL;
	}

	/* allocate memory for the new string */
	temp = malloc(sizeof(char) * (end - start + 2));
	if (temp == NULL)
	{
		return NULL;
	}

	/* copy the section into the new string*/
	for (i = 0, j = start; j < end; i++, j++)
	{
		temp[i] = input[j];
	}

	/* make sure it is NULL terminated */
	temp[i] = '\0';

	return temp;
}

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
long int lastIndex(const char* str, char ch)
{
	unsigned long length;
	unsigned long i;			/* loop variable */
	unsigned long pos;

	/* check that the string exists */
	if (str == NULL)
	{
		return -1;
	}

	length = strlen(str);
	pos = -1;

	/* loop through the entire string */
	for (i = 0; i < length; i++)
	{
		/* if the current character is the one looking for */
		if (str[i] == ch)
		{
			pos = i;
		}
	}

	return pos;
}

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
long int firstIndex(const char* str, char ch)
{
	unsigned long length;
	unsigned long i;			/* loop variable */

	/* check that the string exists */
	if (str == NULL)
	{
		return -1;
	}

	length = strlen(str);

	/* loop through the entire string */
	for (i = 0; i < length; i++)
	{
		/* if the current character is the one looking for */
		if (str[i] == ch)
		{
			return i;
		}
	}

	return -1;
}

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
long int firstIndexOffset(const char* str, char ch, unsigned long offset)
{
	unsigned long length;
	unsigned long i;			/* loop variable */

	/* check that param are valid */
	if (str == NULL)
	{
		return -1;
	}

	length = strlen(str);

	/* loop through the entire string */
	for (i = offset; i < length; i++)
	{
		/* if the current character is the one looking for */
		if (str[i] == ch)
		{
			return i;
		}
	}

	return -1;
}

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
char* trim(char* input)
{
	char* temp;
	int length;
	int start;
	int end;
	int i;				/* loop variable*/

	/* make sure that the input exists */
	if (input == NULL)
	{
		return NULL;
	}

	length = strlen(input);
	start = -1;
	end = -1;

	/* find the start of the string after the leading whitespace */
	for (i = 0; i < length; i++)
	{
		/* if the character is not whitespace */
		if (isspace(input[i]) == 0)
		{
			start = i;
			break;
		}
	}

	/* find the end of the string before the trailing whitespace */
	for (i = length - 1; i >=  0; i--)
	{
		/* if the character is not whitespace */
		if (isspace(input[i]) == 0)
		{
			end = i;
			break;
		}
	}

	/* something went wrong and there is only whitespace */
	if (start == -1 || end == -1)
	{
		free(input);
		return NULL;
	}

	temp = substring(input, start, end + 1);

	free(input);

	/* there are no leading or trailing spaces */
	return temp;
}

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
int strcmp_nocase(const char* str1, const char* str2)
{
	int status;

	char* aLower;
	char* bLower;

	/* convert to lowercase */
	aLower = toLowerStr(str1);
	bLower = toLowerStr(str2);

	/* segfault if param are invalid */
	if (aLower == NULL || bLower == NULL)
	{
		raise(SIGSEGV);
	}

	status = strcmp(aLower, bLower);

	free(aLower);
	free(bLower);

	return status;
}







/* wraper to that unserlying implementation algorithm can change with same front end */
long int strSearch(const char* haystack, const char* needle)
{
	/* make sure that the parameters are given */
	if (haystack == NULL || needle == NULL)
	{
		return -1;
	}

	return boyer_moore(haystack, needle, 0);
}


/* wraper to that unserlying implementation algorithm can change with same front end */
long int strSearchOffset(const char* haystack, const char* needle, long int offset)
{
	/* make sure that the parameters are given */
	if (haystack == NULL || needle == NULL || offset < 0)
	{
		return -1;
	}

	return boyer_moore(haystack, needle, offset);
}



/**
 * boyer_moore
 * Counts the number of anagrams in the text
 * using Boyer-Moor algorithm.
 * This only works for ASCII characters
 *
 * IN:	text, the text to search in
 *		search, the string it is searching for
 * OUT: none
 * POST: Prints the number of matches and the num shifts
 * ERROR: -1 if param are NULL
 * 		  -2 if mem allocation failed
 * 		  index of the start of the term
 * 		  -1 if not found
 */
static long int boyer_moore(const char* text, const char* search, long int offset)
{
	int shiftTable[128];

	char* temp;
	char* temp1;

	long int status;
	long int j;				/* loop var */
	long int i;				/* loop var */
	long int lenS;			/* length of the search string */
	long int lenT;			/* length of the text to search in */
	long int k;
	long int pos;
	long int badSymShift;
	long int suffixShift;

	/* suffix table */
	long int * suffix;


	/* make sure the parameters are given */
	if (text == NULL || search == NULL || offset < 0)
	{
		return -1;
	}

	lenT = strlen(text);
	lenS = strlen(search);

	/* allocate the suffix table */
	suffix = malloc(sizeof(long int) * (lenS + 1));
	if (suffix == NULL)
	{
		return -2;
	}


	/* generate the shift table */
	for (i = 0; i < 128; i++)
	{
		shiftTable[i] = lenS;
	}

	for (i = 0; i < lenS - 1; i++)
	{
		shiftTable[(int)search[i]] = lenS - i - 1;
	}

	suffix[0] = 0;
	suffix[1] = shiftTable[(int)search[lenS - 1]];

	suffix[lenS - 1] = 1;
	suffix[lenS] = 1;

	/* make this mre efficent */
	for (i = 2; i < lenS - 1; i++)
	{
		/* check to see if the longer suffix is a continueation of the last one*/
		if ((lenS - suffix[i - 1] - i < 0) || (lenS - suffix[i - 1] - i >= 0  && search[lenS - suffix[i - 1] - i] == search[lenS - i]))
		{
			suffix[i] = suffix[i - 1];
		}
		else
		{
			/* the suffix is not a continueation */
			/* break the string into a smaller string*/
			temp = strduplicate(search);
			pos = lenS - suffix[i - 1] - 1;

			status = 0;
			do
			{
				temp1 = substring(temp, 0, pos - 1);
				free(temp);
				temp = temp1;
				pos = lastIndex(temp, search[lenS - 1]);

				/* the character is not found so the rest of the suffixes will not be found*/
				if (pos == -1)
				{
					/* set the shift for the rest of the suffixes to the length*/
					for (; i < lenS - 1; i++)
					{
						suffix[i] = lenS;
					}
					status = 1;
				}
				else
				{
					status = 0;
					/* then check to see if the rest of the characters from len -> len-i match pos -> pos-i*/
					for (j = 1; j < i; j++)
					{
						if ((pos - j < 0) || (pos - j >= 0  && temp[pos - j] == search[lenS - j - 1]))
						{
							suffix[i] = lenS - pos - 1;
						}
						else
						{
							/* no match, shift whole str */
							suffix[i] = lenS;
							status = -1;
							break;
						}
					}
				}
			}
			while (status == -1);

			/**
			 * if status
			 * -1 then that sequence was not a match try again
			 * 1 then there is no match jump whle str
			 * 0 then match found
			 */

			free(temp);
			if (status == 1)
			{
				break;
			}
		}
	}

	i = lenS - 1 + offset;					/* pos of search R end */

	while (i < lenT)
	{
		k = 0;

		while (k < lenS && isprint(text[i - k]) != 0 && search[lenS - k - 1] == text[i - k])
		{
			k++;
		}

		/* match found end */
		if (k == lenS)
		{
			free(suffix);
			return i - k + 1;
		}

		/* figure out how much to shift by */
		if (isprint(text[i - k]) != 0)
		{
			badSymShift = shiftTable[(int)text[i - k]] - k;

			if (badSymShift <= 0)
			{
				badSymShift = 1;
			}

			suffixShift = suffix[k];

			if (suffixShift > badSymShift)
			{
				i += suffixShift;
			}
			else
			{
				i += badSymShift;
			}
		}
		else
		{
			i += lenS;
		}
	}

	free(suffix);

	return -1;
}







/* wrapper for the sort function */
void sortStr(char* str)
{
	if (str == NULL)
	{
		return;
	}

	mergeSort(str, 0, strlen(str));
}


/**
 * mergeSort
 * Does mergesort on string
 *
 * IN:	str, the string to sort
 *		start, the start index
 *		end, the last index that is being sorted
 * OUT: none
 * POST: the string gets sorted
 * ERROR: none
 */
static void mergeSort(char* str, long int start, long int end)
{
	long int middle;

	/* check to see if it is finished */
	if (str == NULL || (end - start) == 1)
	{
		return;
	}

	middle = (end + start) / 2;

	/* split the list in half and sort */
	mergeSort(str, start, middle);
	mergeSort(str, middle, end);

	/* put the sublists back together */
	merge(str, start, middle, end);
}

/**
 * merge
 * Does merge sort on the string
 *
 * IN:	str, the string to sort
 *		start, the start index
 *		middle, the index where the bottem 1/2 and top 1/2 meet
 *		end, the last index that is being sorted
 * POST: the string gets sorted
 * ERROR: none
 */
static void merge(char* str, long int start, long int middle, long int end)
{
	long int i;		/* index for lower half */
	long int j;		/* index for upper half */
	long int k;		/* index in temp */

	char* temp;		/* to store the sorted section*/

	/* allocate memory for the temp str */
	temp = malloc(sizeof(char) * (end - start + 1));
	if (str == NULL || temp == NULL)
	{
		free(temp);
		return;
	}

	i = start;
	j = middle;
	k = 0;

	while (i < middle && j < end)
	{
		if (str[i] <= str[j])
		{
			temp[k++] = str[i++];
		}
		else
		{
			temp[k++] = str[j++];
		}
	}

	/* copy the rest of str into temp*/
	while (j < end)
	{
		temp[k++] = str[j++];
	}

	/* copy the rest of str into temp */
	while (i < middle)
	{
		temp[k++] = str[i++];
	}

	/* put temp back into the main one */
	i = 0;
	j = start;

	while (j < end)
	{
		str[j++] = temp[i++];
	}

	free(temp);
}


