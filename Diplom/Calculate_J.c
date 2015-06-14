//
//  Calculate_J.c
//  Diplom
//
//  Created by Alex Tsiganov on 09.06.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Calculate_J.h"
#include "Math_fuctions.h"
#include <stdlib.h>
#include <math.h>
#include "WriteFile.h"
#include "Config.h"

double calc_matrix_item_AJ1(Model_inductor_point_s *i_point, Model_inductor_point_s *k_point)
{
    double yk = k_point->point->y,
           xk = k_point->point->x,
           dxk = (k_point->tan_vector->x == 0)?0:k_point->dSize,
           dyk = (k_point->tan_vector->y == 0)?0:k_point->dSize;
    
    double yi = i_point->point->y,
           xi = i_point->point->x,
           dxi = (i_point->tan_vector->x == 0)?0:i_point->dSize,
           dyi = (i_point->tan_vector->y == 0)?0:i_point->dSize;
    
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
    
    double result = 0;
    
    if (_c1 != 0)
        result += -_c1 * arctan3(_c1, _xkMxi);
    if (_xkMxi != 0)
        result += _xkMxi/2 * log( 1 + pow( _c1/_xkMxi ,2));
    if (_c2 != 0)
        result += _c2 * arctan3(_c2, _xkMxi);
    if (_xkMxi != 0)
        result -= _xkMxi/2 * log( 1 + pow( _c2/_xkMxi ,2));
    if (_c3 != 0)
        result += _c3 * arctan3(_c3, _xkMxi);
    if (_xkMxi != 0)
        result -= _xkMxi/2 * log( 1 + pow( _c3/_xkMxi ,2));
    if (_c4 != 0)
        result += -_c4 * arctan3(_c4, _xkMxi);
    if (_xkMxi != 0)
        result += _xkMxi/2 * log( 1 + pow( _c4/_xkMxi ,2));
    
    result *= (i_point->normal_vector->x > 0)?1:-1;
    /*result *= ( -_c1 * arctan3(_c1, _xkMxi) + _xkMxi/2 * log( 1 + pow( _c1/_xkMxi ,2))+
                 _c2 * arctan3(_c2, _xkMxi) - _xkMxi/2 * log( 1 + pow( _c2/_xkMxi ,2))+
                 _c3 * arctan3(_c3, _xkMxi) - _xkMxi/2 * log( 1 + pow( _c3/_xkMxi ,2))-
                 _c4 * arctan3(_c4, _xkMxi) + _xkMxi/2 * log( 1 + pow( _c4/_xkMxi ,2)));*/
    return result;
}

double calc_matrix_item_AJ2(Model_inductor_point_s *i_point, Model_inductor_point_s *k_point)
{
    double yk = k_point->point->y,
           xk = k_point->point->x,
           dxk = (k_point->tan_vector->x == 0)?0:k_point->dSize,
           dyk = (k_point->tan_vector->y == 0)?0:k_point->dSize;
    
    double yi = i_point->point->y,
           xi = i_point->point->x,
           dxi = (i_point->tan_vector->x == 0)?0:i_point->dSize,
           dyi = (i_point->tan_vector->y == 0)?0:i_point->dSize;
    
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
    
    double result=0;
    if (_c1y != 0)
        result -= 0.5f * _c1y * log(_c1x*_c1x + _c1y*_c1y);
    result += _c1x*arctan3(_c1y, _c1x);
    if (_c2y != 0)
        result += 0.5f * _c2y * log(_c1x*_c1x + _c2y*_c2y);
    result += _c1x*arctan3(_c2y, _c1x);
    if (_c1y != 0)
        result += 0.5f * _c1y * log(_c3x*_c3x + _c1y*_c1y);
    result += _c3x*arctan3(_c1y, _c3x);
    if (_c2y != 0)
        result -= 0.5f * _c2y * log(_c3x*_c3x + _c2y*_c2y);
    result -= _c3x*arctan3(_c2y, _c3x);
    result *= (i_point->normal_vector->x > 0)?1:-1;
    /*result *= (-0.5f * _c1y * log(_c1x*_c1x + _c1y*_c1y) - _c1x*arctan3(_c1y, _c1x)+
                0.5f * _c2y * log(_c1x*_c1x + _c2y*_c2y) + _c1x*arctan3(_c2y, _c1x)+ // log 0 !!
                0.5f * _c1y * log(_c3x*_c3x + _c1y*_c1y) + _c3x*arctan3(_c1y, _c3x)-
                0.5f * _c2y * log(_c3x*_c3x + _c2y*_c2y) - _c3x*arctan3(_c2y, _c3x));*/
    return result;
}

double* matrix_AJ_new(Inductor_model_data_s *inductorModel)
{
    printf("start matrix_AJ_mew\n");
    int inductor_points_length = inductorModel->inductor_size;
    double *result = malloc(sizeof(double)*(inductor_points_length*inductor_points_length));
    for (int k=0; k<inductor_points_length; k++)
    {
        Model_inductor_point_s k_point = inductorModel->inductor[k];
        for (int i=0; i<inductor_points_length; i++)
        {
            double d = 0;
            if (i!=k)
            {
                Model_inductor_point_s i_point = inductorModel->inductor[i];
                double dL = i_point.dSize;
                double xk_ = k_point.point->x * i_point.normal_vector->y - k_point.point->y * i_point.normal_vector->x;
                double yk_ = k_point.point->x * i_point.normal_vector->x - k_point.point->y * i_point.normal_vector->y;
                double n1 = i_point.normal_vector->x * k_point.normal_vector->x + i_point.normal_vector->y * k_point.normal_vector->y;
                double n2 = k_point.normal_vector->x * i_point.normal_vector->y + k_point.normal_vector->y * i_point.normal_vector->x;
                if (n1 != 0)
                    d += n1*(arctan3(yk_, xk_+dL/2) - arctan3(yk_, xk_-dL/2));
                if (n2 != 0)
                    d += 0.5*n2*(log((xk_+dL/2)*(xk_+dL/2) + yk_*yk_) - log((xk_-dL/2)*(xk_-dL/2) + yk_*yk_));
                int h;
                h=1;
                h=2;
            }
            result[i+k*inductor_points_length] = d;
        }
    }
    return result;
}

double* matrix_AJ(Inductor_model_data_s *inductorModel)
{
    printf("start matrix_AJ\n");
    int inductor_points_length = inductorModel->inductor_size;
    double *result = malloc(sizeof(double)*(inductor_points_length*inductor_points_length));
    for (int k=0; k<inductor_points_length; k++)
    {
        Model_inductor_point_s k_point = inductorModel->inductor[k];
        for (int i=0; i<inductor_points_length; i++)
        {
            double d = 0;
            if (i!=k)
            {
                Model_inductor_point_s i_point = inductorModel->inductor[i];
                
                if (k_point.normal_vector->y == 0)
                {
                    if (i_point.normal_vector->y == 0)
                    {
                        d = calc_matrix_item_AJ1(&i_point, &k_point);
                    }
                    else if (i_point.normal_vector->x == 0)
                    {
                        d = calc_matrix_item_AJ2(&i_point, &k_point);
                    }
                }
                else if (k_point.normal_vector->x == 0)
                {
                    if (i_point.normal_vector->y == 0)
                    {
                        d = calc_matrix_item_AJ2(&k_point, &i_point);
                    }
                    else if (i_point.normal_vector->x == 0)
                    {
                        d = calc_matrix_item_AJ1(&k_point, &i_point);
                    }
                }
            }
            result[i+k*inductor_points_length] = d;
        }
    }
    printf("end matrix_AJ\n");
    return result;
}

double* calculate_J0(Inductor_model_data_s *inductorModel)
{
    printf("start calculate_J0\n");
    double *result = malloc(sizeof(double)*inductorModel->inductor_size);
    for (int i=0; i<inductorModel->inductor_size; i++)
    {
        double sum = 0;
        Model_inductor_point_s point_inductora = inductorModel->inductor[i];
        double px = point_inductora.point->x;
        double py = point_inductora.point->y;
        double pSize = point_inductora.dSize;
        for (int j=0; j<inductorModel->katushka_size; j++)
        {
            Model_katuska_point_s point_katushki_faza_A = inductorModel->katushka[Faza_A][j];
            double ax = point_katushki_faza_A.point->x;
            double ay = point_katushki_faza_A.point->y;
            double aWidth = point_katushki_faza_A.dWidth;
            double aHeight = point_katushki_faza_A.dHeight;
            
            Model_katuska_point_s point_katushki_faza_B = inductorModel->katushka[Faza_B][j];
            double bx = point_katushki_faza_B.point->x;
            double by = point_katushki_faza_B.point->y;
            double bWidth = point_katushki_faza_B.dWidth;
            double bHeight = point_katushki_faza_B.dHeight;
            
            Model_katuska_point_s point_katushki_faza_C = inductorModel->katushka[Faza_C][j];
            double cx = point_katushki_faza_C.point->x;
            double cy = point_katushki_faza_C.point->y;
            double cWidth = point_katushki_faza_C.dWidth;
            double cHeight = point_katushki_faza_C.dHeight;
            
            if (point_inductora.tan_vector->y == 0)
            {
                /*
                 x1:=xp[lp,i]+epsxp[lp,i]/2-xa[m]-dxa[m]/2;
                 x2:=xp[lp,i]-epsxp[lp,i]/2-xa[m]-dxa[m]/2;
                 x5:=yp[lp,i]-ya[m]-dya[m]/2;
                 //xp[], yp[] - координаты точек разбиения индуктора
                 //xa[] - координата в фазе А, dxa[], dya[](вдоль у) - ширина разбиения элеиента в катуште.
                 // epsxp[] длина отрезка вдоль х, на границе индуктора
                 x3:=xp[lp,i]+epsxp[lp,i]/2-xa[m]+dxa[m]/2;
                 x4:=xp[lp,i]-epsxp[lp,i]/2-xa[m]+dxa[m]/2;
                 x6:=yp[lp,i]-ya[m]+dya[m]/2;
                 summ:=summ-ia[m]*Int_Bt(x1,x2,x3,x4,x5,x6); // ia[] - значение тока в фазе A
                 */
                 double x1 = px + pSize/2 - ax - aWidth/2;
                 double x2 = px - pSize/2 - ax - aWidth/2;
                 double x5 = py - ay - aHeight/2;
                 double x3 = px + pSize/2 - ax + aWidth/2;
                 double x4 = px - pSize/2 - ax + aWidth/2;
                 double x6 = py - ay + aHeight/2;
                 sum -= point_katushki_faza_A.I_vitka*int_Bt(x1, x2, x3, x4, x5, x6);
                /*
                 x1:=xp[lp,i]+epsxp[lp,i]/2-xb[m]-dxb[m]/2;
                 x2:=xp[lp,i]-epsxp[lp,i]/2-xb[m]-dxb[m]/2;
                 x5:=yp[lp,i]-yb[m]-dyb[m]/2;
                 x3:=xp[lp,i]+epsxp[lp,i]/2-xb[m]+dxb[m]/2;
                 x4:=xp[lp,i]-epsxp[lp,i]/2-xb[m]+dxb[m]/2;
                 x6:=yp[lp,i]-yb[m]+dyb[m]/2;
                 summ:=summ+(1/2)*ib[m]*Int_Bt(x1,x2,x3,x4,x5,x6);
                 */
                 x1 = px + pSize/2 - bx - bWidth/2;
                 x2 = px - pSize/2 - bx - bWidth/2;
                 x5 = py - by - bHeight/2;
                 x3 = px + pSize/2 - bx + bWidth/2;
                 x4 = px - pSize/2 - bx + bWidth/2;
                 x6 = py - by + bHeight/2;
                 sum += 0.5*point_katushki_faza_B.I_vitka*int_Bt(x1, x2, x3, x4, x5, x6);
                 
                 x1 = px + pSize/2 - cx - cWidth/2;
                 x2 = px - pSize/2 - cx - cWidth/2;
                 x5 = py - cy - cHeight/2;
                 x3 = px + pSize/2 - cx + cWidth/2;
                 x4 = px - pSize/2 - cx + cWidth/2;
                 x6 = py - cy + cHeight/2;
                 sum += 0.5*point_katushki_faza_C.I_vitka*int_Bt(x1, x2, x3, x4, x5, x6);
            }
            if (point_inductora.tan_vector->x == 0)
            {
                /*
                 x1:=yp[lp,i]+epsyp[lp,i]/2-ya[m]-dya[m]/2;
                 x2:=yp[lp,i]-epsyp[lp,i]/2-ya[m]-dya[m]/2;
                 x5:=xp[lp,i]-xa[m]-dxa[m]/2;
                 x3:=yp[lp,i]+epsyp[lp,i]/2-ya[m]+dya[m]/2;
                 x4:=yp[lp,i]-epsyp[lp,i]/2-ya[m]+dya[m]/2;
                 x6:=xp[lp,i]-xa[m]+dxa[m]/2;
                 summ:=summ+ia[m]*Int_Bt(x1,x2,x3,x4,x5,x6);
                 */
                 double x1 = py + pSize/2 - ay - aHeight/2;
                 double x2 = py - pSize/2 - ay - aHeight/2;
                 double x5 = px - ax - aWidth/2;
                 double x3 = py + pSize/2 - ay + aHeight/2;
                 double x4 = py - pSize/2 - ay + aHeight/2;
                 double x6 = px - ax + aWidth/2;
                 sum += point_katushki_faza_A.I_vitka*int_Bt(x1, x2, x3, x4, x5, x6);
                /*
                 x1:=yp[lp,i]+epsyp[lp,i]/2-yb[m]-dyb[m]/2;
                 x2:=yp[lp,i]-epsyp[lp,i]/2-yb[m]-dyb[m]/2;
                 x5:=xp[lp,i]-xb[m]-dxb[m]/2;
                 x3:=yp[lp,i]+epsyp[lp,i]/2-yb[m]+dyb[m]/2;
                 x4:=yp[lp,i]-epsyp[lp,i]/2-yb[m]+dyb[m]/2;
                 x6:=xp[lp,i]-xb[m]+dxb[m]/2;
                 summ:=summ-(1/2)*ib[m]*Int_Bt(x1,x2,x3,x4,x5,x6);
                 */
                 x1 = py + pSize/2 - by - bHeight/2;
                 x2 = py - pSize/2 - by - bHeight/2;
                 x5 = px - bx - bWidth/2;
                 x3 = py + pSize/2 - by + bHeight/2;
                 x4 = py - pSize/2 - by + bHeight/2;
                 x6 = px - bx + bWidth/2;
                 sum -= 0.5*point_katushki_faza_B.I_vitka*int_Bt(x1, x2, x3, x4, x5, x6);
                /*
                 x1:=yp[lp,i]+epsyp[lp,i]/2-yc[m]-dyc[m]/2;
                 x2:=yp[lp,i]-epsyp[lp,i]/2-yc[m]-dyc[m]/2;
                 x5:=xp[lp,i]-xc[m]-dxc[m]/2;
                 x3:=yp[lp,i]+epsyp[lp,i]/2-yc[m]+dyc[m]/2;
                 x4:=yp[lp,i]-epsyp[lp,i]/2-yc[m]+dyc[m]/2;
                 x6:=xp[lp,i]-xc[m]+dxc[m]/2;
                 summ:=summ-(1/2)*ic[m]*Int_Bt(x1,x2,x3,x4,x5,x6);
                 */
                 x1 = py + pSize/2 - cy - cHeight/2;
                 x2 = py - pSize/2 - cy - cHeight/2;
                 x5 = px - cx - cWidth/2;
                 x3 = py + pSize/2 - cy + cHeight/2;
                 x4 = py - pSize/2 - cy + cHeight/2;
                 x6 = px - cx + cWidth/2;
                 sum -= 0.5*point_katushki_faza_C.I_vitka*int_Bt(x1, x2, x3, x4, x5, x6);
            }
        }
        sum = 2*1e-7*sum;
        if (point_inductora.tan_vector->y == 0)
        {
            sum*=-_lyambda*(2/(pSize*4*M_PI*1e-7))*point_inductora.tan_vector->x;
        }
        else if (point_inductora.tan_vector->x == 0)
        {
            sum*=-_lyambda*(2/(pSize*4*M_PI*1e-7))*point_inductora.tan_vector->y;
        }
        result[i] = sum;
    }
    printf("end calculate_J0\n");
    return result;
}
                 
Calculate_J_result* calulate_J_inductor(Calculate_J_params calculate_J_params)
{
    printf("Start calulate_J_inductor\n");
    int inductr_size = calculate_J_params.inductorModel->inductor_size;
    Calculate_J_result *result = malloc(sizeof(Calculate_J_result));
    double *j0 = calculate_J0(calculate_J_params.inductorModel);
    double *matrix_A = matrix_AJ_new(calculate_J_params.inductorModel);
    
    double **j = calloc(inductr_size, sizeof(double));
     j[0] = calloc(inductr_size, sizeof(double));
    int sh = 1;
    while (1)
    {
        j[sh] = calloc(inductr_size, sizeof(double));
        for (int i=0; i<inductr_size; i++)
        {
            double j_sum = 0;
            for (int k=0; k<inductr_size; k++)
            {
                j_sum+=matrix_A[i*inductr_size+k]*j[sh-1][k];
            }
            j[sh][i] = j_sum + j0[i];
        }
        //(int index, double *J_inductor, double errorMax, double errorMin, Inductor_model_data_s *inductorModel
        calculate_J_params.on_calculate_J(sh, j[sh], 0,0,calculate_J_params.inductorModel);
        sh++;
        if (sh == 6)
        {
            break;
        }
    } // J(92.531; 0.000) -> 974.130
    
    result->inductorModel = calculate_J_params.inductorModel;
    result->A_matrix = matrix_A;
    result->J0_inductor = j0;
    write_calculate_J0_to_file(result, PATH_RESULT_INDUCTOR_B0_DATA);
    write_calculate_Matrix_AJ_to_file(result->A_matrix, pow(calculate_J_params.inductorModel->inductor_size,2), PATH_RESULT_MATRIX_AJ_DATA);
    printf("End calulate_J_inductor\n");
    return result;
}