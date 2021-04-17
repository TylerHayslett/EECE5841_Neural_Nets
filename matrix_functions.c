#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image_functions.h"
#include "matrix_functions.h"


// Conversion functions
void image_to_matrix(BYTE * image_char, ) {
  
  matrix created = new_matrix(SIZEX,SIZEY);
  
  for (i = 0; i < SIZEX*SIZEY; i++) {
    created.data[i % SIZEX][i / SIZEX] = image_char[i];
  }
  
  return created;
}

void matrix_to_image(matrix matrix_a, char s[]) {
  FILE *iFile = fopen(s,"w");
  if(iFile==0) return; 
  
  // Write pgm header
  fprintf(iFile, "P5 %d %d %d ",SIZEX,SIZEY,255);
  
  int i = 0;
  float * image_float = malloc(SIZEX*SIZEY*sizeof(unsigned char));
  
  for (i = 0; i < SIZEX*SIZEY; i++) {
    image_float[i] = matrix_a.data[i % SIZEX][i / SIZEX];
  }
  
  // Write image data
  fwrite(image_char, sizeof(unsigned char), SIZEX*SIZEY, iFile);
  fclose(iFile);
}

// Matrix functions
matrix new_matrix(int dimx, int dimy);
void sum_matrix(matrix result, matrix matrix_a, matrix matrix_b);
void mult_matrix(matrix result, matrix matrix_a, matrix matrix_b);
void div_matrix(matrix result, matrix matrix_a, float denominator);
void sigmoid_matrix(matrix result, matrix matrix_a);
