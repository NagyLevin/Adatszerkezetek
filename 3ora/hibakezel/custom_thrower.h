#ifndef INC_03_EXCEPTION_CUSTOM_THROWER_H
#define INC_03_EXCEPTION_CUSTOM_THROWER_H

#include "custom_exception.h"

/*
 * Hozz létre egy CustomThrower osztályt négy publikus metódussal:
 * o void throwSmallIssue() - amely SmallIssue-t kivételt dob
 * o void throwBigIssue()   - amely BigIssue kivételt dob
 * o void throwAnyIssue()   - amely std::exception-t dob
 * o void throwSomething()  - amely valamilyen értéket dob
 */

    class CustomThrower {
    public:
    void throwSmallIssue(){
        throw SmallIssue();
    }
    void throwBigIssue(){
        throw BigIssue();
    }

    void throwAnyIssue(){
        throw std::exception();
    }

    void throwSomething(){
        int i = 10;
        throw i;
    }



};

#endif //INC_03_EXCEPTION_CUSTOM_THROWER_H