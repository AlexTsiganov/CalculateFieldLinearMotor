//
//  Calculate_J.h
//  Diplom
//
//  Created by Alex Tsiganov on 09.06.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#ifndef __Diplom__Calculate_J__
#define __Diplom__Calculate_J__

#include "Inductor_model_data.h"

typedef struct
{
    Inductor_model_data_s *inductorModel;
    int count;
    double error;
    double *J0_inductor, **J_inductor, *A_matrix;
}Calculate_J_result;

typedef struct
{
    Inductor_model_data_s *inductorModel;
    double error; // 0-1;
    void (*on_calculate_J)(int index, double *J_inductor, double errorMax, double errorMin, Inductor_model_data_s *inductorModel);
}Calculate_J_params;

Calculate_J_result* calulate_J_inductor(Calculate_J_params calculate_J_params);

#endif
