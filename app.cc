#include <iostream>
#include <vector>
#include "src/controller/controller.h"
// #include "src/model/model.cc"


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
    rendering.parse_filename("objFiles/cube.obj");
    output_vertex(rendering.get_vertexes());
    rendering.set_state(state);
    output_vertex(rendering.get_vertexes());
    return 0;
}