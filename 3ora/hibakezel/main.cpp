#include <iostream>
#include "custom_thrower.h"

int main() {
    CustomThrower c;

    /* Elkaptuk a BigIssue-t, a második catch ág nem fut le */
    try {
        c.throwBigIssue();
    }
    catch (BigIssue &b) {
        std::cout<<b.what()<<std::endl;
    }
    catch (std::exception &e) {
        std::cout<<e.what()<<std::endl;
    }

    /* Mit írt ki a cout és miért? */
    try {
        c.throwSmallIssue();
    }
    catch (std::exception &e) {
        std::cout<<e.what()<<std::endl;
    }

    /* Mit kaptunk el? */
    try {
        c.throwAnyIssue();
    }
    catch (SmallIssue &s) {
        std::cout<<s.what()<<std::endl;
    }
    catch (BigIssue &b) {
        std::cout<<b.what()<<std::endl;
    }
    catch (std::exception &e) {
        std::cout<<e.what()<<std::endl;
    }

    /* Dobni sok mindent lehet */
    try {
        c.throwSomething();
    }
    catch (SmallIssue &s) {
        std::cout<<s.what()<<std::endl;
    }
    catch (BigIssue &b) {
        std::cout<<b.what()<<std::endl;
    }
    catch (std::exception &e) {
        std::cout<<e.what()<<std::endl;
    }
    catch (...) {       //ez elkap bármi mást
        std::cout<<"Derp, wtf?"<<std::endl;
    }

}