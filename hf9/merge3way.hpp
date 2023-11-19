
#ifndef MERGE3WAY_HPP
#define MERGE3WAY_HPP
#include <vector>
using namespace std;
//set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall -Wextra -pedantic")
std::vector<int> merge(std::vector<int>& v1, std::vector<int>& v2) {
    std::vector<int> result;
    result.clear();

    unsigned int it1 = 0, it2 = 0, it3 = 0;
    int n1 = v1.size();
    int n2 = v2.size();




    while(it1 < n1 && it2 < n2){
        if(v1[it1] > v2[it2]){
            result.push_back( v1[it1++]);
        }
        else if (v1[it1] < v2[it2]){
            result.push_back( v2[it2++]);
        }
        else{
            result.push_back( v1[it1++]);
            result.push_back( v2[it2++]);
        }
    }
    while(it1 < n1){
        result.push_back( v1[it1++]);
    }
    while(it2 < n2){
        result.push_back( v2[it2++]);
    }




    return result;
}

void mySort(vector<int> &vec){
    if (vec.size() <= 2) {
        return;
    }

    int size = vec.size();
    int mid1 = size / 3;
    int mid2 = mid1 * 2;

   // cout << mid1 << " " << mid2 << " " << vec.size() <<endl;

    std::vector<int> v1(vec.begin(), vec.begin() + mid1);
   // cout << v1.size() <<endl;
    std::vector<int> v2(vec.begin() + mid1, vec.begin() + mid2);
    //cout << v2.size() <<endl;
    std::vector<int> v3(vec.begin() + mid2, vec.end());
    //cout << v3.size() <<endl;

    mySort(v1);
    mySort(v2);
    mySort(v3);

    if(v2.size() % 3 != 0){
        if(v2[0] < v2[1]){
            int temp = v2[0];
            v2[0]  = v2[1];
            v2[1] = temp;

        }

    }
    if(v1.size() % 3 != 0){
        if(v1[0] < v1[1]){
            int temp = v1[0];
            v1[0]  = v1[1];
            v1[1] = temp;

        }

    }

    vec = merge(v1, v2);
    for (int i = 0; i < vec.size(); ++i) {
       // cout << "vec: " << vec[i] <<endl;
    }


    if(v3.size() % 3 != 0){
        if(v3[0] < v3[1]){
            int temp = v3[0];
            v3[0]  = v3[1];
            v3[1] = temp;

        }

    }



    vec = merge(v3, vec);
    for (int i = 0; i < vec.size(); ++i) {
       // cout << "vec2: " << vec[i] <<endl;
    }

}

void mergeSort3(vector<int> &myArr)
{
    //  cout << "futas elkezdve" <<endl;
    int meret = myArr.size();
    // cout << meret <<endl;


    // int newArr[meret];


    //cout << "ez a hossza az arraynak: " << myArr.size() <<endl;
/*
    for (int j = 0; j < meret; ++j) {
        //    newArr[j] = myArr[j];
      //  cout << myArr[j] <<endl;

    }
    cout << "kezdeti ertekeek" <<endl;
*/
    mySort(myArr);

    //int temp = myArr[0];
    //myArr[0] = myArr[1];
    //myArr[1] = temp;


    //myArr.clear();



    //myArr.insert(myArr.end(), newArr, newArr+meret);
    /*
    for (int j = 0; j < meret; ++j) {

        cout << myArr[j] <<endl;

    }
    cout << "vegen" <<endl;
*/

    return;
}


#endif