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
    double *J0_inductor, *J_inductor;
    int total_index;
    void (*on_calculate_J)(int index, double *J_inductor, double errorMax, double errorMin);
}Calculate_J_result;

typedef struct
{
    Inductor_model_data_s *inductorModel;
    double error; // 0-1;
}Calculate_J_params;

Array_s* calulate_matrix_AJ(Inductor_model_data_s *inductorModel);
Calculate_J_result* calulate_J_inductor(Inductor_model_data_s *inductorModel);

#endif
