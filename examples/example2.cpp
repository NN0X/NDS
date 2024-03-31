#include <nds.h>

int main()
{
    NDS nds("../examples/example2.ndl");

    nds.addGroup("group1");
    nds.addGroup("group2");

    nds.addVariable("int1", "group1", NDS::INT);
    nds.setInt("int1", "group1", -100);
    nds.addVariable("uint1", "group1", NDS::UINT);
    nds.setUInt("uint1", "group1", 50);
    nds.addVariable("float1", "group1", NDS::FLOAT);
    nds.setFloat("float1", "group1", 3.14);
    nds.addVariable("double1", "group1", NDS::DOUBLE);
    nds.setDouble("double1", "group1", 3.14159);
    nds.addVariable("string1", "group1", NDS::STRING);
    nds.setString("string1", "group1", "Hello, World!");

    nds.addVariable("intList1", "group2", NDS::INT_LIST);
    nds.setIntList("intList1", "group2", {-1, -2, 3, -4, -5});
    nds.addVariable("uintList1", "group2", NDS::UINT_LIST);
    nds.setUIntList("uintList1", "group2", {1, 2, 3, 4, 5});
    nds.addVariable("floatList1", "group2", NDS::FLOAT_LIST);
    nds.setFloatList("floatList1", "group2", {1.1, 2.2, 3.3, 4.4, 5.5});
    nds.addVariable("doubleList1", "group2", NDS::DOUBLE_LIST);
    nds.setDoubleList("doubleList1", "group2", {1.1, 2.2, 3.3, 4.4, 5.5});
    nds.addVariable("stringList1", "group2", NDS::STRING_LIST);
    nds.setStringList("stringList1", "group2", {"one", "two", "three", "four", "five"});

    for (auto data : nds.getGroupVariableData())
    {
        std::cout << std::get<0>(data) << " " << std::get<1>(data) << " " << std::get<2>(data) << " " << std::get<3>(data) << std::endl;
    }

    nds.printNDL();

    nds.saveNDL();

    return 0;
}