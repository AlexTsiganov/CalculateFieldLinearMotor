//
//  WriteFile.c
//  Diplom
//
//  Created by Alex Tsiganov on 22.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "WriteFile.h"
#include "Config.h"

void write_Inductor_model_to_file(Inductor_model_data_s *inductorModel, char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f)
    return;
    fprintf(f, "point_x \tpoint_y\n");
    for (int i=0; i<inductorModel->array_model_points->length; i++)
    {
        Point_s *point = ((Model_point_s*)inductorModel->array_model_points->items[i])->point;
        fprintf(f, "%f\t%f\n", point->x, point->y);
    }
    fclose(f);
}

void write_Inductor_model_faza_to_data_file(Array_s *array_points, char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f)
    return;
    fprintf(f, "x \ty\tclass\n");
    for (int i=0; i<array_points->length; i++)
    {
        Point_s *point = ((Model_point_s*)array_points->items[i])->point;
        enum{x,o} znak = ((Model_point_s*)array_points->items[i])->znak;
        fprintf(f, "%f\t%f\t%s\n", point->x, point->y, znak==x?"x":"o");
    }
    fclose(f);
}

void write_calculate_B0_to_file(Array_s *array, char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f)
    return;
    fprintf(f, "point_x \tpoint_y\n");
    for (int i=0; i<array->length; i++)
    {
        Model_point_s *model_point = (Model_point_s*)array->items[i];
        fprintf(f, "%d\t%f\n", i,model_point->value);
    }
    fclose(f);
}

void write_Inductor_model_for_Grapher(Inductor_model_data_s *inductor)
{
#warning TODO:
    FILE *f = fopen("/Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data files/model_inductor.txt", "w");
    if (!f)
    return;
    for (int i=0; i<inductor->array_model_points->length; i++)
    {
        double x = ((Model_point_s*)inductor->array_model_points->items[i])->point->x;
        double y = ((Model_point_s*)inductor->array_model_points->items[i])->point->y;
        fprintf(f, "%f\t%f\n", x, y);
    }
    fclose(f);
    system("echo > tmd_d.txt");
    system("sed -e 's/[^0-9]/,/' /Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data\\ files/model_inductor.txt > /Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data\\ files/tmp_d1.txt");
    system("sed -e 's/[^0-9]/,/' /Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data\\ files/model_inductor.txt > /Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data\\ files/model_inductor1.txt");
}

void write_Inductor_model_to_data_files(Inductor_model_data_s *inductorModel)
{
    write_Inductor_model_to_file(inductorModel, PATH_INDUCTOR_MODEL_DATA);
    write_Inductor_model_faza_to_data_file(inductorModel->array_points_faza_A, PATH_INDUCTOR_MODEL_FAZA_A_DATA);
    write_Inductor_model_faza_to_data_file(inductorModel->array_points_faza_B, PATH_INDUCTOR_MODEL_FAZA_B_DATA);
    write_Inductor_model_faza_to_data_file(inductorModel->array_points_faza_C, PATH_INDUCTOR_MODEL_FAZA_C_DATA);
}
