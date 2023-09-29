//
// Created by Levi on 2023. 09. 23..
//Verziokezeles:
//https://github.com/NagyLevin/Adatszerkezetek
//

#include "PolishNotation.h"
#include <iostream>
#include <math.h>

using namespace std;


PolishNotation::PolishNotation() {

}

int PolishNotation::ConvertDecimal() {

    int szam = 0;
    //int hatvany = 0;
    //int kiegyenlit =0;
    string number = "";
    for (int i = 0; i < 8; ++i) {
        number = number + szamok.top();
        szamok.pop_back();
    }

    //cout << "ezt akarom 10-re convertalni: " << number <<endl;
    if(number[number.size()-1] == '1'){ //akkor ez egy negativ szam


    }
    if(number[number.size()-1] == '0'){ //akkor ez egy pozitiv szam
        for (size_t i = 0; i < number.size(); ++i) {
            if(number[i] == '1'){
                szam = szam + pow(2,i);
               // cout << szam <<endl;
            }



        }

    }
    //cout << "10eskonverter kimenet: " << szam <<endl;


    return szam;
}
void PolishNotation::convertobinar(int szam) {
    szamok.print();
    if (szam > -1) {


        for (int i = 7; i > -1; --i) {

            if (szam - pow(2, i) > -1) {
                szamok.push_back('1');
                szam = szam - pow(2, i);
            }
            else{
                szamok.push_back('0');
            }

    }
    }

    else if (szam >= -1) {
        szam = abs(szam); //abszolutertek

        for (int i = 7; i > -1; --i) {

            if (szam - pow(2, i) > -1) {
                szamok.push_back('1');
                szam = szam - pow(2, i);
            }
            if (szam - pow(2, i) < -1) {
                szamok.push_back('0');
            }

        }
        szamok.push_back('1');

    }


    cout << "vege binar" <<endl;
    szamok.print();
}

int PolishNotation::evaluate(std::string polish_input) {

    lengyel.clear();
    jelek.clear();
    szamok.clear();

    int osszeg = 0;
    char vege = polish_input[polish_input.size()-1];;
    int z = polish_input.size()-1;
    while (polish_input[z] == terkoz){ //hatha van egy space a vegen
        vege = polish_input[z];
        z = z -1 ;
    }

    if( isdigit(vege) ||  vege == zarojel){ //Ha postfix, akkor nem kell átalakítani
        polish_input = convert(polish_input);

    }






    for (size_t i = 0; i < polish_input.size(); i++) { //ha kaptam 8 szamot huzamban, akkor elkuldom a kiertekelonek, es az visszaad egy int? szamot

        //cout << polish_input[i] <<endl;
        if(isdigit(polish_input[i])){



            szamok.push_back(polish_input[i]);


        }
        //cout << i <<endl;
        //cout << "ez a meret" << polish_input.size() <<endl;
        //cout << polish_input <<endl;
       if(!isdigit(polish_input[i]) && polish_input[i] != terkoz){



                //szamok.print();
                int szam2 = ConvertDecimal();
                //cout << szam2 <<endl;

                int szam1 = ConvertDecimal();
                //cout << "convert utan:" <<endl;
                //szamok.print();


                osszeg = muvelet(szam1,szam2,polish_input[i]);
                cout << osszeg << endl;
                convertobinar(osszeg); // binarisba visszakonvertalom, es pushbackelem

                //char cosszeg = osszeg+48;
                //cout << cosszeg << endl;
                //szamok.push_back(cosszeg);///sajnos nem jó
                ///Char ba nem lehet 27 et belerakni, ezert konvertalast el kell tolni








        }



    }

    cout <<"ket szam osszege: "<< osszeg << endl;
    return osszeg;
}


int PolishNotation::muvelet(int szam1, int szam2,char jel) {
    int osszeg = 0;
    cout << jel <<endl;
    if(jel == '*'){

        //cout << szam1 <<endl;
        //cout << szam2 <<endl;
        osszeg = szam1 * szam2;
        //cout << osszeg <<endl;
        //cout << "egyszer" <<endl;

    }
    if(jel == '+'){
        cout << "sz1: " << szam1 <<endl;
        cout << "sz2: " << szam2 <<endl;
        osszeg = szam1 + szam2;
        //cout << osszeg <<endl;
        //cout << "egyszer" <<endl;


    }
    if(jel == '-'){
        cout << "sz1: " << szam1 <<endl;
        cout << "sz2: " << szam2 <<endl;
        osszeg = szam1 - szam2;
        //cout << osszeg <<endl;
    }
    if(jel == '/'){     //meg baj lehet, ha nem egesz szamokat osztunk egymassal
        osszeg = szam1 / szam2;

    }

    return osszeg;
}

string PolishNotation::convert(string polishInfix) {


    int szamszamlalo = 0;
    lengyel.clear();
    jelek.clear();
    szamok.clear();
    for (size_t i = 0; i < polishInfix.size(); ++i) {

        if( polishInfix[i] != terkoz && !isdigit(polishInfix[i])){

            if(polishInfix[i] == zarojel){


                //char test = jelek[jelek.size()-1]; //kesobb popback majd
                //cout << test << endl;
                                      //addig popback amig nem nyitojelet kapunk vissza
                //cout << jelek[jelek.size()-1] <<endl;
                while(jelek.top() != nyitojel){

                    //cout << jelek[jelek.size()-1] <<endl;
                    lengyel.push_back(terkoz);
                    lengyel.push_back(jelek.top());
                    jelek.pop_back();

                    //cout << jelek[jelek.size()-1] <<endl;
                }

                if(jelek.top() == nyitojel){
                    //cout << jelek[jelek.size()-1] <<endl;

                    jelek.pop_back();
                    //cout << jelek[jelek.size()-1] <<endl;
                }
                //cout << jelek[jelek.size()-1] <<endl;

                if(jelek.size() == 1){
                    lengyel.push_back(terkoz);
                    lengyel.push_back(jelek.top());

                    jelek.pop_back();
                }


            } else{

                if( (polishInfix[i] == '+' || polishInfix[i] == '-') && (jelek.top() == '*' || jelek.top() == '/')){    //szorzas osztas prioritása nagyobb

                    while(jelek.size() > 0){
                        lengyel.push_back(terkoz);
                        lengyel.push_back(jelek.top());

                        jelek.pop_back();

                    }

                }
                if( (polishInfix[i] == '+' || polishInfix[i] == '-') && (jelek.top() == '+' || jelek.top() == '-')) {    //szorzas osztas prioritása nagyobb
                    lengyel.push_back(terkoz);
                    lengyel.push_back(jelek.top());

                    jelek.pop_back();

                }
                if( (polishInfix[i] == '*' || polishInfix[i] == '/') && (jelek.top() == '*' || jelek.top() == '/')) {    //szorzas osztas prioritása nagyobb
                    lengyel.push_back(terkoz);
                    lengyel.push_back(jelek.top());

                    jelek.pop_back();

                }


                jelek.push_back(polishInfix[i]);




            }

        }

        if(isdigit(polishInfix[i])){
            if(szamszamlalo == 8){
                lengyel.push_back(terkoz);

                szamszamlalo = 0;

            }

                //cout << polishInfix[i] <<endl;
                lengyel.push_back(polishInfix[i]); //8 szamjegyenkent el tudjuk valasztani a szamokat()
                szamszamlalo = szamszamlalo + 1;



        }


    }
    if(jelek.size() > 0){
        lengyel.push_back(terkoz);
        lengyel.push_back(jelek.top());



        jelek.pop_back();

    }

    string lengyelfroma = "";
    //lengyel.print();
    //cout << lengyel.size() <<endl;
    int meret = lengyel.size();
    for (int i = 0; i < meret; i++) {
        //cout << lengyel.top() <<endl;
        lengyelfroma = lengyel.top()+lengyelfroma;
        lengyel.pop_back();
    }
    //cout << "" <<endl;
    jelek.print();
    //cout << lengyelfroma <<endl;


    return lengyelfroma;
}