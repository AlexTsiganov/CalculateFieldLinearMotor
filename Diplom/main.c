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
    print_Model_Inductor(inductorModel);
    main_calcuate(inductorModel);
    write_Inductor_model_to_data_files(inductorModel);
}

int main(int argc, const char * argv[])
{
//#pragma omp parallel
//   printf("Hello from thread %d, nthreads %d\n", omp_get_thread_num(), omp_get_num_threads());
    create_models_data();
    printf("Done\n");
    return 0;
}
