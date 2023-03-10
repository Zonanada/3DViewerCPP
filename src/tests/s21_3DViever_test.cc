#include <gtest/gtest.h>
#include "../backend/parser.cc"
#include <vector>

TEST(qwefq, qefqegr) {
    Parser cube("/home/user/develop/3DViewerCPP/objFiles/cube.obj");
    std::vector<unsigned int> arrIndexRes = {1, 2, 2, 3, 3, 1, 7, 6, 6, 5, 5, 7, 4, 5, 5, 1, 1, 4, 5, 6, 6, 2, 2, 5, 2, 6, 6, 7, 7, 2, 0, 3, 3, 7, 7, 0, 0, 1, 1, 3, 3, 0, 4, 7, 7, 5, 5, 4, 0, 4, 4, 1, 1, 0, 1, 5, 5, 2, 2, 1, 3, 2, 2, 7, 7, 3, 4, 0, 0, 7, 7, 4};
    std::vector<double> arrVertexRes = {0.500000, -0.500000, -0.500000, 0.500000, -0.500000, 0.500000, -0.500000, -0.500000, 0.500000, -0.500000, -0.500000, -0.500000, 0.500000, 0.500000, -0.500000, 0.500000, 0.500000, 0.500000, -0.500000, 0.500000, 0.500000, -0.500000, 0.500000, -0.500000};
    bool result_vertex = false;
    bool result_index = false;
    auto vertexes = cube.get_vertexes();
    auto indexes = cube.get_indexes();
    for (size_t i = 0; i < vertexes.size(); i++) {
        if (vertexes[i] != arrVertexRes[i]) result_vertex = true;
    }
    for (size_t i = 0; i < indexes.size(); i++) {
        if (indexes[i] != arrIndexRes[i]) result_index = true;
    }

    EXPECT_EQ(result_vertex, false);
    EXPECT_EQ(result_index, false);
}


int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
