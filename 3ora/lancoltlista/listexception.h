#ifndef LISTEXCEPTION_HPP_INCLUDED
#define LISTEXCEPTION_HPP_INCLUDED

#include <exception>

class UnderFlowException : public std::exception {
public:
    const char *what() const noexcept { return "Alulcsordulas!"; }
};

class CurNullException : public std::exception {
public:
    const char *what() const noexcept {
        return "Nincs aktualis elem kivalasztva!";
    }
};

class InvalidIterator : public std::exception {
public:
    const char *what() const noexcept { return "Ervenytelen iterator!"; }
};

#endif // LISTEXCEPTION_HPP_INCLUDED
