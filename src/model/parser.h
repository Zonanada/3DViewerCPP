#include <vector>
#include <iostream>
#include <fstream>

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