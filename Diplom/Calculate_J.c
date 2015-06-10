//
//  Calculate_J.c
//  Diplom
//
//  Created by Alex Tsiganov on 09.06.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Calculate_J.h"
#include <stdlib.h>
#include "Math_fuctions.h"
#include <math.h>

double calc_matrix_item_AJ1(Model_point_s *i_point, Model_point_s *k_point)
{
    double yk = get_y(k_point),
           xk = get_x(k_point),
           dxk = (get_tan_x(k_point) == 0)?0:get_Size(k_point),
           dyk = (get_tan_y(k_point) == 0)?0:get_Size(k_point);
    
    double yi = get_y(i_point),
           xi = get_x(i_point),
           dxi = (get_tan_x(i_point) == 0)?0:get_Size(i_point),
           dyi = (get_tan_y(i_point) == 0)?0:get_Size(i_point);
    
    double _ykPdyk2 = yk+dyk/2,
           _xkPdxk2 = xk+dxk/2,
           _ykMdyk2 = yk-dyk/2,
           _xkMdxk2 = xk-dxk/2;
    
    double _yiPdyi2 = yi+dyi/2,
           _xiPdxi2 = xi+dxi/2,
           _yiMdyi2 = yi-dyi/2,
           _xiMdxi2 = xi-dxi/2;
    
    double _xkMxi = xk-xi;
    
    double _c1 = (_ykPdyk2-_yiPdyi2),
           _c2 = (_ykMdyk2-_yiPdyi2),
           _c3 = (_ykPdyk2-_yiMdyi2),
           _c4 = (_ykMdyk2-_yiMdyi2);
    
    double result = (get_nor_x(i_point)>0)?1:-1;
    result *= ( -_c1 * arctan3(_c1, _xkMxi) + _xkMxi/2 * log( 1 + pow( _c1/_xkMxi ,2))+
                 _c2 * arctan3(_c2, _xkMxi) - _xkMxi/2 * log( 1 + pow( _c2/_xkMxi ,2))+
                 _c3 * arctan3(_c3, _xkMxi) - _xkMxi/2 * log( 1 + pow( _c3/_xkMxi ,2))-
                 _c4 * arctan3(_c4, _xkMxi) + _xkMxi/2 * log( 1 + pow( _c4/_xkMxi ,2)));
    return result;
}

double calc_matrix_item_AJ2(Model_point_s *i_point, Model_point_s *k_point)
{
    double yk = get_y(k_point),
           xk = get_x(k_point),
           dxk = (get_tan_x(k_point) == 0)? 0 : get_Size(k_point),
           dyk = (get_tan_y(k_point) == 0)? 0 : get_Size(k_point);
    
    double yi = get_y(i_point),
           xi = get_x(i_point),
           dxi = (get_tan_x(i_point) == 0)? 0 : get_Size(i_point),
           dyi = (get_tan_y(i_point) == 0)? 0 : get_Size(i_point);
    
    double _ykPdyk2 = yk+dyk/2,
           _xkPdxk2 = xk+dxk/2,
           _ykMdyk2 = yk-dyk/2,
           _xkMdxk2 = xk-dxk/2;
    
    double _yiPdyi2 = yi+dyi/2,
           _xiPdxi2 = xi+dxi/2,
           _yiMdyi2 = yi-dyi/2,
           _xiMdxi2 = xi-dxi/2;
    
    
    double _c1y = _ykPdyk2 - yi,
           _c1x = xk - _xiPdxi2,
           _c2y = _ykMdyk2 - yi,
           _c3x = xk - _xiMdxi2;
    
    double result = (get_nor_x(i_point)>0)?1:-1;
    result *= (-0.5f * _c1y * log(_c1x*_c1x + _c1y*_c1y) - _c1x*arctan3(_c1y, _c1x)+
                0.5f * _c2y * log(_c1x*_c1x + _c2y*_c2y) + _c1x*arctan3(_c2y, _c1x)+
                0.5f * _c1y * log(_c3x*_c3x + _c1y*_c1y) + _c3x*arctan3(_c1y, _c3x)-
                0.5f * _c2y * log(_c3x*_c3x + _c2y*_c2y) - _c3x*arctan3(_c2y, _c3x));
    return result;
}

Array_s* calulate_matrix_AJ(Inductor_model_data_s *inductorModel)
{
    int inductor_points_length = inductorModel->array_model_points->length;
    Array_s *result = array_new(inductor_points_length*inductor_points_length);
    for (int k=0; k<inductor_points_length; k++)
    {
        Model_point_s *k_point = (Model_point_s*)(array_get_by_index(inductorModel->array_model_points, k));
        for (int i=0; i<inductor_points_length; i++)
        {
            double *d = malloc(sizeof(double));
            *d = 0;
            if (i==k)
                array_add(result, d);
            else
            {
                Model_point_s *i_point = (Model_point_s*)(array_get_by_index(inductorModel->array_model_points, i));
                
                if (k_point->normal_vector->y == 0)
                {
                    if (i_point->normal_vector->y == 0)
                    {
                        *d = calc_matrix_item_AJ1(i_point, k_point);
                    }
                    else if (i_point->normal_vector->x == 0)
                    {
                        *d = calc_matrix_item_AJ2(i_point, k_point);
                    }
                }
                else if (k_point->normal_vector->x == 0)
                {
                    if (i_point->normal_vector->y == 0)
                    {
                        *d = calc_matrix_item_AJ2(k_point, i_point);
                    }
                    else if (i_point->normal_vector->x == 0)
                    {
                        *d = calc_matrix_item_AJ1(k_point, i_point);
                    }
                }
                array_add(result, d);
            }
        }
    }
    return result;
}

void calculate(Array_s *matrix_AJ)
{
    
}

