#include "PolishNotation.h"
#include "woodpecker.hpp"


///Basic converting

TEST("Simple convert",1){
    PolishNotation pn;
    CHECK_EQ("00000001 00000010 +", pn.convert("00000001 + 00000010"));
}
TEST("Negative convert",1){
    PolishNotation pn;
    CHECK_EQ("11111111 11111110 +", pn.convert("11111111 + 11111110"));
}
TEST("Medium convert",1) {
    PolishNotation pn;
    CHECK_EQ("00000001 00000010 + 00000011 00000100 - *",
             pn.convert("( 00000001 + 00000010 ) * ( 00000011 - 00000100 )"));
}

///Basic Infix Evaluation

TEST("Simple Infix evaluate",1){
    PolishNotation pn;
    CHECK_EQ(3, pn.evaluate("00000001 + 00000010"));
}
TEST("Negative Infix Addition evaluate",1){
    PolishNotation pn;
    CHECK_EQ(-3, pn.evaluate("11111111 + 11111110"));
}
TEST("Negative Infix Subtraction evaluate",1){
    PolishNotation pn;
    CHECK_EQ(1, pn.evaluate("11111111 - 11111110"));
}
TEST("Medium Infix evaluate",1){
    PolishNotation pn;
    CHECK_EQ(-3, pn.evaluate("( 00000001 + 00000010 ) * ( 00000011 - 00000100 )"));
}
///Basic Postfix Evaluation

TEST("Simple Postfix evaluate",1){
    PolishNotation pn;
    CHECK_EQ(3, pn.evaluate("00000001 00000010 +"));
}
TEST("Negative Postfix Addition evaluate",1){
    PolishNotation pn;
    CHECK_EQ(-3, pn.evaluate("11111111 11111110 +"));
}
TEST("Negative Postfix Subtraction evaluate",1){
    PolishNotation pn;
    CHECK_EQ(1, pn.evaluate("11111111 11111110 -"));
}
TEST("Medium Postfix evaluate",1){
    PolishNotation pn;
    CHECK_EQ(-3, pn.evaluate("00000001 00000010 + 00000011 00000100 - *"));
}


///Other tests


TEST("Multiple Conversions"){
    PolishNotation pn;
    CHECK_EQ("00000001 00000010 +", pn.convert("00000001 + 00000010"));
    CHECK_EQ("11111111 11111110 +", pn.convert("11111111 + 11111110"));
    CHECK_EQ(3, pn.evaluate("00000001 + 00000010"));
    CHECK_EQ(-3, pn.evaluate("11111111 + 11111110"));
    CHECK_EQ("00000001 00000010 +", pn.convert("00000001 + 00000010"));
}

TEST("Overflow"){
    PolishNotation pn;
    bool overflow_handled = (pn.evaluate("01000000 + 01000000") == 128);
    bool overflow_ignored = (pn.evaluate("01000000 + 01000000") == -128);
    CHECK_EQ(true,overflow_handled xor overflow_ignored);
}

TEST("Division"){
    PolishNotation pn;
    CHECK_EQ(1, pn.evaluate("00000011 / 00000010"));
}
TEST("Hard Combined",1){
    PolishNotation pn;
    ///2+4*2-3+4*(3+1)/2-1;
    string infix ="00000010 + 00000100 * 00000010 - 00000011 + 00000100 * ( 00000011 + 00000001 ) / 00000010 - 00000001";
    string postfix = pn.convert(infix);
    CHECK_EQ("00000010 00000100 00000010 * + 00000011 - 00000100 00000011 00000001 + * 00000010 / + 00000001 -",postfix);
    CHECK_EQ(14, pn.evaluate(postfix));
    CHECK_EQ(14, pn.evaluate(infix));
}
WOODPECKER_TEST_MAIN(-1, -1)

