
#ifndef MERGE3WAY_HPP
#define MERGE3WAY_HPP
#include <vector>
using namespace std;
//set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")
void myMerge(const int v1[], size_t n1, const int v2[], size_t n2,const int v3[], size_t n3, int result[]){

    unsigned int it1,it2,it3 = 0;
    int resultemp[n1+n2];

    while (it1 < n1 &&  it2 < n2){
        if(v1[it1] < v2[it2]){
            resultemp[it3++] = v1[it1++]; //kiolvassuk majd növeljuk az erteket
        }
        else if(v1[it1] > v2[it2]){ //masik nagyobb
            resultemp[it3++] = v2[it2++];
        }
        else if(v1[it1] == v2[it2]){   //egyenloek
            resultemp[it3++] = v1[it1++];
            resultemp[it3++] = v2[it2++];

        }

    }

    while(it1 < n1){
        resultemp[it3++] = v1[it1++];
    }
    while(it2 < n2){
        resultemp[it3++] = v2[it2++];
    }

    it1 = 0;
    it2 =0;
    it3 = 0;

    while (it1 < n1+n2 &&  it2 < n3){
        if(resultemp[it1] < v3[it2]){
            result[it3++] = resultemp[it1++]; //kiolvassuk majd növeljuk az erteket
        }
        else if(resultemp[it1] > v3[it2]){ //masik nagyobb
            result[it3++] = v3[it2++];
        }
        else {
            result[it3++] = resultemp[it1++];
            result[it3++] = v3[it2++];

        }

    }

    while(it1 < n1+n2){
        result[it3++] = resultemp[it1++];
    }
    while(it2 < n3){
        result[it3++] = v2[it2++];
    }




}

void mySort(int myArr[], size_t h){
    if(h <3){
        return; //nem lehet 3 reszre osztani
    }
    int h1 = h/3;
    int h2 = (h-h1)/2;
    int h3 = h -h2 -h1;

    //cout << "h1: " << h1 << " h2: " << h2 << " h3: " << h3 << " eredeti: " <<h << " en szamom: " << h1+h2+h3 <<endl;

      mySort(myArr,h1);
      mySort(myArr+h1,h2);
      mySort(myArr+h1+h2,h3);


    int v1[h1], v2[h2], v3[h3];


    for(int i = 0; i<h1; i++){
        v1[i] = myArr[i];
        cout << v1[i] <<endl;
    }
   cout << "v1 vege" <<endl;
    for(int i = 0; i<h2; i++){
        v2[i] = myArr[i+h1];
        cout << v2[i] <<endl;
    }
    cout << "v2 vege" <<endl;
    for(int i = 0; i<h3; i++){
        v3[i] = myArr[i+h1+h2];
        cout << v3[i] <<endl;
    }
    cout << "v3 vege" <<endl;

   myMerge(v1,h1,v2,h2,v3,h3,myArr);
    //cout << "ez a hossza az arraynak: " << sizeof(myArr) <<endl;




}

void mergeSort3(vector<int> &myArr)
{
    int newArr[myArr.size()];
    //cout << "ez a hossza az arraynak: " << myArr.size() <<endl;

    for (int j = 0; j < myArr.size(); ++j) {
        newArr[j] = myArr[j];
        cout << newArr[j] <<endl;

    }
    cout << "kezdeti ertekeek" <<endl;

    mySort(newArr,myArr.size());


    for (int j = 0; j < myArr.size(); ++j) {

        cout << newArr[j] <<endl;

    }
    cout << "vegen" <<endl;



}


#endif