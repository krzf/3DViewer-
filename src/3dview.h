#ifndef _3DVIEW_
#define _3DVIEW_
#define _POSIX_C_SOURCE 200809L
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PI 3.14159265358979323846
#define coordinates 3
#define EPS 0.001

typedef struct facets {
  int *vertexes;
  int verxNums;
} polygon_t;

typedef struct Matrix {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

typedef struct data {
  int count_of_vertexes;
  int count_of_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
} data_t;

// mang

int objParser(char *filePath, data_t *objData);
int allocMatrix(data_t *data);
data_t *allocObjData();
int processPolygon(data_t *data, char *line, int index);
void freeObjData(data_t **data);

//
void move_x(matrix_t *A, double a);
void move_y(matrix_t *A, double a);
void move_z(matrix_t *A, double a);
void rotation_by_ox(matrix_t *A, double angle);
void rotation_by_oy(matrix_t *A, double angle);
void rotation_by_oz(matrix_t *A, double angle);
void scale_model(matrix_t *A, double alp);

void found_min_max_or(matrix_t *A, int **ptr_x, int **ptr_y, int **ptr_z);
void first_centers(matrix_t *A);
void first_init_val_gl(matrix_t *A);
void first_init_val(matrix_t *A);

#endif  // _3DVIEW_