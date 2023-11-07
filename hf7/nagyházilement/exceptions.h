//
// Created by Kolos on 2022. 10. 09..
//

#ifndef NHF1_SKELETON_EXCEPTIONS_H
#define NHF1_SKELETON_EXCEPTIONS_H

#include <exception>


class UnderFlowException : public std::exception {
public:
    const char *what() const noexcept { return "Alulindexelés!"; }
};

class OverFlowException : public std::exception {
public:
    const char *what() const noexcept { return "Tulindexelés!"; }
};

class NoMatchingMatrixException : public std::exception {
public:
    const char *what() const noexcept { return "Nincs egyezés, nincs összeadás!"; }
};

#endif //NHF1_SKELETON_EXCEPTIONS_H
