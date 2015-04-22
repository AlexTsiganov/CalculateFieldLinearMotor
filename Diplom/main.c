//
//  main.c
//  Diplom
//
//  Created by Alex Tsiganov on 17.03.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Inductor_model_data.h"
#include "Config.h"
#include "WriteFile.h"
#include "Main_calculate.h"
#include "Print.h"


void create_models_data()
{
    Inductor_model_data_s *inductorModel = newModelInductor();
    print_Array_s(inductorModel->array_model_points);
    printf("=====================\n");
    print_Array_s(inductorModel->array_points_faza_A);
    printf("=====================\n");
    write_Inductor_model_to_data_files(inductorModel);

   Array_s *array_B0 = calulate_B0(inductorModel);
    print_Array_s(array_B0);
    write_calculate_B0_to_file(array_B0, PATH_RESULT_INDUCTOR_B0_DATA);
}

int main(int argc, const char * argv[])
{
    create_models_data();
    printf("Done\n");
    return 0;
}
