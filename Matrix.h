#pragma once

#include <sstream>
#include "Sequence.h"

#define OutOfRange "Error! Index is out of range!"

using namespace std;

template<class T>
class Matrix {
private:

    Sequence<Sequence<T> *> *elems;
    int rows = 0;
    int cols = 0;

public:

    Matrix() = default;

    Matrix(const int rows, const int cols) {
        if (rows < 0 || cols < 0) throw OutOfRange;
        else {
            this->rows = rows;
            this->cols = cols;
        }
        this->elems = (Sequence<Sequence<T> *> *) new ListSequence<ListSequence<T> *>;
        for (int i = 0; i < rows; i++) this->elems->Append(new ListSequence<T>(this->cols));
    }

    ~Matrix() = default;

    int GetRows() {
        return this->rows;
    }

    int GetColumns() {
        return this->cols;
    }

    T Get(const int i, const int j) {
        if (i < 0 || i >= this->rows || j < 0 || j >= this->cols) throw OutOfRange;

        return this->elems->Get(i)->Get(j);
    }

    void Set(T item, int i, int j) {
        if (i < 0 || i >= this->rows || j < 0 || j >= this->cols) throw OutOfRange;
        this->elems->Get(i)->Set(item, j);
    }

    string ToString() {
        string result = "";
        for (int i = 0; i < this->GetRows(); i++) {
            for (int j = 0; j < this->GetColumns(); j++) {
                stringstream s;
                s << this->Get(i, j);
                result += s.str();
                result += " ";
            }
            result += "\n";
        }
        return result;
    }
};