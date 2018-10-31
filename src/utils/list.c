#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "list.h"

CommandList new_commandlist(int capacity) {
    CommandList list;
    list.capacity = capacity;
    list.array = malloc(capacity * sizeof(Command));
    list.size = 0;
    return list;
}

void insert_commandlist(CommandList *list, int index, Command item) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(Command));
    }
    for (int i = index; i < list->size; ++i)
        list->array[i + 1] = list->array[i];
    list->array[index] = item;
    ++list->size;
}

void append_commandlist(CommandList *list, Command item) {
    insert_commandlist(list, list->size, item);
}

void clear_commandlist(CommandList *list) {
    list->size = 0;
}

Command remove_commandlist(CommandList *list, int index) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    Command item = list->array[index];
    for (int i = index; i < list->size - 1; ++i)
        list->array[i] = list->array[i + 1];
    --list->size;
    return item;
}

Command pop_commandlist(CommandList *list) {
    return remove_commandlist(list, list->size - 1);
}

Command index_commandlist(CommandList *list, int index) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    return list->array[index];
}

CharList new_charlist(int capacity) {
    CharList list;
    list.capacity = capacity;
    list.array = malloc(capacity * sizeof(char));
    list.size = 0;
    return list;
}

void insert_charlist(CharList *list, int index, char item) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(char));
    }
    for (int i = index; i < list->size; ++i)
        list->array[i + 1] = list->array[i];
    list->array[index] = item;
    ++list->size;
}

void append_charlist(CharList *list, char item) {
    insert_charlist(list, list->size, item);
}

void clear_charlist(CharList *list) {
    list->size = 0;
}

char remove_charlist(CharList *list, int index) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    char item = list->array[index];
    for (int i = index; i < list->size - 1; ++i)
        list->array[i] = list->array[i + 1];
    --list->size;
    return item;
}

char pop_charlist(CharList *list) {
    return remove_charlist(list, list->size - 1);
}

char index_charlist(CharList *list, int index) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    return list->array[index];
}

CharCharList new_charcharlist(int capacity) {
    CharCharList list;
    list.capacity = capacity;
    list.array = malloc(capacity * sizeof(CharList));
    list.size = 0;
    return list;
}

void insert_charcharlist(CharCharList *list, int index, CharList item) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(CharList));
    }
    for (int i = index; i < list->size; ++i)
        list->array[i + 1] = list->array[i];
    list->array[index] = item;
    ++list->size;
}

void append_charcharlist(CharCharList *list, CharList item) {
    insert_charcharlist(list, list->size, item);
}

void clear_charcharlist(CharCharList *list) {
    list->size = 0;
}

CharList remove_charcharlist(CharCharList *list, int index) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    CharList item = list->array[index];
    for (int i = index; i < list->size - 1; ++i)
        list->array[i] = list->array[i + 1];
    --list->size;
    return item;
}

CharList pop_charcharlist(CharCharList *list) {
    return remove_charcharlist(list, list->size - 1);
}

CharList index_charcharlist(CharCharList *list, int index) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    return list->array[index];
}

BoolList new_boollist(int capacity) {
    BoolList list;
    list.capacity = capacity;
    list.array = malloc(capacity * sizeof(bool));
    list.size = 0;
    return list;
}

void insert_boollist(BoolList *list, int index, bool item) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    if (list->size == list->capacity) {
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(bool));
    }
    for (int i = index; i < list->size; ++i)
        list->array[i + 1] = list->array[i];
    list->array[index] = item;
    ++list->size;
}

void append_boollist(BoolList *list, bool item) {
    insert_boollist(list, list->size, item);
}

void clear_boollist(BoolList *list) {
    list->size = 0;
}

bool remove_boollist(BoolList *list, int index) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    bool item = list->array[index];
    for (int i = index; i < list->size - 1; ++i)
        list->array[i] = list->array[i + 1];
    --list->size;
    return item;
}

bool pop_boollist(BoolList *list) {
    return remove_boollist(list, list->size - 1);
}

bool index_boollist(BoolList *list, int index) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    return list->array[index];
}

char *convert_arraychar(CharList *charList) {
    char *result = malloc(charList->size * sizeof(char));
    for (int i = 0; i < charList->size; ++i) {
        result[i] = index_charlist(charList, i);
    }
    return result;
}

char **convert_arraycharchar(CharCharList *charCharList) {
    char **result = malloc((charCharList->size + 1) * sizeof(char*));
    CharList charList;
    for (int i = 0; i < charCharList->size; ++i) {
        charList = index_charcharlist(charCharList, i);
        result[i] = convert_arraychar(&charList);
    }
    result[charCharList->size] = NULL;
    return result;
}

bool *convert_boolchar(BoolList *boolList) {
    bool *result = malloc(boolList->size * sizeof(bool));
    for (int i = 0; i < boolList->size; ++i) {
        result[i] = index_boollist(boolList, i);
    }
    return result;
}