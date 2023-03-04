#include <iostream>
//#include "hashsparsematrix.h"
#include "listsparsematrix.h"
#include "tester.h"

using namespace std;

template<typename T>
void generateRandom(SparseMatrix<T> *matrix, float factor);
void comparePerformance();
void  testHashSparse();
void  testListSparse();

int main(int argc, char const *argv[])
{
    //testHashSparse();
    testListSparse();    
    return 0;
}
/*
void  testHashSparse(){
    HashSparseMatrix<int> matrix1, matrix2, matrix3;
    unsigned rows = 5, cols = 5, count = 3;
    matrix1 = HashSparseMatrix<int>(rows, cols);
    matrix1.set(0, 0, 2);
    matrix1.set(2, 1, 3);
    matrix1.set(2, 3, 1);
    matrix1.set(3, 0, 2);
    matrix1.set(4, 4, 2);
    cout<<"Matrix 1:\n";
    matrix1.display();

    matrix2 = HashSparseMatrix<int>(rows, cols);
    matrix2.set(0, 1, 2);
    matrix2.set(2, 3, 3);
    matrix2.set(3, 0, 1);
    matrix2.set(3, 4, 2);
    matrix2.set(4, 4, 1);
    cout<<"Matrix 2:\n";
    matrix2.display();
    
    matrix3 = matrix1 + matrix2;        
    cout<<"\nSuma:\n";
    matrix3.display();

    matrix3 = matrix1 - matrix2;    
    cout<<"\nResta:\n";
    matrix3.display();

    matrix3 = matrix1 * matrix2;    
    cout<<"\nMultiplicacion Matricial:\n";
    matrix3.display();

    matrix3 = (matrix1 * 2) + (matrix2 * 3);       
    cout<<"\nMultiplicacion Escalar:\n";
    matrix3.display();
}
*/
void  testListSparse(){
    ListSparseMatrix<int> matrix1, matrix2, matrix3;
    unsigned rows = 5, cols = 5, count = 3;
    matrix1 = ListSparseMatrix<int>(rows, cols);
    matrix1.set(0, 0, 2);
    matrix1.set(2, 1, 3);
    matrix1.set(2, 3, 1);
    matrix1.set(3, 0, 2);
    matrix1.set(4, 4, 2);
    cout<<"Matrix 1:\n";
    matrix1.display();

    matrix2 = ListSparseMatrix<int>(rows, cols);
    matrix2.set(0, 1, 2);
    matrix2.set(2, 3, 3);
    matrix2.set(3, 0, 1);
    matrix2.set(3, 4, 2);
    matrix2.set(4, 4, 1);
    cout<<"Matrix 2:\n";
    matrix2.display();
    
    matrix3 = matrix1 + matrix2;        
    cout<<"\nSuma:\n";
    matrix3.display();

    matrix3 = matrix1 - matrix2;    
    cout<<"\nResta:\n";
    matrix3.display();
    /*
    matrix3 = matrix1 * matrix2;    
    cout<<"\nMultiplicacion Matricial:\n";
    matrix3.display();
    */
    matrix3 = (matrix1 * 2) + (matrix2 * 3);       
    cout<<"\nMultiplicacion Escalar:\n";
    matrix3.display();
}


template<typename T>
void generateRandom(SparseMatrix<T> *matrix, float factor){
    //TODO
}

void comparePerformance(){
    //TODO
}



