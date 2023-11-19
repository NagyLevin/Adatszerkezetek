#include <iostream>
#include <vector>
#include "woodpecker.hpp"
#include "merge3way.hpp"
#include <cstdlib>

TEST("Short, simple"){
    const int L = 10;
    std::vector<int> base,arr_baseline,arr_student;
    for (int i = 0; i < L; ++i) {
        base.push_back(i);
    }
    arr_student = base;
    mergeSort3(arr_student);

    auto comp = [](int a, int b) {
        return a > b;
    };
/*  for (int num : arr_student) {
        std::cout << num << " ";
    }*/

    bool sorted = std::is_sorted(arr_student.begin(), arr_student.end(), comp);
    CHECK_EQ(true, sorted);
}

TEST("Empty"){
    std::vector<int> base;
    mergeSort3(base);
    bool sorted = std::is_sorted(base.begin(), base.end());
    CHECK_EQ(true, sorted);
}
TEST("Medium timed"){
    const int L = 10000;
    unsigned int seed = 42;
    srand(seed);
    std::vector<int> base,arr_baseline,arr_student;
    for (int i = 0; i < L; ++i) {
        base.push_back(i%10);
    }
    arr_baseline = base;
    arr_student = base;

    TIMER(t_baseline){
        std::sort(arr_baseline.begin(), arr_baseline.end());
        std::reverse(arr_baseline.begin(), arr_baseline.end());
    }
    TIMER(t_student){
        mergeSort3(arr_student);
    }
    auto comp = [](int a, int b) {
        return a > b;
    };
/*        for (int num : arr_student) {
        std::cout << num << " ";
    }*/

    bool sorted = std::is_sorted(arr_student.begin(), arr_student.end(), comp);
    CHECK_EQ(true, sorted);

    double tolerance = t_baseline.count()*4;
    bool fast_enough = max(0,int(t_student.count()-t_baseline.count())) < tolerance;
    //std::cout<<t_baseline.count()<<"+"<<tolerance<<" >? "<<t_student.count()<<endl;
    CHECK_EQ( true, fast_enough);
}
TEST("Large timed"){
    const int L = 1000000;
    unsigned int seed = 42;
    srand(seed);
    std::vector<int> base,arr_baseline,arr_student;
    for (int i = 0; i < L; ++i) {
        base.push_back(rand()%100);
    }
    arr_baseline = base;
    arr_student = base;

    TIMER(t_baseline){
        std::sort(arr_baseline.begin(), arr_baseline.end());
        std::reverse(arr_baseline.begin(), arr_baseline.end());
    }
    TIMER(t_student){
        mergeSort3(arr_student);
    }
    auto comp = [](int a, int b) {
        return a > b;
    };
/*        for (int num : arr_student) {
        std::cout << num << " ";
    }*/

    bool sorted = std::is_sorted(arr_student.begin(), arr_student.end(), comp);
    CHECK_EQ(true, sorted);

    double tolerance = t_baseline.count()*4;
    bool fast_enough = max(0,int(t_student.count()-t_baseline.count())) < tolerance;
    //std::cout<<t_baseline.count()<<"+"<<tolerance<<" >? "<<t_student.count()<<endl;
    CHECK_EQ( true, fast_enough);
}


WOODPECKER_TEST_MAIN()

