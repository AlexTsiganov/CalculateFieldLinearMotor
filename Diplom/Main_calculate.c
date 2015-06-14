//
//  Main_calculate.c
//  Diplom
//
//  Created by Alex Tsiganov on 10.06.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Main_calculate.h"
#include "WriteFile.h"
#include "Config.h"

void on_calculate_J(int index, double *J_inductor, double errorMax, double errorMin, Inductor_model_data_s *inductorModel)
{
    printf("Index: %d\n",index);
    for (int i=0; i<inductorModel->inductor_size; i++)
    {
        Point_s *point = inductorModel->inductor[i].point;
        double j = J_inductor[i];
        printf("J(%.3f; %.3f) -> %.3f\n", point->x, point->y, j);
    }
}

void main_calcuate(Inductor_model_data_s *inductor_model)
{
    Calculate_J_result *result_J = calulate_J_inductor((Calculate_J_params){.inductorModel = inductor_model, .error = 0.3, .on_calculate_J = on_calculate_J});
}