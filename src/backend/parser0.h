#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct vertex {
    double *arrNoChange;
    double *arr;
    double *ptrArr;
    int memory;
    double vertexMax;
} vertex_st;

typedef struct index {
    unsigned *arr;
    unsigned *ptrArr;
    int memory;
} index_st;

typedef struct vertex_index {
    vertex_st vertex;
    index_st index;
} vertex_index_st;

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

typedef struct coordinates_struct {
    double rx;
    double ry;
    double rz;
    double scale;
    double tx;
    double ty;
} state_st;

typedef struct size_color {
    double rL;
    double gL;
    double bL;
    double rV;
    double gV;
    double bV;
    double rW;
    double gW;
    double bW;
    double aW;
    double widthLine;
    double widthVertex;
    int typeLine;
} look_st; 

// Парсер
int isNum(char symbol);
int countIndexInLine(char *line);
void recordIndex(std::string &line);
void recordVertex(char *line, vertex_st *vertex);
int reading(char *filename, vertex_index_st *data);
void record(char *filename, vertex_index_st *data);
void fillData(vertex_index_st *data);
vertex_index_st *getData(char *filename);
void deleteData(vertex_index_st *data);

// Функции меняющие сосотояния
void s21_remove_matrix(matrix_t *A);
void s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
void stateСhange(vertex_st *vertex, state_st *state);
matrix_t *countMatrix(state_st *state);
matrix_t *s21_create_matrix(int rows, int columns);
matrix_t *matrixOX (double align);
matrix_t *matrixOY (double align);
matrix_t *matrixOZ (double align);
matrix_t *scaling(double scale);