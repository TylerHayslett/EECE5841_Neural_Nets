#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "common.h"

int imageread(char s[], unsigned char ** image_char) {
  unsigned levels; //image width/height
  
  FILE *iFile = fopen(s,"r");
  if(iFile==0) return 1;
  
  printf("Image Found\n");
  
  if(3!=fscanf(iFile, "P5 %d %d %d ", &SIZEX, &SIZEY, &levels)) return 1;
  
  // Allocate and read file into memory
  *image_char=(unsigned char *) malloc(SIZEX*SIZEY);
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

// Converts from char to float
void char2float(unsigned char * image_char, float *image_float){
  int i;
  for (i = 0; i < SIZEX*SIZEY; i++) {
    image_float[i] = (float) image_char[i];
  }
}

// Converts from float to char
void float2char(unsigned char * image_char, float *image_float){
  int i;
  for (i = 0; i < SIZEX*SIZEY; i++) {
    image_char[i] = (unsigned char) image_float[i];
  }
}

// Converts from complex to mag and Normalizes for spectrum visualization
void normalize(unsigned char * image_char, float *image_float){
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

void binarize_image(unsigned char * image_char, unsigned char * image_bin, unsigned char threshold) {
  int i;
  
  for (i = 0; i < SIZEX*SIZEY; i++) {
    if (image_char[i] >= threshold) {
      image_bin[i] = 255;
    } else {
      image_bin[i] = 0;
    }
  }
}

int imageread(char s[], matrix * result, int index) {
  
  int i;
  BYTE * image_char = malloc(SIZEX*SIZEY*sizeof(BYTE));
  float * image_data = malloc(SIZEX*SIZEY*sizeof(float));
  
  FILE *iFile = fopen(s,"r");
  if(iFile==0) return 1;
  fseek(iFile, (4*4) + (28 * 28 * index), SEEK_SET);
  fread(image_char,sizeof(BYTE),SIZEX*SIZEY,iFile);
  fclose(iFile);
  
  for (i = 0; i < SIZEX*SIZEY; i++) {
    image_data[i] = (float) image_char[i];
  }
  
  result->col_cnt = SIZEX;
  result->row_cnt = SIZEY;
  result->data = image_data;
  
  free(image_char);
  
  return 0;
}

// Writes out image data provided
int imagewrite(char s[], matrix * image_matrix) {
  FILE *iFile = fopen(s,"w");
  if(iFile==0) return 1; 
  
  int num_elements = image_matrix->col_cnt * image_matrix->row_cnt;
  
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
  fprintf(iFile, "P5 %d %d %d ",image_matrix->col_cnt,image_matrix->row_cnt,255);
  
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
  
  return label;
}
