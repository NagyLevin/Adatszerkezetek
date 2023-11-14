#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

/// Osszefesul ket rendezett sorozatot. //feltesszuk hogy rendezetttek
void mergeArrays(const int vec1[], size_t n1, const int vec2[], size_t n2, int result[]) {
	// TODO
    (void)vec1;
    (void)n1;
    (void)vec2;
    (void)n2;
    (void)result;
}

void mergeSort(int vec[], size_t n) {
	// TODO



    (void)vec;
    (void)n;
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
