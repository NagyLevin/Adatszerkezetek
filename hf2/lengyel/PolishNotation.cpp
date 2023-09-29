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

    if(number[number.size()-1] == '0'){ //akkor ez egy pozitiv szam
        int meret = number.size();
        for (int i = 0; i < meret; ++i) {
            if(number[i] == '1'){
                szam = szam + pow(2,i);
               // cout << szam <<endl;
            }



        }

    }
    if(number[number.size()-1] == '1') { //akkor ez egy negativ szam
        int meret = number.size();
        for (int i = 0; i < meret-1; ++i) {
            if (number[i] == '1') {
                szam = szam + pow(2, i);
                // cout << szam <<endl;
            }

        }
        szam = szam -128;
        //szam = szam *-1;
    }

    //cout << "10eskonverter kimenet: " << szam <<endl;


    return szam;
}
void PolishNotation::convertobinar(int szam) {

    int szamertek = szam ;
    int lepesszam = 0;
    cout << "ez a szam : " << szam <<endl;
    while(szam != 0){




        szam = szam / 2;
        lepesszam = lepesszam +1;
    }

    //cout << "a leopeszam : " << lepesszam <<endl;

    if(szamertek > 0){

        for (int i = 0; i < 8-lepesszam; ++i) {

            szamok.push_back('0');
            //cout << " maradek 0" <<endl;

        }
        for (int i = 0; i < lepesszam; ++i) {

            szamok.push_back('1');
            //cout << " maradek 0" <<endl;

        }


    }
    if(0 > szamertek){
        lepesszam = lepesszam -1;
        for (int i = 0; i < 8-lepesszam; ++i) {

            szamok.push_back('1');
            //cout << " maradek 1" <<endl;

        }
        for (int i = 0; i < lepesszam; ++i) {

            szamok.push_back('0');
            //cout << " maradek 0" <<endl;

        }



    }




    //cout << "vege binar" <<endl;

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
                cout << "muvelet ultan: " <<  osszeg << endl;
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

        cout << "sz1: " << szam1 <<endl;
        cout << "sz2: " << szam2 <<endl;
        osszeg = szam1 * szam2;
        //cout << osszeg <<endl;
        //cout << "egyszer" <<endl;

    }
    if(jel == '+'){
       // cout << "sz1: " << szam1 <<endl;
      //  cout << "sz2: " << szam2 <<endl;
        osszeg = szam1 + szam2;
        //cout << osszeg <<endl;
        //cout << "egyszer" <<endl;


    }
    if(jel == '-'){
      //  cout << "sz1: " << szam1 <<endl;
      //  cout << "sz2: " << szam2 <<endl;
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