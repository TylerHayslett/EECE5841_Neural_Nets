#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image_functions.h"

int SIZEX = 28; 
int SIZEY = 28;

int imageread(char s[], matrix * result, int index) {
  
  int i;
  BYTE * image_char = malloc(SIZEX*SIZEY*sizeof(BYTE));
  float * image_data = malloc(SIZEX*SIZEY*sizeof(float));
  
  FILE *iFile = fopen(s,"r");
  if(iFile==0) return 1;
  fseek(iFile, (4*4) + (28 * 28 * index), SEEK_SET);
  fread(image_char,sizeof(BYTE),SIZEX*SIZEY,iFile);
  fclose(iFile);
  
  printf("opened file\n");
  
  for (i = 0; i < SIZEX*SIZEY; i++) {
    image_data[i] = (float) image_char[i];
  }
  
  result->dimrow = SIZEX;
  result->dimcol = SIZEY;
  result->data = image_data;
  
  printf("assigned data\n");
  
  free(image_char);
  
  return 0;
}

// Writes out image data provided
int imagewrite(char s[], matrix * image_matrix) {
  FILE *iFile = fopen(s,"w");
  if(iFile==0) return 1; 
  
  int num_elements = image_matrix->dimrow * image_matrix->dimcol;
  
  // Normalize matrix
  int i;
  float min = 100000000.0;
  float max = -100000000.0;
  
  float *mag = malloc(sizeof(float)*num_elements);
  BYTE *image_char = malloc(sizeof(BYTE)*num_elements);
  
  for (i = 0; i < num_elements; i++) {
    mag[i] = image_matrix->data[i];
    
    if (mag[i] > max) {
      max = mag[i];
    }
    if (mag[i] < min) {
      min = mag[i];
    }
  }
  for (i = 0; i < num_elements; i++) {
    image_char[i] = (BYTE) ((mag[i]-min) * 255/max);
  }
  
  // Write pgm header
  fprintf(iFile, "P5 %d %d %d ",image_matrix->dimrow,image_matrix->dimcol,255);
  
  // Write image data
  fwrite(image_char, sizeof(unsigned char), num_elements, iFile);
  fclose(iFile);
  free(mag);
  free(image_char);
  return 0;
}

char labelread(char s[], int index) {
  
  FILE *iFile = fopen(s,"r");
  if(iFile==0) return 0;
  
  // Allocate and read file into memory
  fseek(iFile, (4*2) + (index), SEEK_SET);
  char label = (char) fgetc(iFile);
  fclose(iFile);
  
  printf("label read\n");
  
  return label;
}


