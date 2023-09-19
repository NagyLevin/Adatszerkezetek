#include <iostream>
using namespace std;

void Pelda1(){
    std::cout << "Hello, World!" << std::endl;
    int    i  = 5;
    double d  = 4.0;
    int &  r  = i;
    cout << r << endl;

    r++;        //egyet hozzaad az ertekhez

    cout << r << endl;


    int *  p  = &i;

    cout << p << endl;  //p csak egy memóriacim


    (*p)++;

    cout << p << endl; //memoriacimen levo ertekhez ad hozza egyet


    int* & r2 = p;
    (*r2)++;
    int &  r3 = *p;
    const int & k = 6;
    int ** p2 = &p;
    (**p2)++;

    //pelda1
}

void Pelda2(){
    // Ez a program demonstralja a valtozok es a memoria kapcsolatat

    /*
    cout << "1. ora 1. demonstracio - Valtozok\n";

    int i = 5; // Valtozo sajat memoriaterulettel
    cout << "Az i memoriacime " << &i << ", tipusa " << type_name<decltype(i)>()
         << " es a memoriaterulet tartalma " << i << "\n";
    int &r = i; // Referencia az elozo valtozora
    cout << "Az r memoriacime " << &r << ", tipusa " << type_name<decltype(r)>()
         << " es a memoriaterulet tartalma " << r << "\n";

    int *p = &i; // Pointer az elozo memoriateruletre
    cout << "A  p memoriacime " << &p << ", tipusa " << type_name<decltype(p)>()
         << " es a memoriaterulet tartalma " << p << "\n";
    cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
         << ", tipusa " << type_name<decltype(*p)>() << " es annak tartalma "
         << (*p) << "\n";

    cout << "Vegyuk eszre, hogy az eredeti valtozo es a referencia ugyanazon a "
            "cimen dolgozik\n";
    cout << "Vegyuk eszre, hogy a pointer altal tarolt cim pontosan az a cim, "
            "ami az i valtozo cime\n";
    cout << "Tovabba, nezzuk meg azt is, hogy a pointer teljesen mas cimen "
            "talalhato\n";

    cout << "---------------------------------------------------\n";
    cout << "Valtoztassuk meg az ertekeket";
    i++;
    cout << "Az i memoriacime " << &i << " es a memoriaterulet tartalma " << i
         << endl;
    cout << "Az r memoriacime " << &r << " es a memoriaterulet tartalma " << r
         << endl;
    cout << "A  p memoriacime " << &p << " es a memoriaterulet tartalma " << p
         << endl;
    cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
         << " es annak tartalma " << (*p) << endl;
    cout << "---------------------------------------------------\n";
    r++;
    cout << "Az i memoriacime " << &i << " es a memoriaterulet tartalma " << i
         << endl;
    cout << "Az r memoriacime " << &r << " es a memoriaterulet tartalma " << r
         << endl;
    cout << "A  p memoriacime " << &p << " es a memoriaterulet tartalma " << p
         << endl;
    cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
         << " es annak tartalma " << (*p) << endl;
    cout << "---------------------------------------------------n";
    (*p)++;
    cout << "Az i memoriacime " << &i << " es a memoriaterulet tartalma " << i
         << "\n";
    cout << "Az r memoriacime " << &r << " es a memoriaterulet tartalma " << r
         << "\n";
    cout << "A  p memoriacime " << &p << " es a memoriaterulet tartalma " << p
         << "\n";
    cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
         << " es annak tartalma " << (*p) << "\n";
    // FIGYELEM!!
    cout << "---------------------------------------------------\n";
    cout << "- MOST JON EGY SZOKASOS HIBA, ELRETTENTO PELDANAK -\n";
    cout << "---------------------------------------------------\n";
    p++; // Itt a memóriacímet változtatjuk meg
    cout << "Az i memoriacime " << &i << " es a memoriaterulet tartalma " << i
         << "\n";
    cout << "Az r memoriacime " << &r << " es a memoriaterulet tartalma " << r
         << "\n";
    cout << "A  p memoriacime " << &p << " es a memoriaterulet tartalma " << p
         << "\n";
    cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
         << " es annak tartalma " << (*p) << "\n";
    cout << "Nezzuk meg, hogy az uj terulet mogotti dolgokat meg lehet-e "
            "valtoztatni!\n";
    cout << "Itt valami teljesen mas tortenik! A memoriateruletet valtoztattuk "
            "meg!\n";
    (*p)++;
    cout << "A  p memoriacime " << &p << " es a memoriaterulet tartalma " << p
         << "\n";
    cout << "A  p altal hivatkozott memoriaterulet cime " << (&(*p))
         << " es annak tartalma " << (*p) << "\n";
    cout << "Ne feledjuk, c++-ban alapvetoen mindent lehet, kiveve par dolgot "
            "amit tilos!\n";

    */
}
void Pelda3(){
    char *pc = nullptr;     // OK
    int  *pi = nullptr;     // OK
    //bool   b = nullptr;     // OK. b = false.
    //int    i = nullptr;     // hiba

};


void Pelda4(){
    int tomb[5];
    int* p;
    p = tomb; //0 elemre mutat
    *p = 10;

    p++;
    *p = 20;
    p = &tomb[2];
    *p = 30;
    p = tomb + 3; //3. indexu elemre mutat
    *p = 40;
    p = tomb;
    *(p+4) = 50; //negyedik indexure mutat
    cout << tomb[0] << endl;
    cout << tomb[1] << endl;
    cout << tomb[2] << endl;
    cout << tomb[3] << endl;
    cout << tomb[4] << endl;
    //cout << tomb[5] << endl; //rossz eset, kiindexelunk a tombbol, barmi lehet ott


};
void Pelda5(){
    int* p;
    p = new int;
    *p = 10;
    delete p; //
    *p = 20;
    /*
    Amit lefoglalunk azt fel kell szabadítanunk: praktikusan a new és delete párban álljon valamilyen módon.
    delete után tilos hozzáférni a memóriaterülethez, amit felszabadítottunk
    Jó megoldás lehet:

    A delete p; hívás után a p értékét nullptr-re állítjuk: p=nullptr;
    smart pointers – későbbiekben.
     */
};

int main() {

    //Pelda1();
    //Pelda2(); //nem mükszik, de csak a typokat irja ki
    //Pelda3();
    //Pelda4();
    //Ha nem használunk többet egy pointert nullazzuk!!!!!!
    //figyeljuk meddig tartja meg az erteket
    //lokális változora, ami megszünik, ne rakjuk pointert
    //konsttal olyan erteket adunk meg, melyet nem tudunk NEM AKARUNK változtatni
    //lehet konstans memoriacm is, ami nem modosithato
    //vigyázz, mert tudunk tömböt túlindexelni

    Pelda5();
    //a dinamikus memoriakezelesnel nekunk kell manualisan lefoglani a memoriat
    //Konstans cim letezese op rendszertol programmtol es tipustol fugg
    //Ha tombot torolunk, akkor delete tomb[], mert kulonben csak az elso elem torlodik





    return 0;
}
