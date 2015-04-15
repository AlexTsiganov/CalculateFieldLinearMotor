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
    *newModelParams = (Inductor_model_data_s){};
    return newModelParams;
}

void print_model_Inductor(Inductor_model_data_s *model)
{
    for (int i=0; i<model->points->length; i++)
    {
        Mode *point = (Point_value_s*)model->points->items[i];
        printf("x= %.2f, y= %.2f\n", point->point->x, point->point->y);
    }
}

int validateModelInductorDataParams(Inductor_model_data_params_s *model_params)
{
    int result = 1;
    model_params->dWidth_count = 10;
    model_params->dHeight_count = 10;
    model_params->prong_dWidth_count = 10;
    model_params->groove_dHeight_count = 10;
    model_params->groove_dWidth_count = 10;
    
    model_params->width = cDefault_data_inductor_size_widht;
    model_params->height = cDefault_data_inductor_size_height;
    model_params->prong_width = cDefault_data_inducor_prong_width;
    model_params->groove_width = cDefault_data_inducor_groove_width;
    model_params->groove_height = cDefault_data_inducor_groove_height;
    
    model_params->groove_count = 2;
    return result;
}

void on_item_clear1(Array_Item_t *array_item)
{
    Point_value_s *p = (Point_value_s*)array_item;
    free(p->normal_vector);
    free(p->tan_vector);
}

double calculate_line_size(Point_s *start_point, Point_s *end_point)
{
    double v_line = (end_point->x-start_point->x)*(end_point->x-start_point->x) + (end_point->y-start_point->y)*(end_point->y-start_point->y);
    return v_line >= 0 ? sqrt(v_line) : 0;
}

void add_points_line(Array_s *array, int count, Point_s *start_point, Point_s *end_point)
{
    double line_size = calculate_line_size(start_point, end_point);
    double dL = line_size/count;
    double cos_a = (end_point->x-start_point->x)/line_size;
    double sin_a = (end_point->y-start_point->y)/line_size;
    for (int i=0; i<count; i++)
    {
        array_add(array, newPointValue(.point=newPoint(dL*cos_a+start_point->x, dL*sin_a+start_point->y)));
    }
}

Inductor_model_data_s* newModelInductorData_base(Inductor_model_data_params_s model_params)
{
    Inductor_model_data_s *newModelInductorData = initInductorModelData();
    if (!validateModelInductorDataParams(&model_params))
        return newModelInductorData;
    double x0 = 0, y0 = 0;
    Array_s *array = array_new();
    double dProng_Width = model_params.prong_width/model_params.prong_dWidth_count;
    double dGroove_Height = model_params.groove_height/model_params.groove_dHeight_count;
    double dGroove_Width = model_params.groove_width/model_params.groove_dWidth_count;
    for (int i=0; i<model_params.prong_dWidth_count; i++)
        array_add(array, newPointValue(.point=newPoint(x0+(2*i+1)*dProng_Width/2, y0)));
    Point_s *dPoint;
    for (int j=0; j<model_params.groove_count; j++)
    {
        dPoint = newPoint(x0+model_params.groove_width*(j+1)+model_params.prong_width*j, y0);
        
        for (int i=0; i<model_params.groove_dHeight_count; i++)
            array_add(array, newPointValue(.point=newPoint(dPoint->x, dPoint->y+(2*i+1)*dGroove_Height/2))); // |*
        
        dPoint->y += model_params.groove_height;
        
        for (int i=0; i<model_params.groove_dWidth_count; i++)
            array_add(array, newPointValue(.point=newPoint(dPoint->x+(2*i+1)*dGroove_Width/2, dPoint->y))); //  -
        
        dPoint->x += model_params.groove_width;
        
        for (int i=0; i<model_params.groove_dHeight_count; i++)
            array_add(array, newPointValue(.point=newPoint(dPoint->x, dPoint->y-(2*i+1)*dGroove_Height/2))); //  *|
        
        dPoint->y -= model_params.groove_height;
        
        for (int i=0; i<model_params.groove_dHeight_count; i++)
            array_add(array, newPointValue(.point=newPoint(dPoint->x+(2*i+1)*dProng_Width/2, dPoint->y))); //  *|
        
        freePoint(dPoint);
    }
    
    newModelInductorData->params = &model_params;
    newModelInductorData->points = array;
    print_model_Inductor(newModelInductorData);
    return newModelInductorData;
}