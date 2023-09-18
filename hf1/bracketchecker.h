#ifndef ADATSZERK_HF01_BRACKETCHECKER_H
#define ADATSZERK_HF01_BRACKETCHECKER_H

#include <string>
#include "vector"

class BracketChecker {

public:
    bool checkCorrectness(const std::string& expression);
    std::vector<char> zarojelek;
    std::vector<char> nyitojelek;
    std::string jelek;





};


#endif //ADATSZERK_HF01_BRACKETCHECKER_H
