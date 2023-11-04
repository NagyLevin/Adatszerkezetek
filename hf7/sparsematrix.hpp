

#ifndef HF7_SKELETON_SPARSEMATRIX_HPP
#define HF7_SKELETON_SPARSEMATRIX_HPP


#include <iostream>
#include <list>
#include <vector>


class SparseMatrix{
    //TODO sparce matrix with hashtable

    //hashFunction()
private:
    std::vector< std::vector<std::list<int> > > matrix;

    int Sor;
    int TenylegesSor;

    int Oszlop;
    int TenylegesOszlop;



    double defaultv;
    size_t hasitas;



    int getHashSor(const int & key) {

        return key % Sor;

    }
    int getHashOszlop(const int & key) {

        return key % Oszlop;

    }



public:
    //Konstruktor
    SparseMatrix(int size_x, int size_y, double defaultValue, size_t hashLim){


        Sor = size_x;
        TenylegesSor = 0;
        Oszlop = size_y;
        TenylegesOszlop = 0;

        defaultv = defaultValue;
        hasitas = hashLim;


    }

    int AdjSorTenyleg(){
        return TenylegesSor;
    }
    int AdjOszlopTenyleg(){
        return TenylegesOszlop;
    }
    double getdefV(){
        return defaultv;
    }



    //Destruktor
    ~SparseMatrix();

    //Indexeles - kiindexeles eseten hibat dob
    double operator()(int x, int y) const;

    //Matrix elem ertekadas - ha letezik az ertek, felulirja
    //Kiindexeles eseten hibat dob
    void set(int x, int y, double value){

        int myhashSOR = getHashSor(value);
        int myhashOSZLOP = getHashOszlop(value);

        for (std::list<int>::iterator it = matrix[myhashSOR][myhashOSZLOP].begin(); it != matrix[myhashSOR][myhashOSZLOP].end(); ++it) { //iteratoros bejaras

            if(*it == value){
                return;
            }

        }
        matrix[myhashSOR][myhashOSZLOP].push_back(value);   //ha nincs akkor a vegere rakaja
        TenylegesSor = TenylegesSor +1; //meret megnovelese





    }

    //Matrix elem torlese, default ertek esetén nem csinal semmit
    //Kiindexeles eseten hibat dob
    void clear(int x, int y);
	
	//Teljes matrix kiiratasa consolera
    void printMatrix() const;

};
#endif //HF7_SKELETON_SPARSEMATRIX_HPP
