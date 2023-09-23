//
// Created by Levi on 2023. 09. 23..
//

#ifndef LENGYEL_POLISHNOTATION_H
#define LENGYEL_POLISHNOTATION_H
#include <string>
#include <vector>
using namespace std;

class PolishNotation {

public:
    PolishNotation();
    //~PolishNotation();
    string convert(string polishInfix);
    int evaluate(string polish_input);
private:
    int ConvertDecimal(string number);
    vector<char> lengyel;
    vector<char> jelek;
    char nyitojel = '(';
    char zarojel = ')';




};
#endif //LENGYEL_POLISHNOTATION_H
