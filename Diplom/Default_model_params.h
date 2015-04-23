//
//  Default_model_params.h
//  Diplom
//
//  Created by Alex Tsiganov on 13.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#ifndef Diplom_Default_model_params_h
#define Diplom_Default_model_params_h
#include <math.h>

static const double _m0=4*M_PI*1e-7;
static const double _m=1000*_m0;
static const double _lyambda = (_m-_m0)/(_m+_m0);

static const double cDefault_data_inductor_size_widht = 204.5;
static const double cDefault_data_inductor_size_height = 44.5;

static const double cDefault_data_inducor_prong_width = 4.5; // зубец
static const double cDefault_data_inducor_groove_width = 5.5; // паз
static const double cDefault_data_inducor_groove_height = 37.5; // паз

static const double cDefault_data_inducor_katushka_height = 16.5; // паз

#endif
