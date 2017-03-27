
/****************************** ArrayList.c ***********************************
Student Name: Marshall Aaron Asch
maasch@rogers.com

Date: March 25, 2017

change log
	- March 25, 2017
		- added prototypes for some new functions
		- added sort function using merge sort
****************************************************************************/


#include <stdlib.h>
#include "ArrayList.h"



static void merge(void** list, unsigned long int start, unsigned long int middle, unsigned long int end, int (*comp)(void* a, void* b));
static void mergeSort(void** list, unsigned long int start, unsigned long int end, int (*comp)(void* a, void* b));


/**
 * newArrayList
 * Creates a new ArrayList struct in memory
 * initial list is NULL and length is 0
 *
 * @return pointer to the new list on success
 *         NULL on failure
 */
ArrayList* newArrayList()
{
	ArrayList* list;

	/* try allocating memory */
	list = malloc(sizeof(ArrayList));
	if (list == NULL)
	{
		return NULL;
	}

	list->list = NULL;
	list->length = 0;
	list->size = 0;

	return list;
}

/**
 * newArrayList
 * Creates a new ArrayList struct in memory
 * initial list is NULL and length is 0
 *
 * @return pointer to the new list on success
 *         NULL on failure
 */
ArrayList* newArrayListSize(unsigned long int size)
{
	ArrayList* list;
	unsigned long int i;

	/* try allocating memory */
	list = malloc(sizeof(ArrayList));
	if (list == NULL)
	{
		return NULL;
	}

	/* try allocating memory for the new list */
	list->list = malloc(sizeof(void*) * (size));
	if (list->list == NULL)
	{
		free(list);
		return NULL;
	}

	/* set inital values to NULL*/
	for (i = 0; i < size; i++)
	{
		list->list[i] = NULL;
	}

	list->length = 0;
	list->size = size;

	return list;
}

/**
 * destroyArrayList
 * Frees all of the memory being used by the struct
 * uses the given function pointer to free every item
 * in the list.
 * If the function is not given then the list and the struct are freed
 *
 * @param 	list		The list to be freed
 * @param 	destruct	The function pointer to the destructor
 *                  	for each element in the list
 * @return 	1			If the list does not exist (nothing happens)
 *          2			If the function is not given (frees list and struct)
 *          3			If the list is NULL (frees the struct)
 *          0			On success (frees every item, list and struct)
 */
int destroyArrayList(ArrayList* list, void (*destruct)(void* obj))
{
	unsigned long int i;

	/* check if the list exists */
	if (list == NULL)
	{
		return 1;
	}

	/* make sure that a destructor function is given */
	if (destruct == NULL)
	{
		free(list->list);
		free(list);
		return 2;
	}

	/* make sure that the list exists*/
	if (list->list == NULL)
	{
		free(list);
		return 3;
	}

	/* free every object in the list */
	for (i = 0; i < list->length; i++)
	{
		destruct(list->list[i]);
	}

	free(list->list);
	free(list);


	return 0;
}

/**
 * pushArray
 * Adds the new element to the end of the list
 * The list must exist already. The elemnt can be NULL
 *
 * @param  list    	The list to be added to
 * @param  element 	Pointer to the new element to be added
 * @return -1		If the list does not exist
 *         -2		If memory for the new list could not be allocated
 *         0		On success
 */
int pushArray(ArrayList* list, void* element)
{
	void** temp;
	unsigned long int i;

	/* make sure the list is given */
	if (list == NULL)
	{
		return -1;
	}

	if (list->size == list->length)
	{
		/* try allocating memory for the new list */
		temp = malloc(sizeof(void*) * (list->size + 1));
		if (temp == NULL)
		{
			return -2;
		}

		for (i = 0; i < list->length; i++)
		{
			temp[i] = list->list[i];
		}
		list->size++;
	}

	/* add the new element to the end of the list */
	list->list[list->length] = element;
	list->length++;

	free(list->list);

	return 0;
}

/**
 * getArrayAtPos
 * Get the element at position index in the list
 *
 * @param 	list  The list to be retreaved from
 * @param 	index The index of the element to be retrived
 * @return 		  Pointer to the object on success
 *                NULL on failur
 */
void* getArrayAtPos(ArrayList * list, unsigned long int index)
{

	/* make sure the list exists and index is in range */
	if (list == NULL || list->list == NULL || list->length <= index)
	{
		return NULL;
	}

	return list->list[index];
}


int insertAfter(ArrayList * list, void* new, void* after);


int insertBefore(ArrayList* list, void* new, void* before);

int insertAt(ArrayList* list, void* new, long int index);

int setElementAt(ArrayList * list, void* new, long int index);

long int getArrayListSize(ArrayList * list);

long int getArrayListIndexOf(ArrayList * list, void* index);

int arrayListRemoveElement(ArrayList * list, void* element);

int arrayListRemoveIndex(ArrayList * list, long int index);






/* wrapper for the sort function */
int sortArrayList(ArrayList * list, int (*comp)(void* a, void* b))
{
	if (list == NULL || list->list == NULL || comp == NULL)
	{
		return -1;
	}

	mergeSort(list->list, 0, list->length, comp);
	return 0;
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
static void mergeSort(void** list, unsigned long int start, unsigned long int end, int (*comp)(void* a, void * b))
{
	long int middle;

	/* check to see if it is finished */
	if (list == NULL || comp == NULL || (end - start) == 1)
	{
		return;
	}

	middle = (end + start) / 2;

	/* split the list in half and sort */
	mergeSort(list, start, middle, comp);
	mergeSort(list, middle, end, comp);

	/* put the sublists back together */
	merge(list, start, middle, end, comp);
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
static void merge(void** list, unsigned long int start, unsigned long int middle, unsigned long int end, int (*comp)(void* a, void * b))
{
	unsigned long int i;		/* index for lower half */
	unsigned long int j;		/* index for upper half */
	unsigned long int k;		/* index in temp */

	void*** temp;		/* to store the sorted section*/

	/* allocate memory for the temp str */
	temp = malloc(sizeof(void*) * (end - start + 1));
	if (list == NULL || temp == NULL)
	{
		free(temp);
		return;
	}

	i = start;
	j = middle;
	k = 0;

	while (i < middle && j < end)
	{
		if (comp(list[i], list[j]) <= 0 )
		{
			temp[k++] = list[i++];
		}
		else
		{
			temp[k++] = list[j++];
		}
	}

	/* copy the rest of list into temp*/
	while (j < end)
	{
		temp[k++] = list[j++];
	}

	/* copy the rest of list into temp */
	while (i < middle)
	{
		temp[k++] = list[i++];
	}

	/* put temp back into the main one */
	i = 0;
	j = start;

	while (j < end)
	{
		list[j++] = temp[i++];
	}

	free(temp);
}







