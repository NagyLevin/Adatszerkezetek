#include <iostream>
#include "vector"
using namespace std;
//shakesort



void printVector(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}
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
        cout <<  v[i] <<" ";

    }


    return 0;
}



const int RUN = 32;

// This function sorts array from left
// index to to right index which is
// of size atmost RUN
void insertionSort(int arr[], int left, int right)
{
    for (int i = left + 1; i <= right; i++) {
        int temp = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > temp) { //amíg j nem az eslő eleme a tombnek es arr j edik eleme nagyobb mint a tomb aktualis eleme addig minden elemet megcserélünk az elötte levővel

           // cout << arr[j] << " " << arr[j +1]  << temp <<endl;
            arr[j + 1] = arr[j]; //magyarul ha kettesével haladva találunk egy rossz sorrendben lévő elemet, akkor azt vissza letoljuk a tomb azon reszeig, ahol már a temp nagyobb az elemnél

            j--;
        }
        arr[j + 1] = temp;
    }
}
// Utility function to print the Array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d  ", arr[i]);
    printf("\n");
}


// Merge function merges the sorted runs
void merge(int arr[], int l, int m, int r)
{

    // Original array is broken in two
    // parts left and right array
    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];
    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0;
    int j = 0;
    int k = l;

    // After comparing, we
    // merge those two array
    // in larger sub array
    while (i < len1 && j < len2) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of
    // left, if any
    while (i < len1) {
        arr[k] = left[i];
        k++;
        i++;
    }

    // Copy remaining element of
    // right, if any
    while (j < len2) {
        arr[k] = right[j];
        k++;
        j++;
    }
}

// Iterative Timsort function to sort the
// array[0...n-1] (similar to merge sort)
void timSort(int arr[], int n) //array merete
{
    printArray(arr, n);

    // Sort individual subarrays of size RUN
    for (int i = 0; i < n; i += RUN)
        insertionSort(arr, i, min((i + RUN - 1), (n - 1))); //(array) (left i azaz hogy hol tartunk) right pedig visszaadja hogy vagy a tomb merete legyen vagy a RUN + i




    // Start merging from size RUN (or 32).
    // It will merge
    // to form size 64, then 128, 256
    // and so on ....
    for (int size = RUN; size < n; size = 2 * size) {

        // pick starting point of
        // left sub array. We
        // are going to merge
        // arr[left..left+size-1]
        // and arr[left+size, left+2*size-1]
        // After every merge, we
        // increase left by 2*size
        for (int left = 0; left < n; left += 2 * size) {

            // Find ending point of
            // left sub array
            // mid+1 is starting point
            // of right sub array
            int mid = left + size - 1;
            int right = min((left + 2 * size - 1), (n - 1));

            // merge sub array arr[left.....mid] &
            // arr[mid+1....right]
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }

    printArray(arr, n);

}
///////////////////////////////////////eddig timsort

std::vector<int> merge(std::vector<int>& v1, std::vector<int>& v2) {
    std::vector<int> result;
    result.clear();

    unsigned int it1 = 0, it2 = 0;
    unsigned int n1 = v1.size();
    unsigned int n2 = v2.size();






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

void batcherSort(vector<int> &vec){
    //printVector(vec);


    if (vec.size() < 4) {
        return;
    }

    int size = vec.size();
    int s1 = size / 2;


    // cout << mid1 << " " << mid2 << " " << vec.size() <<endl;

    std::vector<int> v1(vec.begin(), vec.begin() + s1);
    // cout << v1.size() <<endl;
    std::vector<int> v2(vec.begin() + s1,vec.end() );
    //cout << v2.size() <<endl;

    batcherSort(v1);
    batcherSort(v2);


    if(v2.size() % 3 != 0){//egy kis hackeles, hogy a ket elemü vektorok is rendezve legyenek
        if(v2[0] < v2[1]){
            swap(v2[0],v2[1]);

        }

    }
    if(v1.size() % 3 != 0){
        if(v1[0] < v1[1]){
            swap(v1[0],v1[1]);

        }

    }



    vector<int> v1p;
    vector<int> v2np;

    vector<int> bV;
    vector<int> v1np;
    vector<int> v2p;
    vector<int> bU;

    for (int i = 0; i < v1.size(); ++i) {
        if(i % 2 == 0){
            v1p.push_back(v1[i]);
        }
        else{
            v1np.push_back(v1[i]);
        }

    }
    for (int i = 0; i < v2.size(); ++i) {
        if(i % 2 == 0){
            v2p.push_back(v2[i]);
        }
        else{
            v2np.push_back(v2[i]);
        }

    }




   bV = merge(v1p, v2np); //elso ketto merge
   bU = merge(v2p, v1np); //elso ketto merge
   vec = merge( bV, bU); //elso ketto merge





















}




int main() {

    vector<int> v1;
    int meret = 100;

    for (int i = 0; i < meret; ++i) {
        v1.push_back(rand()%100);

    }
    int arr[] = { -2, 7,  15,  -14, 0, 15,  0, 7,
                  -7, -4, -13, 5,   8, -14, 12 };
    int n = sizeof(arr) / sizeof(arr[0]);





    //timSort(arr, n);

    //shakesort(v1);

    printVector(v1);
    batcherSort(v1);
    printVector(v1);





    return 0;
}
