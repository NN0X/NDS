#include "../include/nds.h"

NDS::NDS(std::string path)
{
    this->path = path;
}

void NDS::loadNDL()
{
    std::ifstream ndlFile;
    std::string line;

    ndlFile.open(path);

    bool inString = false;
    bool inGroup = false;
    int groupIndex = 0;
    std::string token = "";
    while (std::getline(ndlFile, line))
    {
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == '#')
                break;
            if (line[i] == '"')
                inString = !inString;
            if (line[i] != ' ' || inString == true)
                token += line[i];
        }

        if (inString == true)
        {
            continue;
        }

        std::string variableValue = "";
        int type = -2;

        if (token.find("int;") != -1)
            type = 0;
        else if (token.find("uint;") != -1)
            type = 1;
        else if (token.find("float;") != -1)
            type = 2;
        else if (token.find("double;") != -1)
            type = 3;
        else if (token.find("string;") != -1)
            type = 4;
        else if (int find = token.find(":{") != -1)
        {
            groups.push_back(token.substr(0, token.length() - 2));
            groupsIndex.push_back(std::vector<int>());
            inGroup = true;
        }
        else if (token.find("}") != -1 && inGroup == true)
        {
            inGroup = false;
            groupIndex++;
        }
        else if (token.find("::") != -1)
            type = -1;
        if (int find = token.find(":") != -1)
        {
            std::cout << find << "\n";
            variables.push_back(token.substr(0, find - 1));
            if (find != line.length())
                variableValue = token.substr(find + 1, line.length() - 1);
        }

        if (inGroup == true)
        {
            int loops = 0;
            if (token.find(',') != -1)
            {
                for (char ch : token)
                {
                    if (ch == ',')
                        loops++;
                }
            }
            do
            {
                if (type == -1)
                {
                }
                else if (type == 0)
                {
                    try
                    {
                        ints.push_back(std::stoi(variableValue));
                        groupsIndex[groupIndex].push_back(variables.size() - 1);
                        variableIndex.push_back(std::pair<int, int>(0, ints.size() - 1));
                    }
                    catch (...)
                    {
                        std::cerr << "Value is not an integer\n";
                    }
                }
                else if (type == 1)
                {
                    try
                    {
                        uints.push_back(std::stoul(variableValue));
                        groupsIndex[groupIndex].push_back(variables.size() - 1);
                        variableIndex.push_back(std::pair<int, int>(1, uints.size() - 1));
                    }
                    catch (...)
                    {
                        std::cerr << "Value is not an unsigned integer\n";
                    }
                }
                else if (type == 2)
                {
                    try
                    {
                        floats.push_back(std::stof(variableValue));
                        groupsIndex[groupIndex].push_back(variables.size() - 1);
                        variableIndex.push_back(std::pair<int, int>(2, floats.size() - 1));
                    }
                    catch (...)
                    {
                        std::cerr << "Value is not a float\n";
                    }
                }
                else if (type == 3)
                {
                    try
                    {
                        doubles.push_back(std::stod(variableValue));
                        groupsIndex[groupIndex].push_back(variables.size() - 1);
                        variableIndex.push_back(std::pair<int, int>(3, doubles.size() - 1));
                    }
                    catch (...)
                    {
                        std::cerr << variableValue << " Value is not a double\n";
                    }
                }
                else if (type == 4)
                {
                }
                else if (variableValue.find('"') != -1)
                {
                    strings.push_back(variableValue.substr(1, variableValue.length() - 2));
                    groupsIndex[groupIndex].push_back(variables.size() - 1);
                    variableIndex.push_back(std::pair<int, int>(4, strings.size() - 1));
                }
                else
                {
                    try
                    {
                        ints.push_back(std::stoi(variableValue));
                        groupsIndex[groupIndex].push_back(variables.size() - 1);
                        variableIndex.push_back(std::pair<int, int>(0, ints.size() - 1));
                        break;
                    }
                    catch (...)
                    {
                    }
                    try
                    {
                        floats.push_back(std::stof(variableValue));
                        groupsIndex[groupIndex].push_back(variables.size() - 1);
                        variableIndex.push_back(std::pair<int, int>(2, floats.size() - 1));
                        break;
                    }
                    catch (...)
                    {
                    }
                    try
                    {
                        doubles.push_back(std::stod(variableValue));
                        groupsIndex[groupIndex].push_back(variables.size() - 1);
                        variableIndex.push_back(std::pair<int, int>(3, doubles.size() - 1));
                        break;
                    }
                    catch (...)
                    {
                    }
                    strings.push_back(variableValue.substr(1, variableValue.length() - 2));
                    groupsIndex[groupIndex].push_back(variables.size() - 1);
                    variableIndex.push_back(std::pair<int, int>(4, strings.size() - 1));
                }
                loops--;
            } while (loops > 0);
        }
        token = "";
    }

    if (inString == true)
    {
        std::cerr << "String not closed\n";
        return;
    }
}