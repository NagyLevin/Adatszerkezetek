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
        //cout << khatvany <<endl;
        szam = szam + (hanyszor * khatvany);

        hatvany = hatvany +1;
    }
    //cout << szam <<endl;

    return szam;
}

int PolishNotation::evaluate(std::string polish_input) {

    int szamszamlalo = 0;
    string egyszam = "";

    for (int i = 0; i < polish_input.size(); i++) { //ha kaptam 8 szamot huzamban, akkor elkuldom a kiertekelonek, es az visszaad egy int? szamot

        //cout << polish_input[i] <<endl;
        if(isdigit(polish_input[i])){

            szamszamlalo = szamszamlalo +1;
            egyszam = egyszam + polish_input[i];
            if(szamszamlalo > 7){

                char szam = ConvertDecimal(egyszam)+48; ///ezt told el
                //cout << szam << endl;
                szamok.push_back(szam);
                szamszamlalo = 0;
                egyszam = "";
            }



        }

        if(!isdigit(polish_input[i]) && polish_input[i] != terkoz){
            if(polish_input[i] == '+'){
                int szam2 = int(szamok[szamok.size()-1])-48;
                //cout << szamok[szamok.size()-1] <<endl;
                //cout << szam1 <<endl;
                szamok.pop_back();

                int szam1 = int(szamok[szamok.size()-1])-48;
                //cout << szamok[szamok.size()-1] <<endl;
                //cout << szam2 <<endl;
                szamok.pop_back();
                int osszeg = szam1 + szam2;
                //cout << osszeg <<endl;;

                char cosszeg = osszeg+48;
                //cout << cosszeg << endl;
                szamok.push_back(cosszeg);
            }
            if(polish_input[i] == '-'){
                int szam2 = int(szamok[szamok.size()-1])-48;
                szamok.pop_back();

                int szam1 = int(szamok[szamok.size()-1])-48;
                szamok.pop_back();
                int osszeg = szam1 - szam2;

                char cosszeg = osszeg+48;
                //cout << cosszeg << endl;
                szamok.push_back(cosszeg);

            }
            if(polish_input[i] == '*'){
                int szam2 = int(szamok[szamok.size()-1])-48;
                szamok.pop_back();

                int szam1 = int(szamok[szamok.size()-1])-48;
                szamok.pop_back();///siman csak 8 popback es utana meg 8 pushback
                int osszeg = szam1 * szam2;

                char cosszeg = osszeg+48;
                cout << cosszeg << endl;
                szamok.push_back(cosszeg);///sajnos nem jó
                ///Char ba nem lehet 27 et belerakni, ezert konvertalast el kell tolni


            }





        }



    }

    return 0;
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
    for (int i = 0; i < lengyel.size(); i++) {
        //cout << lengyel[i] <<endl;
        lengyelfroma = lengyelfroma + lengyel[i];
    }
    //cout << lengyelfroma <<endl;


    return lengyelfroma;
}