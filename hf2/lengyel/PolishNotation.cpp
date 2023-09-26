//
// Created by Levi on 2023. 09. 23..
//

#include "PolishNotation.h"
#include <iostream>
#include <math.h>

using namespace std;


PolishNotation::PolishNotation() {

}

int PolishNotation::ConvertDecimal() {

    int szam = 0;
    int hatvany = 0;
    int kiegyenlit =0;
    string number = "";
    for (int i = 0; i < 8; ++i) {
        number = number + szamok[szamok.size()-1];
        szamok.pop_back();
    }

    //cout << number <<endl;
    for (size_t i = number.size()-1; i > 0; --i) {
        int hanyszor = (int(number[hatvany]))-48;
        if(hanyszor == 1 && i == number.size()){
            kiegyenlit = 1;
        }
        //cout << hanyszor <<endl;
        int khatvany = pow(2,hatvany);
        //cout << "ez a hatvany: " << khatvany <<endl;
        szam = szam + (hanyszor * khatvany);

        hatvany = hatvany +1;

    }


    //cout << "ToDecElott:" << szam <<endl;
    //cout << "Ez az utcso karakter:" << number[number.size()-1] <<endl;
    if(number[number.size()-1] == '1'){ //utolso eleme
        szam = szam -pow(2,hatvany)+kiegyenlit;
        //cout << szam  <<endl;
        //cout << pow(2,hatvany)  <<endl;
    }


   //cout << "ToDec:" << szam <<endl;

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

        //cout << "convertalas infix" << polish_input <<endl;
        //if(polish_input[polish_input.size()-1] == terkoz && isdigit(polish_input[polish_input.size()-1]) && polish_input[polish_input.size()-1] == zarojel){
      //      cout << "convertalas infix" << polish_input <<endl;
            polish_input = convert(polish_input);

       // }
    //cout << "convertalas nelkul" << polish_input <<endl;





    for (size_t i = 0; i < polish_input.size(); i++) { //ha kaptam 8 szamot huzamban, akkor elkuldom a kiertekelonek, es az visszaad egy int? szamot

        //cout << polish_input[i] <<endl;
        if(isdigit(polish_input[i])){



            szamok.push_back(polish_input[i]);


        }
        //cout << i <<endl;
        //cout << "ez a meret" << polish_input.size() <<endl;
        //cout << polish_input <<endl;
       if(!isdigit(polish_input[i]) && polish_input[i] != terkoz){




                int szam2 = ConvertDecimal();
                //cout << szam2 <<endl;

                int szam1 = ConvertDecimal();


                osszeg = muvelet(szam1,szam2,polish_input[i]);
                //cout << osszeg << endl;
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
    //cout << jel <<endl;
    if(jel == '*'){

        //cout << szam1 <<endl;
        //cout << szam2 <<endl;
        osszeg = szam1 * szam2;
        //cout << osszeg <<endl;
        //cout << "egyszer" <<endl;

    }
    if(jel == '+'){
        //cout << "sz1: " << szam1 <<endl;
        //cout << "sz2: " << szam2 <<endl;
        osszeg = szam1 + szam2;
        //cout << osszeg <<endl;
        //cout << "egyszer" <<endl;


    }
    if(jel == '-'){
        //cout << "sz1: " << szam1 <<endl;
        //cout << "sz2: " << szam2 <<endl;
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
                lengyel.push_back(terkoz);
                lengyel.push_back(jelek[jelek.size()-1]);                        //addig popback amig nem nyitojelet kapunk vissza
                //cout << jelek[jelek.size()-1] <<endl;
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
    if(jelek.size() > 0){
        lengyel.push_back(terkoz);
        lengyel.push_back(jelek[jelek.size()-1]);


        jelek.pop_back();
    }

    string lengyelfroma = "";
    for (size_t i = 0; i < lengyel.size(); i++) {
        //cout << lengyel[i] <<endl;
        lengyelfroma = lengyelfroma + lengyel[i];
    }

    //cout << lengyelfroma <<endl;


    return lengyelfroma;
}