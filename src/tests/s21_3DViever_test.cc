#include <gtest/gtest.h>
#include "../model/parser.cc"
#include <vector>

TEST(ParserTest, ReadFileException) {
  ASSERT_THROW(Parser("nonexistent_file.obj"), std::out_of_range);
}

TEST(ParserTest, ReadingTest) {
Parser parser("../objFiles/cube.obj");
std::vector<double> expected_vertexes = {-1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 1.000000,
1.000000, 1.000000, 1.000000, 1.000000, -1.000000, 1.000000,
-1.000000, -1.000000, -1.000000, -1.000000, 1.000000, -1.000000,
1.000000, 1.000000, -1.000000, 1.000000, -1.000000, -1.000000};
ASSERT_EQ(parser.get_vertexes(), expected_vertexes);
std::vector<unsigned int> expected_indexes = { 0, 1, 1, 2, 2, 3, 3, 0, 4, 5, 5, 6, 6, 7, 7, 4, 1, 5, 5, 1, 0, 4, 4, 0, 2, 6, 6, 2, 3, 7, 7, 3};
ASSERT_EQ(parser.get_indexes(), expected_indexes);
}

TEST(ParserTest, ParseFilenameTest) {
Parser parser;
parser.parse_filename("../objFiles/cube.obj");
std::vector<double> expected_vertexes = {-1.000000, -1.000000, 1.000000, -1.000000, 1.000000, 1.000000,
1.000000, 1.000000, 1.000000, 1.000000, -1.000000, 1.000000,
-1.000000, -1.000000, -1.000000, -1.000000, 1.000000, -1.000000,
1.000000, 1.000000, -1.000000, 1.000000, -1.000000, -1.000000};
ASSERT_EQ(parser.get_vertexes(), expected_vertexes);
std::vector<unsigned int> expected_indexes = {1, 2, 3, 4, 5, 6, 7, 8, 2, 6, 1, 5, 3, 7, 4, 8};
ASSERT_EQ(parser.get_indexes(), expected_indexes);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
