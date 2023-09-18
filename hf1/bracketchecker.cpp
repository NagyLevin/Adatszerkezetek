#include "bracketchecker.h"
#include <iostream>

using namespace std;
BracketChecker::BracketChecker() {
    nyitojelek.push('(');
    zarojelek.push(')');
    nyitojelek.push('[');
    zarojelek.push(']');
    nyitojelek.push('{');
    zarojelek.push('}');


}

bool BracketChecker::checkCorrectness(const std::string& expression) {
    // TODO solve homework by deadline

    jelek = "";
    //cout << jelek <<endl;
    for (int i = 0; i < int(expression.length()); ++i) { //megnezi a zarojel kezdetet
        //cout << expression[i] << endl;
        char egykarakter = expression[i];

        for (int j = 0; j < int(nyitojelek.size()); ++j) {
            //std::cout << int(zarojelek.size()) << std::endl;
            if(egykarakter == nyitojelek.GiveItem(j)){
                //cout << egykarakter << "es" << zarojelek[j] << endl;
                jelek = jelek + zarojelek.GiveItem(j); //a parjat hozzairja egy stringhez
                //cout << "hozzaadva: " << jelek << "!" << endl;


            }


            }
        for (int k = 0; k < int(zarojelek.size()); ++k) { //megnezi a zarojel masik felet
            if(egykarakter == zarojelek.GiveItem(k)){
                //cout << "help" << endl;

                //cout << "egykarakter: " << egykarakter << "!" << endl;

                //cout << "elotte: " << jelek << "!" << endl;


                if(jelek.length() < 1){ //különben bezaratlan marad a zarojel

                    return false;
                }

                if(jelek[jelek.length()-1] == zarojelek.GiveItem(k)){

                    //cout << "elotte: " << jelek << "!" << endl;
                    jelek = jelek.substr(0, jelek.size()-1); //ha megtalalja a parjat akkor torolje oket
                    //cout << "utana: " << jelek << "!" << endl;
                }

            }

        }


        }

    //cout << expression <<endl;
    //cout << "part done:" << jelek << "!" << endl;
    if(jelek.length() == 0){

        return true;

    }
    else{

        return false;
    }





    //(void) expression;
    //return true;
}
