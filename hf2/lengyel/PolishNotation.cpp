//
// Created by Levi on 2023. 09. 23..
//

#include "PolishNotation.h"
#include <iostream>
#include <math.h>

using namespace std;


PolishNotation::PolishNotation() {



}

int PolishNotation::ConvertDecimal(std::string number) {

}

int PolishNotation::evaluate(std::string polish_input) {
    int szam1 = 0;
    int szam2 = 0;
    int szamszamlalo = 0;

    for (int i = 0; i < polish_input.size(); ++i) { //ha kaptam 8 szamot huzamban, akkor elkuldom a kiertekelonek, es az visszaad egy int? szamot
        if(isdigit(polish_input[i])){
            if(szamszamlalo <= 8){

                int hatvany = 8-szamszamlalo;
                int hanyszor = (int(polish_input[i]))-48;
                //cout << hatvany <<endl;
                int hatvanyozva = pow(2,hatvany);

                szam1 = szam1 + hanyszor*hatvanyozva;

                //int teszt = pow(2,3);
                //cout << teszt <<endl;



            }
            szamszamlalo = szamszamlalo +1;

        }

    }
    cout << szam1 <<endl;

}

string PolishNotation::convert(string polishInfix) {
    int szamszamlalo = 0;

    for (int i = 0; i < polishInfix.size(); ++i) {

        if( polishInfix[i] != ' ' && !isdigit(polishInfix[i])){

            if(polishInfix[i] == zarojel){

                //char test = jelek[jelek.size()-1]; //kesobb popback majd
                //cout << test << endl;
                lengyel.push_back(' ');
                lengyel.push_back(jelek[jelek.size()-1]);                        //addig popback amig nem nyitojelet kapunk vissza
                while(jelek[jelek.size()-1] != nyitojel){
                    //cout << jelek[jelek.size()-1] <<endl;
                    jelek.pop_back();
                    //cout << jelek[jelek.size()-1] <<endl;
                }

                if(jelek[jelek.size()-1] == nyitojel){
                    //cout << jelek[jelek.size()-1] <<endl;
                    /*
                    for (int j = 0; j < jelek.size(); ++j) {
                       cout << jelek[j] <<endl;
                    }
                    */
                    jelek.pop_back();
                    //cout << jelek[jelek.size()-1] <<endl;
                }
                //cout << jelek[jelek.size()-1] <<endl;

                if(jelek.size() == 1){
                    lengyel.push_back(' ');
                    lengyel.push_back(jelek[jelek.size()-1]);

                    jelek.pop_back();
                }


            } else{

                //cout << "vege" <<endl;
                jelek.push_back(polishInfix[i]);

            }

        }

        if(isdigit(polishInfix[i])){
            if(szamszamlalo == 8){
                lengyel.push_back(' ');
                szamszamlalo = 0;

            }

                lengyel.push_back(polishInfix[i]); //8 szamjegyenkent el tudjuk valasztani a szamokat()
                szamszamlalo = szamszamlalo + 1;



        }


    }
    string lengyelfroma = "";
    for (int i = 0; i < lengyel.size(); ++i) {
        //cout << lengyel[i] <<endl;
        lengyelfroma = lengyelfroma + lengyel[i];
    }
    cout << lengyelfroma <<endl;


    return lengyelfroma;
}