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

#define Katushka_faza_count 3
typedef enum
{
    Faza_A, Faza_B, Faza_C
}Faza;

typedef struct
{
    double width, height, prong_width, groove_width, groove_height;
    int groove_count;
    int dWidth_count, dHeight_count, prong_dWidth_count, groove_dHeight_count, groove_dWidth_count;
    
    double katushka_zazor, katushka_height;
    int dKatushka_width_count, dKatushka_height_count;
    
    double I_katushki;
}Inductor_model_data_params_s;


typedef struct Model_inductor_data_s
{
    Inductor_model_data_params_s *params;
    Model_inductor_point_s *inductor;
    int inductor_size;
    Model_katuska_point_s *katushka[Katushka_faza_count];
    int katushka_size;
}Inductor_model_data_s;

typedef struct Model_line_data_s
{
    Point_s *points;
    int count;
}Model_line_data_s;

Inductor_model_data_s* newModelInductorData(Inductor_model_data_params_s *model_params);

Model_line_data_s* newModelLineData(Point_s startPoint, Point_s endPoint, double count);

#endif
