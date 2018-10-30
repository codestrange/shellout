#include <stdlib.h>
#include "command.h"
#include "list.h"

List new_list(int capacity) {
    List list;
    list.capacity = capacity;
    list.array = malloc(capacity * sizeof(Command));
    list.size = 0;
    return list;
}

void insert_list(List *list, int index, Command item) {
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

void append_list(List *list, Command item) {
    insert_list(list, list->size, item);
}

void clear_list(List *list) {
    list->size = 0;
}

Command remove_list(List *list, int index) {
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

Command pop_list(List *list) {
    return remove_list(list, list->size - 1);
}

Command index_list(List *list, int index) {
    if (index < 0)
        index = 0;
    if (index > list->size)
        index = list->size;
    return list->array[index];
}