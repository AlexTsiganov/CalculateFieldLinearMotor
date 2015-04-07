//
//  Model_data.h
//  Diplom
//
//  Created by Alex Tsiganov on 07.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Data_s.h"

static const double cDefault_data_inductor_size_widht = 204.5;
static const double cDefault_data_inductor_size_height = 44.5;

static const double cDefault_data_inducor_prong_width = 4.5; // зубец
static const double cDefault_data_inducor_prong_height = 4.5; // зубец
static const double cDefault_data_inducor_groove_width = 5.5; // паз

typedef struct
{
    double width, height, prong_width, groove_width, groove_height;
    int groove_count, prong_count;
    int dWidth_number, dHeight_number, dProng_width_number, dProng_height_number, dGroove_width_number;
}Model_inductor_data_params_s;

typedef struct Model_inductor_data_s
{
    Model_inductor_data_params_s *params;
    List_Points_s *points;
    List_Points_s* (*getAllPoints)(struct Model_inductor_data_s *inductor);
}Model_inductor_data_s;


#define newModelInductor(...) newModelInductorData_base((Model_inductor_data_params_s)\
{\
    .width = -1, \
    .height = -1, \
    .prong_width = -1, \
    .groove_width = -1, \
    .groove_height = -1, \
    __VA_ARGS__})

Model_inductor_data_s* newModelInductorData_base(Model_inductor_data_params_s model_params);

