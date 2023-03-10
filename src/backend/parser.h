#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>


// typedef struct vertex {
//     double *arrNoChange;
//     double *ptrArr;
//     int memory;
//     double vertexMax;
// } vertex_st;

// typedef struct index {
//     unsigned *arr;
//     unsigned *ptrArr;
//     int memory;
// } index_st;

// typedef struct vertex_index {
//     vertex_st vertex;
//     index_st index;
// } vertex_index_st;

// typedef struct matrix_struct {
//     double** matrix;
//     int rows;
//     int columns;
// } matrix_t;

// typedef struct coordinates_struct {
//     double rx;
//     double ry;
//     double rz;
//     double scale;
//     double tx;
//     double ty;
// } state_st;

// typedef struct size_color {
//     double rL;
//     double gL;
//     double bL;
//     double rV;
//     double gV;
//     double bV;
//     double rW;
//     double gW;
//     double bW;
//     double aW;
//     double widthLine;
//     double widthVertex;
//     int typeLine;
// } look_st; 


class Parser {
    public:
        Parser(std::string input_filename) : filename(input_filename) {
            reading();
            record();
        }
        std::vector<double> &get_vertexes() {
            return vertexes;
        }

        std::vector<unsigned int> &get_indexes() {
            return indexes;
        }

    private:
        int isNum(char symbol);
        int countIndexInLine(std::string &line);
        void recordIndex(std::string &line);
        void recordVertex(std::string &line);
        void reading();
        void record();

        double vertex_max = 0;
        unsigned int it_vertexes = 0;
        unsigned int it_indexes = 0;
        std::string filename;
        std::vector<double> vertexes;
        std::vector<unsigned int> indexes;
};






// Парсер
// int isNum(char symbol);
// int countIndexInLine(char *line);
// void recordIndex(char *line, index_st *index);
// void recordVertex(char *line, vertex_st *vertex);
// int reading(char *filename, vertex_index_st *data);
// void record(char *filename, vertex_index_st *data);
// void fillData(vertex_index_st *data);
// vertex_index_st *getData(char *filename);
// void deleteData(vertex_index_st *data);

// // Функции меняющие сосотояния
// void s21_remove_matrix(matrix_t *A);
// void s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// void stateСhange(vertex_st *vertex, state_st *state);
// matrix_t *countMatrix(state_st *state);
// matrix_t *s21_create_matrix(int rows, int columns);
// matrix_t *matrixOX (double align);
// matrix_t *matrixOY (double align);
// matrix_t *matrixOZ (double align);
// matrix_t *scaling(double scale);