#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H


#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

struct State {
    double rotate_by_x;
    double rotate_by_y;
    double rotete_by_z;
    double scale;
    double transfer_by_x;
    double transfer_by_y;
    double transfer_by_z;
};

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
        
    private:
        void apply_state();
        void rotate_by_x(unsigned index_value_y, unsigned index_value_z);
        void rotate_by_y(unsigned index_value_x, unsigned index_value_z);
        void rotate_by_z(unsigned index_value_x, unsigned index_value_y);
        void scaling(unsigned in_x, unsigned in_y, unsigned in_z);
        void transfer_by_x(unsigned in_x);
        void transfer_by_y(unsigned in_y);
        void transfer_by_z(unsigned in_z);
        Parser parser;
        State state;
        std::vector <double> change_vertexes;
        std::vector <double> &original_vertexes = parser.get_vertexes();
        void copy_original_vertex();

        void output_vertex(std::vector <double> &nums);
};

#endif