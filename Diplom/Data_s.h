//
//  Data_s.h
//  Diplom
//
//  Created by Alex Tsiganov on 26.03.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

typedef struct
{
    double x, y;
}Point_s;

typedef struct
{
    double value;
    Point_s *point, *tan_vector, *normal_vector;
}Point_value_s;

typedef struct
{
    Point_value_s *points;
    int count;
}List_Points_s;

Point_s* newPoint(double x, double y);

#define newPointValue(...) newPointValue_base((Point_value_s){__VA_ARGS__})
Point_value_s* newPointValue_base(Point_value_s inPointValue);

List_Points_s* newListPoints();
void addListPoints(List_Points_s *list, Point_value_s *pointValue);
void freeListPoints(List_Points_s *list);