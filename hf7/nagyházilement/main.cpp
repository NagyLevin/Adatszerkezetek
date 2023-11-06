#include <iostream>
#include "sparsematrix.hpp"
#include "woodpecker.hpp"

TEST("Egyszeru ures"){
    SparseMatrix s = SparseMatrix(1000,1000,0,42);
    CHECK_EQ(s(100,10),0);
    CHECK_EQ(s(999,42),0);
}
TEST("Meglevo ertek torlese"){
    SparseMatrix s = SparseMatrix(1000,1000,2,256);
    CHECK_NOEXC(s.clear(10,10));
    CHECK_EQ(s(10,10),2);
}
TEST("Meglevo ertek felulirasa"){
    SparseMatrix s = SparseMatrix(1000,1000,2,255);
    s.set(12,12,40);
    s.set(12,12,10);
    CHECK_EQ(s(12,12), 10);
}
TEST("Kis matrix ertekekkel"){
    SparseMatrix s = SparseMatrix(10,10,1,5);
    s.set(2,2,2.2);
    s.set(2,1,2.1);
    s.set(2,8,2.8);
    s.set(2,4,2.4);
    s.set(1,4,1.4);
    s.set(8,3,8.3);
    s.set(6,0,6.0);
    s.printMatrix();
    CHECK_EQ(s(2,2), 2.2);
    CHECK_EQ(s(2,1), 2.1);
    CHECK_EQ(s(2,8), 2.8);
    CHECK_EQ(s(2,4), 2.4);
    CHECK_EQ(s(1,4), 1.4);
    CHECK_EQ(s(8,3), 8.3);
    CHECK_EQ(s(6,0), 6.0);
    CHECK_EQ(s(0,0), 1);
    CHECK_EQ(s(0,1), 1);
    CHECK_EQ(s(0,2), 1);
    CHECK_EQ(s(0,3), 1);
    CHECK_EQ(s(1,1), 1);
    CHECK_EQ(s(1,2), 1);
    CHECK_EQ(s(1,3), 1);
    CHECK_EQ(s(6,1), 1);
    CHECK_EQ(s(9,9), 1);
    CHECK_EQ(s(9,8), 1);
    CHECK_EQ(s(9,0), 1);
}
TEST("Nagy matrix ertekekkel"){
    SparseMatrix s = SparseMatrix(1000,1000,0,254);
    s.set(885, 12, 42);
    s.set(0, 442, 998);
    CHECK_EQ(s(100,10),0);
    CHECK_EQ(s(999,42),0);
    CHECK_EQ(s(885, 12),42);
    CHECK_EQ(s(0, 442),998);
}
TEST("Egyszeru ertekekkel - nemnegyzetes"){
    SparseMatrix s = SparseMatrix(1000,100,0,253);
    s.set(885, 12, 42);
    s.set(0, 42, 998);
    CHECK_EQ(s(100,10),0);
    CHECK_EQ(s(999,42),0);
    CHECK_EQ(s(885, 12),42);
    CHECK_EQ(s(0, 42),998);
}
TEST("Egyszeru ertekekkel es eltavolitassal"){
    SparseMatrix s = SparseMatrix(1000,1000,0,252);
    for(int i = 0; i < 100; i++){
        s.set(200+i, 40+2*i, i+5);
    }
    s.set(885, 12, 42);
    s.set(0, 442, 998);
    CHECK_EQ(s(100,10),0);
    CHECK_EQ(s(999,42),0);
    CHECK_EQ(s(885, 12),42);
    CHECK_EQ(s(0, 442),998);
    for(int i = 0; i < 100; i++){
        CHECK_EQ(s(200+i, 40+2*i),i+5);
        CHECK_EQ(s(199, 40+2*i),0);
    }
    for(int i = 0; i < 100; i++){
        s.clear(200+i, 40+2*i);
    }
    for(int i = 0; i < 100; i++){
        CHECK_EQ(s(200+i, 40+2*i),0);
        CHECK_EQ(s(199, 40+2*i),0);
    }

}
TEST("Egyszeru ertekekkel - kiindexeles"){
    SparseMatrix s = SparseMatrix(1000,100,0,251);
    bool ok = true;
    try{
        s.set(1200, 12, 42);
        ok = false;
        std::cerr<< " ->Kiindexelesre nem ad hibat: s(1200,12)-nel:" << s(1200,12) << "\n";
    }catch(...){
//std::cerr << " ->OK\n";
    }
    try{
        s.set(80, 120, 42);
        ok = false;
        std::cerr<< " ->Kiindexelesre nem ad hibat: s(80,120)-nal:" << s(80,120) << "\n";
    }catch(...){
//std::cerr << " ->OK\n";
    }
    CHECK_EQ(ok,true);
    try{
        s.set(-80, 80, 42);
        ok = false;
        std::cerr<< " ->NEGATIV Kiindexelesre nem ad hibat: s(-80,80)-nal:" << s(-80,80) << "\n";
    }catch(...){
//std::cerr << " ->OK\n";
    }
    CHECK_EQ(ok,true);
}
TEST("Matrix nemnulla default ertekkel"){
    SparseMatrix s = SparseMatrix(1000,1000,42,250);
    s.set(885, 12, 40);
    s.set(0, 442, 998);
    CHECK_EQ(s(100,10),42);
    CHECK_EQ(s(999,42),42);
    CHECK_EQ(s(885, 12),40);
    CHECK_EQ(s(0, 442),998);
    for(int i = 0; i < 100; i++){
        CHECK_EQ(s(200+i, 40+2*i),42);
    }
}



WOODPECKER_TEST_MAIN()