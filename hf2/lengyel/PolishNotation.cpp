//
// Created by Levi on 2023. 09. 23..
//

#include "PolishNotation.h"
#include <iostream>
using namespace std;


PolishNotation::PolishNotation() {



}


string PolishNotation::convert(string polishInfix) {
    bool voltnyito = false;

    for (int i = 0; i < polishInfix.size(); ++i) {
        if(polishInfix[i] == nyitojel){
            jelek.push_back(polishInfix[i]);
            voltnyito = true;

        }
        if(voltnyito == true && polishInfix[i] != ' ' && !isdigit(polishInfix[i])){

            if(polishInfix[i] == zarojel){

                //char test = jelek[jelek.size()-1]; //kesobb popback majd
                //cout << test << endl;
                voltnyito = false;
                lengyel.push_back(jelek[jelek.size()-1]);                        //addig popback amig nem nyitojelet kapunk vissza


            } else{
                jelek.push_back(polishInfix[i]);
            }

        }

        if(isdigit(polishInfix[i])){
            lengyel.push_back(polishInfix[i]); //8 szamjegyenkent el tudjuk valasztani a szamokat()


        }


    }
    for (int i = 0; i < lengyel.size(); ++i) {
        cout << lengyel[i] <<endl;
    }



    return "0";
}