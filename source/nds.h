#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>
#include <algorithm>

struct NDSVariableInfo
{
    std::string name;
    int index;
    unsigned int type;
    bool isArray;

    NDSVariableInfo();
    NDSVariableInfo(const std::string &name, int index, unsigned int type, bool isArray);

    struct Hash
    {
        std::size_t operator()(const NDSVariableInfo &variableInfo) const
        {
            return std::hash<std::string>()(variableInfo.name) ^ std::hash<unsigned int>()(variableInfo.type) ^ std::hash<bool>()(variableInfo.isArray);
        }
    };
};

struct NDSVariable
{
    union
    {
        unsigned int _uint;
        int _int;
        float _float;
        double _double;
        std::string *_string;
    };

    NDSVariable();
    NDSVariable(unsigned int value, unsigned int type);
    NDSVariable(int value, unsigned int type);
    NDSVariable(float value);
    NDSVariable(double value);
    NDSVariable(const std::string &value);

    struct Hash
    {
        std::size_t operator()(const NDSVariable &variable) const
        {
            return std::hash<int>()(variable._int) ^ std::hash<unsigned int>()(variable._uint) ^ std::hash<float>()(variable._float) ^ std::hash<double>()(variable._double) ^ std::hash<std::string>()(*variable._string);
        }
    };
};

class NDS
{
private:
    std::string path;

    std::vector<std::string> groupNames;
    std::unordered_map<std::string, std::unordered_map<std::string, NDSVariableInfo>> groupVariables; // groupName, variableName, variableInfo
    std::vector<NDSVariable> variables;
    std::vector<std::vector<NDSVariable>> variableArrays;

public:
    enum VariableType
    {
        UINT = 0,
        INT,
        FLOAT,
        DOUBLE,
        STRING
    };

    enum Directive
    {
        TEMPLATE,
        USING
    };

    NDS(const std::string &path);

    void printVariable(const NDSVariableInfo &variableInfo);
    void printNDL();

    void loadNDL();
    void loadNDL(const std::string &path);

    void saveNDL();
    void saveNDL(const std::string &path);

    void addGroup(const std::string &groupName);
    void removeGroup(const std::string &groupName);
    std::vector<std::string> getGroupNames();

    void addVariable(const std::string &variableName, const std::string &groupName, unsigned int variableType);
    void addArray(const std::string &variableName, const std::string &groupName, unsigned int variableType);

    void removeVariable(const std::string &variableName, const std::string &groupName);
    void removeArray(const std::string &variableName, const std::string &groupName);

    void setUInt(const std::string &variableName, const std::string &groupName, unsigned int value);
    void setInt(const std::string &variableName, const std::string &groupName, int value);
    void setFloat(const std::string &variableName, const std::string &groupName, float value);
    void setDouble(const std::string &variableName, const std::string &groupName, double value);
    void setString(const std::string &variableName, const std::string &groupName, const std::string &value);

    void setUIntArray(const std::string &variableName, const std::string &groupName, const std::vector<unsigned int> &value);
    void setIntArray(const std::string &variableName, const std::string &groupName, const std::vector<int> &value);
    void setFloatArray(const std::string &variableName, const std::string &groupName, const std::vector<float> &value);
    void setDoubleArray(const std::string &variableName, const std::string &groupName, const std::vector<double> &value);
    void setStringArray(const std::string &variableName, const std::string &groupName, const std::vector<std::string> &value);

    void addUIntsToArray(const std::string &variableName, const std::string &groupName, const std::vector<unsigned int> &value);
    void addIntsToArray(const std::string &variableName, const std::string &groupName, const std::vector<int> &value);
    void addFloatsToArray(const std::string &variableName, const std::string &groupName, const std::vector<float> &value);
    void addDoublesToArray(const std::string &variableName, const std::string &groupName, const std::vector<double> &value);
    void addStringsToArray(const std::string &variableName, const std::string &groupName, const std::vector<std::string> &value);

    void addUIntToArray(const std::string &variableName, const std::string &groupName, unsigned int value);
    void addIntToArray(const std::string &variableName, const std::string &groupName, int value);
    void addFloatToArray(const std::string &variableName, const std::string &groupName, float value);
    void addDoubleToArray(const std::string &variableName, const std::string &groupName, double value);
    void addStringToArray(const std::string &variableName, const std::string &groupName, const std::string &value);

    unsigned int getUInt(const std::string &variableName, const std::string &groupName);
    int getInt(const std::string &variableName, const std::string &groupName);
    float getFloat(const std::string &variableName, const std::string &groupName);
    double getDouble(const std::string &variableName, const std::string &groupName);
    std::string getString(const std::string &variableName, const std::string &groupName);

    std::vector<unsigned int> getUIntArray(const std::string &variableName, const std::string &groupName);
    std::vector<int> getIntArray(const std::string &variableName, const std::string &groupName);
    std::vector<float> getFloatArray(const std::string &variableName, const std::string &groupName);
    std::vector<double> getDoubleArray(const std::string &variableName, const std::string &groupName);
    std::vector<std::string> getStringArray(const std::string &variableName, const std::string &groupName);

    unsigned int getUIntFromArray(const std::string &variableName, const std::string &groupName, int index);
    int getIntFromArray(const std::string &variableName, const std::string &groupName, int index);
    float getFloatFromArray(const std::string &variableName, const std::string &groupName, int index);
    double getDoubleFromArray(const std::string &variableName, const std::string &groupName, int index);
    std::string getStringFromArray(const std::string &variableName, const std::string &groupName, int index);

    void clear();

    void setPath(const std::string &path);
    std::string getPath();
};