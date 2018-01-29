#include "string.h"

void init_string(String* string, int initial_capacity)
{
    string->size = 0;
    string->capacity = initial_capacity;
    string->str = malloc(sizeof(char) * (string->capacity));
    string->str[0] = '\0';
}

void set_string(String* string, char* text)
{
    int length = 0;
    string->size = 0;

    while(text[length] != '\0')
        length++;

    if (string->capacity <= length)
    {
        string->capacity = length + 1;
        string->str = realloc(string->str, sizeof(char) * string->capacity);
    }

    for (int i = 0; i < length; i++)
        string->str[i] = text[i];
    string->str[length] = '\0';

    string->size = length;
    printf("%s\n", string->str);
}

void int_to_string(String* output, int input)
{
    init_string(output, 1);

    output->size = 0;

    while (input > 0)
    {
        push_back_str(output, (input % 10) + '0');
        input /= 10;
    }

    push_back_str(output, '\0');
}

void concatenate(String* output, String* first, String* second)
{
    init_string(output, first->size + second->size + 1);

    // not using push_back_str() because output will have desired capacity
    for (int i = 0; i < first->size; i++)
        output->str[i] = first->str[i];
    for (int i = 0; i < second->size; i++)
        output->str[i + first->size] = second->str[i];

    output->size = first->size + second->size;
    output->str[output->size] = '\0';
}

void push_back_str(String* string, char character)
{
    if (string->size >= string->capacity)
    {
        string->capacity *= 2;
        string->str = realloc(string->str, (sizeof(char) * string->capacity + 1));
    }

    string->str[string->size] = character;
    string->size++;
    string->str[string->size] = '\0';
}
