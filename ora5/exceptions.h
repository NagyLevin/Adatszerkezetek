#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED
#include <exception>

class CopyNotImplemented : public std::exception {
public:
    const char *what() const throw() { return "Masolas nincs implementalva!"; }
};

class InternalError : public std::exception {
    const char *message;

public:
    InternalError(const char *msg = "Hiba van az implementacioban!")
            : message(msg) {}

    const char *what() const throw() { return message; }
};

class InvalidBinarySearchTree : public std::exception {
public:
    const char *what() const throw() {
        return "Serulnek a binaris keresofa kriteriumok!";
    }
};

class InvalidAvlTree : public std::exception {
public:
    const char *what() const throw() {
        return "Serulnek az AVL fa tulajdonsagok!";
    }
};

class InvalidIterator : public std::exception {
public:
    const char *what() const throw() { return "NULL elemre mutat az iterator!"; }
};

#endif // EXCEPTIONS_HPP_INCLUDED