#include <iostream>
#include <vector>
#include "src/controller/controller.h"
#include <array>
using namespace std; 
// #include "src/model/model.h"


void output_index(std::vector <unsigned int> &nums) {
    for (auto it : nums) {
        std::cout << it << " "; 
    }
    std::cout << "\n";
}

void output_vertex(std::vector <double> &nums) {
    for (auto it : nums) {
        std::cout << it << " "; 
    }
    std::cout << "\n";
}

int main() {
    State state;
    state.rotate_by_x = 0.5;
    state.rotate_by_y = 0.5;
    state.rotete_by_z = 0.5;
    state.scale = 1.2;
    state.transfer_by_x = 0.1;
    state.transfer_by_y = 0.1;
    state.transfer_by_z = 0.1;
    Controller rendering;
    rendering.parse_filename("objFiles/chair.obj");
    // output_vertex(rendering.get_vertexes());
    // output_index(rendering.get_indexes());
    rendering.set_state(state);
    // output_vertex(rendering.get_vertexes());


    // Matrix ox;
    // Matrix oy;
    // Matrix oz;
    // Matrix scale;
    // Matrix vertex;
    // ox.Matrix_4X4_OX(0.4);
    // oy.Matrix_4X4_OY(0.7);
    // oz.Matrix_4X4_OZ(2.3);
    // scale.Matrix_4X4_scaling(1.2);
    // vertex.Matrix_vertex(1, -1, -1);
    // Matrix res =  oy * oz * ox * scale * vertex;
    // Matrix res2 = res * vertex;
    // output_matrix(ox);
    // output_matrix(oy);
    // output_matrix(res);
    // output_matrix(res2);


    return 0;
}