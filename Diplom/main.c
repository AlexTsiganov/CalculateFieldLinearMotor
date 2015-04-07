//
//  main.c
//  Diplom
//
//  Created by Alex Tsiganov on 17.03.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include <stdio.h>
#include "Model_data.h"

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

void create_model_data()
{
    Model_inductor_data_s *inductor = newModelInductor();
}

int main(int argc, const char * argv[])
{
    create_model_data();
    //writeResultsToFile();
    test_t();
    return 0;
}
