#ifndef _STRING
#define _STRING

#include <stdlib.h>

typedef struct String
{
    char* str;
    int size;
    int capacity;

} String;

// initializes new string
void init_string(String* string, int initial_capacity);

// converts an int to a string
void int_to_string(String* output, int input);

// adds two strings together
void concatenate(String* output, String* first, String* second);

// adds a character to a string
void push_back_str(String* string, char character);

#endif
