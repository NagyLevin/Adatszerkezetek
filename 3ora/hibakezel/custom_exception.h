#ifndef INC_03_EXCEPTION_CUSTOM_EXCEPTION_H
#define INC_03_EXCEPTION_CUSTOM_EXCEPTION_H
#include <exception>
/*
 *
 * Hozz létre két kivétel osztályt:
 * - SmallIssue
 * - BigIssue
 *
 * Mindkét kivétel osztály az std::exception-ből származzon publikusan
 *
 * Mindkét osztályban add meg a publikus what metódust és implementációját a következő módon:
 * const char* what() const noexcept { return "értelmes szöveg"; }
 *
 * Ahol a return-nel visszaadott érték utal a kivétel osztályára (pl. beleírod, hogy ez melyik osztály)
 *
 */
class SmallIssue: public std::exception {
public:
    const char* what() const noexcept {
        return "there is a small issue";
    }

};
class BigIssue: public std::exception {
public:
    const char* what() const noexcept {
        return "there is a big issue";
    }

};



#endif //INC_03_EXCEPTION_CUSTOM_EXCEPTION_H