#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

class NDS
{
private:
    std::string path;

    std::vector<std::string> groupNames;
    std::vector<std::tuple<int, std::string, int, int>> groupVariableData; // groupIndex, variableName, variableType, variableIndex

    std::vector<int> ints;
    std::vector<unsigned int> uints;
    std::vector<float> floats;
    std::vector<double> doubles;
    std::vector<std::string> strings;

    std::vector<std::vector<int>> intLists;
    std::vector<std::vector<unsigned int>> uintLists;
    std::vector<std::vector<float>> floatLists;
    std::vector<std::vector<double>> doubleLists;
    std::vector<std::vector<std::string>> stringLists;

public:
    enum VariableType
    {
        INT = 0,
        UINT = 1,
        FLOAT = 2,
        DOUBLE = 3,
        STRING = 4,
        INT_LIST = 10,
        UINT_LIST = 11,
        FLOAT_LIST = 12,
        DOUBLE_LIST = 13,
        STRING_LIST = 14
    };

    NDS(std::string path);

    void printNDL();

    void loadNDL();
    void loadNDL(std::string path);
    // void loadBinaryNDL();
    // void loadBinaryNDL(std::string path);

    void saveNDL();
    void saveNDL(std::string path);
    // void saveBinaryNDL();
    // void saveBinaryNDL(std::string path);

    int getInt(std::string variableName, std::string groupName);
    unsigned int getUInt(std::string variableName, std::string groupName);
    float getFloat(std::string variableName, std::string groupName);
    double getDouble(std::string variableName, std::string groupName);
    std::string getString(std::string variableName, std::string groupName);

    std::vector<int> getIntList(std::string variableName, std::string groupName);
    std::vector<unsigned int> getUIntList(std::string variableName, std::string groupName);
    std::vector<float> getFloatList(std::string variableName, std::string groupName);
    std::vector<double> getDoubleList(std::string variableName, std::string groupName);
    std::vector<std::string> getStringList(std::string variableName, std::string groupName);

    std::vector<std::string> getGroupNames();
    std::vector<std::tuple<int, std::string, int, int>> getGroupVariableData();
    std::vector<int> getInts();
    std::vector<unsigned int> getUInts();
    std::vector<float> getFloats();
    std::vector<double> getDoubles();
    std::vector<std::string> getStrings();

    std::vector<std::vector<int>> getIntLists();
    std::vector<std::vector<unsigned int>> getUIntLists();
    std::vector<std::vector<float>> getFloatLists();
    std::vector<std::vector<double>> getDoubleLists();
    std::vector<std::vector<std::string>> getStringLists();

    void setInt(std::string variableName, std::string groupName, int value);
    void setUInt(std::string variableName, std::string groupName, unsigned int value);
    void setFloat(std::string variableName, std::string groupName, float value);
    void setDouble(std::string variableName, std::string groupName, double value);
    void setString(std::string variableName, std::string groupName, std::string value);

    void setIntList(std::string variableName, std::string groupName, std::vector<int> value);
    void setUIntList(std::string variableName, std::string groupName, std::vector<unsigned int> value);
    void setFloatList(std::string variableName, std::string groupName, std::vector<float> value);
    void setDoubleList(std::string variableName, std::string groupName, std::vector<double> value);
    void setStringList(std::string variableName, std::string groupName, std::vector<std::string> value);

    void addGroup(std::string groupName);
    void removeGroup(std::string groupName);
    void clearGroup(std::string groupName);
    void addVariable(std::string variableName, std::string groupName, int variableType);
    void removeVariable(std::string variableName, std::string groupName);
    void clearVariable(std::string variableName, std::string groupName);

    void clearAll();

    void setPath(std::string path);
    std::string getPath();
};