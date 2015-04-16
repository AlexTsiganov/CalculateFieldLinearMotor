//
//  Inductor_model_data.c
//  Diplom
//
//  Created by Alex Tsiganov on 15.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "Inductor_model_data.h"
#include <stdlib.h>
#include <math.h>

static Inductor_model_data_s *initInductorModelData()
{
    Inductor_model_data_s *newModelParams = malloc(sizeof(Inductor_model_data_s));
    *newModelParams = (Inductor_model_data_s){.array_model_points = array_new()};
    return newModelParams;
}

void print_model_Inductor(Inductor_model_data_s *model)
{
    for (int i=0; i<model->array_model_points->length; i++)
    {
        Model_point_s *point = (Model_point_s*)model->array_model_points->items[i];
        printf("x= %.2f, y= %.2f\n", point->point->x, point->point->y);
    }
}

int validateModelInductorDataParams(Inductor_model_data_params_s *model_params)
{
    int result = 1;
    model_params->dWidth_count = 50;
    model_params->dHeight_count = 30;
    model_params->prong_dWidth_count = 10;
    model_params->groove_dHeight_count = 20;
    model_params->groove_dWidth_count = 10;
    
    model_params->groove_count = 20;
    

    model_params->prong_width = cDefault_data_inducor_prong_width;
    model_params->groove_width = cDefault_data_inducor_groove_width;
    model_params->groove_height = cDefault_data_inducor_groove_height;
    model_params->width = cDefault_data_inducor_groove_width*model_params->groove_count+cDefault_data_inducor_prong_width*(model_params->groove_count+1);
    model_params->height = cDefault_data_inductor_size_height;
    
    return result;
}


Inductor_model_data_s* newModelInductorData_base(Inductor_model_data_params_s model_params)
{
    Inductor_model_data_s *inductor_model = initInductorModelData();
    if (!validateModelInductorDataParams(&model_params))
        return inductor_model;
    double x0 = 0, y0 = 0;
    
    double dProng_Width = model_params.prong_width/model_params.prong_dWidth_count;
    double dGroove_Height = model_params.groove_height/model_params.groove_dHeight_count;
    double dGroove_Width = model_params.groove_width/model_params.groove_dWidth_count;
    double dInductor_Width = model_params.width/model_params.dWidth_count;
    double dInductor_Height = model_params.height/model_params.dHeight_count;
    
    for (int i=0; i<model_params.prong_dWidth_count; i++)
        array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=x0+(2*i+1)*dProng_Width/2, .y=y0)));
    
    Point_s *dPoint = newPoint();
    
    for (int j=0; j<model_params.groove_count; j++)
    {
        dPoint->x = x0+model_params.groove_width*(j)+model_params.prong_width*(j+1);
        dPoint->y = y0;
        
        for (int i=0; i<model_params.groove_dHeight_count; i++)
            array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y+(2*i+1)*dGroove_Height/2))); // |*
        
        dPoint->y += model_params.groove_height;
        
        for (int i=0; i<model_params.groove_dWidth_count; i++)
            array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x+(2*i+1)*dGroove_Width/2, .y=dPoint->y))); //  -
        
        dPoint->x += model_params.groove_width;
        
        for (int i=0; i<model_params.groove_dHeight_count; i++)
            array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y-(2*i+1)*dGroove_Height/2))); //  *|
        
        dPoint->y -= model_params.groove_height;
        
        for (int i=0; i<model_params.groove_dWidth_count; i++)
            array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x+(2*i+1)*dProng_Width/2, .y=dPoint->y))); //  *|
    }
    
    dPoint->x += model_params.prong_width;
    for (int i=0; i<model_params.dHeight_count; i++)
        array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y+(2*i+1)*dInductor_Height/2)));
    
    dPoint->y += model_params.height;
    for (int i=0; i<model_params.dWidth_count; i++)
        array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(dPoint->x-(2*i+1)*dInductor_Width/2, dPoint->y)));
    
    dPoint->x -= model_params.width;
    for (int i=0; i<model_params.dHeight_count; i++)
        array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y-(2*i+1)*dInductor_Height/2)));
    
    
    inductor_model->params = &model_params;
    print_model_Inductor(inductor_model);
    return inductor_model;
}