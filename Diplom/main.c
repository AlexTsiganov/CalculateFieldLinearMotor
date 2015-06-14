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

#include <stdlib.h>

Inductor_model_data_s *create_models_data(Inductor_model_data_params_s *model_params)
{
    Inductor_model_data_s *inductorModel = newModelInductorData(model_params);
    print_Model_Inductor(inductorModel);
    write_Inductor_model_to_data_files(inductorModel);
    return inductorModel;
}

int main(int argc, const char * argv[])
{
    Inductor_model_data_params_s *model_params = malloc(sizeof(Inductor_model_data_params_s));
    
     Inductor_model_data_s *inductorModel = create_models_data(model_params);
    Model_line_data_s *line_model = newModelLineData((Point_s){.x=0,.y=-10}, (Point_s){.x=inductorModel->params->width,.y=-10}, 1000);
    main_calcuate(inductorModel, line_model);
    printf("Done\n");
    return 0;
}
