#ifndef ADATSZERK_HF01_BRACKETCHECKER_H
#define ADATSZERK_HF01_BRACKETCHECKER_H

#include <string>
#include "mystack.h"

class BracketChecker {

public:
    bool checkCorrectness(const std::string& expression);
    MyStack myStack;
    MyStack zarojelek;
    MyStack nyitojelek;
    std::string jelek;





};


#endif //ADATSZERK_HF01_BRACKETCHECKER_H
