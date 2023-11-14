#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

/// Osszefesul ket rendezett sorozatot. //feltesszuk hogy rendezetttek
void mergeArrays(const int vec1[], size_t n1, const int vec2[], size_t n2, int result[]) {
	unsigned int it1,it2,it3 = 0;
    while (it1 < n1 &&  it2 < n2){
        if(vec1[it1] < vec2[it2]){
            result[it3++] = vec1[it1++]; //kiolvassuk majd növeljuk az erteket
        }
        else if(vec1[it1] > vec2[it2]){ //masik nagyobb
            result[it3++] = vec2[it2++];
        }
        else if(vec1[it1] == vec2[it2]){   //egyenloek
            result[it3++] = vec1[it1++];
            result[it3++] = vec2[it2++];

        }

    }
    while (it1 < n1 ){  //ha meg maradtak valamelyikben elemek
        result[it3++] = vec1[it1++];

    }
    while (it2 < n2 ){
        result[it3++] = vec2[it2++];

    }



}

void mergeSort(int vec[], size_t n) {
	if(n <2){
        return;
    }
    int n1 = n/2 , n2 = n-n1;

    mergeSort(vec,n1);  //vektor ket reszre bontasa
    mergeSort(vec+n1,n2);   //vektor ket reszre bontasa

    int elsofel[n1] , masodikfel[n2];

    for (int i = 0; i < n1; ++i) {
        elsofel[i] = vec[i];

    }
    for (int i = 0; i < n2; ++i) {
        masodikfel[i] = vec[n1+i];//n1 el eltolva nezzuk az ertekeket

    }
    mergeArrays(elsofel,n1,masodikfel,n2,vec);//osszefesules meghivasa



}


int main() {
	srand(time(NULL));
	const std::size_t LARGE_TEST_SIZE = 100000;
	/// MergeSort
	cout << "mergeSort tesztelese:" << endl;
	const int n = 11;
	int t[n] = { 123, 2, -3, 9998, 10, 15, -12, -120, 112, 998, 0 };
	mergeSort(t, n);
	for (int i = 0; i < n; i++)
		cout << t[i] << ' ';
	std::cout << std::endl;
	std::cout << "mergeSort : " << (is_sorted(t, t + n) ? "OK" : "NOK")
			<< std::endl;
	std::cout << "Nagyobb teszt : " << std::flush;
	int * tlarge = new int[LARGE_TEST_SIZE];
	for (std::size_t i = 0; i < LARGE_TEST_SIZE; ++i) {
		tlarge[i] = rand();
	}
	mergeSort(tlarge, LARGE_TEST_SIZE);

	std::cout << (is_sorted(tlarge, tlarge + LARGE_TEST_SIZE) ? "OK" : "NOK")
			<< std::endl;
	delete[] tlarge;

}
