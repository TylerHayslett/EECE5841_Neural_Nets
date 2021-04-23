// Tyler Hayslett
// 2021-03-22
#ifndef common
#define common

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Read and write function for pgm images
int imageread(char s[], unsigned char ** image_char);
int imagewrite(char s[], unsigned char * image_char);

void char2float(unsigned char * image_char, float *image_float);
void float2char(unsigned char * image_char, float *image_float);
void normalize2(unsigned char * image_char, float *image_float);
void binarize_image(unsigned char * image_char, unsigned char * image_bin, unsigned char threshold);

// Read label for image from label file
char labelread(char s[], int index);


#endif
