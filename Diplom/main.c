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
//#include <omp.h>


void create_models_data()
{
    Inductor_model_data_s *inductorModel = newModelInductor();
//    print_Array_s(inductorModel->array_model_points);
//    printf("=====================\n");
//    print_Array_s(inductorModel->array_points_faza_A);
//    printf("=====================\n");
//    write_Inductor_model_to_data_files(inductorModel);

    Array_s *matrix = calulate_matrix_AJ(inductorModel);
    write_calculate_Matrix_AJ_to_file(matrix, PATH_RESULT_MATRIX_AJ_DATA);
    //print_Array_s_Matrix_Jitems(matrix);
    
    //Array_s *array_B0 = calulate_B0(inductorModel);
    //print_Array_s(array_B0);
    //write_calculate_B0_to_file(array_B0, PATH_RESULT_INDUCTOR_B0_DATA);
    
    //system("/Users/alextsiganov/Documents/University/Projects/CalculateFieldLinearMotor/Scripts/Build_PDF_Inductor_B0.sh");
    
}

int main(int argc, const char * argv[])
{
//#pragma omp parallel
//   printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
    create_models_data();
    printf("Done\n");
    return 0;
}
