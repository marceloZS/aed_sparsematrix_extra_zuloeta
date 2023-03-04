#ifndef LIST_SPARSE_MATRIX_H
#define LIST_SPARSE_MATRIX_H
#include "sparsematrix.h"
#include <vector>
using namespace std;

template <typename T>
struct Node {
    public:
        T data;
        int posX;
        int posY;
        Node<T>* next;//row
        Node<T>* down;//column
};

template <class T>
class ListSparseMatrix : public SparseMatrix<T> {
    private:
        vector<Node<T>*> X;
        vector<Node<T>*> Y;                

    public:
        ListSparseMatrix();
        ListSparseMatrix(unsigned rows, unsigned columns);
        ~ListSparseMatrix();

        bool set(unsigned posX, unsigned posY, T data);

        T get(unsigned posX, unsigned posY);//O(1) + O(m)
        bool remove(unsigned posX, unsigned posY);

        T operator()(unsigned posX, unsigned posY);   
        ListSparseMatrix<T>& operator * (T scalar);   
        ListSparseMatrix<T>& operator + (const ListSparseMatrix<T> &other);  
        ListSparseMatrix<T>& operator - (const ListSparseMatrix<T> &other);
        ListSparseMatrix<T>& operator * (const ListSparseMatrix<T> &other);
        ListSparseMatrix<T>& transpose();
        
        void display();
};

#endif

