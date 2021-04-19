// Tyler Hayslett
// 2021-03-22
#ifndef common_deffs
#define common_deffs

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned char BYTE;

typedef struct matrix {
  int row_cnt;
  int col_cnt;
  float * data;
} matrix;

typedef struct matrix_set {
  int number_of_matrices;
  matrix ** set;
} matrix_set;

#endif
