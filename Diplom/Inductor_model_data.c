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
    *newModelParams = (Inductor_model_data_s){.array_model_points = array_new(),
                                              .array_points_faza_A = array_new(),
                                              .array_points_faza_B = array_new(),
                                              .array_points_faza_C = array_new()};
    return newModelParams;
}

void print_model_Inductor(Inductor_model_data_s *model)
{
    for (int i=0; i<model->array_model_points->length; i++)
    {
        Model_point_s *point = (Model_point_s*)model->array_model_points->items[i];
        printf("Point: (%.3f; %.3f) -> %.3f", point->point->x, point->point->y, point->size);
        if (point->normal_vector)
            printf(", normal_vector: (%.3f; %.3f)", point->normal_vector->x, point->normal_vector->y);
        if (point->tan_vector)
            printf(", tan_vector: (%.3f; %.3f)", point->tan_vector->x, point->tan_vector->y);
        printf("\n");
    }
}

int validateModelInductorDataParams(Inductor_model_data_params_s *model_params)
{
    int result = 1;
    model_params->dWidth_count = 100;
    model_params->dHeight_count = 30;
    model_params->prong_dWidth_count = 6;
    model_params->groove_dHeight_count = 28;
    model_params->groove_dWidth_count = 5;
    
    model_params->groove_count = 20;

    model_params->prong_width = cDefault_data_inducor_prong_width;
    model_params->groove_width = cDefault_data_inducor_groove_width;
    model_params->groove_height = cDefault_data_inducor_groove_height;
    model_params->width = cDefault_data_inducor_groove_width*model_params->groove_count+cDefault_data_inducor_prong_width*(model_params->groove_count+1);
    model_params->height = cDefault_data_inductor_size_height;
    
    model_params->katushka_zazor = 0.5;
    model_params->katushka_height = cDefault_data_inducor_katushka_height;
    model_params->dKatushka_width_count = 4;
    model_params->dKatushka_height_count = 20;
    return result;
}

void points_katushka(Array_s *array, Point_s *startPoint, double width, double height, double dWidth_count, double dHeight_count, int normal)
{
    double dKatushka_width = width/dWidth_count;
    double dKatushka_height = height/dHeight_count;
    for (int i=0; i<dWidth_count; i++)
    {
        for (int j=0; j<dHeight_count; j++)
        {
            array_add(array, newModelPoint(.value=normal, .point=newPoint(.x=startPoint->x+(2*i+1)*dKatushka_width/2, .y=startPoint->y-(2*j+1)*dKatushka_height/2)));
        }
    }
}

#define verific_katushki  {\
    if (dPoint.x >= model_params.width-2*model_params.prong_width-2*model_params.groove_width + model_params.katushka_zazor \
         \
        && dPoint.y>model_params.groove_height-2*model_params.katushka_zazor-model_params.katushka_height)\
    {\
        dPoint.x -= model_params.width-model_params.prong_width;\
        dPoint.x += 2*model_params.prong_width+2*model_params.groove_width;\
    }\
    if (dPoint.x>model_params.width)\
        dPoint.x -= model_params.width-model_params.prong_width;\
    if (isPointEquals(startPoint, &dPoint))\
        break;\
}

void points_katushki_in_faza(Array_s *array_points_faza, Point_s *startPoint, Inductor_model_data_params_s model_params)
{
    Point_s dPoint = (Point_s){.x=startPoint->x, .y=startPoint->y};
    startPoint = newPoint(.x=startPoint->x, .y=startPoint->y);
    
    double katushka_width = (model_params.groove_width - 2*model_params.katushka_zazor);
    int sh=0;
    do
    {
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count, 0);
        
        dPoint.x += 2*model_params.prong_width+2*model_params.groove_width;
        dPoint.y = model_params.groove_height-model_params.katushka_zazor;
        
        verific_katushki
        
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count,1);
        
        dPoint.y = model_params.groove_height-2*model_params.katushka_zazor-model_params.katushka_height;
        
        verific_katushki
        
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count,1);
        
        dPoint.x += 2*model_params.prong_width+2*model_params.groove_width;
        
        verific_katushki
        
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count,0);
        
        dPoint.y = model_params.groove_height-model_params.katushka_zazor;
        
        verific_katushki
        
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count,0);
        
        dPoint.x += 2*model_params.prong_width+2*model_params.groove_width;
        dPoint.y = model_params.groove_height-2*model_params.katushka_zazor-model_params.katushka_height;
        
        verific_katushki
        
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count,1);
        
        dPoint.x+= 3*model_params.prong_width+3*model_params.groove_width;
        dPoint.y = model_params.groove_height-model_params.katushka_zazor;
        sh++;
        
        verific_katushki
        
    } while (1);
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
        array_add(inductor_model->array_model_points,
                  newModelPoint(.point=newPoint(.x=x0+(2*i+1)*dProng_Width/2, .y=y0),
                                .normal_vector=newPoint(.x=0, .y=-1),
                                .size=dProng_Width,
                                .tan_vector=newPoint(.x=1, .y=0)));
    
    Point_s *dPoint = newPoint();
    
    for (int j=0; j<model_params.groove_count; j++)
    {
        dPoint->x = x0+model_params.groove_width*(j)+model_params.prong_width*(j+1);
        dPoint->y = y0;
        
        for (int i=0; i<model_params.groove_dHeight_count; i++)
            array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y+(2*i+1)*dGroove_Height/2),
                                                                        .normal_vector=newPoint(.x=1, .y=0),
                                                                        .size=dGroove_Height,
                                                                        .tan_vector=newPoint(.x=0,.y=1))); // |*
        
        dPoint->y += model_params.groove_height;
        
        for (int i=0; i<model_params.groove_dWidth_count; i++)
            array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x+(2*i+1)*dGroove_Width/2, .y=dPoint->y),
                                                                        .normal_vector=newPoint(.x=0, .y=-1),
                                                                        .size=dGroove_Width,
                                                                        .tan_vector=newPoint(.x=1, .y=0))); //  -
        
        dPoint->x += model_params.groove_width;
        
        for (int i=0; i<model_params.groove_dHeight_count; i++)
            array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y-(2*i+1)*dGroove_Height/2),
                                                                        .normal_vector=newPoint(.x=-1, .y=0),
                                                                        .size=dGroove_Height,
                                                                        .tan_vector=newPoint(.x=0, .y=-1))); //  *|
        
        dPoint->y -= model_params.groove_height;
        
        for (int i=0; i<model_params.prong_dWidth_count; i++)
            array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x+(2*i+1)*dProng_Width/2, .y=dPoint->y),
                                                                        .normal_vector=newPoint(.x=0, .y=-1),
                                                                        .size=dProng_Width,
                                                                        .tan_vector=newPoint(.x=1, .y=0))); //  _
    }
    
    dPoint->x += model_params.prong_width;
    for (int i=0; i<model_params.dHeight_count; i++)
        array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y+(2*i+1)*dInductor_Height/2),
                                                                    .normal_vector=newPoint(.x=1, .y=0),
                                                                    .size=dInductor_Height,
                                                                    .tan_vector=newPoint(.x=0, .y=1)));
    
    dPoint->y += model_params.height;
    for (int i=0; i<model_params.dWidth_count; i++)
        array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(dPoint->x-(2*i+1)*dInductor_Width/2, dPoint->y),
                                                                    .normal_vector=newPoint(.x=0, .y=1),
                                                                    .size=dInductor_Width,
                                                                    .tan_vector=newPoint(.x=-1, .y=0)));
    
    dPoint->x -= model_params.width;
    for (int i=0; i<model_params.dHeight_count; i++)
        array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y-(2*i+1)*dInductor_Height/2),
                                                                    .normal_vector=newPoint(.x=-1, .y=0),
                                                                    .size=dInductor_Height,
                                                                    .tan_vector=newPoint(.x=0, .y=-1)));
    
    freePoint(dPoint);
    // Faza A
    dPoint = newPoint(.x=x0+model_params.prong_width+model_params.katushka_zazor,
                          .y=y0+model_params.groove_height-model_params.katushka_zazor);
    
    points_katushki_in_faza(inductor_model->array_points_faza_A, dPoint, model_params);
    
    // Faza C
    model_params.dKatushka_width_count+=2;
    dPoint->x += 3*model_params.prong_width+3*model_params.groove_width;
    points_katushki_in_faza(inductor_model->array_points_faza_C, dPoint, model_params);
    
    // Faza B
     model_params.dKatushka_width_count+=2;
    dPoint->x += 3*model_params.prong_width+3*model_params.groove_width;
    points_katushki_in_faza(inductor_model->array_points_faza_B, dPoint, model_params);
    
    inductor_model->params = &model_params;
    print_model_Inductor(inductor_model);
    return inductor_model;
}