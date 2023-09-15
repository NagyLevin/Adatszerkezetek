#include <iostream>
#include "woodpecker.hpp"
#include "bracketchecker.h"
using namespace std;

TEST("Simple & small") {
    BracketChecker bracketChecker;
    bool result = bracketChecker.checkCorrectness("()");
    cout << result << endl;
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("(");
    CHECK_EQ(result, false);
    result = bracketChecker.checkCorrectness("{}");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("[]");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("][");
    CHECK_EQ(result, false);
    result = bracketChecker.checkCorrectness("[ [ ] ] { { } } ( ( ) )");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("this is the simplest case");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("");
    CHECK_EQ(result, true);
}
TEST("Simple") {
    BracketChecker bracketChecker;
    bool result = bracketChecker.checkCorrectness(" ( ) \n [[this text should be ignored]]....{{}}");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("{  } ( ( ( ( ( ( ( ( ( ( ( ( [ [ ] ] ) ) ) ) ) ) ) ) ) ) ) )");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("{([(1+2)-(4/6)*4]/5)-3+6}+(12/3)");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("{}(()[]{}(({}{}{}[]{}{}{})){})");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("{}(()[]{}(({}{}{}[{}{}{})){})");
    CHECK_EQ(result, false);
}
TEST("Bad cases") {
    BracketChecker bracketChecker;
    bool result = bracketChecker.checkCorrectness("(()");
    CHECK_EQ(result, false);
    result = bracketChecker.checkCorrectness("{{{})}");
    CHECK_EQ(result, false);
    result = bracketChecker.checkCorrectness("[(])");
    CHECK_EQ(result, false);
    result = bracketChecker.checkCorrectness("1-(2+3)/6)+(4-(2+2)");
    CHECK_EQ(result, false);
}
TEST("Complex cases") {
    BracketChecker bracketChecker;
    bool result = bracketChecker.checkCorrectness("Solve (12+13+14)-(((12*2+5-4*(9-4)*[6-3]+{2-(2*7)})+5)*3)-111");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(f(x)))))))))))))))))))))))))))))))))))))))))))))))))))))");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("[{1}{2}{(3})]");
    CHECK_EQ(result, false);
    result = bracketChecker.checkCorrectness("//{([{1}{2}{(3)}])-([{1}{2}{(3)}])[1:12]}/({([{1}{2}{(3)}])-([{1}{2}{(3)}])[1:12]}+{1-{2+3}/5})={{([{1}{2}{(3)}])-([{1}{2}{(3)}])[1:12]}[1:4]};");
    CHECK_EQ(result, true);
    result = bracketChecker.checkCorrectness("(){()()(){()()()(())}(){()()(())()(())()()(())(())}{()}}{{(())()(){((()))()()(){(())(){(){[][][]([][])[]}}}(()){(){[][][][]}(){}}}(){(){[]([])}()(){[]([])()}}}}");
    CHECK_EQ(result, true);


}

WOODPECKER_TEST_MAIN()
