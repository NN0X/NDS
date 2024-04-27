#include <nds.h>

int main()
{
    NDS nds("../examples/example2");

    nds.addGroup("group1");
    nds.addGroup("group2");

    nds.addVariable("uint1", "group1", NDS::UINT);
    nds.setUInt("uint1", "group1", 50);
    nds.addVariable("int1", "group1", NDS::INT);
    nds.setInt("int1", "group1", -100);
    nds.addVariable("float1", "group1", NDS::FLOAT);
    nds.setFloat("float1", "group1", 3.14);
    nds.addVariable("double1", "group1", NDS::DOUBLE);
    nds.setDouble("double1", "group1", 3.14159);
    nds.addVariable("string1", "group1", NDS::STRING);
    nds.setString("string1", "group1", "Hello, World!");

    nds.addArray("uintList1", "group2", NDS::UINT);
    nds.addUIntsToArray("uintList1", "group2", {1, 2, 3, 4, 5});
    nds.addUIntToArray("uintList1", "group2", 6);

    nds.addArray("intList1", "group2", NDS::INT);
    nds.addIntsToArray("intList1", "group2", {-1, -2, 3, -4, -5});
    nds.addIntToArray("intList1", "group2", 6);

    nds.addArray("floatList1", "group2", NDS::FLOAT);
    nds.addFloatsToArray("floatList1", "group2", {1.1, 2.2, 3.3, 4.4, 5.5});
    nds.addFloatToArray("floatList1", "group2", 6.6);

    nds.addArray("doubleList1", "group2", NDS::DOUBLE);
    nds.addDoublesToArray("doubleList1", "group2", {1.1, 2.2, 3.3, 4.4, 5.5});
    nds.addDoubleToArray("doubleList1", "group2", 6.6);

    nds.addArray("stringList1", "group2", NDS::STRING);
    nds.addStringsToArray("stringList1", "group2", {"one", "two", "three", "four", "five"});
    nds.addStringToArray("stringList1", "group2", "six");

    nds.addArray("stringList2", "group2", NDS::STRING);
    nds.setStringArray("stringList2", "group2", {"Tom", "Joef", "Alice", "Bob", "Charlie"});

    nds.printNDL();

    nds.saveNDL();

    return 0;
}