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

#define newPoint(...) newPoint_base((Point_s){__VA_ARGS__})
Point_s* newPoint_base(Point_s point_args);
void freePoint(Point_s *point);

typedef struct
{
    double value;
    double size, width, height;
    Point_s *point, *tan_vector, *normal_vector;
    enum {o, x} znak;
}Model_point_s;

#define newModelPoint(...) newModelPoint_base((Model_point_s){__VA_ARGS__})
Model_point_s* newModelPoint_base(Model_point_s modelPointArgs);

/*typedef struct
{
    double value;
    Point_s *point;
}Model_point_B_s;

#define newModelPointB(...) newModelPointB_base((Model_point_B_s){__VA_ARGS__})
Model_point_B_s* newModelPointB_base(Model_point_B_s modelPointBArgs);

typedef struct
{
    double value;
    double width, height;
    Point_s *center;
    enum {o, x} znak;
}Model_point_katuski_s;

#define newModelPointKatuski(...) newModelPointKatuski_base((Model_point_katuski_s){__VA_ARGS__})
Model_point_katuski_s* newModelPointKatuski_base(Model_point_katuski_s modelPointKatuskiArgs);*/


int isPointEquals(Point_s* p1, Point_s *p2);
int isTan_x(Model_point_s *modelPoint);
int isTan_y(Model_point_s *modelPoint);
double get_x(Model_point_s *modelPoint);
double get_y(Model_point_s *modelPoint);
double get_Size(Model_point_s *modelPoint);
double get_tan_x(Model_point_s *modelPoint);
double get_tan_y(Model_point_s *modelPoint);


#endif
