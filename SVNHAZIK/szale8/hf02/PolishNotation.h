//
// Created by Levi on 2023. 09. 23..
//

#ifndef LENGYEL_POLISHNOTATION_H
#define LENGYEL_POLISHNOTATION_H
#include <string>
#include "DynamicIntStack.h"
using namespace std;

class PolishNotation {

public:
    PolishNotation();
    //~PolishNotation();
    string convert(string polishInfix);
    int evaluate(string polish_input);
private:
    int ConvertDecimal();
    int muvelet(int szam1, int szam2, char jel);
    void convertobinar(int szam);
    //DynamicIntStack dynamicIntStack;
    DynamicIntStack lengyel;
    DynamicIntStack jelek;
    DynamicIntStack szamok;
    char nyitojel = '(';
    char zarojel = ')';
    char terkoz = ' ';
    int bitmeret = 8;


};
#endif //LENGYEL_POLISHNOTATION_H
