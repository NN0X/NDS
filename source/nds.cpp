#include <nds.h>

NDSVariableInfo::NDSVariableInfo()
{
}

NDSVariableInfo::NDSVariableInfo(const std::string &name, int index, unsigned int type, bool isArray) : name(name), index(index), type(type), isArray(isArray)
{
    this->name = name;
    this->index = index;
    this->type = type;
    this->isArray = isArray;
}

NDSVariable::NDSVariable()
{
}

NDSVariable::NDSVariable(unsigned int value, unsigned int type)
{
    if (type == NDS::UINT)
        _uint = value;
    else if (type == NDS::INT)
        _int = value;
    else if (type == NDS::FLOAT)
        _float = value;
    else if (type == NDS::DOUBLE)
        _double = value;
}

NDSVariable::NDSVariable(int value, unsigned int type)
{
    if (type == NDS::UINT)
        _uint = value;
    else if (type == NDS::INT)
        _int = value;
    else if (type == NDS::FLOAT)
        _float = value;
    else if (type == NDS::DOUBLE)
        _double = value;
}

NDSVariable::NDSVariable(float value)
{
    _float = value;
}

NDSVariable::NDSVariable(double value)
{
    _double = value;
}

NDSVariable::NDSVariable(const std::string &value)
{
    _string = new std::string(value);
}

NDS::NDS(const std::string &path)
{
    this->path = path;
}

void NDS::printVariable(const NDSVariableInfo &variableInfo)
{
    if (!variableInfo.isArray)
    {
        switch (variableInfo.type)
        {
        case INT:
            std::cout << "int;" << variableInfo.name << ":" << variables[variableInfo.index]._int << "\n";
            break;
        case UINT:
            std::cout << "uint;" << variableInfo.name << ":" << variables[variableInfo.index]._uint << "\n";
            break;
        case FLOAT:
            std::cout << "float;" << variableInfo.name << ":" << variables[variableInfo.index]._float << "\n";
            break;
        case DOUBLE:
            std::cout << "double;" << variableInfo.name << ":" << variables[variableInfo.index]._double << "\n";
            break;
        case STRING:
            std::cout << "string;" << variableInfo.name << ":\"" << *variables[variableInfo.index]._string << "\"\n";
            break;
        }
    }
    else
    {
        switch (variableInfo.type)
        {
        case INT:
            std::cout << "int;" << variableInfo.name << ":[";
            for (int i = 0; i < variableArrays[variableInfo.index].size(); i++)
                std::cout << variableArrays[variableInfo.index][i]._int << (i == variableArrays[variableInfo.index].size() - 1 ? "" : ",");
            std::cout << "]\n";
            break;
        case UINT:
            std::cout << "uint;" << variableInfo.name << ":[";
            for (int i = 0; i < variableArrays[variableInfo.index].size(); i++)
                std::cout << variableArrays[variableInfo.index][i]._uint << (i == variableArrays[variableInfo.index].size() - 1 ? "" : ",");
            std::cout << "]\n";
            break;
        case FLOAT:
            std::cout << "float;" << variableInfo.name << ":[";
            for (int i = 0; i < variableArrays[variableInfo.index].size(); i++)
                std::cout << variableArrays[variableInfo.index][i]._float << (i == variableArrays[variableInfo.index].size() - 1 ? "" : ",");
            std::cout << "]\n";
            break;
        case DOUBLE:
            std::cout << "double;" << variableInfo.name << ":[";
            for (int i = 0; i < variableArrays[variableInfo.index].size(); i++)
                std::cout << variableArrays[variableInfo.index][i]._double << (i == variableArrays[variableInfo.index].size() - 1 ? "" : ",");
            std::cout << "]\n";
            break;
        case STRING:
            std::cout << "string;" << variableInfo.name << ":[";
            for (int i = 0; i < variableArrays[variableInfo.index].size(); i++)
                std::cout << "\"" << *variableArrays[variableInfo.index][i]._string << "\"" << (i == variableArrays[variableInfo.index].size() - 1 ? "" : ",");
            std::cout << "]\n";
            break;
        }
    }
}

void NDS::printNDL()
{
    for (std::string groupName : groupNames)
    {
        std::cout << groupName << ":\n";
        for (auto variableInfo : groupVariables[groupName])
        {
            std::cout << "\t";
            printVariable(variableInfo.second);
        }
    }
}

int getType(const std::string &type)
{
    if (type == "uint")
        return NDS::UINT;
    else if (type == "int")
        return NDS::INT;
    else if (type == "float")
        return NDS::FLOAT;
    else if (type == "double")
        return NDS::DOUBLE;
    else if (type == "string")
        return NDS::STRING;

    return -1;
}

unsigned int convertToUInt(const std::string &str)
{
    unsigned int result = 0;
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
            result = result * 10 + (c - '0');
    }
    return result;
}

int convertToInt(const std::string &str)
{
    int result = 0;
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
            result = result * 10 + (c - '0');
    }
    return result;
}

float convertToFloat(const std::string &str)
{
    float result = 0;
    int decimalIndex = str.find(".");

    if (decimalIndex == std::string::npos)
        return (float)convertToInt(str);

    int decimalPlaces = str.size() - decimalIndex - 1;
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
            result = result * 10 + (c - '0');
    }
    return result / pow(10, decimalPlaces);
}

double convertToDouble(const std::string &str)
{
    double result = 0;
    int decimalIndex = str.find(".");

    if (decimalIndex == std::string::npos)
        return (double)convertToInt(str);

    int decimalPlaces = str.size() - decimalIndex - 1;
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
            result = result * 10 + (c - '0');
    }
    return result / pow(10, decimalPlaces);
}

std::string convertToString(const std::string &str)
{
    return str.substr(str.find('"') + 1, str.size() - 2);
}

void NDS::addGroup(const std::string &groupName)
{
    groupNames.push_back(groupName);
}

void NDS::removeGroup(const std::string &groupName)
{
    groupNames.erase(std::remove(groupNames.begin(), groupNames.end(), groupName), groupNames.end());
    groupVariables.erase(groupName);
}

std::vector<std::string> NDS::getGroupNames()
{
    return groupNames;
}

void NDS::addVariable(const std::string &variableName, const std::string &groupName, unsigned int type)
{
    groupVariables[groupName][variableName] = NDSVariableInfo(variableName, variables.size(), type, false);
    variables.emplace_back();
}

void NDS::addArray(const std::string &variableName, const std::string &groupName, unsigned int type)
{
    groupVariables[groupName][variableName] = NDSVariableInfo(variableName, variableArrays.size(), type, true);
    variableArrays.emplace_back();
}

void NDS::removeVariable(const std::string &variableName, const std::string &groupName)
{
}

void NDS::removeArray(const std::string &variableName, const std::string &groupName)
{
}

void NDS::setUInt(const std::string &variableName, const std::string &groupName, unsigned int value)
{

    variables[groupVariables[groupName][variableName].index]._uint = value;
}

void NDS::setInt(const std::string &variableName, const std::string &groupName, int value)
{
    variables[groupVariables[groupName][variableName].index]._int = value;
}

void NDS::setFloat(const std::string &variableName, const std::string &groupName, float value)
{
    variables[groupVariables[groupName][variableName].index]._float = value;
}

void NDS::setDouble(const std::string &variableName, const std::string &groupName, double value)
{
    variables[groupVariables[groupName][variableName].index]._double = value;
}

void NDS::setString(const std::string &variableName, const std::string &groupName, const std::string &value)
{
    variables[groupVariables[groupName][variableName].index]._string = new std::string(value);
}

void NDS::setUIntArray(const std::string &variableName, const std::string &groupName, const std::vector<unsigned int> &values)
{
    variableArrays[groupVariables[groupName][variableName].index].clear();
    for (unsigned int value : values)
        variableArrays[groupVariables[groupName][variableName].index].emplace_back(value, UINT);
}

void NDS::setIntArray(const std::string &variableName, const std::string &groupName, const std::vector<int> &values)
{
    variableArrays[groupVariables[groupName][variableName].index].clear();
    for (int value : values)
        variableArrays[groupVariables[groupName][variableName].index].emplace_back(value, INT);
}

void NDS::setFloatArray(const std::string &variableName, const std::string &groupName, const std::vector<float> &values)
{
    variableArrays[groupVariables[groupName][variableName].index].clear();
    for (float value : values)
        variableArrays[groupVariables[groupName][variableName].index].emplace_back(value);
}

void NDS::setDoubleArray(const std::string &variableName, const std::string &groupName, const std::vector<double> &values)
{
    variableArrays[groupVariables[groupName][variableName].index].clear();
    for (double value : values)
        variableArrays[groupVariables[groupName][variableName].index].emplace_back(value);
}

void NDS::setStringArray(const std::string &variableName, const std::string &groupName, const std::vector<std::string> &values)
{
    variableArrays[groupVariables[groupName][variableName].index].clear();
    for (std::string value : values)
        variableArrays[groupVariables[groupName][variableName].index].emplace_back(value);
}

void NDS::addUIntsToArray(const std::string &variableName, const std::string &groupName, const std::vector<unsigned int> &values)
{
    for (unsigned int value : values)
        variableArrays[groupVariables[groupName][variableName].index].emplace_back(value, UINT);
}

void NDS::addIntsToArray(const std::string &variableName, const std::string &groupName, const std::vector<int> &values)
{
    for (int value : values)
        variableArrays[groupVariables[groupName][variableName].index].emplace_back(value, INT);
}

void NDS::addFloatsToArray(const std::string &variableName, const std::string &groupName, const std::vector<float> &values)
{
    for (float value : values)
        variableArrays[groupVariables[groupName][variableName].index].emplace_back(value);
}

void NDS::addDoublesToArray(const std::string &variableName, const std::string &groupName, const std::vector<double> &values)
{
    for (double value : values)
        variableArrays[groupVariables[groupName][variableName].index].emplace_back(value);
}

void NDS::addStringsToArray(const std::string &variableName, const std::string &groupName, const std::vector<std::string> &values)
{
    for (std::string value : values)
        variableArrays[groupVariables[groupName][variableName].index].emplace_back(value);
}

void NDS::addUIntToArray(const std::string &variableName, const std::string &groupName, unsigned int value)
{
    variableArrays[groupVariables[groupName][variableName].index].emplace_back(value, UINT);
}

void NDS::addIntToArray(const std::string &variableName, const std::string &groupName, int value)
{
    variableArrays[groupVariables[groupName][variableName].index].emplace_back(value, INT);
}

void NDS::addFloatToArray(const std::string &variableName, const std::string &groupName, float value)
{
    variableArrays[groupVariables[groupName][variableName].index].emplace_back(value);
}

void NDS::addDoubleToArray(const std::string &variableName, const std::string &groupName, double value)
{
    variableArrays[groupVariables[groupName][variableName].index].emplace_back(value);
}

void NDS::addStringToArray(const std::string &variableName, const std::string &groupName, const std::string &value)
{
    variableArrays[groupVariables[groupName][variableName].index].emplace_back(value);
}

unsigned int NDS::getUInt(const std::string &variableName, const std::string &groupName)
{
    return variables[groupVariables[groupName][variableName].index]._uint;
}

int NDS::getInt(const std::string &variableName, const std::string &groupName)
{
    return variables[groupVariables[groupName][variableName].index]._int;
}

float NDS::getFloat(const std::string &variableName, const std::string &groupName)
{
    return variables[groupVariables[groupName][variableName].index]._float;
}

double NDS::getDouble(const std::string &variableName, const std::string &groupName)
{
    return variables[groupVariables[groupName][variableName].index]._double;
}

std::string NDS::getString(const std::string &variableName, const std::string &groupName)
{
    return *variables[groupVariables[groupName][variableName].index]._string;
}

std::vector<unsigned int> NDS::getUIntArray(const std::string &variableName, const std::string &groupName)
{
    std::vector<unsigned int> result;
    for (NDSVariable &variable : variableArrays[groupVariables[groupName][variableName].index])
        result.push_back(variable._uint);
    return result;
}

std::vector<int> NDS::getIntArray(const std::string &variableName, const std::string &groupName)
{
    std::vector<int> result;
    for (NDSVariable &variable : variableArrays[groupVariables[groupName][variableName].index])
        result.push_back(variable._int);
    return result;
}

std::vector<float> NDS::getFloatArray(const std::string &variableName, const std::string &groupName)
{
    std::vector<float> result;
    for (NDSVariable &variable : variableArrays[groupVariables[groupName][variableName].index])
        result.push_back(variable._float);
    return result;
}

std::vector<double> NDS::getDoubleArray(const std::string &variableName, const std::string &groupName)
{
    std::vector<double> result;
    for (NDSVariable &variable : variableArrays[groupVariables[groupName][variableName].index])
        result.push_back(variable._double);
    return result;
}

std::vector<std::string> NDS::getStringArray(const std::string &variableName, const std::string &groupName)
{
    std::vector<std::string> result;
    for (NDSVariable &variable : variableArrays[groupVariables[groupName][variableName].index])
        result.push_back(*variable._string);
    return result;
}

unsigned int NDS::getUIntFromArray(const std::string &variableName, const std::string &groupName, int index)
{
    return variableArrays[groupVariables[groupName][variableName].index][index]._uint;
}

int NDS::getIntFromArray(const std::string &variableName, const std::string &groupName, int index)
{
    return variableArrays[groupVariables[groupName][variableName].index][index]._int;
}

float NDS::getFloatFromArray(const std::string &variableName, const std::string &groupName, int index)
{
    return variableArrays[groupVariables[groupName][variableName].index][index]._float;
}

double NDS::getDoubleFromArray(const std::string &variableName, const std::string &groupName, int index)
{
    return variableArrays[groupVariables[groupName][variableName].index][index]._double;
}

std::string NDS::getStringFromArray(const std::string &variableName, const std::string &groupName, int index)
{
    return *variableArrays[groupVariables[groupName][variableName].index][index]._string;
}

void NDS::clear()
{
    groupNames.clear();
    groupVariables.clear();
    variables.clear();
    variableArrays.clear();
}

void NDS::setPath(const std::string &path)
{
    this->path = path;
}

std::string NDS::getPath()
{
    return path;
}

void NDS::loadNDL()
{
    loadNDL(this->path);
}

void NDS::loadNDL(const std::string &path)
{
    std::ifstream file(path + ".ndl");

    std::string allLines = "";
    std::string line;
    while (std::getline(file, line))
    {
        bool stringMode = false;
        for (char c : line)
        {
            if (c == '#')
                break;
            if (c == '"')
                stringMode = !stringMode;
            if (c != ' ' && c != '\t' && c != '\r')
                allLines += c;
            else if (c == ' ' && stringMode)
                allLines += ' ';
        }
    }

    std::string groups;

    std::string templateGroups = "";
    size_t start, end;
    while ((start = allLines.find("<template>")) != std::string::npos &&
           (end = allLines.find("</template>")) != std::string::npos)
    {
        templateGroups += allLines.substr(start + 10, end - start - 10);
        allLines = allLines.substr(0, start) + allLines.substr(end + 11);
    }

    while ((start = allLines.find("<using:")) != std::string::npos &&
           (end = allLines.find("</using:")) != std::string::npos)
    {
        int arraySize = -1; // for syntax checking
        // thing beetwen <using: and > is used group
        std::string usedGroupName = allLines.substr(start + 7, allLines.find('>', start + 7) - start - 7);
        size_t usedGroupStart = templateGroups.find(usedGroupName + ":{");
        size_t usedGroupEnd = templateGroups.find("}", usedGroupStart);
        std::string usedGroup = templateGroups.substr(usedGroupStart + usedGroupName.size() + 2, usedGroupEnd - usedGroupStart - usedGroupName.size() - 2);
        // using group is between start and end
        std::string usingGroups = allLines.substr(allLines.find(">") + 1, end - allLines.find(">") - 1);
        while (usingGroups.size() != 0)
        {
            std::string groupName = usingGroups.substr(0, usingGroups.find(":{"));
            std::string groupData = usingGroups.substr(usingGroups.find(":{") + 2, usingGroups.find("}") - usingGroups.find(":{") - 2);
            usingGroups = usingGroups.substr(usingGroups.find("}") + 1);
            std::string usedGroupCopy = usedGroup;
            while (groupData.size() != 0)
            {
                size_t placeholder = usedGroupCopy.find("?");
                if (usedGroupCopy.find("?[") != std::string::npos && usedGroupCopy.find("?[") < placeholder + 1)
                {
                    placeholder = usedGroupCopy.find("?[");
                    size_t endPlaceholder = usedGroupCopy.find("]", placeholder);
                    arraySize = convertToInt(usedGroupCopy.substr(placeholder + 2, endPlaceholder - placeholder - 2));
                    usedGroupCopy = usedGroupCopy.substr(0, placeholder) + "?" + usedGroupCopy.substr(endPlaceholder + 1);
                }
                size_t valueSeparator = groupData.find(";");
                if (valueSeparator == std::string::npos)
                    valueSeparator = groupData.size();
                std::string value = groupData.substr(0, valueSeparator);
                groupData = groupData.substr(valueSeparator + 1 < groupData.size() ? valueSeparator + 1 : groupData.size());
                usedGroupCopy = usedGroupCopy.substr(0, placeholder) + value + usedGroupCopy.substr(placeholder + 1);
            }
            groups += groupName + ":{" + usedGroupCopy + "}";
        }

        allLines = allLines.substr(0, start) + allLines.substr(end + 8 + usedGroupName.size() + 1);
    }

    groups += allLines;

    while (groups != "")
    {
        size_t groupStart = groups.find(":{");
        size_t groupEnd = groups.find("}");
        std::string groupName = groups.substr(0, groupStart);
        std::string groupData = groups.substr(groupStart + 2, groupEnd - groupStart - 2);
        groups = groups.substr(groupEnd + 1);

        addGroup(groupName);

        while (groupData != "")
        {
            bool isArray = false;
            std::string variableType = groupData.substr(0, groupData.find(":"));
            if (variableType.find("[]") != std::string::npos)
            {
                isArray = true;
                variableType = variableType.substr(0, variableType.size() - 2);
            }

            size_t variableNameStart = groupData.find(":") + 1;
            size_t variableNameEnd = groupData.find("=");
            std::string variableName = groupData.substr(variableNameStart, variableNameEnd - variableNameStart);
            size_t variableValueStart = groupData.find("=") + 1;
            size_t variableValueEnd = groupData.find(";", variableValueStart);
            std::string variableValue = groupData.substr(variableValueStart, variableValueEnd - variableValueStart);

            if (variableValue == "?")
            {
                groupData = groupData.substr(variableValueEnd + 1);
                continue;
            }

            if (!isArray)
            {

                if (variableType == "uint")
                {
                    addVariable(variableName, groupName, UINT);
                    setUInt(variableName, groupName, convertToUInt(variableValue));
                }
                else if (variableType == "int")
                {
                    addVariable(variableName, groupName, INT);
                    setInt(variableName, groupName, convertToInt(variableValue));
                }
                else if (variableType == "float")
                {
                    addVariable(variableName, groupName, FLOAT);
                    setFloat(variableName, groupName, convertToFloat(variableValue));
                }
                else if (variableType == "double")
                {
                    addVariable(variableName, groupName, DOUBLE);
                    setDouble(variableName, groupName, convertToDouble(variableValue));
                }
                else if (variableType == "string")
                {
                    addVariable(variableName, groupName, STRING);
                    setString(variableName, groupName, convertToString(variableValue));
                }
            }
            else
            {
                variableValue = variableValue.substr(1, variableValue.find("]") - 1);
                std::vector<std::string> values;
                if (variableValue.find(",") == std::string::npos)
                    values.push_back(variableValue);
                else
                {
                    while (variableValue != "")
                    {
                        size_t separator = variableValue.find(",");
                        if (separator == std::string::npos)
                            separator = variableValue.size();
                        values.push_back(variableValue.substr(0, separator));
                        variableValue = variableValue.substr(separator + 1 < variableValue.size() ? separator + 1 : variableValue.size());
                    }
                }

                if (variableType == "uint")
                {
                    addArray(variableName, groupName, UINT);
                    for (std::string &value : values)
                        addUIntToArray(variableName, groupName, convertToUInt(value));
                }
                else if (variableType == "int")
                {
                    addArray(variableName, groupName, INT);
                    for (std::string &value : values)
                        addIntToArray(variableName, groupName, convertToInt(value));
                }
                else if (variableType == "float")
                {
                    addArray(variableName, groupName, FLOAT);
                    for (std::string &value : values)
                        addFloatToArray(variableName, groupName, convertToFloat(value));
                }
                else if (variableType == "double")
                {
                    addArray(variableName, groupName, DOUBLE);
                    for (std::string &value : values)
                        addDoubleToArray(variableName, groupName, convertToDouble(value));
                }
                else if (variableType == "string")
                {
                    addArray(variableName, groupName, STRING);
                    for (std::string &value : values)
                        addStringToArray(variableName, groupName, convertToString(value));
                }
            }
            groupData = groupData.substr(variableValueEnd + 1);
        }
    }
    file.close();
}

void NDS::saveNDL()
{
    saveNDL(this->path);
}

void NDS::saveNDL(const std::string &path)
{
    std::ofstream file(path + ".ndl");

    for (std::string groupName : groupNames)
    {
        file << groupName << ":{\n";
        for (auto variableInfo : groupVariables[groupName])
        {
            file << "\t";
            if (!variableInfo.second.isArray)
            {
                switch (variableInfo.second.type)
                {
                case INT:
                    file << "int:" << variableInfo.first << "=" << variables[variableInfo.second.index]._int << ";\n";
                    break;
                case UINT:
                    file << "uint:" << variableInfo.first << "=" << variables[variableInfo.second.index]._uint << ";\n";
                    break;
                case FLOAT:
                    file << "float:" << variableInfo.first << "=" << variables[variableInfo.second.index]._float << ";\n";
                    break;
                case DOUBLE:
                    file << "double:" << variableInfo.first << "=" << variables[variableInfo.second.index]._double << ";\n";
                    break;
                case STRING:
                    file << "string:" << variableInfo.first << "=\"" << *variables[variableInfo.second.index]._string << "\";\n";
                    break;
                }
            }
            else
            {
                switch (variableInfo.second.type)
                {
                case INT:
                    file << "int[]:" << variableInfo.first << "=[";
                    for (int i = 0; i < variableArrays[variableInfo.second.index].size(); i++)
                        file << variableArrays[variableInfo.second.index][i]._int << (i == variableArrays[variableInfo.second.index].size() - 1 ? "" : ",");
                    file << "];";
                    break;
                case UINT:
                    file << "uint[]:" << variableInfo.first << "=[";
                    for (int i = 0; i < variableArrays[variableInfo.second.index].size(); i++)
                        file << variableArrays[variableInfo.second.index][i]._uint << (i == variableArrays[variableInfo.second.index].size() - 1 ? "" : ",");
                    file << "];";
                    break;
                case FLOAT:
                    file << "float[]:" << variableInfo.first << "=[";
                    for (int i = 0; i < variableArrays[variableInfo.second.index].size(); i++)
                        file << variableArrays[variableInfo.second.index][i]._float << (i == variableArrays[variableInfo.second.index].size() - 1 ? "" : ",");
                    file << "];";
                    break;
                case DOUBLE:
                    file << "double[]:" << variableInfo.first << "=[";
                    for (int i = 0; i < variableArrays[variableInfo.second.index].size(); i++)
                        file << variableArrays[variableInfo.second.index][i]._double << (i == variableArrays[variableInfo.second.index].size() - 1 ? "" : ",");
                    file << "];";
                    break;
                case STRING:
                    file << "string[]:" << variableInfo.first << "=[";
                    for (int i = 0; i < variableArrays[variableInfo.second.index].size(); i++)
                        file << "\"" << *variableArrays[variableInfo.second.index][i]._string << "\"" << (i == variableArrays[variableInfo.second.index].size() - 1 ? "" : ",");
                    file << "];";
                    break;
                }

                file << "\n";
            }
        }
        file << "}\n\n";
    }
    file.close();
}