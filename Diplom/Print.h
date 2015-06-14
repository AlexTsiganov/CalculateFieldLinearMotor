//
//  Print.h
//  Diplom
//
//  Created by Alex Tsiganov on 22.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#ifndef __Diplom__Print__
#define __Diplom__Print__

#include <stdio.h>
#include "Inductor_model_data.h"

void print_Model_Inductor(Inductor_model_data_s *inductor_model);
void print_Array_s_Matrix_Jitems(double *A_matrix, int size);

#endif
