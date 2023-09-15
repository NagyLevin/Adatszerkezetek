#include "bracketchecker.h"
#include <iostream>
#include "vector"
using namespace std;
bool BracketChecker::checkCorrectness(const std::string& expression) {
    // TODO solve homework by deadline


    //std::string array[2] = {"(",")"};
    //std::string array[2] = {"[","]"};
    //std::string array[2] = {"{","}"};
    vector<char> zarojelek;
    vector<char> nyitojelek;

    nyitojelek.push_back('(');
    zarojelek.push_back(')');
    nyitojelek.push_back('[');
    zarojelek.push_back(']');
    nyitojelek.push_back('{');
    zarojelek.push_back('}');

    char keresettjel = ' ';


    for (int i = 0; i < int(expression.length()); ++i) {
        //cout << expression[i] << endl;
        char egykarakter = expression[i];
        for (int j = 0; j < int(nyitojelek.size()); ++j) {
            //std::cout << int(zarojelek.size()) << std::endl;
            if(egykarakter == nyitojelek[j]){
                //cout << egykarakter << "es" << zarojelek[j] << endl;
                keresettjel = zarojelek[j]; //a nyitojel melle zarot keresem
                //mi van akkor, ha (( vagy ([ jön egymás utan


            } else{

                for (int k = 0; k < int(zarojelek.size()); ++k) {
                    if(egykarakter == zarojelek[k]){
                        if(keresettjel == zarojelek[k]){
                            keresettjel = ' ';
                        }
                    }

                    }



            }



        }

    }
    cout << "part done" << endl;





    (void) expression;
    return true;
}
