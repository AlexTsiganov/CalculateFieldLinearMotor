//
//  Calculate_B0.h
//  Diplom
//
//  Created by Alex Tsiganov on 16.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#ifndef __Diplom__Calculate_B0__
#define __Diplom__Calculate_B0__

#include "Inductor_model_data.h"
#include "Calculate_J.h"
#include <complex.h>

typedef struct
{
    double complex *Bx, *By;
}Calculate_B0_result;

typedef struct
{
    Inductor_model_data_s *inductorModel;
    int total_count;
    double error;
    double *J0_inductor, **J_inductor, *A_matrix;
}Calculate_B_result;

typedef struct
{
    Inductor_model_data_s *inductorModel;
    Calculate_J_result *j_result;
    double error; // 0-1;
    void (*on_calculate_J)(int index, double *J_inductor, double errorMax, double errorMin, Inductor_model_data_s *inductorModel);
}Calculate_B_params;

Calculate_B0_result* calulate_line_B0(Inductor_model_data_s *inductorModel,Model_line_data_s *lineModel);

#endif
