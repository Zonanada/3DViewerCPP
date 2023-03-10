#include <iostream>
#include <vector>
#include "src/backend/parser.h"


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
    Parser parser("/home/user/develop/3DViewerCPP/objFiles/cube.obj");
    output_vertex(parser.get_vertexes());
    // output_index(parser.get_indexes());
    

    return 0;
}