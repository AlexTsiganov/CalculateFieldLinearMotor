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
#include <complex.h>

Inductor_model_data_s *initInductorModelData(Inductor_model_data_params_s model_params)
{
    Inductor_model_data_s *newModelParams = malloc(sizeof(Inductor_model_data_s));
    int inductor_size = model_params.dWidth_count + 2*model_params.dHeight_count+
                        model_params.groove_count * ( 2*model_params.groove_dHeight_count +
                                                      model_params.groove_dWidth_count +
                                                      model_params.prong_dWidth_count)+
                        model_params.prong_dWidth_count,
        katushka_size = model_params.dKatushka_height_count*model_params.dKatushka_width_count*12;
    
    *newModelParams = (Inductor_model_data_s){ .inductor = malloc(sizeof(Model_inductor_point_s)*inductor_size),
                                               .params = &model_params,
                                               .inductor_size = inductor_size,
                                               .katushka[Faza_A] = malloc(sizeof(Model_katuska_point_s)*katushka_size),
                                               .katushka[Faza_B] = malloc(sizeof(Model_katuska_point_s)*katushka_size),
                                               .katushka[Faza_C] = malloc(sizeof(Model_katuska_point_s)*katushka_size),
                                               .katushka_size = katushka_size};
    return newModelParams;
}

int validateModelInductorDataParams(Inductor_model_data_params_s *model_params)
{
    int result = 1;
    
    model_params->dWidth_count = 140;
    model_params->dHeight_count = 50;
    model_params->prong_dWidth_count = 8;
    model_params->groove_dHeight_count = 40;
    model_params->groove_dWidth_count = 8;

    model_params->groove_count = 20;

    model_params->prong_width = cDefault_data_inducor_prong_width;
    model_params->groove_width = cDefault_data_inducor_groove_width;
    model_params->groove_height = cDefault_data_inducor_groove_height;
    model_params->width = cDefault_data_inducor_groove_width*model_params->groove_count+cDefault_data_inducor_prong_width*(model_params->groove_count+1);
    model_params->height = cDefault_data_inductor_size_height;
    
    model_params->katushka_zazor = 0.5;
    model_params->katushka_height = cDefault_data_inducor_katushka_height;
    model_params->dKatushka_width_count = 5;
    model_params->dKatushka_height_count = 14;
    return result;
}

void points_katushka(Model_katuska_point_s *points, Point_s *startPoint, double width, double height, int dWidth_count, int dHeight_count, double value, int *sh)
{
    double dKatushka_width = width/dWidth_count;
    double dKatushka_height = height/dHeight_count;
    for (int i=0; i<dWidth_count; i++)
    {
        for (int j=0; j<dHeight_count; j++, (*sh)++)
        {
            if (*sh == 499)
            {
                printf("");
            }
            points[*sh] = (Model_katuska_point_s){ .I_vitka=(value==0)?1:-1,
                                                                .drift = (value==0)?o:x,
                                                                .dWidth=dKatushka_width,
                                                                .dHeight=dKatushka_height,
                                                                .point=newPoint(.x=startPoint->x+(2*i+1)*dKatushka_width/2,
                                                                                .y=startPoint->y-(2*j+1)*dKatushka_height/2)};
            /*array_add(array, newModelPoint(.value=(value==0)?1000:-1000,
                                           .znak = (value==0)?o:x,
                                           .width=dKatushka_width,
                                           .height=dKatushka_height,
                                           .point=newPoint(.x=startPoint->x+(2*i+1)*dKatushka_width/2,
                                                           .y=startPoint->y-(2*j+1)*dKatushka_height/2)));*/
        }
    }
}



void points_katushki_in_faza(Model_katuska_point_s *array_points_faza, Inductor_model_data_s *inductor_model, Point_s *startPoint, Inductor_model_data_params_s model_params)
{
    #define verific_katushki  {\
        if (dPoint.x >= model_params.width-2*model_params.prong_width-2*model_params.groove_width + model_params.katushka_zazor \
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
    
    Point_s dPoint = (Point_s){.x=startPoint->x, .y=startPoint->y};
    startPoint = newPoint(.x=startPoint->x, .y=startPoint->y);
    
    double katushka_width = (model_params.groove_width - 2*model_params.katushka_zazor);
    int sh=0;
    do
    {
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count, 0, &sh);
        
        dPoint.x += 2*model_params.prong_width+2*model_params.groove_width;
        dPoint.y = model_params.groove_height-model_params.katushka_zazor;
        
        verific_katushki
        
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count,1, &sh);
        
        dPoint.y = model_params.groove_height-2*model_params.katushka_zazor-model_params.katushka_height;
        
        verific_katushki
        
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count,1, &sh);
        
        dPoint.x += 2*model_params.prong_width+2*model_params.groove_width;
        
        verific_katushki
        
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count,0, &sh);
        
        dPoint.y = model_params.groove_height-model_params.katushka_zazor;
        
        verific_katushki
        
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count,0, &sh);
        
        dPoint.x += 2*model_params.prong_width+2*model_params.groove_width;
        dPoint.y = model_params.groove_height-2*model_params.katushka_zazor-model_params.katushka_height;
        
        verific_katushki
        
        points_katushka(array_points_faza, &dPoint, katushka_width, model_params.katushka_height, model_params.dKatushka_width_count, model_params.dKatushka_height_count,1, &sh);
        
        dPoint.x+= 3*model_params.prong_width+3*model_params.groove_width;
        dPoint.y = model_params.groove_height-model_params.katushka_zazor;
       // sh++;
        
        verific_katushki
        
    } while (1);
#undef verific_katushki
    inductor_model->katushka_size = sh;
}

Inductor_model_data_s* newModelInductorData(Inductor_model_data_params_s *model_params)
{
    validateModelInductorDataParams(model_params);
    Inductor_model_data_s *inductor_model = initInductorModelData(*model_params);
    if (!validateModelInductorDataParams(model_params))
        return inductor_model;
    double x0 = 0, y0 = 0;
    
    double dProng_Width = model_params->prong_width/model_params->prong_dWidth_count;
    double dGroove_Height = model_params->groove_height/model_params->groove_dHeight_count;
    double dGroove_Width = model_params->groove_width/model_params->groove_dWidth_count;
    double dInductor_Width = model_params->width/model_params->dWidth_count;
    double dInductor_Height = model_params->height/model_params->dHeight_count;
    
    int _test_sh = 0;
    
    for (int i=0; i<model_params->prong_dWidth_count; i++, _test_sh++)
    {
        inductor_model->inductor[i] = (Model_inductor_point_s){ .point = newPoint(.x=x0+(2*i+1)*dProng_Width/2, .y=y0),
                                                                .normal_vector = newPoint(.x=0, .y=-1),
                                                                .dSize = dProng_Width,
                                                                .tan_vector = newPoint(.x=1, .y=0) };
        /*array_add(inductor_model->array_model_points,
                  newModelPoint(.point=newPoint(.x=x0+(2*i+1)*dProng_Width/2, .y=y0),
                                .normal_vector=newPoint(.x=0, .y=-1),
                                .size=dProng_Width,
                                .tan_vector=newPoint(.x=1, .y=0),
                                .width=0));*/
    }
    Point_s *dPoint = newPoint();

    for (int j=0; j<model_params->groove_count; j++)
    {
        dPoint->x = x0+model_params->groove_width*(j)+model_params->prong_width*(j+1);
        dPoint->y = y0;
        
        for (int i=0; i<model_params->groove_dHeight_count; i++, _test_sh++)
            inductor_model->inductor[_test_sh] = (Model_inductor_point_s){
                .point = newPoint(.x=dPoint->x, .y=dPoint->y+(2*i+1)*dGroove_Height/2),
                .normal_vector = newPoint(.x=1, .y=0),
                .dSize = dGroove_Height,
                .tan_vector = newPoint(.x=0, .y=1) };
            /*array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y+(2*i+1)*dGroove_Height/2),
                                                                        .normal_vector=newPoint(.x=1, .y=0),
                                                                        .size=dGroove_Height,
                                                                        .tan_vector=newPoint(.x=0,.y=1))); // |* */
        
        dPoint->y += model_params->groove_height;

        for (int i=0; i<model_params->groove_dWidth_count; i++, _test_sh++)
            inductor_model->inductor[_test_sh] = (Model_inductor_point_s){
                .point = newPoint(.x=dPoint->x+(2*i+1)*dGroove_Width/2, .y=dPoint->y),
                .normal_vector = newPoint(.x=0, .y=-1),
                .dSize = dGroove_Width,
                .tan_vector = newPoint(.x=1, .y=0) };

        
        dPoint->x += model_params->groove_width;
        

        for (int i=0; i<model_params->groove_dHeight_count; i++, _test_sh++)
            inductor_model->inductor[_test_sh] = (Model_inductor_point_s){
                .point = newPoint(.x=dPoint->x, .y=dPoint->y-(2*i+1)*dGroove_Height/2),
                .normal_vector = newPoint(.x=-1, .y=0),
                .dSize = dGroove_Height,
                .tan_vector = newPoint(.x=0, .y=-1) };

        
        dPoint->y -= model_params->groove_height;
        
        for (int i=0; i<model_params->prong_dWidth_count; i++, _test_sh++)
        {
            inductor_model->inductor[_test_sh] = (Model_inductor_point_s){
                .point = newPoint(.x=dPoint->x+(2*i+1)*dProng_Width/2, .y=dPoint->y),
                .normal_vector = newPoint(.x=0, .y=-1),
                .dSize = dProng_Width,
                .tan_vector = newPoint(.x=1, .y=0) };
        }
            /*array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x+(2*i+1)*dProng_Width/2, .y=dPoint->y),
                                                                        .normal_vector=newPoint(.x=0, .y=-1),
                                                                        .size=dProng_Width,
                                                                        .tan_vector=newPoint(.x=1, .y=0)));*/ //  _
    }
    
    dPoint->x += model_params->prong_width;

    
    for (int i=0; i<model_params->dHeight_count; i++, _test_sh++)
        inductor_model->inductor[_test_sh] = (Model_inductor_point_s){
            .point = newPoint(.x=dPoint->x, .y=dPoint->y+(2*i+1)*dInductor_Height/2),
            .normal_vector = newPoint(.x=1, .y=0),
            .dSize = dInductor_Height,
            .tan_vector = newPoint(.x=0, .y=1) };
        /*array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y+(2*i+1)*dInductor_Height/2),
                                                                    .normal_vector=newPoint(.x=1, .y=0),
                                                                    .size=dInductor_Height,
                                                                    .tan_vector=newPoint(.x=0, .y=1)));*/
    
    dPoint->y += model_params->height;

    for (int i=0; i<model_params->dWidth_count; i++, _test_sh++)
        inductor_model->inductor[_test_sh] = (Model_inductor_point_s){
            .point = newPoint(dPoint->x-(2*i+1)*dInductor_Width/2, dPoint->y),
            .normal_vector = newPoint(.x=0, .y=1),
            .dSize = dInductor_Width,
            .tan_vector = newPoint(.x=-1, .y=0) };
        /*array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(dPoint->x-(2*i+1)*dInductor_Width/2, dPoint->y),
                                                                    .normal_vector=newPoint(.x=0, .y=1),
                                                                    .size=dInductor_Width,
                                                                    .tan_vector=newPoint(.x=-1, .y=0)));*/
    
    dPoint->x -= model_params->width;

    for (int i=0; i<model_params->dHeight_count; i++, _test_sh++)
        inductor_model->inductor[_test_sh] = (Model_inductor_point_s){
            .point = newPoint(.x=dPoint->x, .y=dPoint->y-(2*i+1)*dInductor_Height/2),
            .normal_vector = newPoint(.x=-1, .y=0),
            .dSize = dInductor_Height,
            .tan_vector = newPoint(.x=0, .y=-1) };
        /*array_add(inductor_model->array_model_points, newModelPoint(.point=newPoint(.x=dPoint->x, .y=dPoint->y-(2*i+1)*dInductor_Height/2),
                                                                    .normal_vector=newPoint(.x=-1, .y=0),
                                                                    .size=dInductor_Height,
                                                                    .tan_vector=newPoint(.x=0, .y=-1)));*/
    
    freePoint(dPoint);
    // Faza A
    dPoint = newPoint(.x=x0+model_params->prong_width+model_params->katushka_zazor,
                      .y=y0+model_params->groove_height-model_params->katushka_zazor);
    
    points_katushki_in_faza(inductor_model->katushka[Faza_A], inductor_model, dPoint, *model_params);
    
    // Faza C
    dPoint->x += 3*model_params->prong_width+3*model_params->groove_width;
    points_katushki_in_faza(inductor_model->katushka[Faza_C], inductor_model, dPoint, *model_params);
    
    // Faza B
    dPoint->x += 3*model_params->prong_width+3*model_params->groove_width;
    points_katushki_in_faza(inductor_model->katushka[Faza_B], inductor_model, dPoint, *model_params);
    
    freePoint(dPoint);
    
    inductor_model->params = model_params;
    return inductor_model;
}


Model_line_data_s* newModelLineData(Point_s startPoint, Point_s endPoint, double count)
{
    Model_line_data_s *lineModel = malloc(sizeof(Model_line_data_s));
    Point_s *points = malloc(sizeof(Point_s)*count);
    double dL = (endPoint.x - startPoint.x)/count;
    for (int i=0; i<count; i++)
    {
        points[i] = (Point_s){.x=startPoint.x+dL/2, .y=startPoint.y};
        startPoint.x+=dL;
    }
    lineModel->points = points;
    lineModel->count = count;
    return lineModel;
}