#include <iostream>
#include "vector"
using namespace std;

int shakesort(vector<int> v){

    int minmax = v[0];



    for (int i = 0; i < v.size(); ++i) {

        for (int j = 0; j < v.size(); ++j) {

            if(minmax > v[j]){

                int temp = minmax;
                minmax = v[j];
                v[j] = temp;



            }



        }
        for (int j = v.size()-1; j > i; --j) {

            if(minmax < v[j]){

                int temp = minmax;
                minmax = v[j];
                v[j] = temp;



            }



        }


    }

    for (int i = 0; i < v.size(); ++i) {
        cout <<  v[i] <<endl;

    }


    return 0;
}


int main() {

    vector<int> v1;
    int meret = 100;

    for (int i = 0; i < meret; ++i) {
        v1.push_back(rand()%100);

    }


    shakesort(v1);







    return 0;
}
