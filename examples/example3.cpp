#include <nds.h>

int main()
{
    NDS nds("../examples/example3");

    for (int i = 0; i < 100; i++)
    {
        std::string groupName = std::to_string(i);
        nds.addGroup(groupName);
        for (int j = 0; j < 50; j++)
        {
            std::string variableName = std::to_string(j);
            nds.addArray(variableName, groupName, NDS::DOUBLE);
            nds.setDoubleArray(variableName, groupName, {1.1, 2.2, 3.3});
        }
        std::cout << i << "/99\n";
    }

    nds.saveNDL();

    std::cout << "Press 'ENTER' to continue...";
    std::cin.get();

    nds.clear();

    nds.loadNDL();

    nds.printNDL();

    return 0;
}