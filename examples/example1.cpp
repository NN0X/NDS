#include <nds.h>

int main()
{
    NDS nds("../examples/example1");
    nds.loadNDL();
    nds.printNDL();
    return 0;
}