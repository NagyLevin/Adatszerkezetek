#include <iostream>

using namespace std;

void doSomething(int & a, int & b) {    //jobb referencia kent atadni, mert akkor nem foglalodik uj memoria terulet
 a++;
 b++;
}


int main()
{
    cout << "Hello world!" << endl;



   // int i;  //valtozo
   // int & r = i;    //referencia ugyanaz a valtozo, nem foglal uj memoriat
   // int * p = & i;  //pionter, melynek foglalodik memoriaterület, memoriacimet tárol
    int t[] = {1, 2, 3, 4}; //tömb
    /*
    int fv() { return 1;}   //függvény

    int square(int x) { //parameteres fv //ha void, akkor eljaras, ami nem ad vissza semmit
        return x*x; }
    */
    { int i = 1; int j = 2;}
    //while (condition) statement;
    //for( ; ; ) statement;
    //if (condition) statement1;
    //    else statement2;
    //switch (condition) {
    //    case <case1>: statements; <break>
    //    default:      statements;

    int i = 10;
    cout <<i <<endl; //változo kiirása
    int* p = &i;
    *p++;
    cout << *p <<endl; //memoriacim erteke
    cout << p <<endl; //memoriacim kiirasa
    int* & r2 = p;
    (*r2)++;
    cout << i <<endl;


    const int z = 5; //ezt nem lehet modositani
    //const int & z;

/*
    for (int &v : tomb) {   //foreachszerü
        v = 2 * v;
        cout << v;
        }

*/









    return 0;
}
