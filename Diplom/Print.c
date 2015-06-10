//
//  Print.c
//  Diplom
//
//  Created by Alex Tsiganov on 22.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Print.h"
#include "Model_point.h"

void print_Array_s(Array_s *array)
{
    for (int i=0; i<array->length; i++)
    {
        Model_point_s *point = (Model_point_s*)array->items[i];
        printf("Point: (%.3f; %.3f) -> %.3f (w:%.3f; h:%.3f)", point->point->x, point->point->y, point->size, point->width, point->height);
        if (point->value)
            printf(", value: %.6f", point->value);
        if (point->normal_vector)
            printf(", normal_vector: (%.3f; %.3f)", point->normal_vector->x, point->normal_vector->y);
        if (point->tan_vector)
            printf(", tan_vector: (%.3f; %.3f)", point->tan_vector->x, point->tan_vector->y);
        printf("\n");
    }
}

void print_Array_s_Matrix_Jitems(Array_s *array)
{
    printf("Print Matrix J items: \n");
    for (int i=0; i<array->length/2; i++)
    {
        for (int k=0; k<array->length/2; k++)
        {
            double *d = ((double*)array_get_by_index(array, i));
            printf("  %.3f  ", *d);
        }
        printf("\n");
    }
}