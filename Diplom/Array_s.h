//
//  Array_s.h
//  Diplom
//
//  Created by Alex Tsiganov on 13.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#ifndef __Diplom__Array_s__
#define __Diplom__Array_s__

#include <stdio.h>

#define DEFAULT_CAPACITY 500

typedef void* Array_Item_t;

extern Array_Item_t *item_not_found;

typedef struct
{
    int length;
    int capacity;
    Array_Item_t *items;
    void (*on_item_clear)(Array_Item_t *array_item);
} Array_s;

Array_s* array_new();
void array_add(Array_s *array, Array_Item_t item);
Array_Item_t* array_get(Array_s *array);
Array_Item_t* array_get_by_index(Array_s *array, int index);
void array_clear(Array_s *list);

#endif
