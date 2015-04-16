//
//  Calculate_base.c
//  Diplom
//
//  Created by Alex Tsiganov on 15.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Calculate_base.h"
#include <math.h>

double calculate_line_size(Point_s *start_point, Point_s *end_point)
{
    double v_line = (end_point->x-start_point->x)*(end_point->x-start_point->x) + (end_point->y-start_point->y)*(end_point->y-start_point->y);
    return v_line >= 0 ? sqrt(v_line) : 0;
}