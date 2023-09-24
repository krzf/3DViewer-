#include "3dview.h"

int objParser(char *filePath, data_t *objData) {
  FILE *file = fopen(filePath, "r");
  fpos_t pos;
  char *currentObjString;
  size_t objStrlen = 128;
  int error = 1;

  if (NULL == file || objData == NULL) return 0;

  currentObjString = malloc(objStrlen);

  fgetpos(file, &pos);
  while (-1 != getline(&currentObjString, &objStrlen, file)) {
    if ('f' == currentObjString[0] && ' ' == currentObjString[1])
      objData->count_of_facets += 1;
    if ('v' == currentObjString[0] && ' ' == currentObjString[1])
      objData->count_of_vertexes += 1;
  }
  fsetpos(file, &pos);
  allocMatrix(objData);
  int v = 1, f = 1;
  while (-1 != getline(&currentObjString, &objStrlen, file)) {
    if ('v' == currentObjString[0] && ' ' == currentObjString[1]) {
      if (3 == sscanf(currentObjString, "v %lf%lf%lf",
                      &objData->matrix_3d.matrix[v][0],
                      &objData->matrix_3d.matrix[v][1],
                      &objData->matrix_3d.matrix[v][2])) {
        v++;
      } else
        error = 0;
    }
    if ('f' == currentObjString[0] && ' ' == currentObjString[1]) {
      processPolygon(objData, currentObjString, f);
      f++;
    }
  }
  if (currentObjString != NULL) free(currentObjString);
  if (file != NULL) fclose(file);
  return error;
}

data_t *allocObjData() {
  data_t *data = NULL;
  data = (data_t *)malloc(sizeof(data_t));
  data->count_of_facets = 0;
  data->count_of_vertexes = 0;
  data->matrix_3d.matrix = NULL;
  data->matrix_3d.columns = 0;
  data->matrix_3d.rows = 0;
  data->polygons = NULL;
  return data;
}

int allocMatrix(data_t *data) {
  int error = 1;
  if (data == NULL)
    error = 0;
  else {
    data->matrix_3d.rows = data->count_of_vertexes + 1;
    data->matrix_3d.columns = 3;
    data->matrix_3d.matrix =
        (double **)malloc(sizeof(double *) * data->matrix_3d.rows);

    for (int i = 0; i < data->matrix_3d.rows; ++i)
      data->matrix_3d.matrix[i] =
          (double *)malloc(sizeof(double) * data->matrix_3d.columns);

    for (int i = 0; i < data->matrix_3d.rows; ++i)
      for (int j = 0; j < 3; ++j) data->matrix_3d.matrix[i][j] = .0;

    data->polygons = malloc(sizeof(polygon_t) * (data->count_of_facets + 1));
    data->polygons[0].vertexes = malloc(1);
  }
  return error;
}

int processPolygon(data_t *data, char *currentObjStr, int index) {
  int error = 1;
  if (data == NULL)
    error = 0;
  else if (currentObjStr == NULL)
    error = 0;
  else {
    int count = 0;
    char *buffLine = NULL;
    buffLine = malloc(strlen(currentObjStr) + 1);
    char *token = NULL;
    strcpy(buffLine, currentObjStr);
    token = strtok(buffLine, " ");
    for (; (token = strtok(NULL, " ")) != NULL && (atoi(token) != 0); ++count)
      ;

    data->polygons[index].verxNums = count;
    data->polygons[index].vertexes = malloc(sizeof(int) * count);
    if (data->polygons[index].vertexes == NULL) error = 0;
    strcpy(buffLine, currentObjStr);
    token = strtok(buffLine, " ");
    token = strtok(NULL, " ");
    for (int i = 0; i < data->polygons[index].verxNums; ++i) {
      int digit = atoi(token);
      if (digit != 0) data->polygons[index].vertexes[i] = digit;
      token = strtok(NULL, " ");
    }
    free(buffLine);
  }
  return error;
}

void freeObjData(data_t **srcData) {
  data_t *data = *srcData;
  for (int i = 0; i <= data->count_of_facets; ++i) {
    free(data->polygons[i].vertexes);
    data->polygons[i].vertexes = NULL;
  }
  free(data->polygons);
  data->polygons = NULL;
  for (int i = 0; i < data->matrix_3d.rows; ++i) {
    free(data->matrix_3d.matrix[i]);
    data->matrix_3d.matrix[i] = NULL;
  }
  free(data->matrix_3d.matrix);
  data->matrix_3d.matrix = NULL;
  free(data);
  *srcData = NULL;
}
