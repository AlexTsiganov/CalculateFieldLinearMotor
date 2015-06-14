//
//  Print.c
//  Diplom
//
//  Created by Alex Tsiganov on 22.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Print.h"
#include "Model_point.h"

void print_Model_Inductor(Inductor_model_data_s *inductor_model)
{
    for (int i=0; i<inductor_model->inductor_size; i++)
    {
        Model_inductor_point_s inductor_point = inductor_model->inductor[i];
        printf("Point: (%.3f; %.3f) -> %.3f", inductor_point.point->x, inductor_point.point->y, inductor_point.dSize);
        if (inductor_point.normal_vector)
            printf(", normal_vector: (%.3f; %.3f)", inductor_point.normal_vector->x, inductor_point.normal_vector->y);
        if (inductor_point.tan_vector)
            printf(", tan_vector: (%.3f; %.3f)", inductor_point.tan_vector->x, inductor_point.tan_vector->y);
        printf("\n");
    }
}

void print_Array_s_Matrix_Jitems(double *A_matrix, int size)
{
    printf("Print Matrix J items: \n");
    for (int i=0; i<size/2; i++)
    {
        for (int k=0; k<size/2; k++)
        {
            printf("  %.3f  ", A_matrix[k+i*size/2]);
        }
        printf("\n");
    }
}