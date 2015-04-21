//
//  Model_point.c
//  Diplom
//
//  Created by Alex Tsiganov on 15.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Model_point.h"
#include <stdlib.h>

Point_s* newPoint_base(Point_s point_args)
{
    Point_s *point = malloc(sizeof(Point_s));
    *point = point_args;
    return point;
}

void freePoint(Point_s *point)
{
    free(point);
}

int isPointEquals(Point_s* p1, Point_s *p2)
{
    return p1->x == p2->x && p1->y && p2->y;
}

Model_point_s* newModelPoint_base(Model_point_s modelPointArgs)
{
    Model_point_s *model_point = malloc(sizeof(Model_point_s));
    model_point->size = modelPointArgs.size;
    model_point->point = modelPointArgs.point;
    model_point->tan_vector = modelPointArgs.tan_vector;
    model_point->normal_vector = modelPointArgs.normal_vector;
    model_point->value = modelPointArgs.value;
    return model_point;
}
