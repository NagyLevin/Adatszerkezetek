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
    int ConvertDecimal();
    int muvelet(int szam1, int szam2, char jel);
    void convertobinar(int szam);
    vector<char> lengyel;
    vector<char> jelek;
    vector<char> szamok;
    char nyitojel = '(';
    char zarojel = ')';
    char terkoz = ' ';



};
#endif //LENGYEL_POLISHNOTATION_H
