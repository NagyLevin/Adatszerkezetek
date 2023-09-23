//
// Created by Levi on 2023. 09. 23..
//

#ifndef LENGYEL_POLISHNOTATION_H
#define LENGYEL_POLISHNOTATION_H
#include <string>
using namespace std;

class PolishNotation {

public:
    PolishNotation();
    //~PolishNotation();
    string convert(string polishInfix);
    int evaluate(string polish_input);
private:
    int ConvertDecimal(string number);


};
#endif //LENGYEL_POLISHNOTATION_H
