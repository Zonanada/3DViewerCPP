#ifndef SRC_MODEL_MODEL_H
#define SRC_MODEL_MODEL_H

#include "parser.h"
#include <cmath>
#include <thread>
using namespace std;


struct State {
    double rotate_by_x;
    double rotate_by_y;
    double rotete_by_z;
    double scale;
    double transfer_by_x;
    double transfer_by_y;
    double transfer_by_z;
};


class Rendering {
    public:
        Rendering() {};
        void parse_filename(std::string filename);
        void set_state(State input_state);
        bool get_projection();
        void set_projection(bool have_or_not);

        std::vector <double> &get_vertexes();
        std::vector <unsigned int> &get_indexes();
        
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
        
        std::vector <double> change_vertexes;
        std::vector <double> &original_vertexes = parser.get_vertexes();

        bool projection = false;
        int offset_along_z = 0;
        void copy_original_vertex();
        void apply_state_run(unsigned i);
        void output_vertex(std::vector <double> &nums);

        Parser parser;
        State state;
};

#endif