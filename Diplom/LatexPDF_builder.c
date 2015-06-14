//
//  LatexPDF_builder.c
//  Diplom
//
//  Created by Alex Tsiganov on 13.06.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include "LatexPDF_builder.h"
#include <stdio.h>

#define LatexUsepackage "\\documentclass[10pt]{article}\
\\usepackage[usenames]{color}\
\\usepackage{pgfplots}\
\\usepackage{comment}\
\\usepackage{pgffor}\
\\usepackage[utf8]{inputenc}\
\\usepackage[russian]{babel}\
\\usepackage{pgfplotstable}\
\\usepgfplotslibrary{dateplot}\
\\usepackage[letterpaper, total={130mm,297mm}, landscape,left=2mm, right=2mm, top=2mm, bottom=2mm]{geometry}"

void create_PDFTex_file_with_J_result(Calculate_J_result *j_result, char *filePath)
{
    FILE *file = fopen(filePath, "w");
    if (!file)
        return;
    fprintf(file, LatexUsepackage);
    
}