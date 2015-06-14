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
    printf("on_calculate_J_inductora  with: Index: %d\n",index);
    for (int i=0; i<inductorModel->inductor_size; i++)
    {
        Point_s *point = inductorModel->inductor[i].point;
        double j = J_inductor[i];
        printf("J(%.3f; %.3f) -> %.3f\n", point->x, point->y, j);
    }
}

void main_calcuate(Inductor_model_data_s *inductor_model, Model_line_data_s *line)
{
    calulate_line_B0(inductor_model, line);
    Calculate_J_result *result_J = calulate_J_inductor((Calculate_J_params){.inductorModel = inductor_model, .error = 0.3, .on_calculate_J = on_calculate_J});
    
    write_calculate_inductor_J_to_file(result_J, inductor_model, PATH_RESULT_INDUCTOR_J_DATA);
}