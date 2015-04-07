//
//  main.c
//  Diplom
//
//  Created by Alex Tsiganov on 17.03.15.
//  Copyright (c) 2015 Alex Tsiganov. All rights reserved.
//

#include <stdio.h>

static const double cDefSizeWidht = 204.5;
static const double cDefSizeHeight = 44.5;

static const double cDefSizeProng = 4.5; // зубец
static const double cDefSizeGroove = 5.5; // паз



void writeResultsToFile()
{
    FILE *f = fopen("/Users/alextsiganov/Documents/testtet.rtf", "w");
    if (f == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    if (fprintf(f, "Some text: \n"))
    {
        printf("success\n");
    }
     fclose(f);
    return;
    
    
    /* print some text */
    const char *text = "Write this to the file";
    fprintf(f, "Some text: %s\n", text);
    
    /* print integers and floats */
    int i = 4;
    float py = 3.1415927;
    fprintf(f, "Integer: %d, float: %f\n", i, py);
    
    /* printing single chatacters */
    char c = 'A';
    fprintf(f, "A character: %c\n", c);
    
    fclose(f);
}

int main(int argc, const char * argv[])
{
    writeResultsToFile();
    return 0;
}
