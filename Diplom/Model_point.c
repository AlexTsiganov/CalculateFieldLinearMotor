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

/*int isTan_x(Model_point_s *modelPoint)
{
    return modelPoint->tan_vector->x == 0;
}

int isTan_y(Model_point_s *modelPoint)
{
    return modelPoint->tan_vector->y == 0;
}

int isNor_x(Model_point_s *modelPoint)
{
    return modelPoint->tan_vector->x == 0;
}

int isNor_y(Model_point_s *modelPoint)
{
    return modelPoint->tan_vector->y == 0;
}

double get_x(Model_point_s *modelPoint)
{
    return modelPoint->point->x;
}

double get_y(Model_point_s *modelPoint)
{
    return modelPoint->point->y;
}

double get_Size(Model_point_s *modelPoint)
{
    return modelPoint->size;
}

double get_tan_x(Model_point_s *modelPoint)
{
    return modelPoint->tan_vector->x;
}

double get_tan_y(Model_point_s *modelPoint)
{
    return modelPoint->tan_vector->y;
}

double get_nor_x(Model_point_s *modelPoint)
{
    return modelPoint->normal_vector->x;
}

double get_nor_y(Model_point_s *modelPoint)
{
    return modelPoint->normal_vector->y;
}

Model_point_s* newModelPoint_base(Model_point_s modelPointArgs)
{
    Model_point_s *model_point = malloc(sizeof(Model_point_s));
    model_point->size = modelPointArgs.size;
    model_point->width = modelPointArgs.width;
    model_point->height = modelPointArgs.height;
    model_point->value = modelPointArgs.value;
    model_point->znak = modelPointArgs.znak;
    model_point->point = modelPointArgs.point;
    model_point->tan_vector = modelPointArgs.tan_vector;
    model_point->normal_vector = modelPointArgs.normal_vector;
    return model_point;
}*/

/*Model_point_B_s* newModelPointB_base(Model_point_B_s modelPointBArgs)
{
    Model_point_B_s *model_point_B = malloc(sizeof(Model_point_B_s));
    model_point_B->point
    return model_point_B;
}

Model_point_katuski_s* newModelPointKatuski_base(Model_point_katuski_s modelPointKatuskiArgs)
{
    Model_point_katuski_s *model_point_katuski = malloc(sizeof(Model_point_katuski_s));
    model_point_katuski->center = modelPointKatuskiArgs.center;
    model_point_katuski->width = modelPointKatuskiArgs.width;
    model_point_katuski->height = modelPointKatuskiArgs.height;
    model_point_katuski->value = modelPointKatuskiArgs.value;
    model_point_katuski->znak = modelPointKatuskiArgs.znak;
    return model_point_katuski;
}*/
