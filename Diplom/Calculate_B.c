//
//  Calculate_B0.c
//  Diplom
//
//  Created by Alex Tsiganov on 16.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Calculate_B.h"
#include <stdlib.h>
#include "Default_model_params.h"

double _bxk(Point_s *mPoint, Model_katuska_point_s *kPoint)
{
    double result=0;
    double xm = mPoint->x,
    ym = mPoint->y,
    xk = kPoint->point->x,
    yk = kPoint->point->y,
    dx = kPoint->dWidth,
    dy = kPoint->dHeight;
    
    double c1 = xm - (xk + dx/2),
           c2 = ym - (yk + dy/2),
           c3 = c1*c1+c2*c2;
    if (c1 != 0 && c3>0)
        result+=c1/2*log(c3);
    
    double c4 = ym - (yk - dy/2),
           c5 = c1*c1+c4*c4;
    if (c1 != 0 && c5>0)
        result-=c1/2*log(c5);
    
    double c6 = xm - (xk - dx/2),
           c7 = c6*c6+c2*c2;
    if (c6 != 0 && c7>0)
        result-=c6/2*log(c3);
    
    double c8 = c4*c4+c6*c6;
    if (c6 != 0 && c8>0)
        result+=c6/2*log(c8);
    
    if (c2 != 0)
        result+=c2*atan(c1/c2);
    
    if (c4 != 0)
        result-=c4*atan(c1/c4);
    
    if (c2 != 0)
        result-=c2*atan(c6/c2);
    
    if (c4 != 0)
        result+=c4*atan(c6/c4);
    
    if (result !=0)
        result*=-_m0/(2*M_PI);
    return result;
}

double _byk(Point_s *mPoint, Model_katuska_point_s *kPoint)
{
    double result=0;
    double xm = mPoint->x,
    ym = mPoint->y,
    xk = kPoint->point->x,
    yk = kPoint->point->y,
    dx = kPoint->dWidth,
    dy = kPoint->dHeight;
    
    double c1 = xm - (xk + dx/2),
           c2 = ym - (yk + dy/2),
           c3 = ym - (yk - dy/2),
           c4 = xm - (xk - dx/2),
           c5 = c1*c1 + c2*c2,
           c6 = c4*c4 + c2*c2,
           c7 = c1*c1 + c3*c3,
           c8 = c4*c4 + c3*c3;
    if (c2 != 0 && c5>0)
        result+=c2/2*log(c5);
    
    if (c2 != 0 && c6>0)
        result-=c1/2*log(c6);
    
    if (c3 != 0 && c7>0)
        result-=c3/2*log(c7);
    
    if (c3 != 0 && c8>0)
        result+=c3/2*log(c8);
    
    if (c1 != 0)
        result+=c1*atan(c2/c1);
    
    if (c4 != 0)
        result-=c4*atan(c2/c4);
    
    if (c1 != 0)
        result-=c1*atan(c3/c1);
    
    if (c4 != 0)
        result+=c4*atan(c3/c4);
    
    if (result !=0)
        result*=_m0/(2*M_PI);
    return result;
}

Calculate_B0_result* calulate_line_B0(Inductor_model_data_s *inductorModel,Model_line_data_s *lineModel)
{
    Calculate_B0_result *result = malloc(sizeof(Calculate_B0_result));
    double Im = inductorModel->params->I_katushki;
    double complex *Bx = malloc(sizeof(double complex)*lineModel->count),
                   *By = malloc(sizeof(double complex)*lineModel->count);
    double dS = inductorModel->params->katushka_height*(inductorModel->params->groove_width-2*inductorModel->params->katushka_zazor);
    for (int i=0; i<lineModel->count; i++)
    {
        Point_s point = lineModel->points[i];
        double _bx=0, _by=0;
        for (int k=0; k<inductorModel->katushka_size; k++)
        {
            Model_katuska_point_s katushkaPoint = inductorModel->katushka[Faza_A][k];
            _bx += _bxk(&point, &katushkaPoint);
            _by += _byk(&point, &katushkaPoint);
        }
        Bx[i] = _bx/**(Im - 0.5f*Im - 0.5f*Im)*/ + _bx/**(-sqrt(3)/2 + sqrt(3)/2)*/*_Complex_I;
        By[i] = _by/**(Im - 0.5f*Im - 0.5f*Im)*/ + _by/**(-sqrt(3)/2 + sqrt(3)/2)*/*_Complex_I;
        
        
        double t1 = creal(Bx[i]);
        double t2 = cimag(Bx[i]);
    }
    result->By = By;
    result->Bx = Bx;
    return result;
}