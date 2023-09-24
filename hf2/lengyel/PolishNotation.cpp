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

    int szam = 0;
    int hatvany = 0;
    //cout << number <<endl;
    for (int i = number.size()-1; i > -1; --i) {
        int hanyszor = (int(number[i]))-48;
        //cout << hanyszor <<endl;
        int khatvany = pow(2,hatvany);
        szam = szam + hanyszor * khatvany;
        hatvany = hatvany +1;
    }
    cout << szam <<endl;
    /*
    int hatvany = 8-szamszamlalo;

    //cout << hatvany <<endl;
    int hatvanyozva = pow(2,hatvany);

    szam1 = szam1 + hanyszor*hatvanyozva;

    //int teszt = pow(2,3);
    //cout << teszt <<endl;
     */

}

int PolishNotation::evaluate(std::string polish_input) {

    int szamszamlalo = 0;
    string egyszam = "";

    for (int i = 0; i < polish_input.size(); ++i) { //ha kaptam 8 szamot huzamban, akkor elkuldom a kiertekelonek, es az visszaad egy int? szamot
        if(isdigit(polish_input[i])){

            if(szamszamlalo == 8){

                char szam = ConvertDecimal(egyszam);
                szamok.push_back(szam);
                cout << szam <<endl;
                szamszamlalo = 0;
                egyszam = "";


            }
           egyszam = egyszam + polish_input[i];
            szamszamlalo = szamszamlalo +1;

        }
        if(!isdigit(polish_input[i]) && polish_input[i] != terkoz){
            if(polish_input[i] == '+'){

            }


        }



    }


}

string PolishNotation::convert(string polishInfix) {
    int szamszamlalo = 0;

    for (int i = 0; i < polishInfix.size(); ++i) {

        if( polishInfix[i] != terkoz && !isdigit(polishInfix[i])){

            if(polishInfix[i] == zarojel){

                //char test = jelek[jelek.size()-1]; //kesobb popback majd
                //cout << test << endl;
                lengyel.push_back(terkoz);
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
                    lengyel.push_back(terkoz);
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
                lengyel.push_back(terkoz);

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