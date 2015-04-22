//
//  Calculate_B0.c
//  Diplom
//
//  Created by Alex Tsiganov on 16.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Calculate_B0.h"
#include "Intergals.h"
#include <math.h>
#include <stdlib.h>

Array_s* calulate_B0(Inductor_model_data_s *inductorModel)
{
    Array_s *array_B0 = array_new();
    for (int i=0; i<inductorModel->array_model_points->length; i++)
    {
        double sum = 0;
        
        Model_point_s *point_inductora = inductorModel->array_model_points->items[i];
        double px = get_x(point_inductora);
        double py = get_y(point_inductora);
        double pSize = get_Size(point_inductora);
        for (int j=0; j<inductorModel->array_points_faza_A->length; j++)
        {
            Model_point_s *point_katushki_faza_A = inductorModel->array_points_faza_A->items[j];
            double ax = point_katushki_faza_A->point->x;
            double ay = point_katushki_faza_A->point->y;
            double aWidth = point_katushki_faza_A->width;
            double aHeight = point_katushki_faza_A->height;
            
            Model_point_s *point_katushki_faza_B = inductorModel->array_points_faza_B->items[j];
            double bx = point_katushki_faza_B->point->x;
            double by = point_katushki_faza_B->point->y;
            double bWidth = point_katushki_faza_B->width;
            double bHeight = point_katushki_faza_B->height;
            
            Model_point_s *point_katushki_faza_C = inductorModel->array_points_faza_C->items[j];
            double cx = point_katushki_faza_C->point->x;
            double cy = point_katushki_faza_C->point->y;
            double cWidth = point_katushki_faza_C->width;
            double cHeight = point_katushki_faza_C->height;
            
            if (isTan_y(point_inductora))
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
                sum -= point_katushki_faza_A->value*int_Bt(x1, x2, x3, x4, x5, x6);
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
                sum += 0.5*point_katushki_faza_B->value*int_Bt(x1, x2, x3, x4, x5, x6);
                
                x1 = px + pSize/2 - cx - cWidth/2;
                x2 = px - pSize/2 - cx - cWidth/2;
                x5 = py - cy - cHeight/2;
                x3 = px + pSize/2 - cx + cWidth/2;
                x4 = px - pSize/2 - cx + cWidth/2;
                x6 = py - cy + cHeight/2;
                sum += 0.5*point_katushki_faza_C->value*int_Bt(x1, x2, x3, x4, x5, x6);
            }
            if (isTan_x(point_inductora))
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
                sum += point_katushki_faza_A->value*int_Bt(x1, x2, x3, x4, x5, x6);
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
                sum -= 0.5*point_katushki_faza_B->value*int_Bt(x1, x2, x3, x4, x5, x6);
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
                sum -= 0.5*point_katushki_faza_C->value*int_Bt(x1, x2, x3, x4, x5, x6);
            }
        }
        sum = 2*1e-7*sum;
        if (isTan_y(point_inductora))
        {
            sum*=-_lyambda*(2/(pSize*4*M_PI*1e-7))*get_tan_x(point_inductora);
        }
        else if (isTan_x(point_inductora))
        {
            sum*=-_lyambda*(2/(pSize*4*M_PI*1e-7))*get_tan_y(point_inductora);
        }
        point_inductora->value = sum;
        array_add(array_B0, newModelPoint(.point = point_inductora->point,
                                          .value = sum));
    }
    return array_B0;
}