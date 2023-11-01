

#ifndef HF7_SKELETON_SPARSEMATRIX_HPP
#define HF7_SKELETON_SPARSEMATRIX_HPP
class SparseMatrix{
    //TODO sparce matrix with hashtable

    //hashFunction()
public:
    //Konstruktor
    SparseMatrix(int size_x, int size_y, double defaultValue, size_t hashLim);

    //Destruktor
    ~SparseMatrix();

    //Indexeles - kiindexeles eseten hibat dob
    double operator()(int x, int y) const;

    //Matrix elem ertekadas - ha letezik az ertek, felulirja
    //Kiindexeles eseten hibat dob
    void set(int x, int y, double value);

    //Matrix elem torlese, default ertek esetén nem csinal semmit
    //Kiindexeles eseten hibat dob
    void clear(int x, int y);
	
	//Teljes matrix kiiratasa consolera
    void printMatrix() const;

};
#endif //HF7_SKELETON_SPARSEMATRIX_HPP
