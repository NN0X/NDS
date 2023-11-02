// D:\Dev\NDS\build> g++ ../examples/example1.cpp ../source/nds.cpp -o test

#include "../include/nds.h"

int main()
{
    NDS nds("../examples/example1.ndl");
    nds.loadNDL();
    return 0;
}