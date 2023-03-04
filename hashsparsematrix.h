#ifndef HASH_SPARSE_MATRIX_H
#define HASH_SPARSE_MATRIX_H
#include "sparsematrix.h"
#include <unordered_map>
using namespace std;

template <typename T>
class HashSparseMatrix: public SparseMatrix<T>
{
    private:
        std::unordered_map<int, T> hash; 

    public:
        HashSparseMatrix();
        HashSparseMatrix(unsigned rows, unsigned columns);
        ~HashSparseMatrix();

        bool set(unsigned posX, unsigned posY, T data);
        T get(unsigned posX, unsigned posY);
        bool remove(unsigned posX, unsigned posY);

        T& operator()(unsigned posX, unsigned posY); 
        HashSparseMatrix<T>& operator * (T scalar);   
        HashSparseMatrix<T>& operator + (const HashSparseMatrix<T> &other);  
        HashSparseMatrix<T>& operator - (const HashSparseMatrix<T> &other);
        HashSparseMatrix<T>& operator * (const HashSparseMatrix<T> &other);
        HashSparseMatrix<T>& transpose();
        
        void display();
};

#endif