#include <iostream>
#include "vector"
#include "FixedSor.h"
#include "FixedVerem.h"
#include "DinamicVerem.h"
#include "DinamicSor.h"
#include "2xList.h"
#include "binfa.h"
#include "awltree.h"

using namespace std;




int main() {

    //sor
    FixedQueue sor;
    sor.in(1);

    //verem
    FixedStack verem;
    verem.push(1);

    //Dinamic Stack
    DynamicIntStack DinamicVerem;
    DinamicVerem.push(10);
    DinamicVerem.print();

    //Dinamic Queue
    DynamicIntQueue DinamicSor;
    DinamicSor.in(11);
    DinamicSor.print();


    //zhpelda

    //2xLancoltlista
    List<int> lista;

    lista.insertFirst(10);
    lista.print();

    //Binarfa
    Bs_tree<int> binarfa;
    //binarfa.insert(1);
    //binarfa.find(1);

    //avlfa
    AvlTree<int> awl;
    awl.insert(13);
    awl.getRoot();


    //piros fekete?





    return 0;
}
