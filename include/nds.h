#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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
    std::vector<std::vector<int>> groupsIndex;
    std::vector<std::string> variables;
    std::vector<std::pair<int, int>> variableIndex; // <type, index>

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