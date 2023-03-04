#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

template <typename T>
class SparseMatrix {
    protected:
        unsigned rows; //numero de filas
        unsigned columns; //numero de columnas

    public:        
        virtual bool set(unsigned posX, unsigned posY, T data) = 0;
        virtual T get(unsigned posX, unsigned posY) = 0;
        virtual bool remove(unsigned posX, unsigned posY) = 0;
        virtual void display() = 0; 
};

#endif