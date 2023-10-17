#ifndef EXCEPTIONS_HPP_INCLUDED
#define EXCEPTIONS_HPP_INCLUDED

#include <exception>
#include <string>

class copy_not_implemented : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Masolas nincs implementalva!";
    }
};

class invalid_binary_search_tree : public std::exception {
public:
    [[nodiscard]] const char *what() const noexcept override {
        return "Serulnek a binaris keresofa kriteriumok!";
    }
};

class invalid_rb_tree : public std::exception {
    std::string message = "Serulnek az piros-fekete fa tulajdonsagok!";

public:
    invalid_rb_tree() noexcept = default;
    explicit invalid_rb_tree(const std::string_view &msg) noexcept {
        message += "Serulnek az piros-fekete fa tulajdonsagok: ";
        message += msg;
    }
    [[nodiscard]] const char *what() const noexcept override {
        return message.c_str();
    }
};

#endif // EXCEPTIONS_HPP_INCLUDED
