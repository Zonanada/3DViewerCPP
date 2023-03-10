/*!
\file
\brief Файл с в котором происходит парсинг и афинные преобразования
*/

#include "parser0.h"

/**
 * @brief create new matrix
 *
 * @param rows
 * @param columns
 * @return new matrix_t
 */
matrix_t *s21_create_matrix(int rows, int columns) {
  matrix_t *result = malloc(1 * sizeof(matrix_t));
  double **row = malloc(rows * sizeof(double *));
  double **ptrRow = row;
  for (int i = 0; i < rows; i++) {
    *ptrRow = calloc(columns, sizeof(double));
    ptrRow++;
  }
  result->matrix = row;
  result->rows = rows;
  result->columns = columns;
  return result;
}

/**
 * @brief remove matrix and free all dynamic memory
 *
 * @param  matrix pointer
 */
void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
  free(A->matrix);
  free(A);
}

/**
 * @brief  multiplication of two matrices
 *
 * @param pointer first matrix
 * @param pointer second matrix
 * @param pointer matrix for record result
 * @return pointer matrix result
 */
void s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < B->rows; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
}

/**
 * @brief creating a matrix for affine transformations along the x-axis
 *
 * @param degree of displacement
 * @return matrix for affine transformations
 */
matrix_t *matrixOX(double align) {
  matrix_t *OXMatrix = s21_create_matrix(4, 4);
  OXMatrix->matrix[0][0] = 1;
  OXMatrix->matrix[1][1] = cos(align);
  OXMatrix->matrix[1][2] = -sin(align);
  OXMatrix->matrix[2][1] = sin(align);
  OXMatrix->matrix[2][2] = cos(align);
  OXMatrix->matrix[3][3] = 1;
  return OXMatrix;
}
/**
 * @brief creating a matrix for affine transformations along the y-axis
 *
 * @param degree of displacement
 * @return matrix for affine transformations
 */
matrix_t *matrixOY(double align) {
  matrix_t *OYMatrix = s21_create_matrix(4, 4);
  OYMatrix->matrix[0][0] = cos(align);
  OYMatrix->matrix[0][2] = sin(align);
  OYMatrix->matrix[1][1] = 1;
  OYMatrix->matrix[2][0] = -sin(align);
  OYMatrix->matrix[2][2] = cos(align);
  OYMatrix->matrix[3][3] = 1;
  return OYMatrix;
}

/**
 * @brief creating a matrix for affine transformations along the z-axis
 *
 * @param degree of displacement
 * @return matrix for affine transformations
 */
matrix_t *matrixOZ(double align) {
  matrix_t *OZMatrix = s21_create_matrix(4, 4);
  OZMatrix->matrix[0][0] = cos(align);
  OZMatrix->matrix[0][1] = -sin(align);
  OZMatrix->matrix[1][0] = sin(align);
  OZMatrix->matrix[1][1] = cos(align);
  OZMatrix->matrix[2][2] = 1;
  OZMatrix->matrix[3][3] = 1;
  return OZMatrix;
}

/**
 * @brief creating a matrix for affine transformations. decrease/increase
 *
 * @param degree of displacement
 * @return matrix for affine transformations
 */
matrix_t *scaling(double scale) {
  matrix_t *scaleMatrix = s21_create_matrix(4, 4);
  scaleMatrix->matrix[0][0] = scale;
  scaleMatrix->matrix[1][1] = scale;
  scaleMatrix->matrix[2][2] = scale;
  scaleMatrix->matrix[3][3] = 1;
  return scaleMatrix;
}

/**
 * @brief creating a matrix to calculate new coordinates shifted by a given
 * offset
 *
 * @param structure with degrees to which the shift is made
 * @return matrix for counting new coordinates
 */
matrix_t *countMatrix(state_st *state) {
  matrix_t *OXMatrix = matrixOX(state->rx);
  matrix_t *OYMatrix = matrixOY(state->ry);
  matrix_t *OZMatrix = matrixOZ(state->rz);
  matrix_t *scaleMaitrix = scaling(state->scale);
  matrix_t *resultXY = s21_create_matrix(4, 4);
  matrix_t *resultXYZ = s21_create_matrix(4, 4);
  matrix_t *resultXYZScale = s21_create_matrix(4, 4);
  matrix_t *resultMatrix = s21_create_matrix(4, 4);

  s21_mult_matrix(OXMatrix, OYMatrix, resultXY);
  s21_mult_matrix(resultXY, OZMatrix, resultXYZ);
  s21_mult_matrix(resultXYZ, scaleMaitrix, resultMatrix);

  s21_remove_matrix(OXMatrix);
  s21_remove_matrix(OYMatrix);
  s21_remove_matrix(OZMatrix);
  s21_remove_matrix(scaleMaitrix);
  s21_remove_matrix(resultXY);
  s21_remove_matrix(resultXYZ);
  s21_remove_matrix(resultXYZScale);

  return resultMatrix;
}

/**
 * @brief counting new coordinates
 *
 * @param structure in which changes will be made
 * @param structure structure with powers for transformations
 */
void stateСhange(vertex_st *vertex, state_st *state) {
  matrix_t *resultMatrix = countMatrix(state);
  double *ptr = vertex->arr;
  double *ptrN = vertex->arrNoChange;
  matrix_t *vert = s21_create_matrix(4, 1);
  matrix_t *result = s21_create_matrix(4, 1);

  for (int i = 0; i < vertex->memory / 3; i++) {
    double *temp_x = ptr;
    double *temp_xN = ptrN;
    ptr++;
    ptrN++;
    double *temp_y = ptr;
    double *temp_yN = ptrN;
    ptr++;
    ptrN++;
    double *temp_z = ptr;
    double *temp_zN = ptrN;
    ptr++;
    ptrN++;

    vert->matrix[0][0] = *temp_xN;
    vert->matrix[1][0] = *temp_yN;
    vert->matrix[2][0] = *temp_zN;

    s21_mult_matrix(resultMatrix, vert, result);

    *temp_x = result->matrix[0][0] + state->tx;
    *temp_y = result->matrix[1][0] + state->ty;
    *temp_z = result->matrix[2][0];
  }
  free(state);
  s21_remove_matrix(result);
  s21_remove_matrix(vert);
  s21_remove_matrix(resultMatrix);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief checking for a number
 *
 * @param symbol type char
 * @return true or false
 */
int isNum(char symbol) {
  return (symbol >= '0' && symbol <= '9') || symbol == ',' || symbol == '.' ||
         symbol == '-' || symbol == '+';
}
/**
 * @brief free all dynamics memory
 *
 * @param pointer to structure "vertex_index_st" to clean up
 */
void deleteData(vertex_index_st *data) {
  free(data->index.arr);
  free(data->vertex.arr);
  free(data);
}

/**
 * @brief counting the number of indices in a row
 *
 * @param pointer to string
 * @return count of indices
 */
int countIndexInLine(char *line) {
  int countIndex = 0;
  char *ptrLine = line;
  while (*ptrLine != '\0') {
    if (isNum(*ptrLine)) {
      while (isNum(*ptrLine)) {
        ptrLine++;
      }
      countIndex++;
      while (*ptrLine != ' ' && *ptrLine != '\n' && *ptrLine != '\0') {
        ptrLine++;
      }
    }
    ptrLine++;
  }
  return countIndex;
}

/**
 * @brief counting the number of indices in a row
 *
 * @param pointer to string
 * @return count of indices
 */
void recordIndex(char *line, index_st *index) {
  char *ptrLine = line;
  char numStr[50];
  int firstIndex = 1;
  int countIndexRecord = 0;
  char *ptrStr = numStr;
  while (*ptrLine != '\0') {
    if (isNum(*ptrLine)) {
      while (isNum(*ptrLine)) {
        *ptrStr = *ptrLine;
        ptrStr++;
        ptrLine++;
      }
      *ptrStr = '\0';
      ptrStr = numStr;

      int pushNum = atoi(numStr) - 1;
      if (firstIndex) {
        *index->ptrArr = pushNum;
        index->ptrArr++;
        firstIndex = 0;
        countIndexRecord++;
      } else {
        *index->ptrArr = pushNum;
        index->ptrArr++;
        countIndexRecord++;
        *index->ptrArr = pushNum;
        index->ptrArr++;
        countIndexRecord++;
      }

      while (*ptrLine != ' ' && *ptrLine != '\n' && *ptrLine != '\0') {
        ptrLine++;
      }
    }
    ptrLine++;
  }
  *index->ptrArr = *(index->ptrArr - countIndexRecord);
  index->ptrArr++;
}

/**
 * @brief counting the number of vertex in a row
 *
 * @param pointer to string
 * @return count of vertex
 */
void recordVertex(char *line, vertex_st *vertex) {
  char *ptrLine = line;
  char numStr[50];
  char *ptrStr = numStr;
  while (*ptrLine != '\0') {
    if (isNum(*ptrLine)) {
      while (isNum(*ptrLine)) {
        *ptrStr = *ptrLine;
        ptrStr++;
        ptrLine++;
      }
      *ptrStr = '\0';
      ptrStr = numStr;
      *vertex->ptrArr = atof(numStr);
      if (*vertex->ptrArr > vertex->vertexMax)
        vertex->vertexMax = *vertex->ptrArr;
      vertex->ptrArr++;

      while (*ptrLine != ' ' && *ptrLine != '\n' && *ptrLine != '\0') {
        ptrLine++;
      }
    }
    ptrLine++;
  }
}

/**
 * @brief reading from a file
 *
 * @param pointer to filename
 * @param pointer to struct data
 * @return reading success
 */
int reading(char *filename, vertex_index_st *data) {
  int countVertex = 0;
  int countIndex = 0;
  char line[512];
  FILE *fp;

  if ((fp = fopen(filename, "r")) != NULL) {
    while ((fgets(line, 256, fp)) != NULL) {
      if (*line == 'v' && *(line + 1) == ' ') {
        countVertex++;
      }
      if (*line == 'f' && *(line + 1) == ' ') {
        countIndex += countIndexInLine(line);
      }
    }
    data->vertex.memory = countVertex * 3;
    data->index.memory = countIndex * 2;

    fclose(fp);
  } else {
    printf("File not found!\n");
    return 1;
  }

  return 0;
}

/**
 * @brief parsing and writing data from a file
 *
 * @param pointer to string file name
 * @param pointer to struct with all data
 */
void record(char *filename, vertex_index_st *data) {
  char line[256];
  FILE *fp;

  if ((fp = fopen(filename, "r")) != NULL) {
    while ((fgets(line, 256, fp)) != NULL) {
      if (*line == 'v' && *(line + 1) == ' ') {
        recordVertex(line, &data->vertex);
      }
      if (*line == 'f' && *(line + 1) == ' ') {
        recordIndex(line, &data->index);
      }
    }

    for (int i = 0; i < data->vertex.memory; i++) {
      data->vertex.arrNoChange[i] = data->vertex.arr[i];
    }

    int coeff = data->vertex.vertexMax / 0.5;
    for (int i = 0; i < data->vertex.memory; i++) {
      data->vertex.arr[i] /= coeff;
      data->vertex.arrNoChange[i] /= coeff;
    }

    fclose(fp);
  } else {
    printf("File not found!\n");
  }
}

/**
 * @brief memory allocation for milestone arrays
 *
 * @param pointer to struct with all data
 */
void fillData(vertex_index_st *data) {
  data->vertex.arr = calloc(data->vertex.memory, sizeof(double));
  data->vertex.ptrArr = data->vertex.arr;
  data->vertex.arrNoChange = calloc(data->vertex.memory, sizeof(double));
  data->vertex.vertexMax = 0;

  data->index.arr = calloc(data->index.memory, sizeof(unsigned));
  data->index.ptrArr = data->index.arr;
}

/**
 * @brief function to retrieve data for rendering
 *
 * @param pointer to string file name
 */
vertex_index_st *getData(char *filename) {
  vertex_index_st *data = calloc(1, sizeof(vertex_index_st));
  printf("%s\n", filename);
  if (reading(filename, data) == 0) {
    fillData(data);
    record(filename, data);
  }
  free(filename);
  return data;
}
