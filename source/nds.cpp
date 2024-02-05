#include "../include/nds.h"

NDS::NDS(std::string path)
{
    this->path = path;
}

void NDS::printNDL()
{
    int groupIndex = -1;
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) != groupIndex)
        {
            groupIndex = std::get<0>(data);
            std::cout << groupNames[groupIndex] << ":\n";
        }
        switch (std::get<2>(data))
        {
        case 0:
            std::cout << "int;" << std::get<1>(data) << ":" << ints[std::get<3>(data)] << "\n";
            break;
        case 1:
            std::cout << "uint;" << std::get<1>(data) << ":" << uints[std::get<3>(data)] << "\n";
            break;
        case 2:
            std::cout << "float;" << std::get<1>(data) << ":" << floats[std::get<3>(data)] << "\n";
            break;
        case 3:
            std::cout << "double;" << std::get<1>(data) << ":" << doubles[std::get<3>(data)] << "\n";
            break;
        case 4:
            std::cout << "string;" << std::get<1>(data) << ":" << strings[std::get<3>(data)] << "\n";
            break;
        case 10:
            std::cout << "int[];" << std::get<1>(data) << ":[" << intLists[std::get<3>(data)][0];
            for (int i = 1; i < intLists[std::get<3>(data)].size(); i++)
                std::cout << "," << intLists[std::get<3>(data)][i];
            std::cout << "]\n";
            break;
        case 11:
            std::cout << "uint[];" << std::get<1>(data) << ":[" << uintLists[std::get<3>(data)][0];
            for (int i = 1; i < uintLists[std::get<3>(data)].size(); i++)
                std::cout << "," << uintLists[std::get<3>(data)][i];
            std::cout << "]\n";
            break;
        case 12:
            std::cout << "float[];" << std::get<1>(data) << ":[" << floatLists[std::get<3>(data)][0];
            for (int i = 1; i < floatLists[std::get<3>(data)].size(); i++)
                std::cout << "," << floatLists[std::get<3>(data)][i];
            std::cout << "]\n";
            break;
        case 13:
            std::cout << "double[];" << std::get<1>(data) << ":[" << doubleLists[std::get<3>(data)][0];
            for (int i = 1; i < doubleLists[std::get<3>(data)].size(); i++)
                std::cout << "," << doubleLists[std::get<3>(data)][i];
            std::cout << "]\n";
            break;
        case 14:
            std::cout << "string[];" << std::get<1>(data) << ":[" << stringLists[std::get<3>(data)][0];
            for (int i = 1; i < stringLists[std::get<3>(data)].size(); i++)
                std::cout << "," << stringLists[std::get<3>(data)][i];
            std::cout << "]\n";
            break;
        }
    }
}

int getType(std::string type)
{
    if (type == "int")
        return 0;
    else if (type == "uint")
        return 1;
    else if (type == "float")
        return 2;
    else if (type == "double")
        return 3;
    else
        return 4;
}

unsigned int convertToUInt(std::string str)
{
    unsigned int result = 0;
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
            result = result * 10 + (c - '0');
    }
    return result;
}

int convertToInt(std::string str)
{
    int result = 0;
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
            result = result * 10 + (c - '0');
    }
    return result;
}

float convertToFloat(std::string str)
{
    float result = 0;
    int decimalIndex = str.find(".");
    int decimalPlaces = str.size() - decimalIndex - 1;
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
            result = result * 10 + (c - '0');
    }
    return result / pow(10, decimalPlaces);
}

double convertToDouble(std::string str)
{
    double result = 0;
    int decimalIndex = str.find(".");
    int decimalPlaces = str.size() - decimalIndex - 1;
    for (char c : str)
    {
        if (c >= '0' && c <= '9')
            result = result * 10 + (c - '0');
    }
    return result / pow(10, decimalPlaces);
}

std::string convertToString(std::string str)
{
    return str.substr(str.find('"') + 1, str.size() - 2);
}

void NDS::loadNDL()
{
    loadNDL(this->path);
}

void NDS::loadNDL(std::string path)
{
    std::ifstream file(path);
    std::vector<std::string> alllines;
    std::string line;
    std::string lineParsed;

    bool inString = false;
    while (std::getline(file, line))
    {
        for (char c : line)
        {
            if (c == '"')
                inString = !inString;
            if (c == '#')
                break;
            else if (c != ' ' || inString)
                lineParsed += c;
        }
        inString = false;
        if (lineParsed != "")
        {
            alllines.push_back(lineParsed);
            lineParsed = "";
        }
    }

    int groupIndex = 0;
    int type = -1;
    bool isList = false;
    for (std::string l : alllines)
    {
        if (l.find("{") != std::string::npos)
        {
            groupNames.push_back(l.substr(0, l.find(":")));
            continue;
        }
        if (l.find("}") != std::string::npos)
        {
            groupIndex++;
            continue;
        }

        std::string typeStr = l.substr(0, l.find(";"));

        if (typeStr.find("[") != std::string::npos)
        {
            isList = true;
            typeStr = typeStr.substr(0, typeStr.find("["));
        }
        else
            isList = false;

        type = getType(typeStr);

        std::string variableName = l.substr(l.find(";") + 1, l.find(":") - l.find(";") - 1);

        if (isList)
        {
            std::string str = l.substr(l.find("[") + 1, l.size());
            str = str.substr(str.find("[") + 1, str.size());
            switch (type)
            {
            case 0:
                intLists.push_back(std::vector<int>());
                groupVariableData.push_back(std::make_tuple(groupIndex, variableName, type + 10, intLists.size() - 1));
                while (true)
                {
                    intLists[intLists.size() - 1].push_back(convertToInt(str.substr(0, str.find(","))));
                    str = str.substr(str.find(",") + 1, str.size());
                    if (str.find(",") == std::string::npos)
                    {
                        str = str.substr(0, str.size() - 1);
                        intLists[intLists.size() - 1].push_back(convertToInt(str));
                        break;
                    }
                }
                break;
            case 1:
                uintLists.push_back(std::vector<unsigned int>());
                groupVariableData.push_back(std::make_tuple(groupIndex, variableName, type + 10, uintLists.size() - 1));
                while (true)
                {
                    uintLists[uintLists.size() - 1].push_back(convertToUInt(str.substr(0, str.find(","))));
                    str = str.substr(str.find(",") + 1, str.size());
                    if (str.find(",") == std::string::npos)
                    {
                        str = str.substr(0, str.size() - 1);
                        uintLists[uintLists.size() - 1].push_back(convertToUInt(str));
                        break;
                    }
                }
                break;
            case 2:
                floatLists.push_back(std::vector<float>());
                groupVariableData.push_back(std::make_tuple(groupIndex, variableName, type + 10, floatLists.size() - 1));
                while (true)
                {
                    floatLists[floatLists.size() - 1].push_back(convertToFloat(str.substr(0, str.find(","))));
                    str = str.substr(str.find(",") + 1, str.size());
                    if (str.find(",") == std::string::npos)
                    {
                        str = str.substr(0, str.size() - 1);
                        floatLists[floatLists.size() - 1].push_back(convertToFloat(str));
                        break;
                    }
                }
                break;
            case 3:
                doubleLists.push_back(std::vector<double>());
                groupVariableData.push_back(std::make_tuple(groupIndex, variableName, type + 10, doubleLists.size() - 1));
                while (true)
                {
                    doubleLists[doubleLists.size() - 1].push_back(convertToDouble(str.substr(0, str.find(","))));
                    str = str.substr(str.find(",") + 1, str.size());
                    if (str.find(",") == std::string::npos)
                    {
                        str = str.substr(0, str.size() - 1);
                        doubleLists[doubleLists.size() - 1].push_back(convertToDouble(str));
                        break;
                    }
                }
                break;
            case 4:
                stringLists.push_back(std::vector<std::string>());
                groupVariableData.push_back(std::make_tuple(groupIndex, variableName, type + 10, stringLists.size() - 1));
                while (true)
                {
                    stringLists[stringLists.size() - 1].push_back(convertToString(str.substr(0, str.find(","))));
                    str = str.substr(str.find(",") + 1, str.size());
                    if (str.find(",") == std::string::npos)
                    {
                        str = str.substr(0, str.size() - 1);
                        stringLists[stringLists.size() - 1].push_back(convertToString(str));
                        break;
                    }
                }
                break;
            }
        }
        else
        {
            std::string str = l.substr(l.find(":") + 1, l.size());
            switch (type)
            {
            case 0:
                ints.push_back(convertToInt(str));
                groupVariableData.push_back(std::make_tuple(groupIndex, variableName, type, ints.size() - 1));
                break;
            case 1:
                uints.push_back(convertToUInt(str));
                groupVariableData.push_back(std::make_tuple(groupIndex, variableName, type, uints.size() - 1));
                break;
            case 2:
                floats.push_back(convertToFloat(str));
                groupVariableData.push_back(std::make_tuple(groupIndex, variableName, type, floats.size() - 1));
                break;
            case 3:
                doubles.push_back(convertToDouble(str));
                groupVariableData.push_back(std::make_tuple(groupIndex, variableName, type, doubles.size() - 1));
                break;
            case 4:
                strings.push_back(convertToString(str));
                groupVariableData.push_back(std::make_tuple(groupIndex, variableName, type, strings.size() - 1));
                break;
            }
        }
    }

    file.close();
}

void NDS::saveNDL()
{
    saveNDL(this->path);
}

void NDS::saveNDL(std::string path)
{
    std::ofstream file(path);
    for (int i = 0; i < groupNames.size(); i++)
    {
        file << groupNames[i] << ":{\n";
        for (std::tuple<int, std::string, int, int> data : groupVariableData)
        {
            if (std::get<0>(data) == i)
            {
                switch (std::get<2>(data))
                {
                case 0:
                    file << "\tint;" << std::get<1>(data) << ":" << ints[std::get<3>(data)] << "\n";
                    break;
                case 1:
                    file << "\tuint;" << std::get<1>(data) << ":" << uints[std::get<3>(data)] << "\n";
                    break;
                case 2:
                    file << "\tfloat;" << std::get<1>(data) << ":" << floats[std::get<3>(data)] << "\n";
                    break;
                case 3:
                    file << "\tdouble;" << std::get<1>(data) << ":" << doubles[std::get<3>(data)] << "\n";
                    break;
                case 4:
                    file << "\tstring;" << std::get<1>(data) << ":\"" << strings[std::get<3>(data)] << "\"\n";
                    break;
                case 10:
                    file << "\tint[];" << std::get<1>(data) << ":[" << intLists[std::get<3>(data)][0];
                    for (int i = 1; i < intLists[std::get<3>(data)].size(); i++)
                        file << "," << intLists[std::get<3>(data)][i];
                    file << "]\n";
                    break;
                case 11:
                    file << "\tuint[];" << std::get<1>(data) << ":[" << uintLists[std::get<3>(data)][0];
                    for (int i = 1; i < uintLists[std::get<3>(data)].size(); i++)
                        file << "," << uintLists[std::get<3>(data)][i];
                    file << "]\n";
                    break;
                case 12:
                    file << "\tfloat[];" << std::get<1>(data) << ":[" << floatLists[std::get<3>(data)][0];
                    for (int i = 1; i < floatLists[std::get<3>(data)].size(); i++)
                        file << "," << floatLists[std::get<3>(data)][i];
                    file << "]\n";
                    break;
                case 13:
                    file << "\tdouble[];" << std::get<1>(data) << ":[" << doubleLists[std::get<3>(data)][0];
                    for (int i = 1; i < doubleLists[std::get<3>(data)].size(); i++)
                        file << "," << doubleLists[std::get<3>(data)][i];
                    file << "]\n";
                    break;
                case 14:
                    file << "\tstring[];" << std::get<1>(data) << ":[\"" << stringLists[std::get<3>(data)][0] << "\"";
                    for (int i = 1; i < stringLists[std::get<3>(data)].size(); i++)
                        file << ",\"" << stringLists[std::get<3>(data)][i] << "\"";
                    file << "]\n";
                    break;
                }
            }
        }
        file << "}\n\n";
    }
    file.close();
}

int NDS::getInt(std::string variableName, std::string groupName)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 0)
            return ints[std::get<3>(data)];
    }
    return 0;
}

unsigned int NDS::getUInt(std::string variableName, std::string groupName)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 1)
            return uints[std::get<3>(data)];
    }
    return 0;
}

float NDS::getFloat(std::string variableName, std::string groupName)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 2)
            return floats[std::get<3>(data)];
    }
    return 0;
}

double NDS::getDouble(std::string variableName, std::string groupName)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 3)
            return doubles[std::get<3>(data)];
    }
    return 0;
}

std::string NDS::getString(std::string variableName, std::string groupName)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 4)
            return strings[std::get<3>(data)];
    }
    return "";
}

std::vector<int> NDS::getIntList(std::string variableName, std::string groupName)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 10)
            return intLists[std::get<3>(data)];
    }
    return std::vector<int>();
}

std::vector<unsigned int> NDS::getUIntList(std::string variableName, std::string groupName)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 11)
            return uintLists[std::get<3>(data)];
    }
    return std::vector<unsigned int>();
}

std::vector<float> NDS::getFloatList(std::string variableName, std::string groupName)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 12)
            return floatLists[std::get<3>(data)];
    }
    return std::vector<float>();
}

std::vector<double> NDS::getDoubleList(std::string variableName, std::string groupName)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 13)
            return doubleLists[std::get<3>(data)];
    }
    return std::vector<double>();
}

std::vector<std::string> NDS::getStringList(std::string variableName, std::string groupName)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 14)
            return stringLists[std::get<3>(data)];
    }
    return std::vector<std::string>();
}

std::vector<std::string> NDS::getGroupNames()
{
    return groupNames;
}

std::vector<std::tuple<int, std::string, int, int>> NDS::getGroupVariableData()
{
    return groupVariableData;
}

std::vector<int> NDS::getInts()
{
    return ints;
}

std::vector<unsigned int> NDS::getUInts()
{
    return uints;
}

std::vector<float> NDS::getFloats()
{
    return floats;
}

std::vector<double> NDS::getDoubles()
{
    return doubles;
}

std::vector<std::string> NDS::getStrings()
{
    return strings;
}

std::vector<std::vector<int>> NDS::getIntLists()
{
    return intLists;
}

std::vector<std::vector<unsigned int>> NDS::getUIntLists()
{
    return uintLists;
}

std::vector<std::vector<float>> NDS::getFloatLists()
{
    return floatLists;
}

std::vector<std::vector<double>> NDS::getDoubleLists()
{
    return doubleLists;
}

std::vector<std::vector<std::string>> NDS::getStringLists()
{
    return stringLists;
}

void NDS::setInt(std::string variableName, std::string groupName, int value)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 0)
        {
            ints[std::get<3>(data)] = value;
            return;
        }
    }
}

void NDS::setUInt(std::string variableName, std::string groupName, unsigned int value)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 1)
        {
            uints[std::get<3>(data)] = value;
            return;
        }
    }
}

void NDS::setFloat(std::string variableName, std::string groupName, float value)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 2)
        {
            floats[std::get<3>(data)] = value;
            return;
        }
    }
}

void NDS::setDouble(std::string variableName, std::string groupName, double value)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 3)
        {
            doubles[std::get<3>(data)] = value;
            return;
        }
    }
}

void NDS::setString(std::string variableName, std::string groupName, std::string value)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 4)
        {
            strings[std::get<3>(data)] = value;
            return;
        }
    }
}

void NDS::setIntList(std::string variableName, std::string groupName, std::vector<int> value)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 10)
        {
            intLists[std::get<3>(data)] = value;
            return;
        }
    }
}

void NDS::setUIntList(std::string variableName, std::string groupName, std::vector<unsigned int> value)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 11)
        {
            uintLists[std::get<3>(data)] = value;
            return;
        }
    }
}

void NDS::setFloatList(std::string variableName, std::string groupName, std::vector<float> value)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 12)
        {
            floatLists[std::get<3>(data)] = value;
            return;
        }
    }
}

void NDS::setDoubleList(std::string variableName, std::string groupName, std::vector<double> value)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 13)
        {
            doubleLists[std::get<3>(data)] = value;
            return;
        }
    }
}

void NDS::setStringList(std::string variableName, std::string groupName, std::vector<std::string> value)
{
    for (std::tuple<int, std::string, int, int> data : groupVariableData)
    {
        if (std::get<0>(data) == std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)) && std::get<1>(data) == variableName && std::get<2>(data) == 14)
        {
            stringLists[std::get<3>(data)] = value;
            return;
        }
    }
}

void NDS::addGroup(std::string groupName)
{
    groupNames.push_back(groupName);
}

void NDS::removeGroup(std::string groupName)
{
    int groupIndex = std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName));
    groupNames.erase(groupNames.begin() + groupIndex);
    for (int i = 0; i < groupVariableData.size(); i++)
    {
        if (std::get<0>(groupVariableData[i]) == groupIndex)
        {
            groupVariableData.erase(groupVariableData.begin() + i);
            i--;
        }
    }
}

void NDS::clearGroup(std::string groupName)
{
    int groupIndex = std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName));
    for (int i = 0; i < groupVariableData.size(); i++)
    {
        if (std::get<0>(groupVariableData[i]) == groupIndex)
        {
            groupVariableData.erase(groupVariableData.begin() + i);
            i--;
        }
    }
}

void NDS::addVariable(std::string variableName, std::string groupName, int variableType)
{
    groupVariableData.push_back(std::make_tuple(std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName)), variableName, variableType, -1));

    switch (variableType)
    {
    case 0:
        ints.push_back(0);
        groupVariableData[groupVariableData.size() - 1] = std::make_tuple(std::get<0>(groupVariableData[groupVariableData.size() - 1]), std::get<1>(groupVariableData[groupVariableData.size() - 1]), std::get<2>(groupVariableData[groupVariableData.size() - 1]), ints.size() - 1);
        break;
    case 1:
        uints.push_back(0);
        groupVariableData[groupVariableData.size() - 1] = std::make_tuple(std::get<0>(groupVariableData[groupVariableData.size() - 1]), std::get<1>(groupVariableData[groupVariableData.size() - 1]), std::get<2>(groupVariableData[groupVariableData.size() - 1]), uints.size() - 1);
        break;
    case 2:
        floats.push_back(0);
        groupVariableData[groupVariableData.size() - 1] = std::make_tuple(std::get<0>(groupVariableData[groupVariableData.size() - 1]), std::get<1>(groupVariableData[groupVariableData.size() - 1]), std::get<2>(groupVariableData[groupVariableData.size() - 1]), floats.size() - 1);
        break;
    case 3:
        doubles.push_back(0);
        groupVariableData[groupVariableData.size() - 1] = std::make_tuple(std::get<0>(groupVariableData[groupVariableData.size() - 1]), std::get<1>(groupVariableData[groupVariableData.size() - 1]), std::get<2>(groupVariableData[groupVariableData.size() - 1]), doubles.size() - 1);
        break;
    case 4:
        strings.push_back("");
        groupVariableData[groupVariableData.size() - 1] = std::make_tuple(std::get<0>(groupVariableData[groupVariableData.size() - 1]), std::get<1>(groupVariableData[groupVariableData.size() - 1]), std::get<2>(groupVariableData[groupVariableData.size() - 1]), strings.size() - 1);
        break;
    case 10:
        intLists.push_back(std::vector<int>());
        groupVariableData[groupVariableData.size() - 1] = std::make_tuple(std::get<0>(groupVariableData[groupVariableData.size() - 1]), std::get<1>(groupVariableData[groupVariableData.size() - 1]), std::get<2>(groupVariableData[groupVariableData.size() - 1]), intLists.size() - 1);
        break;
    case 11:
        uintLists.push_back(std::vector<unsigned int>());
        groupVariableData[groupVariableData.size() - 1] = std::make_tuple(std::get<0>(groupVariableData[groupVariableData.size() - 1]), std::get<1>(groupVariableData[groupVariableData.size() - 1]), std::get<2>(groupVariableData[groupVariableData.size() - 1]), uintLists.size() - 1);
        break;
    case 12:
        floatLists.push_back(std::vector<float>());
        groupVariableData[groupVariableData.size() - 1] = std::make_tuple(std::get<0>(groupVariableData[groupVariableData.size() - 1]), std::get<1>(groupVariableData[groupVariableData.size() - 1]), std::get<2>(groupVariableData[groupVariableData.size() - 1]), floatLists.size() - 1);
        break;
    case 13:
        doubleLists.push_back(std::vector<double>());
        groupVariableData[groupVariableData.size() - 1] = std::make_tuple(std::get<0>(groupVariableData[groupVariableData.size() - 1]), std::get<1>(groupVariableData[groupVariableData.size() - 1]), std::get<2>(groupVariableData[groupVariableData.size() - 1]), doubleLists.size() - 1);
        break;
    case 14:
        stringLists.push_back(std::vector<std::string>());
        groupVariableData[groupVariableData.size() - 1] = std::make_tuple(std::get<0>(groupVariableData[groupVariableData.size() - 1]), std::get<1>(groupVariableData[groupVariableData.size() - 1]), std::get<2>(groupVariableData[groupVariableData.size() - 1]), stringLists.size() - 1);
        break;
    }
}

void NDS::removeVariable(std::string variableName, std::string groupName)
{
    int groupIndex = std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName));
    for (int i = 0; i < groupVariableData.size(); i++)
    {
        if (std::get<0>(groupVariableData[i]) == groupIndex && std::get<1>(groupVariableData[i]) == variableName)
        {
            switch (std::get<2>(groupVariableData[i]))
            {
            case 0:
                ints.erase(ints.begin() + std::get<3>(groupVariableData[i]));
                break;
            case 1:
                uints.erase(uints.begin() + std::get<3>(groupVariableData[i]));
                break;
            case 2:
                floats.erase(floats.begin() + std::get<3>(groupVariableData[i]));
                break;
            case 3:
                doubles.erase(doubles.begin() + std::get<3>(groupVariableData[i]));
                break;
            case 4:
                strings.erase(strings.begin() + std::get<3>(groupVariableData[i]));
                break;
            case 10:
                intLists.erase(intLists.begin() + std::get<3>(groupVariableData[i]));
                break;
            case 11:
                uintLists.erase(uintLists.begin() + std::get<3>(groupVariableData[i]));
                break;
            case 12:
                floatLists.erase(floatLists.begin() + std::get<3>(groupVariableData[i]));
                break;
            case 13:
                doubleLists.erase(doubleLists.begin() + std::get<3>(groupVariableData[i]));
                break;
            case 14:
                stringLists.erase(stringLists.begin() + std::get<3>(groupVariableData[i]));
                break;
            }
            groupVariableData.erase(groupVariableData.begin() + i);
            i--;
        }
    }
}

void NDS::clearVariable(std::string variableName, std::string groupName)
{
    int groupIndex = std::distance(groupNames.begin(), std::find(groupNames.begin(), groupNames.end(), groupName));
    for (int i = 0; i < groupVariableData.size(); i++)
    {
        if (std::get<0>(groupVariableData[i]) == groupIndex && std::get<1>(groupVariableData[i]) == variableName)
        {
            switch (std::get<2>(groupVariableData[i]))
            {
            case 0:
                ints[std::get<3>(groupVariableData[i])] = 0;
                break;
            case 1:
                uints[std::get<3>(groupVariableData[i])] = 0;
                break;
            case 2:
                floats[std::get<3>(groupVariableData[i])] = 0;
                break;
            case 3:
                doubles[std::get<3>(groupVariableData[i])] = 0;
                break;
            case 4:
                strings[std::get<3>(groupVariableData[i])] = "";
                break;
            case 10:
                intLists[std::get<3>(groupVariableData[i])] = std::vector<int>();
                break;
            case 11:
                uintLists[std::get<3>(groupVariableData[i])] = std::vector<unsigned int>();
                break;
            case 12:
                floatLists[std::get<3>(groupVariableData[i])] = std::vector<float>();
                break;
            case 13:
                doubleLists[std::get<3>(groupVariableData[i])] = std::vector<double>();
                break;
            case 14:
                stringLists[std::get<3>(groupVariableData[i])] = std::vector<std::string>();
                break;
            }
        }
    }
}

void NDS::clearAll()
{
    ints.clear();
    uints.clear();
    floats.clear();
    doubles.clear();
    strings.clear();
    intLists.clear();
    uintLists.clear();
    floatLists.clear();
    doubleLists.clear();
    stringLists.clear();
    groupVariableData.clear();
    groupNames.clear();
}

void NDS::setPath(std::string path)
{
    this->path = path;
}

std::string NDS::getPath()
{
    return this->path;
}