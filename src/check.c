#include <check.h>
#include <stdio.h>
#include <wchar.h>

#include "3dview.h"

#define SUCCESS 1
#define FAILURE 0

#define GREEN "\x1B[32m"
#define RED "\x1B[31m"
#define WHITE "\x1B[0m"

// create
START_TEST(found_min_max_or_1) {
  matrix_t matrix;
  int *ptr_x;
  int *ptr_y;
  int *ptr_z;
  matrix.rows = 4;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(sizeof(double *) * matrix.rows);

  for (int i = 0; i < matrix.rows; ++i)
    matrix.matrix[i] = (double *)malloc(sizeof(double) * matrix.columns);

  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix.matrix[i][j] = .0;

  for (int i = 1; i < matrix.rows; ++i) {
    matrix.matrix[i][0] = i;
    matrix.matrix[i][1] = i;
    matrix.matrix[i][2] = i;
  }

  found_min_max_or(&matrix, &ptr_x, &ptr_y, &ptr_z);
  ck_assert_int_eq(ptr_x[0], 1);
  ck_assert_int_eq(ptr_x[1], 3);
  ck_assert_int_eq(ptr_y[0], 1);
  ck_assert_int_eq(ptr_y[1], 3);
  ck_assert_int_eq(ptr_z[0], 1);
  ck_assert_int_eq(ptr_z[1], 3);

  for (int i = 0; i < matrix.rows; ++i) free(matrix.matrix[i]);
  free(matrix.matrix);
  free(ptr_x);
  free(ptr_y);
  free(ptr_z);
}
END_TEST

START_TEST(first_init_val_gl_1) {
  matrix_t matrix;
  matrix.rows = 4;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(sizeof(double *) * matrix.rows);

  for (int i = 0; i < matrix.rows; ++i)
    matrix.matrix[i] = (double *)malloc(sizeof(double) * matrix.columns);

  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix.matrix[i][j] = .0;

  for (int i = 1; i < matrix.rows; ++i) {
    matrix.matrix[i][0] = i;
    matrix.matrix[i][1] = i;
    matrix.matrix[i][2] = i;
  }

  first_init_val_gl(&matrix);

  for (int i = 1; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j)
      ck_assert_double_eq(matrix.matrix[i][j], i * 0.5);

  for (int i = 0; i < matrix.rows; ++i) free(matrix.matrix[i]);
  free(matrix.matrix);
}
END_TEST

START_TEST(move_x_1) {
  double arg;
  arg = 1.0;
  matrix_t matrix;
  matrix.rows = 2;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(sizeof(double *) * matrix.rows);

  for (int i = 0; i < matrix.rows; ++i)
    matrix.matrix[i] = (double *)malloc(sizeof(double) * matrix.columns);

  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix.matrix[i][j] = .0;

  for (int i = 1; i < matrix.rows; ++i) {
    matrix.matrix[i][0] = i;
    matrix.matrix[i][1] = i;
    matrix.matrix[i][2] = i;
  }
  move_x(&matrix, arg);

  for (int i = 1; i < matrix.rows; ++i)
    ck_assert_double_eq(matrix.matrix[i][0], i + arg);

  for (int i = 0; i < matrix.rows; ++i) free(matrix.matrix[i]);
  free(matrix.matrix);
}
END_TEST

START_TEST(move_y_1) {
  double arg;
  arg = 1.0;
  matrix_t matrix;
  matrix.rows = 2;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(sizeof(double *) * matrix.rows);

  for (int i = 0; i < matrix.rows; ++i)
    matrix.matrix[i] = (double *)malloc(sizeof(double) * matrix.columns);

  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix.matrix[i][j] = .0;

  for (int i = 1; i < matrix.rows; ++i) {
    matrix.matrix[i][0] = i;
    matrix.matrix[i][1] = i;
    matrix.matrix[i][2] = i;
  }
  move_y(&matrix, arg);

  for (int i = 1; i < matrix.rows; ++i)
    ck_assert_double_eq(matrix.matrix[i][1], i + arg);
  for (int i = 0; i < matrix.rows; ++i) free(matrix.matrix[i]);
  free(matrix.matrix);
}
END_TEST

START_TEST(move_z_1) {
  double arg;
  arg = 1.0;
  matrix_t matrix;
  matrix.rows = 2;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(sizeof(double *) * matrix.rows);

  for (int i = 0; i < matrix.rows; ++i)
    matrix.matrix[i] = (double *)malloc(sizeof(double) * matrix.columns);

  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix.matrix[i][j] = .0;

  for (int i = 1; i < matrix.rows; ++i) {
    matrix.matrix[i][0] = i;
    matrix.matrix[i][1] = i;
    matrix.matrix[i][2] = i;
  }
  move_z(&matrix, arg);

  for (int i = 1; i < matrix.rows; ++i)
    ck_assert_double_eq(matrix.matrix[i][2], i + arg);

  for (int i = 0; i < matrix.rows; ++i) free(matrix.matrix[i]);
  free(matrix.matrix);
}
END_TEST

START_TEST(rotation_by_ox_1) {
  double arg;
  arg = PI / 2;
  matrix_t matrix;
  matrix.rows = 2;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(sizeof(double *) * matrix.rows);

  for (int i = 0; i < matrix.rows; ++i)
    matrix.matrix[i] = (double *)malloc(sizeof(double) * matrix.columns);

  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix.matrix[i][j] = .0;

  for (int i = 0; i < matrix.rows; ++i) {
    matrix.matrix[i][0] = 1;
    matrix.matrix[i][1] = 1;
    matrix.matrix[i][2] = 1;
  }

  rotation_by_ox(&matrix, arg);

  for (int i = 0; i < matrix.rows; ++i) {
    ck_assert_double_eq(matrix.matrix[i][0], 1);
    ck_assert_double_eq(matrix.matrix[i][1], cos(arg) + sin(arg));
    ck_assert_double_eq(matrix.matrix[i][2], -sin(arg) + cos(arg));
  }

  for (int i = 0; i < matrix.rows; ++i) free(matrix.matrix[i]);
  free(matrix.matrix);
}
END_TEST

START_TEST(rotation_by_oy_1) {
  double arg;
  arg = PI / 2;
  matrix_t matrix;
  matrix.rows = 2;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(sizeof(double *) * matrix.rows);

  for (int i = 0; i < matrix.rows; ++i)
    matrix.matrix[i] = (double *)malloc(sizeof(double) * matrix.columns);

  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix.matrix[i][j] = .0;

  for (int i = 0; i < matrix.rows; ++i) {
    matrix.matrix[i][0] = 1;
    matrix.matrix[i][1] = 1;
    matrix.matrix[i][2] = 1;
  }

  rotation_by_oy(&matrix, arg);

  for (int i = 0; i < matrix.rows; ++i) {
    ck_assert_double_eq(matrix.matrix[i][0], cos(arg) + sin(arg));
    ck_assert_double_eq(matrix.matrix[i][1], 1);
    ck_assert_double_eq(matrix.matrix[i][2], -sin(arg) + cos(arg));
  }
  for (int i = 0; i < matrix.rows; ++i) free(matrix.matrix[i]);
  free(matrix.matrix);
}
END_TEST

START_TEST(rotation_by_oz_1) {
  double arg;
  arg = PI / 2;
  matrix_t matrix;
  matrix.rows = 2;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(sizeof(double *) * matrix.rows);

  for (int i = 0; i < matrix.rows; ++i)
    matrix.matrix[i] = (double *)malloc(sizeof(double) * matrix.columns);

  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix.matrix[i][j] = .0;

  for (int i = 0; i < matrix.rows; ++i) {
    matrix.matrix[i][0] = 1;
    matrix.matrix[i][1] = 1;
    matrix.matrix[i][2] = 1;
  }

  rotation_by_oz(&matrix, arg);

  for (int i = 0; i < matrix.rows; ++i) {
    ck_assert_double_eq(matrix.matrix[i][0], cos(arg) + sin(arg));
    ck_assert_double_eq(matrix.matrix[i][1], -sin(arg) + cos(arg));
    ck_assert_double_eq(matrix.matrix[i][2], 1);
  }
  for (int i = 0; i < matrix.rows; ++i) free(matrix.matrix[i]);
  free(matrix.matrix);
}
END_TEST

START_TEST(first_centers_1) {
  matrix_t matrix;
  matrix.rows = 2;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(sizeof(double *) * matrix.rows);

  for (int i = 0; i < matrix.rows; ++i)
    matrix.matrix[i] = (double *)malloc(sizeof(double) * matrix.columns);

  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix.matrix[i][j] = .0;

  for (int i = 0; i < matrix.rows; ++i) {
    matrix.matrix[i][0] = 1;
    matrix.matrix[i][1] = 1;
    matrix.matrix[i][2] = 1;
  }
  first_centers(&matrix);

  for (int i = 1; i < matrix.rows; ++i)
    for (int j = 0; j < matrix.columns; ++j)
      ck_assert_double_eq(matrix.matrix[i][j], 0);

  for (int i = 0; i < matrix.rows; ++i) free(matrix.matrix[i]);
  free(matrix.matrix);
}
END_TEST

START_TEST(scale_model_1) {
  double arg;
  arg = 1.1111;
  matrix_t matrix;
  matrix.rows = 2;
  matrix.columns = 3;
  matrix.matrix = (double **)malloc(sizeof(double *) * matrix.rows);

  for (int i = 0; i < matrix.rows; ++i)
    matrix.matrix[i] = (double *)malloc(sizeof(double) * matrix.columns);

  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < 3; ++j) matrix.matrix[i][j] = .0;

  for (int i = 0; i < matrix.rows; ++i) {
    matrix.matrix[i][0] = 1;
    matrix.matrix[i][1] = 1;
    matrix.matrix[i][2] = 1;
  }
  scale_model(&matrix, arg);
  for (int i = 0; i < matrix.rows; ++i)
    for (int j = 0; j < matrix.columns; ++j)
      ck_assert_double_eq(matrix.matrix[i][j], arg);

  for (int i = 0; i < matrix.rows; ++i) free(matrix.matrix[i]);
  free(matrix.matrix);
}
END_TEST

Suite *test_affine() {
  Suite *suite;

  suite = suite_create("my3dview_affine");
  TCase *tcase_found_min_max_or = tcase_create("found_min_max_or");
  TCase *tcase_first_init_val_gl = tcase_create("first_init_val_gl");
  TCase *tcase_move = tcase_create("move");
  TCase *tcase_rotation_by = tcase_create("rotation_by");
  TCase *tcase_first_center = tcase_create("first_center");
  TCase *tcase_scale_model = tcase_create("tcase_scale_model");

  suite_add_tcase(suite, tcase_found_min_max_or);
  tcase_add_test(tcase_found_min_max_or, found_min_max_or_1);

  suite_add_tcase(suite, tcase_first_init_val_gl);
  tcase_add_test(tcase_first_init_val_gl, first_init_val_gl_1);

  suite_add_tcase(suite, tcase_move);
  tcase_add_test(tcase_move, move_x_1);
  tcase_add_test(tcase_move, move_y_1);
  tcase_add_test(tcase_move, move_z_1);

  suite_add_tcase(suite, tcase_rotation_by);
  tcase_add_test(tcase_rotation_by, rotation_by_ox_1);
  tcase_add_test(tcase_rotation_by, rotation_by_oy_1);
  tcase_add_test(tcase_rotation_by, rotation_by_oz_1);

  suite_add_tcase(suite, tcase_first_center);
  tcase_add_test(tcase_first_center, first_centers_1);

  suite_add_tcase(suite, tcase_scale_model);
  tcase_add_test(tcase_scale_model, scale_model_1);

  return suite;
}

START_TEST(case1) {
  char *filepath = "obj/pyramid_test.obj";
  data_t *objData = allocObjData();

  ck_assert_ptr_nonnull(objData);
  int error = objParser(filepath, objData);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(objData->count_of_facets, 4);
  ck_assert_int_eq(objData->count_of_vertexes, 4);
  ck_assert_ptr_nonnull(objData->polygons);

  ck_assert_int_eq(objData->polygons[1].verxNums, 3);
  ck_assert_int_eq(objData->polygons[2].verxNums, 3);
  ck_assert_int_eq(objData->polygons[3].verxNums, 3);
  ck_assert_int_eq(objData->polygons[4].verxNums, 3);

  ck_assert_int_eq(objData->polygons[1].vertexes[0], 1);
  ck_assert_int_eq(objData->polygons[1].vertexes[1], 2);
  ck_assert_int_eq(objData->polygons[1].vertexes[2], 3);
  ck_assert_int_eq(objData->polygons[2].vertexes[0], 1);
  ck_assert_int_eq(objData->polygons[2].vertexes[1], 2);
  ck_assert_int_eq(objData->polygons[2].vertexes[2], 4);
  ck_assert_int_eq(objData->polygons[3].vertexes[0], 2);
  ck_assert_int_eq(objData->polygons[3].vertexes[1], 3);
  ck_assert_int_eq(objData->polygons[3].vertexes[2], 4);
  ck_assert_int_eq(objData->polygons[4].vertexes[0], 3);
  ck_assert_int_eq(objData->polygons[4].vertexes[1], 1);
  ck_assert_int_eq(objData->polygons[4].vertexes[2], 4);

  ck_assert_ptr_nonnull(objData->matrix_3d.matrix);

  ck_assert_double_eq(objData->matrix_3d.matrix[1][0], -1.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[1][1], 0.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[1][2], -1.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[2][0], 1.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[2][1], 0.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[2][2], -1.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[3][0], 0.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[3][1], 0.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[3][2], 1.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[4][0], 0.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[4][1], 1.0);
  ck_assert_double_eq(objData->matrix_3d.matrix[4][2], 0.0);

  ck_assert_int_eq(objData->matrix_3d.columns, 3);
  ck_assert_int_eq(objData->matrix_3d.rows, 5);

  freeObjData(&objData);

  ck_assert_ptr_null(objData);
}
END_TEST

START_TEST(case2) {
  char *filepath = "obj/cube_test.obj";
  data_t *objData = allocObjData();

  ck_assert_ptr_nonnull(objData);
  int error = objParser(filepath, objData);
  ck_assert_int_eq(error, 1);
  ck_assert_int_eq(objData->count_of_facets, 6);
  ck_assert_int_eq(objData->count_of_vertexes, 8);
  ck_assert_ptr_nonnull(objData->polygons);

  ck_assert_int_eq(objData->polygons[1].verxNums, 4);
  ck_assert_int_eq(objData->polygons[2].verxNums, 4);
  ck_assert_int_eq(objData->polygons[3].verxNums, 4);
  ck_assert_int_eq(objData->polygons[4].verxNums, 4);

  ck_assert_int_eq(objData->polygons[1].vertexes[0], 1);
  ck_assert_int_eq(objData->polygons[1].vertexes[1], 2);
  ck_assert_int_eq(objData->polygons[1].vertexes[2], 4);
  ck_assert_int_eq(objData->polygons[1].vertexes[3], 3);

  ck_assert_int_eq(objData->polygons[2].vertexes[0], 5);
  ck_assert_int_eq(objData->polygons[2].vertexes[1], 6);
  ck_assert_int_eq(objData->polygons[2].vertexes[2], 8);
  ck_assert_int_eq(objData->polygons[2].vertexes[3], 7);

  ck_assert_int_eq(objData->polygons[3].vertexes[0], 1);
  ck_assert_int_eq(objData->polygons[3].vertexes[1], 2);
  ck_assert_int_eq(objData->polygons[3].vertexes[2], 6);
  ck_assert_int_eq(objData->polygons[3].vertexes[3], 5);

  ck_assert_int_eq(objData->polygons[4].vertexes[0], 3);
  ck_assert_int_eq(objData->polygons[4].vertexes[1], 4);
  ck_assert_int_eq(objData->polygons[4].vertexes[2], 8);
  ck_assert_int_eq(objData->polygons[4].vertexes[3], 7);

  ck_assert_int_eq(objData->polygons[5].vertexes[0], 1);
  ck_assert_int_eq(objData->polygons[5].vertexes[1], 3);
  ck_assert_int_eq(objData->polygons[5].vertexes[2], 7);
  ck_assert_int_eq(objData->polygons[5].vertexes[3], 5);

  ck_assert_int_eq(objData->polygons[6].vertexes[0], 2);
  ck_assert_int_eq(objData->polygons[6].vertexes[1], 4);
  ck_assert_int_eq(objData->polygons[6].vertexes[2], 8);
  ck_assert_int_eq(objData->polygons[6].vertexes[3], 6);

  ck_assert_ptr_nonnull(objData->matrix_3d.matrix);

  ck_assert_double_eq(objData->matrix_3d.matrix[1][0], -.5);
  ck_assert_double_eq(objData->matrix_3d.matrix[1][1], -.5);
  ck_assert_double_eq(objData->matrix_3d.matrix[1][2], -.5);

  ck_assert_double_eq(objData->matrix_3d.matrix[2][0], .5);
  ck_assert_double_eq(objData->matrix_3d.matrix[2][1], -.5);
  ck_assert_double_eq(objData->matrix_3d.matrix[2][2], -.5);

  ck_assert_double_eq(objData->matrix_3d.matrix[3][0], -.5);
  ck_assert_double_eq(objData->matrix_3d.matrix[3][1], .5);
  ck_assert_double_eq(objData->matrix_3d.matrix[3][2], -.5);

  ck_assert_double_eq(objData->matrix_3d.matrix[4][0], .5);
  ck_assert_double_eq(objData->matrix_3d.matrix[4][1], .5);
  ck_assert_double_eq(objData->matrix_3d.matrix[4][2], -.5);

  ck_assert_double_eq(objData->matrix_3d.matrix[5][0], -.5);
  ck_assert_double_eq(objData->matrix_3d.matrix[5][1], -.5);
  ck_assert_double_eq(objData->matrix_3d.matrix[5][2], .5);

  ck_assert_double_eq(objData->matrix_3d.matrix[6][0], .5);
  ck_assert_double_eq(objData->matrix_3d.matrix[6][1], -.5);
  ck_assert_double_eq(objData->matrix_3d.matrix[6][2], .5);

  ck_assert_double_eq(objData->matrix_3d.matrix[7][0], -.5);
  ck_assert_double_eq(objData->matrix_3d.matrix[7][1], .5);
  ck_assert_double_eq(objData->matrix_3d.matrix[7][2], .5);

  ck_assert_double_eq(objData->matrix_3d.matrix[8][0], .5);
  ck_assert_double_eq(objData->matrix_3d.matrix[8][1], .5);
  ck_assert_double_eq(objData->matrix_3d.matrix[8][2], .5);

  ck_assert_int_eq(objData->matrix_3d.columns, 3);
  ck_assert_int_eq(objData->matrix_3d.rows, 9);

  freeObjData(&objData);

  ck_assert_ptr_null(objData);
}
END_TEST

Suite *test_parser(void) {
  Suite *s = suite_create("my3dview_parser");
  TCase *tc = tcase_create("test_parser");

  tcase_add_test(tc, case1);
  tcase_add_test(tc, case2);

  suite_add_tcase(s, tc);
  return s;
}

int main(void) {
  int failed = 0;
  Suite *my3dview_test[] = {test_affine(), test_parser(), NULL

  };

  for (int i = 0; my3dview_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(my3dview_test[i]);
    srunner_run_all(sr, CK_NORMAL);
    failed += srunner_ntests_failed(sr);
    srunner_free(sr);

    if (failed == 0)
      printf(GREEN "Success\n" WHITE);
    else
      printf(RED "Failed\n" WHITE);

    failed = 0;
  }

  return 0;
}
