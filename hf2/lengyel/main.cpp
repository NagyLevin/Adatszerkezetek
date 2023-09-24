#include <iostream>
#include "PolishNotation.h"
int main() {

    PolishNotation pn;
    string szam = pn.convert("( 00000001 + 00000010 ) * ( 00000010 - 00000001 )");
    pn.evaluate(szam);
    std::cout << "vege" << std::endl;
    return 0;
}
