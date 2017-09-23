
/****************************** testing.c ***********************************
   Student Name: Marshall Aaron Asch
   Date: March 28, 2017

   Tast harness for the library
****************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ArrayList.h"
#include "myinput.h"
#include "mystring.h"

#include "queue.h"

/* function for testing mystring.c */
static void testJoin();
static void testLower();
static void testJoin_char();
static void testdup();
static void testSubstr();
static void testLastIndex();
static void testFirstIndex();
static void testFirstIndexOffset();
static void testTrim();
static void testStrcmp_nocase();
static void testStrSearch();
static void testStrSearch_offset();
static void testsortStr();

static void testQueue();


/*for queue test */
void destroy(void *data);

int  main(void)
{
    /* function for testing mystring.c */
    testLower();
    testJoin();
    testJoin_char();
    testdup();
    testSubstr();
    testLastIndex();
    testFirstIndex();
    testFirstIndexOffset();
    testTrim();
    testStrcmp_nocase();
    testStrSearch();
    testStrSearch_offset();
    testsortStr();
    testQueue();

    /* code */
    return 0;
}

/**
 * 1 NULL str
 * 2 empty str
 * 3 normal
 * 4 lowecase and special
 */
static void testLower()
{
    char *in;
    char *res;


    /********************
       test to lower
    ********************/

    in  = NULL;
    res = toLowerStr(in);

    if (res != NULL)
    {
        printf("FAILED 1: NULL str\n");
    }
    free(res);

    in  = "";
    res = toLowerStr(in);

    if ((res == NULL) || (strcmp(res, "") != 0))
    {
        printf("FAILED 2: empty str\n");
    }
    free(res);

    in  = "ABCDEF";
    res = toLowerStr(in);

    if ((res == NULL) || (strcmp(res, "abcdef") != 0))
    {
        printf("FAILED 3: normal\n");
    }
    free(res);

    in  = "ABCDEFghij !@#$?..,\n8098765";
    res = toLowerStr(in);

    if ((res == NULL) || (strcmp(res, "abcdefghij !@#$?..,\n8098765") != 0))
    {
        printf("FAILED 4: lowercase + special\n");
    }
    free(res);
}

/**
 * 5 NULL args
 * 6 add NULL to str
 * 7 add str to NULL
 * 8 add str to str
 */
static void testJoin()
{
    char *in;
    char *res;

    /********************
       test to join
    ********************/


    in  = NULL;
    res = join(in, NULL);

    if (res != NULL)
    {
        printf("FAILED 5: NULL args\n");
    }

    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");
    res = join(in, NULL);

    if ((res == NULL) || (strcmp(res, "test") != 0))
    {
        printf("FAILED 6: adding NULL to str\n");
    }
    free(res);

    res = join(NULL, "test");

    if ((res == NULL) || (strcmp(res, "test") != 0))
    {
        printf("FAILED 7: adding str to NULL\n");
    }
    free(res);


    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");
    res = join(in, "test");

    if ((res == NULL) || (strcmp(res, "testtest") != 0))
    {
        printf("FAILED 8: adding str to str\n");
    }
    free(res);
}

/**
 * 9  NULL str NUL char
 * 10 NUL to str
 * 11 char to NULL
 * 12 char to str
 */
static void testJoin_char()
{
    char *in;
    char *res;

    /********************
       test to joinC
    ********************/


    in  = NULL;
    res = joinC(in, '\0');

    if ((res == NULL) || (strcmp(res, "") != 0))
    {
        printf("FAILED 9: NULL str NUL char \n");
    }
    free(res);

    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");
    res = joinC(in, '\0');

    if ((res == NULL) || (strcmp(res, "test") != 0))
    {
        printf("FAILED 10: adding NUL to str\n");
    }
    free(res);


    res = joinC(NULL, 'a');

    if ((res == NULL) || (strcmp(res, "a") != 0))
    {
        printf("FAILED 11: adding char to NULL\n");
    }
    free(res);


    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");
    res = joinC(in, 'a');

    if ((res == NULL) || (strcmp(res, "testa") != 0))
    {
        printf("FAILED 12: adding char to str\n");
    }
    free(res);
}

/**
 * 13 NULL
 * 14 str literal
 * 15 char ptr
 * 16 special characters
 */
static void testdup()
{
    char *res;
    char *in;

    /********************
       test to strduplicate
    ********************/

    res = strduplicate(NULL);

    if (res != NULL)
    {
        printf("FAILED 13: NULL \n");
    }

    res = strduplicate("abc");

    if ((res == NULL) || (strcmp(res, "abc") != 0))
    {
        printf("FAILED 14: str literal\n");
    }
    free(res);

    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");
    res = strduplicate(in);

    if ((res == NULL) || (strcmp(res, "test") != 0))
    {
        printf("FAILED 15: char pointer\n");
    }
    free(in);
    free(res);

    res = strduplicate("abc BA 3789*&/. ");

    if ((res == NULL) || (strcmp(res, "abc BA 3789*&/. ") != 0))
    {
        printf("FAILED 16: special characters\n");
    }
    free(res);
}

/**
 * 17 NULL
 * 18 len 0
 * 19 char ptr len 1
 * 20 str literal 1 -> strlen()
 */
static void testSubstr()
{
    char *res;
    char *in;

    /********************
       test to substring
    ********************/

    res = substring(NULL, 0, 0);

    if (res != NULL)
    {
        printf("FAILED 17: NULL \n");
    }

    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");
    res = substring(in, 0, 0);

    if ((res == NULL) || (strcmp(res, "") != 0))
    {
        printf("FAILED 18: str len 0 \n");
    }
    free(in);
    free(res);

    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");
    res = substring(in, 0, 1);

    if ((res == NULL) || (strcmp(res, "t") != 0))
    {
        printf("FAILED 19: len 1 str ptr \n");
    }
    free(in);
    free(res);

    res = substring("test", 1, strlen("test"));

    if ((res == NULL) || (strcmp(res, "est") != 0))
    {
        printf("FAILED 20: str literal 1 -> strlen()\n");
    }
    free(res);
}

/**
 * 21 NULL
 * 22 2 chars
 * 23 1 char
 * 24 not found
 * 25 in a char ptr
 */
static void testLastIndex()
{
    char *in;

    /********************
       test to lastIndex
    ********************/

    if (lastIndex(NULL, '\0') != -1)
    {
        printf("FAILED 21: NULL\n");
    }

    if (lastIndex("test", 't') != 3)
    {
        printf("FAILED 22: 2 of them\n");
    }

    if (lastIndex("test", 'e') != 1)
    {
        printf("FAILED 23: 1 of them\n");
    }

    if (lastIndex("test", 'H') != -1)
    {
        printf("FAILED 24: none of them\n");
    }

    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");

    if (lastIndex(in, 's') != 2)
    {
        printf("FAILED 25: in a char ptr\n");
    }
    free(in);
}

/**
 * 26 NULL
 * 27 2 chars
 * 28 1 char
 * 29 not found
 * 30 in a char ptr
 */
static void testFirstIndex()
{
    char *in;

    /********************
       test to firstIndex
    ********************/

    if (firstIndex(NULL, '\0') != -1)
    {
        printf("FAILED 26: NULL\n");
    }

    if (firstIndex("test", 't') != 0)
    {
        printf("FAILED 27: 2 of them\n");
    }

    if (firstIndex("test", 'e') != 1)
    {
        printf("FAILED 28: 1 of them\n");
    }

    if (firstIndex("test", 'H') != -1)
    {
        printf("FAILED 29: none of them\n");
    }

    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");

    if (firstIndex(in, 's') != 2)
    {
        printf("FAILED 30: in a char ptr\n");
    }
    free(in);
}

/**
 * 31 NULL
 * 32 2 chars offset 1
 * 33 2 char offset 2
 * 34 1 offset 0
 * 35 none of them
 * 36 index too high
 * 37 index too low
 * 38 from a char ptr
 */
static void testFirstIndexOffset()
{
    char *in;

    /********************
       test to firstIndexOffset
    ********************/

    if (firstIndexOffset(NULL, '\0', 0) != -1)
    {
        printf("FAILED 31: NULL\n");
    }

    if (firstIndexOffset("test", 't', 1) != 3)
    {
        printf("FAILED 32: 2 of them offset 1\n");
    }

    if (firstIndexOffset("test", 't', 0) != 0)
    {
        printf("FAILED 33: 2 of them offset 0\n");
    }

    if (firstIndexOffset("test", 'e', 0) != 1)
    {
        printf("FAILED 34: 1 of them offset 0\n");
    }

    if (firstIndexOffset("test", 'H', 2) != -1)
    {
        printf("FAILED 35: none of them\n");
    }

    if (firstIndexOffset("test", 't', 9) != -1)
    {
        printf("FAILED 36: index too high \n");
    }

    if (firstIndexOffset("test", 't', -1) != -1)
    {
        printf("FAILED 37: index too low \n");
    }

    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");

    if (firstIndexOffset(in, 's', 1) != 2)
    {
        printf("FAILED 38: in a char ptr\n");
    }
    free(in);
}

/**
 * 39 NULL
 * 40 no white space
 * 41 leading space
 * 42 trailing space
 * 43 leading and trailing
 * 44 internal spaces
 */
static void testTrim()
{
    char *res;
    char *in;

    /********************
       test to trim
    ********************/

    res = trim(NULL);

    if (res != NULL)
    {
        printf("FAILED 39: NULL\n");
    }

    in = malloc(sizeof(char) * 40);
    sprintf(in, "test");
    res = trim(in);

    if (strcmp(res, "test") != 0)
    {
        printf("FAILED 40: no whitespace \n");
    }
    free(res);

    in = malloc(sizeof(char) * 40);
    sprintf(in, "   test");
    res = trim(in);

    if (strcmp(res, "test") != 0)
    {
        printf("FAILED 41: leading space\n");
    }
    free(res);

    in = malloc(sizeof(char) * 40);
    sprintf(in, "test    ");
    res = trim(in);

    if (strcmp(res, "test") != 0)
    {
        printf("FAILED 42: trailing space\n");
    }
    free(res);


    in = malloc(sizeof(char) * 30);
    sprintf(in, " \n  test \t   ");
    res = trim(in);

    if (strcmp(res, "test") != 0)
    {
        printf("FAILED 43: leading and trailing space\n");
    }
    free(res);


    in = malloc(sizeof(char) * 40);
    sprintf(in, "tes   t");
    res = trim(in);

    if (strcmp(res, "tes   t") != 0)
    {
        printf("FAILED 44: internal space\n");
    }
    free(res);
}

/**
 * 45 lowecase
 * 46 upperCase
 * 47 upper lower match
 * 48 A before B
 * 49 A match B char ptr
 */
static void testStrcmp_nocase()
{
    char *in;

    /********************
       test to strcmp_nocase
    ********************/

    if (strcmp_nocase("abc", "abc") != 0)
    {
        printf("FAILED 45: 2 lowercase match\n");
    }

    if (strcmp_nocase("ABC", "ABC") != 0)
    {
        printf("FAILED 46: 2 upper match\n");
    }

    if (strcmp_nocase("ABC", "abc") != 0)
    {
        printf("FAILED 47:  upper-lower match\n");
    }

    if (strcmp_nocase("ABC", "cdr") >= 0)
    {
        printf("FAILED 48:  A is before B\n");
    }

    in = malloc(sizeof(char) * 40);
    sprintf(in, "abc");

    if (strcmp_nocase("ABC", in) != 0)
    {
        printf("FAILED 49:  A match B, char ptr\n");
    }
    free(in);
}

/**
 * 50 NULL haystack
 * 51 NULL needle
 * 52 match found
 * 53 no match
 * 54 haystack in mem
 */
static void testStrSearch()
{
    char *in;

    /********************
       test to strSearch
    ********************/

    if (strSearch(NULL, "is") != -1)
    {
        printf("FAILED 50: NULL haystack\n");
    }

    if (strSearch("This is a test string. a is long one....", NULL) != -1)
    {
        printf("FAILED 51: NULL needle\n");
    }

    if (strSearch("This is a test string. a is long one....", "is") != 2)
    {
        printf("FAILED 52: match\n");
    }

    if (strSearch("This is a test string. a is long one....", "not") != -1)
    {
        printf("FAILED 53: no match\n");
    }

    in = malloc(sizeof(char) * 50);
    sprintf(in, "This is a test string. a is long one....");

    if (strSearch(in, "this") >= 0)
    {
        printf("FAILED 54:  haystack in ptr\n");
    }
    free(in);
}

/**
 * 55 NULL haystack
 * 56 NULL needle
 * 57 match found 3rd
 * 58 no match
 * 59 haystack in mem
 * 60 offset too low
 * 61 offset too high
 */
static void testStrSearch_offset()
{
    char *in;

    /********************
       test to strSearchOffset
    ********************/

    if (strSearchOffset(NULL, "is", 0) != -1)
    {
        printf("FAILED 55: NULL haystack\n");
    }

    if (strSearchOffset("This is a test string. a is long one....", NULL,
                        0) != -1)
    {
        printf("FAILED 56: NULL needle\n");
    }

    if (strSearchOffset("This is a test string. a is long one....", "is",
                        9) != 25)
    {
        printf("FAILED 57: match 3rd\n");
    }

    if (strSearchOffset("This is a test string. a is long one....", "not",
                        0) != -1)
    {
        printf("FAILED 58: no match\n");
    }

    in = malloc(sizeof(char) * 50);
    sprintf(in, "This is a test string. a is long one....");

    if (strSearchOffset(in, "this", 0) >= 0)
    {
        printf("FAILED 59:  haystack in ptr\n");
    }
    free(in);


    if (strSearchOffset("This is a test string. a is long one....", "a",
                        -1) != -1)
    {
        printf("FAILED 60: offset tooo low\n");
    }

    if (strSearchOffset("This is a test string. a is long one....", "a",
                        50) != -1)
    {
        printf("FAILED 61: offset too high\n");
    }
}

/**
 * 62 NULL
 * 63 alreadyt sorted
 * 64 reverse order
 * 65 upercase lowercase
 */
static void testsortStr()
{
    char *in;

    /********************
       test to sortStr
    ********************/

    in = NULL;
    sortStr(in);

    if (in != NULL)
    {
        printf("FAILED 62: NULL\n");
    }

    in = malloc(sizeof(char) * 40);
    sprintf(in, "abcdef");
    sortStr(in);

    if (strcmp(in, "abcdef") != 0)
    {
        printf("FAILED 63: already sorted\n");
    }
    free(in);

    in = malloc(sizeof(char) * 40);
    sprintf(in, "fedcba");
    sortStr(in);

    if (strcmp(in, "abcdef") != 0)
    {
        printf("FAILED 64: reverse order\n");
    }
    free(in);

    in = malloc(sizeof(char) * 40);
    sprintf(in, "AaBbCc");
    sortStr(in);

    if (strcmp(in, "ABCabc") != 0)
    {
        printf("FAILED 65: upercase lowercase\n");
    }
    free(in);
}

static void testQueue()
{
    struct Queue *queue;
    int status;

    queue = newQueue();

    if ((queue == NULL) || (queue->first != NULL) || (queue->last != NULL))
    {
        printf("FAILED 66: Queue not created properly\n");
    }


    status = destroyQueue(NULL, NULL);

    if (status != -1)
    {
        printf("FAILED 67: NULL queue to destroy\n");
    }

    queue  = newQueue();
    status = destroyQueue(queue, NULL);

    if (status != 0)
    {
        printf("FAILED 68: NULL destroy func empty queue\n");
    }

    queue  = newQueue();
    status = destroyQueue(queue, &free);

    if (status != 0)
    {
        printf("FAILED 69: free() destroy func empty queue\n");
    }

    queue  = newQueue();
    status = destroyQueue(queue, &destroy);

    if (status != 0)
    {
        printf("FAILED 70: free() destroy func empty queue\n");
    }

    queue = newQueue();
}

void destroy(void *data)
{
    printf("-- destroying\n");
    free(data);
}
