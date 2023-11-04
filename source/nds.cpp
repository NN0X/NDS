#include "../include/nds.h"

NDS::NDS(std::string path)
{
    this->path = path;
}

void NDS::loadNDL()
{
    std::ifstream ndlFile;
    ndlFile.open(path);

    std::string lines = "";
    std::string line = "";
    int type = -1;
    bool inGroup = false;
    bool inList = false;
    while (getline(ndlFile, line))
    {
        if (line.find('#') != -1)
            line = line.substr(0, line.find('#'));
        if (line == "" || line == " ")
            continue;

        if (line.find(":{") != -1 && inGroup == false)
        {
            groups.push_back(line.substr(0, line.find(":{")));
            // std::cout << "Group: " << groups.back() << std::endl;
            inGroup = true;
            continue;
        }

        if (line.find("}") != -1)
        {
            inGroup = false;
            continue;
        }

        if (line.find(";") != -1 && inGroup == true && inList == false)
        {
            std::string typeString = line.substr(0, line.find(";"));
            typeString.erase(std::remove_if(typeString.begin(), typeString.end(), isspace), typeString.end());
            if (typeString == "int")
            {
                type = 0;
                line = line.substr(line.find(";") + 1);
            }
            else if (typeString == "uint")
            {
                type = 1;
                line = line.substr(line.find(";") + 1);
            }
            else if (typeString == "float")
            {
                type = 2;
                line = line.substr(line.find(";") + 1);
            }
            else if (typeString == "double")
            {
                type = 3;
                line = line.substr(line.find(";") + 1);
            }
            else if (typeString == "string")
            {
                type = 4;
                line = line.substr(line.find(";") + 1);
            }
            else
                std::cerr << "Error: Invalid type" << std::endl;
            // std::cout << "Type: " << typeString << " ";
        }
        else
            type = -1;

        if (line.find(":") != -1 && inGroup == true && inList == false)
        {
            std::string varName = line.substr(0, line.find(":"));
            varName.erase(std::remove_if(varName.begin(), varName.end(), isspace), varName.end());
            // std::cout << "Variable: " << varName << " ";
            variables.push_back(varName);
            groupVariableIndex.push_back({groups.size() - 1, variables.size() - 1});
        }

        if (line.find("[") != -1 && line.find("]") && inGroup == true && inList == false)
        {
            // std::cout << "= ";
            inList = true;
            line = line.substr(line.find("[") + 1, line.find("]"));
        }
        else if (line.find("[") != -1 && inGroup == true && inList == false)
        {
            // std::cout << "= ";
            inList = true;
            lines += line.substr(line.find("[") + 1);
            continue;
        }
        std::vector<std::string> list;
        if (inList == true)
        {
            if (line.find("]") != -1)
            {
                inList = false;
                lines += line.substr(0, line.find("]"));

                while (lines.find(",") != -1)
                {
                    list.push_back(lines.substr(0, lines.find(",")));
                    lines = lines.substr(lines.find(",") + 1);
                }
                list.push_back(lines.substr(0, lines.find("]")));
                for (std::string element : list)
                {
                    element.erase(std::remove_if(element.begin(), element.end(), isspace), element.end());
                    // std::cout << element << " ";
                }
                lines = "";
            }
            else
            {
                lines += line;
                continue;
            }
        }

        if (list.size() == 0)
        {
            switch (type)
            {
            case 0:
                line = line.substr(line.find(":") + 1);
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                ints.push_back(std::stoi(line));
                variableIndex.push_back({variables.size() - 1, type, ints.size() - 1});
                // std::cout << ints.back() << std::endl;
                type = -1;
                continue;
            case 1:
                line = line.substr(line.find(":") + 1);
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                uints.push_back(std::stoul(line));
                variableIndex.push_back({variables.size() - 1, type, uints.size() - 1});
                // std::cout << uints.back() << std::endl;
                type = -1;
                continue;
            case 2:
                line = line.substr(line.find(":") + 1);
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                floats.push_back(std::stof(line));
                variableIndex.push_back({variables.size() - 1, type, floats.size() - 1});
                // std::cout << floats.back() << std::endl;
                type = -1;
                continue;
            case 3:
                line = line.substr(line.find(":") + 1);
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                doubles.push_back(std::stod(line));
                variableIndex.push_back({variables.size() - 1, type, doubles.size() - 1});
                // std::cout << doubles.back() << std::endl;
                type = -1;
                continue;
            case 4:
                line = line.substr(line.find(":") + 1);
                line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
                strings.push_back(line);
                variableIndex.push_back({variables.size() - 1, type, strings.size() - 1});
                // std::cout << strings.back() << std::endl;
                type = -1;
                continue;
            }
        }
        else
        {
            switch (type)
            {
            case 0:
                for (std::string element : list)
                {
                    element.erase(std::remove_if(element.begin(), element.end(), isspace), element.end());
                    ints.push_back(std::stoi(element));
                    variableIndex.push_back({variables.size() - 1, type, ints.size() - 1});
                    // std::cout << ints.back() << " ";
                }
                // std::cout << std::endl;
                type = -1;
                continue;
            case 1:
                for (std::string element : list)
                {
                    element.erase(std::remove_if(element.begin(), element.end(), isspace), element.end());
                    uints.push_back(std::stoul(element));
                    variableIndex.push_back({variables.size() - 1, type, uints.size() - 1});
                    // std::cout << uints.back() << " ";
                }
                // std::cout << std::endl;
                type = -1;
                continue;
            case 2:
                for (std::string element : list)
                {
                    element.erase(std::remove_if(element.begin(), element.end(), isspace), element.end());
                    floats.push_back(std::stof(element));
                    variableIndex.push_back({variables.size() - 1, type, floats.size() - 1});
                    // std::cout << floats.back() << " ";
                }
                // std::cout << std::endl;
                type = -1;
                continue;
            case 3:
                for (std::string element : list)
                {
                    element.erase(std::remove_if(element.begin(), element.end(), isspace), element.end());
                    doubles.push_back(std::stod(element));
                    variableIndex.push_back({variables.size() - 1, type, doubles.size() - 1});
                    // std::cout << doubles.back() << " ";
                }
                // std::cout << std::endl;
                type = -1;
                continue;
            case 4:
                for (std::string element : list)
                {
                    element.erase(std::remove_if(element.begin(), element.end(), isspace), element.end());
                    strings.push_back(element);
                    variableIndex.push_back({variables.size() - 1, type, strings.size() - 1});
                    // std::cout << strings.back() << " ";
                }
                // std::cout << std::endl;
                type = -1;
                continue;
            }
        }

        if (type != -1)
            continue;

        if (list.size() == 0)
        {
            line = line.substr(line.find(":") + 1);
            line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

            try
            {
                ints.push_back(std::stoi(line));
                variableIndex.push_back({variables.size() - 1, 0, ints.size() - 1});
                continue;
            }
            catch (...)
            {
            }

            try
            {
                uints.push_back(std::stoul(line));
                variableIndex.push_back({variables.size() - 1, 1, uints.size() - 1});
                continue;
            }
            catch (...)
            {
            }

            try
            {
                floats.push_back(std::stof(line));
                variableIndex.push_back({variables.size() - 1, 2, floats.size() - 1});
                continue;
            }
            catch (...)
            {
            }

            try
            {
                doubles.push_back(std::stod(line));
                variableIndex.push_back({variables.size() - 1, 3, doubles.size() - 1});
                continue;
            }
            catch (...)
            {
            }

            strings.push_back(line);
            variableIndex.push_back({variables.size() - 1, 4, strings.size() - 1});
        }
        else
        {
            for (std::string element : list)
            {
                element.erase(std::remove_if(element.begin(), element.end(), isspace), element.end());

                try
                {
                    ints.push_back(std::stoi(element));
                    variableIndex.push_back({variables.size() - 1, 0, ints.size() - 1});
                    continue;
                }
                catch (...)
                {
                }

                try
                {
                    uints.push_back(std::stoul(element));
                    variableIndex.push_back({variables.size() - 1, 1, uints.size() - 1});
                    continue;
                }
                catch (...)
                {
                }

                try
                {
                    floats.push_back(std::stof(element));
                    variableIndex.push_back({variables.size() - 1, 2, floats.size() - 1});
                    continue;
                }
                catch (...)
                {
                }

                try
                {
                    doubles.push_back(std::stod(element));
                    variableIndex.push_back({variables.size() - 1, 3, doubles.size() - 1});
                    continue;
                }
                catch (...)
                {
                }

                strings.push_back(element);
                variableIndex.push_back({variables.size() - 1, 4, strings.size() - 1});
            }
        }
    }

    ndlFile.close();

    /*std::cout << groups.size() << std::endl;
    std::cout << variables.size() << std::endl;
    std::cout << ints.size() << std::endl;
    std::cout << uints.size() << std::endl;
    std::cout << floats.size() << std::endl;
    std::cout << doubles.size() << std::endl;
    std::cout << strings.size() << std::endl;*/

    for (auto gvIndex : groupVariableIndex)
    {
        std::cout << groups[gvIndex.first] << " " << variables[gvIndex.second] << ": ";

        for (auto vIndex : variableIndex)
        {
            if (std::get<0>(vIndex) != gvIndex.second)
                continue;

            switch (std::get<1>(vIndex))
            {
            case 0:
                std::cout << ints[std::get<2>(vIndex)] << std::endl;
                break;
            case 1:
                std::cout << uints[std::get<2>(vIndex)] << std::endl;
                break;
            case 2:
                std::cout << floats[std::get<2>(vIndex)] << std::endl;
                break;
            case 3:
                std::cout << doubles[std::get<2>(vIndex)] << std::endl;
                break;
            case 4:
                std::cout << strings[std::get<2>(vIndex)] << std::endl;
                break;
            }
        }
    }
}
