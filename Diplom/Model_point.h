//
//  Model_point.h
//  Diplom
//
//  Created by Alex Tsiganov on 15.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#ifndef __Diplom__Model_point__
#define __Diplom__Model_point__

#include <stdio.h>

typedef struct
{
    double x, y;
}Point_s;

typedef struct
{
    double size;
    Point_s *point, *tan_vector, *normal_vector;
}Model_point_s;

#define newPoint(...) newPoint_base((Point_s){__VA_ARGS__})
Point_s* newPoint_base(Point_s point_args);
void freePoint(Point_s *point);

#define newModelPoint(...) newModelPoint_base((Model_point_s){__VA_ARGS__})
Model_point_s* newModelPoint_base(Model_point_s modelPointArgs);

#endif
