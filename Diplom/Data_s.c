//
//  Data_s.c
//  Diplom
//
//  Created by Alex Tsiganov on 26.03.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Data_s.h"
#include <stdlib.h>

Point_s* newPoint(double x, double y)
{
    Point_s *point = malloc(sizeof(Point_s));
    point->x = x;
    point->y = y;
    return point;
}

Point_value_s* newPointValue_base(Point_value_s inPointValue)
{
    Point_value_s *pointValue = malloc(sizeof(Point_value_s));
    pointValue->value = inPointValue.value;
    pointValue->point = inPointValue.point;
    pointValue->tan_vector = inPointValue.tan_vector;
    pointValue->normal_vector = inPointValue.normal_vector;
    return pointValue;
}

List_Points_s* newListPoints()
{
    List_Points_s *list = malloc(sizeof(List_Points_s));
    *list = (List_Points_s){};
    return list;
}

void addListPoints(List_Points_s *list, Point_value_s *pointValue)
{
    list->count++;
    list->points = realloc(list->points, sizeof(Point_value_s*)*list->count);
    list->points[list->count-1] = pointValue;
}

void freeListPoints(List_Points_s *list)
{
    for (int i=0; i<list->count; i++)
        free(list->points[i]);
}