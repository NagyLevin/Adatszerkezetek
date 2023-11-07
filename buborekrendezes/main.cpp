#include <iostream>
#include "vector"

int main() {

   std::vector<int> tomb;

    tomb = {7, 6 , 5 , 4 , 2};

    for (int i = 0; i < tomb.size(); ++i) {
        std::cout << tomb[i] << "ittavege" << std::endl;

    }

    for (int j = 0; j < tomb.size()-1 ; ++j) {

        for (int i = 0; i < tomb.size()-1; ++i) {


            if (tomb[i] > tomb[i + 1]) {
                int temp = tomb[i + 1];
                tomb[i + 1] = tomb[i];
                tomb[i] = temp;


            }

        }
    }

    for (int i = 0; i < tomb.size(); ++i) {
        std::cout << tomb[i] <<std::endl;

    }




    std::cout << "Hello, World!" << std::endl;
    return 0;
}
