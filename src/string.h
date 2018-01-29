#ifndef _STRING
#define _STRING

#include <stdlib.h>
#include <stdio.h>

typedef struct String
{
    char* str;
    int size;
    int capacity;

} String;

// initializes new string
void init_string(String* string, int initial_capacity);

// initializes a string with given char*
void set_string(String* string, char* text);

// reverses a string ("aaabb -> bbaaa")
void reverse_string(String* to_be_reversed);

// converts an int to a string
void int_to_string(String* output, int input);

// adds two strings together
void concatenate(String* output, String* first, String* second);

// adds a character to a string
void push_back_str(String* string, char character);

#endif
