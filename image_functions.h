// Tyler Hayslett
// 2021-03-22
#ifndef image_functions
#define image_functions

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common_deffs.h"

extern int SIZEX; 
extern int SIZEY;

// Read from data file and write to pgm
int imageread(char s[], matrix * result, int index);
int imagewrite(char s[], matrix * image_matrix);

// Read label for image from label file
char labelread(char s[], int index);



#endif

