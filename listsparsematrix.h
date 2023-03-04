#ifndef LIST_SPARSE_MATRIX_H
#define LIST_SPARSE_MATRIX_H
#include "sparsematrix.h"
#include <vector>
using namespace std;

template <typename T>
struct Node {
    public:
        T data; //valor del elemento
        int posX; //fila del elemento
        int posY; //columna del elemento
        Node<T>* next;//siguiente nodo en la misma fila
        Node<T>* down;//siguiente nodo en la misma columna
};

template <class T>
class ListSparseMatrix : public SparseMatrix<T> {
    private:
        vector<Node<T>*> X; //vector para almacenar las cabezas de la fila
        vector<Node<T>*> Y; //vector para almacenar las cabezas de la columna

    public:
    ListSparseMatrix(){
        this->rows = 0;
        this->columns = 0;
        X.push_back(nullptr);
        Y.push_back(nullptr);
    }
    // inicializa los valores de rows y columns a cero y agrega un elemento nulo a los
    // vectores X e Y.

    ListSparseMatrix(unsigned rows, unsigned columns){
        this->rows = rows;
        this->columns = columns;
        X.resize(rows + 1, nullptr);
        Y.resize(columns + 1, nullptr);
        for (unsigned i = 0; i <= rows; i++) {
            X[i] = new Node<T>();
            X[i]->posX = i;
            X[i]->next = nullptr;
        }
        for (unsigned i = 0; i <= columns; i++) {
            Y[i] = new Node<T>();
            Y[i]->posY = i;
            Y[i]->down = nullptr;
        }
    }
    // establece los valores de rows y columns según los parámetros proporcionados y
    // crea los vectores X e Y con la cantidad de elementos necesarios.
    // También crea los nodos de cabecera para cada fila y columna y los inicializa
    // con los valores correspondientes.


    ~ListSparseMatrix(){
        for (unsigned i = 0; i <= this->rows; i++) {
            Node<T>* current = X[i];
            while (current != nullptr) {
                Node<T>* temp = current->next;
                delete current;
                current = temp;
            }
        }
        for (unsigned i = 0; i <= this->columns; i++) {
            Node<T>* current = Y[i];
            while (current != nullptr) {
                Node<T>* temp = current->down;
                delete current;
                current = temp;
            }
        }
    }
    // el destructor elimina todos los nodos de la matriz dispersa,
    // incluidos los nodos de cabecera.


    bool set(unsigned posX, unsigned posY, T data){
        if (posX >= this->rows || posY >= this->columns) {
            return false;
        }
        Node<T>* newNode = new Node<T>();
        newNode->data = data;
        newNode->posX = posX;
        newNode->posY = posY;
        newNode->next = nullptr;
        newNode->down = nullptr;

        Node<T>* currentX = X[posX];
        Node<T>* currentY = Y[posY];
        Node<T>* prevX = nullptr;
        Node<T>* prevY = nullptr;

        while (currentX != nullptr && currentX->posY < posY) {
            prevX = currentX;
            currentX = currentX->next;
        }
        if (currentX != nullptr && currentX->posY == posY) {
            currentX->data = data;
            delete newNode;
            return true;
        }
        while (currentY != nullptr && currentY->posX < posX) {
            prevY = currentY;
            currentY = currentY->down;
        }
        if (currentY != nullptr && currentY->posX == posX) {
            prevX = nullptr;
            currentX = X[posX];
            while (currentX != nullptr && currentX->posY < posY) {
                prevX = currentX;
                currentX = currentX->next;
            }
            if (currentX != nullptr && currentX->posY == posY) {
                currentX->data = data;
                delete newNode;
                return true;
            }
            newNode->next = currentY->next;
            currentY->next = newNode;
            return true;
        }
        newNode->next = currentX;
        newNode->down = currentY;

        if (prevX == nullptr) {
            X[posX] = newNode;
        }
        else {
            prevX->next = newNode;
        }
        if (prevY == nullptr) {
            Y[posY] = newNode;
        }
        else {
            prevY->down = newNode;
        }
        return true;
    }

    //get: busca la posicion X,Y en la matriz
    T get(unsigned posX, unsigned posY){//O(1) + O(m)
        // si las posiciones están fuera del rango de la matriz, retorna un valor por defecto
        // en caso de que sí, se retorna un valor por defecto.
        if (posX >= this->rows || posY >= this->columns) {
            return T();
        }
        Node<T>* curr = X[posX];
        // luego, se recorre la lista enlazada correspondiente a la fila posX hasta
        // encontrar el nodo cuya columna es mayor o igual a posY.
        while (curr != nullptr && curr->posY < posY) {
            curr = curr->next;
        }
        // si se encuentra un nodo con columna igual a posY, se retorna el dato almacenado
        if (curr != nullptr && curr->posY == posY) {
            return curr->data;
        }
        // si no se encuentra el nodo con columna posY, se retorna un valor por defecto.
        return T();
    }
    // cumple con la complejidad O(1) + O(m),
    // donde m es el número de elementos en la fila (posX).


    // funcion remover:
    bool remove(unsigned posX, unsigned posY){
        // si las posiciones están fuera del rango de la matriz,
        // no se puede eliminar ningún elemento
        if (posX >= this->rows || posY >= this->columns) {
            return false;
        }
        Node<T>* currX = X[posX];
        Node<T>* prevX = nullptr;
        // se recorre la lista enlazada correspondiente a la fila posX
        // buscando el nodo que contiene la columna posY
        while (currX != nullptr && currX->posY < posY) {
            prevX = currX;
            currX = currX->next;
        }
        if (currX != nullptr && currX->posY == posY) {
            Node<T>* currY = Y[posY];
            Node<T>* prevY = nullptr;
            // se recorre la lista enlazada correspondiente a la columna posY
            // buscando el nodo que contiene la fila posX
            while (currY != nullptr && currY->posX < posX) {
                prevY = currY;
                currY = currY->down;
            }
            if (currY != nullptr && currY->posX == posX) {

                if (prevX == nullptr) {
                    X[posX] = currX->next;
                } else {
                    prevX->next = currX->next;
                }
                if (prevY == nullptr) {
                    Y[posY] = currY->down;
                } else {
                    prevY->down = currY->down;
                }
                // si se encuentran ambos nodos, se eliminan
                // y se actualizan los punteros correspondientes.
                delete currX;
                delete currY;
                return true;
            }
        }
        // si no están ambos nodos se retorna falso ya que no eliminó nada.
        return false;
    }
    // complejidad O(1) + O(m + n),
    // m = num de elem. en fila, n = num de elem. en column.


    T operator()(unsigned posX, unsigned posY){
        Node<T>* current = X[posX];
        // recorre la fila correspondiente a posX hasta encontrar el nodo con columna posY
        // o un nodo con columna mayor a posY
        while (current != nullptr && current->posY < posY) {
            current = current->next;
        }
        // si el nodo no existe, retorna un valor por defecto.
        if (current == nullptr || current->posY > posY) {
            return T();
        }
        return current->data;
    }

    // funcion que multiplica cada elemento en la matriz por un escalar:
    ListSparseMatrix<T>& operator * (T scalar){
        ListSparseMatrix<T>* result = new ListSparseMatrix<T>(this->rows, this->columns);
        for (int i = 0; i < this->rows; i++) {
            Node<T>* current = X[i];
            while (current != nullptr) {
                result->set(current->posX, current->posY, current->data * scalar);
                current = current->next;
            }   // crea una nueva matriz y recorre la matriz original para crear nodos con
            // los elementos multiplicados por el escalar scalar
        }
        return *result; // devuelve una referencia a la matriz resultado
    }

    // funcion suma sobrecargando el operador +
    ListSparseMatrix<T>& operator + (const ListSparseMatrix<T> &other){
        // comprueba que ambas matrices tienen las mismas dimensiones.
        if (this->rows != other.rows || this->columns != other.columns) {
            throw invalid_argument("Matrices must have same dimensions");
        }

        ListSparseMatrix<T>* result = new ListSparseMatrix<T>(this->rows, this->columns);
        for (int i = 0; i < this->rows; i++) {
            Node<T>* currentA = X[i];
            Node<T>* currentB = other.X[i];
            // agrega los valores en cada celda de la matriz resultante
            while (currentA != nullptr || currentB != nullptr) {
                // si una celda tiene un valor en una matriz pero no en la otra,
                // simplemente copia ese valor en la matriz resultante
                if (currentA == nullptr) {
                    result->set(currentB->posX, currentB->posY, currentB->data);
                    currentB = currentB->next;
                } else if (currentB == nullptr) {
                    result->set(currentA->posX, currentA->posY, currentA->data);
                    currentA = currentA->next;
                } else if (currentA->posY < currentB->posY) {
                    result->set(currentA->posX, currentA->posY, currentA->data);
                    currentA = currentA->next;
                } else if (currentB->posY < currentA->posY) {
                    result->set(currentB->posX, currentB->posY, currentB->data);
                    currentB = currentB->next;
                }
                    // si una celda tiene valores en ambas matrices,
                    // los suma y agrega el resultado en la matriz resultante.
                else {
                    result->set(currentA->posX, currentA->posY, currentA->data + currentB->data);
                    currentA = currentA->next;
                    currentB = currentB->next;
                }
            }
        }
        return *result;
    }

    // funcion resta sobrecargando el operador -
    ListSparseMatrix<T>& operator - (const ListSparseMatrix<T> &other){
        // se verifica que ambas matrices tengan las mismas dimensiones
        if (this->rows != other.rows || this->columns != other.columns) {
            throw runtime_error("Las matrices deben tener las mismas dimensiones");
        }
        // se crea una nueva matriz que será el resultado de la resta
        ListSparseMatrix<T> *result = new ListSparseMatrix<T>(this->rows, this->columns);

        // se recorren ambas matrices simultáneamente
        Node<T> *aux1, *aux2;
        for (int i = 0; i < this->rows; i++) {
            aux1 = this->X[i]->next; // primer nodo de la fila i de la matriz this
            aux2 = other.X[i]->next; // primer nodo de la fila i de la matriz other

            while (aux1 && aux2) { // mientras haya nodos en ambas filas
                if (aux1->posY == aux2->posY) { // si los nodos tienen la misma columna
                    // se agrega un nodo con la resta de los valores
                    result->set(i, aux1->posY, aux1->data - aux2->data);
                    aux1 = aux1->next;
                    aux2 = aux2->next;
                } else if (aux1->posY < aux2->posY) { // si el nodo de this está a la izquierda del nodo de other
                    // se agrega un nodo con el valor de this
                    result->set(i, aux1->posY, aux1->data);
                    aux1 = aux1->next;
                } else { // si el nodo de this está a la derecha del nodo de other
                    // se agrega un nodo con el valor negativo de other
                    result->set(i, aux2->posY, -aux2->data);
                    aux2 = aux2->next;
                }
            }
            // si quedan nodos en this que no se han procesado
            while (aux1) {
                result->set(i, aux1->posY, aux1->data);
                aux1 = aux1->next;
            }
            // si quedan nodos en other que no se han procesado
            while (aux2) {
                result->set(i, aux2->posY, -aux2->data);
                aux2 = aux2->next;
            }
        }
        return *result;
    }


    // funcion multiplicacion sobrecargando el operador *
    ListSparseMatrix<T>& operator * (const ListSparseMatrix<T> &other){
        if (this->columns != other.rows) {
            throw invalid_argument("Error: cannot multiply matrices with incompatible dimensions");
        }
        // realiza la multiplicación de matrices utilizando tres ciclos for para recorrer
        // las filas y columnas de ambas matrices.
        ListSparseMatrix<T>* result = new ListSparseMatrix<T>(this->rows, other.columns);
        // se obtiene el valor de la celda en la posición i, j de la matriz resultante mediante la
        // suma de los productos de los elementos de las filas de la matriz izquierda y las columnas
        // de la matriz derecha
        for (unsigned i = 0; i < this->rows; i++) {
            for (unsigned j = 0; j < other.columns; j++) {
                T sum = 0;
                for (unsigned k = 0; k < this->columns; k++) {
                    sum += this->get(i, k) * other.get(k, j);
                } // se almacena el valor en la posición correspondiente de la matriz resultante
                result->set(i, j, sum);
            }
        }
        // se devuelve la matriz resultante
        return *result;
    }


    ListSparseMatrix<T>& transpose(){
        ListSparseMatrix<T>* result = new ListSparseMatrix<T>(this->columns, this->rows);
        // transpuesta de la matriz iterando por filas
        for (unsigned i = 0; i < this->rows; i++) {
            unsigned temp = this->posX[i];
            this->posX[i] = this->posY[i];
            this->posY[i] = temp;

            result->set(this->posY[i], this->posX[i], this->data[i]);
        }
        return *result;
    }

    void display(){
        for (unsigned i = 0; i < this->rows; i++) {
            for (unsigned j = 0; j < this->columns; j++) {
                cout << this->get(i, j) << " ";
            }
            cout << std::endl;
        }
    }
};

#endif

