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
    Point_s *point, *tan_v, *normal_v;
}Point_value_s;

typedef struct
{
    Point_value_s *list;
    int count;
}List_Points;

List_Points* newList_Pints(int count);
