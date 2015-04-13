//
//  Model_data.c
//  Diplom
//
//  Created by Alex Tsiganov on 07.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Model_data.h"
#include <stdlib.h>

static Model_inductor_data_s *initModelInductorData()
{
    Model_inductor_data_s *newModelParams = malloc(sizeof(Model_inductor_data_s));
    *newModelParams = (Model_inductor_data_s){};
    return newModelParams;
}

List_Points_s *list(Model_inductor_data_s *model)
{
    List_Points_s *s = newListPoints(10);
    return s;
}

int validateModelInductorDataParams(Model_inductor_data_params_s *model_params)
{
    int result = 1;
    model_params->dGroove_width_number = 10;
    model_params->dHeight_number = 10;
    model_params->dProng_height_number = 10;
    model_params->dProng_width_number = 1000000000;
    model_params->dWidth_number = 10;
    return result;
}

Model_inductor_data_s* newModelInductorData_base(Model_inductor_data_params_s model_params)
{
    Model_inductor_data_s *newModelInductorData = initModelInductorData();
    if (!validateModelInductorDataParams(&model_params))
    {
        return newModelInductorData;
    }
    double x0 = 0, y0 = 0;
    
    List_Points_s *pointsProng = newListPoints();
    for (int i=0; i<model_params.dProng_width_number; i++)
    {
        addListPoints(pointsProng, newPointValue(.value = i, .point=newPoint(i, 0), .normal_vector = newPoint(1, 1) ));
    }
    
    newModelInductorData->params = &model_params;
    return newModelInductorData;
}

