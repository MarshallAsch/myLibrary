#ifndef __ARRAY_LIST_H__
#define __ARRAY_LIST_H__



typedef struct ArrayList
{
	void** list;
	unsigned long int length;
	unsigned long int size;
} ArrayList;


/**
 * newArrayList
 * Creates a new ArrayList struct in memory
 * initial list is NULL and length is 0
 *
 * @return pointer to the new list on success
 *         NULL on failure
 */
ArrayList* newArrayList();


/**
 * newArrayList
 * Creates a new ArrayList struct in memory
 * initial list is NULL and length is 0
 *
 * @return pointer to the new list on success
 *         NULL on failure
 */
ArrayList* newArrayListSize(unsigned long int size);

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
int destroyArrayList(ArrayList* list, void (*destruct)(void* obj));



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
int pushArray(ArrayList* list, void* element);


/**
 * getArrayAtPos
 * Get the element at position index in the list
 *
 * @param 	list  The list to be retreaved from
 * @param 	index The index of the element to be retrived
 * @return 		  Pointer to the object on success
 *                NULL on failur
 */
void* getArrayAtPos(ArrayList * list, unsigned long int index);


int sortArrayList(ArrayList * list, int (*comp)(void* a, void* b));


#endif
