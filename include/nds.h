// MOVE LISTS TO SEPARATE VARIABLES
// SHRINK variableIndex TO ONLY CONTAIN THE VARIABLE TYPE AND VECTOR INDEX

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

struct Config
{
    std::string path;

    Config(std::string path);
};

class NDS
{
private:
    std::string path;
    // Config config;

    std::vector<std::string> groups;
    std::vector<std::pair<int, int>> groupVariableIndex; // <group index, var index>
    std::vector<std::string> variables;
    std::vector<std::tuple<int, int, int>> variableIndex; // <var index, var type, var vector index>

    std::vector<int> ints;
    std::vector<unsigned int> uints;
    std::vector<float> floats;
    std::vector<double> doubles;
    std::vector<std::string> strings;

public:
    NDS(std::string path);
    // NDS(std::string pathNDS, std::string pathConfig);

    void loadNDL();
};