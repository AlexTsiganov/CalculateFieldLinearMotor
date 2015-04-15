//
//  Model_data.h
//  Diplom
//
//  Created by Alex Tsiganov on 07.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Data_s.h"
#include "Array_s.h"
#include "Default_model_params.h"

typedef struct
{
    double width, height, prong_width, groove_width, groove_height;
    int groove_count;
    int dWidth_count, dHeight_count, prong_dWidth_count, groove_dHeight_count, groove_dWidth_count;
}Inductor_model_data_params_s;

typedef struct Model_inductor_data_s
{
    Inductor_model_data_params_s *params;
    Array_s *points;
}Inductor_model_data_s;


#define newModelInductor(...) newModelInductorData_base((Inductor_model_data_params_s)\
{\
    /*.width = -1, \
    .height = -1, \
    .prong_width = -1, \
    .groove_width = -1, \
    .groove_height = -1,*/ \
    __VA_ARGS__\
})

Inductor_model_data_s* newModelInductorData_base(Inductor_model_data_params_s model_params);

