//
//  Math_fuctions.c
//  Diplom
//
//  Created by Alex Tsiganov on 22.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Math_fuctions.h"
#include <math.h>

double calculate_line_size(Point_s *start_point, Point_s *end_point)
{
    double v_line = (end_point->x-start_point->x)*(end_point->x-start_point->x) + (end_point->y-start_point->y)*(end_point->y-start_point->y);
    return v_line >= 0 ? sqrt(v_line) : 0;
}

double arctan3(double y, double x)
{
    if (fabs(x)>1e-15)
        return atan(y/x);
    else
        return M_PI/2;
}

//*************************************************************************************************************************************

/*function Int_Bt(x1,x2,x3,x4,x5,x6:Extended):Extended;
 var a,b,c,d:Extended;
 begin
 a:=(1/4)*(x1*x1-x5*x5)*ln(x1*x1+x5*x5)+x1*x5*arctan3(x1,x5)-(1/4)*(x2*x2-x5*x5)*ln(x2*x2+x5*x5)-x2*x5*arctan3(x2,x5);
 b:=(1/4)*(x1*x1-x6*x6)*ln(x1*x1+x6*x6)+x1*x6*arctan3(x1,x6)-(1/4)*(x2*x2-x6*x6)*ln(x2*x2+x6*x6)-x2*x6*arctan3(x2,x6);
 c:=(1/4)*(x3*x3-x5*x5)*ln(x3*x3+x5*x5)+x3*x5*arctan3(x3,x5)-(1/4)*(x4*x4-x5*x5)*ln(x4*x4+x5*x5)-x4*x5*arctan3(x4,x5);
 d:=(1/4)*(x3*x3-x6*x6)*ln(x3*x3+x6*x6)+x3*x6*arctan3(x3,x6)-(1/4)*(x4*x4-x6*x6)*ln(x4*x4+x6*x6)-x4*x6*arctan3(x4,x6);
 Int_Bt:=a-b-c+d;
 end;
 begin*/

//-------------------------------------------------------------------------------------------------------------------------------------

double int_Bt(double x1, double x2, double x3, double x4, double x5, double x6)
{
    double a = (1/4)*(x1*x1-x2*x2)*log(x1*x1+x5*x5)+x1*x5*arctan3(x1,x5)-(1/4)*(x2*x2-x5*x5)*log(x2*x2+x5*x5)-x2*x5*arctan3(x2,x5);
    double b = (1/4)*(x1*x1-x6*x6)*log(x1*x1+x6*x6)+x1*x6*arctan3(x1,x6)-(1/4)*(x2*x2-x6*x6)*log(x2*x2+x6*x6)-x2*x6*arctan3(x2,x6);
    double c = (1/4)*(x3*x3-x5*x5)*log(x3*x3+x5*x5)+x3*x5*arctan3(x3,x5)-(1/4)*(x4*x4-x5*x5)*log(x4*x4+x5*x5)-x4*x5*arctan3(x4,x5);
    double d = (1/4)*(x3*x3-x6*x6)*log(x3*x3+x6*x6)+x3*x6*arctan3(x3,x6)-(1/4)*(x4*x4-x6*x6)*log(x4*x4+x6*x6)-x4*x6*arctan3(x4,x6);
    return a-b-c+d;
}

//*************************************************************************************************************************************