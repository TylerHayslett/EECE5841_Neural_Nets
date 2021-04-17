#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "image_functions.h"

int SIZEX = 28; 
int SIZEY = 28;

int imageread(char s[], unsigned char ** image_char, int index) {

  FILE *iFile = fopen(s,"r");
  if(iFile==0) return 1;
  
  // Allocate and read file into memory
  *image_char=(unsigned char *) malloc(SIZEX*SIZEY);
  fseek(iFile, (4*4) + (28 * 28 * index), SEEK_SET);
  fread(*image_char,sizeof(unsigned char),SIZEX*SIZEY,iFile);
  fclose(iFile);
  
  return 0;
}

// Writes out image data provided
int imagewrite(char s[], unsigned char * image_char) {
  FILE *iFile = fopen(s,"w");
  if(iFile==0) return 1; 
  
  // Write pgm header
  fprintf(iFile, "P5 %d %d %d ",SIZEX,SIZEY,255);
  
  // Write image data
  fwrite(image_char, sizeof(unsigned char), SIZEX*SIZEY, iFile);
  fclose(iFile);
  
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


// Converts from complex to mag and Normalizes for spectrum visualization
void normalize2(unsigned char * image_char, float *image_float){
  int i;
  float min = 100000000.0;
  float max = -100000000.0;
  
  int *mag = malloc(sizeof(float)*SIZEX*SIZEY);
  
  for (i = 0; i < SIZEX*SIZEY; i++) {
    mag[i] = image_float[i];
    
    if (mag[i] > max) {
      max = mag[i];
    }
    if (mag[i] < min) {
      min = mag[i];
    }
  }
  for (i = 0; i < SIZEX*SIZEY; i++) {
    image_char[i] = (unsigned char) ((mag[i]-min) * 255/max);
  }
  
  free(mag);
}




