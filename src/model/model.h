#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H


#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>
#include <array>
#include <thread>
using namespace std;


// class Matrix {
//     public:
//         Matrix(){};
//         Matrix(int input_rows, int input_cols) : rows(input_rows), cols(input_cols){};
//         Matrix (const Matrix &other) {
//             rows = other.rows;
//             cols = other.cols;
//             matrix = other.matrix;
//         }
//         Matrix (Matrix &&other) {
//             rows = other.rows;
//             cols = other.cols;
//             matrix = std::move(other.matrix);
//         }
//         Matrix operator=(const Matrix &other) {
//             matrix = other.matrix;
//             rows = other.rows;
//             cols = other.cols;
//             return *this;
//         }
//         Matrix operator=(Matrix &&other) {
//             matrix = std::move(other.matrix);
//             rows = other.rows;
//             cols = other.cols;
//             return *this;
//         }
//         array<double, 4> &operator[](int row) {
//             return matrix[row];
//         }
//         Matrix operator*(const Matrix &other) {
//             Matrix copy_this(*this);
//             copy_this.multMatrix(other);
//             return std::move(copy_this);
//         }
//         Matrix operator*=(const Matrix &other) {
//             multMatrix(other);
//             return *this;
//         }

//         void output_matrix() {
//             for (int i = 0; i < rows; i++) {
//                 for (int j = 0; j < cols; j++) {
//                     cout << matrix[i][j] << " ";
//                 }
//                 cout << "\n";
//             }
//             cout << "\n";
//         }

//         array<array<double, 4>, 4> matrix = {0};
//         int rows;
//         int cols;
        
//         void multMatrix(const Matrix &other) {
//             Matrix res_matrix(4,4);
//             for (int i = 0; i < rows; i++) {
//                 for (int j = 0; j < other.cols; j++) {
//                     for (int k = 0; k < other.rows; k++) {
//                     res_matrix[i][j] += matrix[i][k] * other.matrix[k][j];
//                     }
//                 }
//             }
//             *this = std::move(res_matrix);
//         }

//         void Matrix_4X4_OX(double align) {
//             rows = 4;
//             cols = 4;
//             matrix[0][0] = 1;
//             matrix[0][0] = 1;
//             matrix[1][1] = cos(align);
//             matrix[1][2] = -sin(align);
//             matrix[2][1] = sin(align);
//             matrix[2][2] = cos(align);
//             matrix[3][3] = 1;
//         }

//         void Matrix_4X4_OY(double align) {
//             rows = 4;
//             cols = 4;
//             matrix[0][0] = cos(align);
//             matrix[0][2] = sin(align);
//             matrix[1][1] = 1;
//             matrix[2][0] = -sin(align);
//             matrix[2][2] = cos(align);
//             matrix[3][3] = 1;
//         }

//         void Matrix_4X4_OZ(double align) {
//             rows = 4;
//             cols = 4;
//             matrix[0][0] = cos(align);
//             matrix[0][1] = -sin(align);
//             matrix[1][0] = sin(align);
//             matrix[1][1] = cos(align);
//             matrix[2][2] = 1;
//             matrix[3][3] = 1;
//         }

//         void Matrix_4X4_scaling(double scale) {
//             rows = 4;
//             cols = 4;
//             matrix[0][0] = scale;
//             matrix[1][1] = scale;
//             matrix[2][2] = scale;
//             matrix[3][3] = 1;
//         }

//         void Matrix_vertex(double x, double y, double z) {
//             rows = 4;
//             cols = 4;
//             matrix[0][0] = x;
//             matrix[1][0] = y;
//             matrix[2][0] = z;
//         }

// };


struct State {
    double rotate_by_x;
    double rotate_by_y;
    double rotete_by_z;
    double scale;
    double transfer_by_x;
    double transfer_by_y;
    double transfer_by_z;
};




class Parser {
    public:
        Parser(){};
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

        void parse_filename(std::string input_filename) {
            filename = input_filename;
            reading();
            record();
        };

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

class Rendering {
    public:
        Rendering() {};
        void parse_filename(std::string filename);
        void set_state(State input_state);
        std::vector <double> &get_vertexes();
        std::vector <unsigned int> &get_indexes();
        bool get_projection();
        void set_projection(bool have_or_not);
        
    private:
        void apply_state();
        void rotate_by_x(unsigned index_value_y, unsigned index_value_z);
        void rotate_by_y(unsigned index_value_x, unsigned index_value_z);
        void rotate_by_z(unsigned index_value_x, unsigned index_value_y);
        void scaling(unsigned in_x, unsigned in_y, unsigned in_z);

        void second_theard_state();
        void first_theard_state();
        void third_theard_state();
        void four_theard_state();
        void fifth_theard_state();
        void sixth_theard_state();
        void seventh_theard_state();
        void eighth_theard_state();

        void first_theard_copy();
        void second_theard_copy();
        void transfer_by_x(unsigned in_x);
        void transfer_by_y(unsigned in_y);
        void transfer_by_z(unsigned in_z);

        Parser parser;
        State state;
        std::vector <double> change_vertexes;
        std::vector <double> &original_vertexes = parser.get_vertexes();
        bool projection = false;
        int offset_along_z = 0;
 
        void copy_original_vertex();
        void apply_state_run(unsigned i);

        void output_vertex(std::vector <double> &nums);
};

#endif