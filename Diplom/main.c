//
//  main.c
//  Diplom
//
//  Created by Alex Tsiganov on 17.03.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include <stdio.h>
#include "Model_data.h"
#include <stdlib.h>
#include "Config.h"

void test_t()
{
    FILE *f = fopen("/Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data files/model_graph.data", "w");
    if (!f)
        return;
    for (int i=0; i<10; i++)
    {
        fprintf(f, "%d\t%f\n", i, (i*i*2.35));
    }
    fclose(f);
}

void write_Inductor_model_to_file(Inductor_model_data_s *inductorModel, char *filePath)
{
    FILE *f = fopen(filePath, "w");
    if (!f)
        return;
    fprintf(f, "point_x \tpoint_y\n");
    for (int i=0; i<inductorModel->points->length; i++)
    {
        Point_s *point = ((Point_value_s*)inductorModel->points->items[i])->point;
        fprintf(f, "%f\t%f\n", point->x, point->y);
    }
    fclose(f);
}

void write_Inductor_model_for_Grapher(Inductor_model_data_s *inductor)
{
#warning TODO:
    FILE *f = fopen("/Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Data files/model_inductor.txt", "w");
    if (!f)
        return;
    for (int i=0; i<inductor->points->length; i++)
    {
        double x = ((Point_value_s*)inductor->points->items[i])->point->x;
        double y = ((Point_value_s*)inductor->points->items[i])->point->y;
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
    write_Inductor_model_to_file(inductorModel, PATH_MODEL_DATA_INDUCTOR);
}

int main(int argc, const char * argv[])
{
    create_models_data();
    return 0;
}
