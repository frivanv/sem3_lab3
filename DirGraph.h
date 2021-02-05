#pragma once

#include "Sequence.h"
#include "Matrix.h"

using namespace std;

template<class T>
class DirGraph {
protected:
    Matrix<T> *adjMatrix;
private:

    void _ts_(int v, bool visited[], ArraySequence<int> *stack) {
        visited[v] = true;
        for (int i = 0; i < this->GetSize(); i++)
            if ((this->adjMatrix->Get(v, i) != 0) && (!visited[i]))
                this->_ts_(i, visited, stack);
        stack->Prepend(v);
    }

public:

    DirGraph(int size) {
        this->adjMatrix = new Matrix<T>(size, size);
    }

    ~DirGraph() = default;

    virtual void ChangeEdge(int vert1, int vert2, T weight) {
        if (vert1 == vert2) throw OutOfRange;
        this->adjMatrix->Set(weight, vert1, vert2);
    }

    int GetSize() {

        return this->adjMatrix->GetRows();
    }

    string ToString() {

        return this->adjMatrix->ToString();
    }

    ArraySequence<int> *GetPath(int vert1, int vert2) {
        const int INF = 10000000;
        ArraySequence<int> dist(this->GetSize());
        ArraySequence<bool> beenTo(this->GetSize());
        ArraySequence<int> parent(this->GetSize());

        for (int i = 0; i < this->GetSize(); i++) {
            dist.Set(INF, i);
            beenTo.Set(false, i);
            parent.Set(-1, i);
        }

        int min;
        int index_min = 0;
        int temp;
        dist.Set(0, vert1);

        for (int i = 0; i < this->GetSize(); i++) {
            min = INF;
            for (int j = 0; j < this->GetSize(); j++)
                if (!beenTo.Get(j) && dist.Get(j) < min) {
                    min = dist.Get(j);
                    index_min = j;
                }
            beenTo.Set(true, index_min);
            for (int j = 0; j < this->GetSize(); j++)
                if (adjMatrix->Get(index_min, j) > 0) {
                    temp = min + adjMatrix->Get(index_min, j);
                    if (temp < dist.Get(j)) {
                        dist.Set(temp, j);
                        parent.Set(index_min, j);
                    }
                }
            if (beenTo.Get(vert2)) break;
        }

        ArraySequence<int> *path = new ArraySequence<int>(0);
        if (parent.Get(vert2) == -1) {
            path->Append(-1);
            return path;
        }
        for (int i = vert2; i != -1; i = parent.Get(i)) path->Prepend(i);

        return path;
    }

    T GetPathWeight(ArraySequence<int> *path) {
        if (path->Get(0) == -1) throw OutOfRange;
        T result = 0;
        for (int i = 0; i < path->GetSize() - 1; i++) {
            if (this->adjMatrix->Get(path->Get(i), path->Get(i + 1)) == 0) throw OutOfRange;
            result += this->adjMatrix->Get(path->Get(i), path->Get(i + 1));
        }

        return result;
    }

    ArraySequence<int> *GetTopologicalSort() {
        ArraySequence<int> *stack;
        stack = new ArraySequence<int>();
        bool *visited = new bool[this->GetSize()];

        for (int i = 0; i < this->GetSize(); i++) visited[i] = false;

        for (int i = 0; i < this->GetSize(); i++)
            if (!visited[i]) this->_ts_(i, visited, stack);

        return stack;
    }
};