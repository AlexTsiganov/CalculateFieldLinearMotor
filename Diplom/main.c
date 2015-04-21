//
//  main.c
//  Diplom
//
//  Created by Alex Tsiganov on 17.03.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Inductor_model_data.h"
#include "Config.h"
#include <stdlib.h>
#include "Main_calculate.h"

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
        double normal = ((Model_point_s*)array_points->items[i])->value;
        fprintf(f, "%f\t%f\t%s\n", point->x, point->y, normal==1?"x":"o");
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

void create_models_data()
{
    Inductor_model_data_s *inductorModel = newModelInductor();
    write_Inductor_model_to_file(inductorModel, PATH_INDUCTOR_MODEL_DATA);
    write_Inductor_model_faza_to_data_file(inductorModel->array_points_faza_A, PATH_INDUCTOR_MODEL_FAZA_A_DATA);
    write_Inductor_model_faza_to_data_file(inductorModel->array_points_faza_B, PATH_INDUCTOR_MODEL_FAZA_B_DATA);
    write_Inductor_model_faza_to_data_file(inductorModel->array_points_faza_C, PATH_INDUCTOR_MODEL_FAZA_C_DATA);
    calulate_B0(inductorModel);
}

int main(int argc, const char * argv[])
{
    create_models_data();
    printf("Done\n");
    return 0;
}
