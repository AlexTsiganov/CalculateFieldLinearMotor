//
//  Inductor_model_data.h
//  Diplom
//
//  Created by Alex Tsiganov on 15.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#ifndef __Diplom__Inductor_model_data__
#define __Diplom__Inductor_model_data__

#include "Model_point.h"
#include "Default_model_params.h"

typedef struct
{
    double width, height, prong_width, groove_width, groove_height;
    int groove_count;
    int dWidth_count, dHeight_count, prong_dWidth_count, groove_dHeight_count, groove_dWidth_count;
    
    double katushka_zazor, katushka_height;
    int dKatushka_width_count, dKatushka_height_count;
    
}Inductor_model_data_params_s;

#define Katushka_faza_count 3
typedef enum
{
    Faza_A, Faza_B, Faza_C
}Faza;

typedef struct Model_inductor_data_s
{
    Inductor_model_data_params_s *params;
    Model_inductor_point_s *inductor;
    int inductor_size;
    Model_katuska_point_s *katushka[Katushka_faza_count];
    int katushka_size;
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

#endif
