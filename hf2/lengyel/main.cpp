#include <iostream>
#include "PolishNotation.h"
int main() {

    PolishNotation pn;
    pn.convert("( 00000001 + 00000010 ) * ( 00000010 - 00000001 )");

    std::cout << "vege" << std::endl;
    return 0;
}
