//
//  WriteFile.c
//  Diplom
//
//  Created by Alex Tsiganov on 22.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "WriteFile.h"
#include "Config.h"

void write_Inductor_to_file(Inductor_model_data_s *inductorModel, char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f)
    return;
    fprintf(f, "point_x \tpoint_y\n");
    for (int i=0; i<inductorModel->inductor_size; i++)
    {
        Point_s *point = inductorModel->inductor[i].point;
        fprintf(f, "%f\t%f\n", point->x, point->y);
    }
    fclose(f);
}

void write_Katushka_to_data_file(Model_katuska_point_s *points, int lenght, char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f)
    return;
    fprintf(f, "x\ty\tclass\n");
    for (int i=0; i<lenght; i++)
    {
        Point_s *point = points[i].point;
        Drift_e znak = points[i].drift;
        fprintf(f, "%f\t%f\t%s\n", point->x, point->y, znak==x?"x":"o");
    }
    fclose(f);
}

void write_calculate_inductor_J_to_file(Calculate_J_result *j_result, Inductor_model_data_s *inductorModel, char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f)
    return;
    fprintf(f, "n\tx\ty\tJ\tJ0\n");
    for (int i=0; i<inductorModel->inductor_size; i++)
    {
        Model_inductor_point_s model_point = inductorModel->inductor[i];
        double j = j_result->J_inductor[j_result->total_count][i];
        double j0 = j_result->J0_inductor[i];
        j = j0+j0/2;
        fprintf(f, "%d\t%f\t%f\t%f\t%f\n",i , model_point.point->x, model_point.point->y, j, j0);
    }
    fclose(f);
}

void write_Inductor_model_for_Grapher(Inductor_model_data_s *inductor_model)
{
#warning TODO:
    FILE *f = fopen("/Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data files/model_inductor.txt", "w");
    if (!f)
        return;
    for (int i=0; i<inductor_model->inductor_size; i++)
    {
        double x = inductor_model->inductor[i].point->x;
        double y = inductor_model->inductor[i].point->y;
        fprintf(f, "%f\t%f\n", x, y);
    }
    fclose(f);
    system("echo > tmd_d.txt");
    system("sed -e 's/[^0-9]/,/' /Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data\\ files/model_inductor.txt > /Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data\\ files/tmp_d1.txt");
    system("sed -e 's/[^0-9]/,/' /Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data\\ files/model_inductor.txt > /Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data\\ files/model_inductor1.txt");
}

void write_Inductor_model_to_data_files(Inductor_model_data_s *inductorModel)
{
    write_Inductor_to_file(inductorModel, PATH_INDUCTOR_MODEL_DATA);
    write_Katushka_to_data_file(inductorModel->katushka[Faza_A], inductorModel->katushka_size, PATH_INDUCTOR_MODEL_FAZA_A_DATA);
    write_Katushka_to_data_file(inductorModel->katushka[Faza_B], inductorModel->katushka_size, PATH_INDUCTOR_MODEL_FAZA_B_DATA);
    write_Katushka_to_data_file(inductorModel->katushka[Faza_C], inductorModel->katushka_size, PATH_INDUCTOR_MODEL_FAZA_C_DATA);
}

void write_calculate_Matrix_AJ_to_file(double *A_matrix, int size, char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f)
        return;
    int length = sqrt(size);
    for (int i=0; i<length; i++)
    {
        fprintf(f, "%.6f", A_matrix[i*length]);
        for (int k=1; k<length; k++)
        {
            fprintf(f, "%-10.6f", A_matrix[i*length+k]);
        }
        fprintf(f, "\n\n\n");
    }
    fclose(f);
}
