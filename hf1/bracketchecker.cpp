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

    string jelek = "";


    for (int i = 0; i < int(expression.length()); ++i) {
        //cout << expression[i] << endl;
        char egykarakter = expression[i];
        for (int j = 0; j < int(nyitojelek.size()); ++j) {
            //std::cout << int(zarojelek.size()) << std::endl;
            if(egykarakter == nyitojelek[j]){
                //cout << egykarakter << "es" << zarojelek[j] << endl;
                jelek = jelek + zarojelek[j]; //a parjat hozzairja egy stringhez



            } else{

                for (int k = 0; k < int(zarojelek.size()); ++k) {
                    if(egykarakter == zarojelek[k]){
                        //cout << "help" << endl;

                        if(jelek.length() == 0){ //különben bezaratlan marad a zarojel

                            return false;
                        }
                        /////////////////////////////////valamit talalj ki arra, ha ())
                        if(jelek[jelek.length()-1] == zarojelek[k]){

                            //cout << "elotte: " << jelek << "!" << endl;
                            jelek = jelek.substr(0, jelek.size()-1); //ha megtalalja a parjat akkor torolje oket
                            //cout << "utana: " << jelek << "!" << endl;
                        }

                    }

                    }



            }



        }

    }
    //cout << "part done:" << jelek.length() << "!" << endl;
    if(jelek.length() == 0){

        return true;

    }
    else{

        return false;
    }





    //(void) expression;
    //return true;
}
