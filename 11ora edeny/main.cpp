#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;


void bucketSort(int vec[], size_t n) {
    if(n < 2){


    }
    int min = vec[0] ;
    int max = vec[0];

    for (int i = 0; i < n; ++i) {
        if(vec[i] < min){
            min = vec[i];
        }
        if(vec[i] > max){
            max = vec[i];
        }

    }

    vector<int> buckets(max-min+1,0); //tartomany //azert +1 mert a min max ot is taroljuk
    //dafault ertek 0

    for (int i = 0; i < n; ++i) {
        buckets[vec[i]-min ]++;


    }

    int s = 0;

    for (int i = 0; i < buckets.size(); ++i) {
        for (int j = 0; j < buckets[i]; ++j) {
            vec[s++] = min+i;

        }



    }





}

template<typename T, typename Keyfun>
void bucketSort(T vec[], size_t n, Keyfun f) {
    if(n < 2){
    }


    int min = f(vec[0]) ;
    int max = f(vec[0]);

    for (int i = 0; i < n; ++i) {
        if(f(vec[i]) < min){
            min = f(vec[i]);
        }
        if(f(vec[i]) > max){
            max = f(vec[i]);
        }

    }

    vector<queue<T>> buckets(max-min+1); //tartomany //azert +1 mert a min max ot is taroljuk


    for (int i = 0; i < n; ++i) {
        buckets[f(vec[i]) - min ].push(vec[i]);


    }

    int s = 0;

    for (int i = 0; i < buckets.size(); ++i) {
        while(!buckets[i].empty()) {
            vec[s++] = buckets[i].front();
            buckets[i].pop(); //tavolitsuk is el a sorbol az elemet

        }


        }





}

struct Date {
    int year, month, day;
    Date(int y, int m, int d) : year(y), month(m), day(d) {}
    Date() : year(0), month(0), day(0) {}
    // Csak ellenorzes vegett, a radixSort nem fogja hasznalni
    bool operator<(const Date &rhs) {
        return (this->year < rhs.year || (this->year == rhs.year && (this->month < rhs.month || (this->month == rhs.month && this->day < rhs.day))));
    }
};

int getDay(Date& d){
    return d.day;
}

int getMonth(Date& d){
    return d.month;
}

int getYear(Date& d){
    return d.year;
}



void radixSort(Date vec[], size_t size) { //harom edenyrendezes egymas utan

    bucketSort(vec,size, getDay);
    bucketSort(vec,size, getMonth);
    bucketSort(vec,size, getYear);


}

// Ellenorzesre. C++11 ota az algorithm headerben megtalalhato
template<typename Iterator> bool isSorted(Iterator begin, Iterator end) {
    if (begin == end) {
        return true;
    }
    Iterator previous = begin;
    Iterator current = begin;
    ++current;
    for (; current != end; ++current) {
        if (*current < *previous) {
            return false;
        }
        ++previous;
    }
    return true;
}

int main() {
    srand(time(NULL));
    const std::size_t LARGE_TEST_SIZE = 100000;

    ///BucketSort
    cout << endl << "bucketSort tesztelese: " << endl;
    const int n = 11; //contst kell hogy ne dinamikusan legyen ertekadas
    int t2[n] = { 123, 2, -3, 9998, 10, 15, -12, -120, 112, 998, 0 };
    bucketSort(t2, n);
    for (int i = 0; i < n; i++)
        cout << t2[i] << ' ';
    std::cout << std::endl;
    std::cout << "bucketSort : " << (isSorted(t2, t2 + n) ? "OK" : "NOK")
              << std::endl;
    std::cout << "Nagyobb teszt : " << std::flush;
    int *t2large = new int[LARGE_TEST_SIZE];
    for (std::size_t i = 0; i < LARGE_TEST_SIZE; ++i) {
        t2large[i] = rand() % 1000;
    }
    bucketSort(t2large, LARGE_TEST_SIZE);

    std::cout << (isSorted(t2large, t2large + LARGE_TEST_SIZE) ? "OK" : "NOK")
              << std::endl;
    delete[] t2large;

    ///RadixSort
    cout << endl << "radixSort tesztelese: " << endl;
    const int datesize = 7;
    Date dates[datesize] = { Date(2013, 3, 9), Date(1993, 2, 26), Date(2012, 2,
                                                                       12), Date(2000, 12, 21), Date(1994, 9, 11), Date(2000, 1, 1), Date(
            1999, 12, 31) };
    radixSort(dates, datesize);
    for (int i = 0; i < datesize; i++)
        cout << dates[i].year << '.' << dates[i].month << '.' << dates[i].day
             << endl;
    std::cout << std::endl;
    std::cout << "radixSort : "
              << (isSorted(dates, dates + datesize) ? "OK" : "NOK") << std::endl;
    std::cout << "Nagyobb teszt : " << std::flush;
    Date *dlarge = new Date[LARGE_TEST_SIZE];
    for (std::size_t i = 0; i < LARGE_TEST_SIZE; ++i) {
        dlarge[i] = Date(rand() % 2014, rand() % 12 + 1, rand() % 28 + 1);
    }
    radixSort(dlarge, LARGE_TEST_SIZE);

    std::cout << (isSorted(dlarge, dlarge + LARGE_TEST_SIZE) ? "OK" : "NOK")
              << std::endl;
    delete[] dlarge;
}