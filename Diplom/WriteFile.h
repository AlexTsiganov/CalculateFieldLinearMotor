//
//  WriteFile.h
//  Diplom
//
//  Created by Alex Tsiganov on 22.04.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#ifndef __Diplom__WriteFile__
#define __Diplom__WriteFile__

#include <stdio.h>
#include "Inductor_model_data.h"
#include "Calculate_J.h"

void write_Inductor_model_to_data_files(Inductor_model_data_s *inductorModel);
void write_calculate_inductor_J_to_file(Calculate_J_result *j_result, Inductor_model_data_s *inductorModel, char *filePath);

#endif
