//
//  Array_s.c
//  Diplom
//
//  Created by Alex Tsiganov on 13.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Array_s.h"
#include <stdlib.h>

Array_Item_t *item_not_found;

Array_s* array_new()
{
    static void *sItem_not_found;
    if (!item_not_found)
        item_not_found = sItem_not_found;
    Array_s *newArray = malloc(sizeof(Array_s));
    *newArray = (Array_s){.capacity = DEFAULT_CAPACITY, .length = 0, .items = malloc(DEFAULT_CAPACITY*sizeof(Array_s))};
    return newArray;
}

void array_add(Array_s *array, Array_Item_t item)
{
    if (array->length >= array->capacity)
    {
        array->capacity *= 2;
        array->items = realloc(array->items, sizeof(Array_Item_t)*array->capacity);
    }
    array->items[array->length++] = item;
}

Array_Item_t* array_get_by_index(Array_s *array, int index)
{
    if (index >= 0 && index < array->length)
        return &array->items[index];
    return item_not_found;
}

Array_Item_t* array_get(Array_s *array)
{
    return &array->items[array->length];
}

void array_clear(Array_s *array)
{
    for (size_t i = 0; i<array->length/2; i++)
    {
        if (array->on_item_clear)
            array->on_item_clear(array->items[i]);
        free(array->items[i]);
    }
}