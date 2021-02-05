#pragma once

#include "DirGraph.h"

template<class T>
class Graph : virtual public DirGraph<T> {
public:

    Graph(int size) : DirGraph<T>(size) {};

    void ChangeEdge(int vert1, int vert2, T weight) {
        if (vert1 == vert2) throw OutOfRange;
        this->adjMatrix->Set(weight, vert1, vert2);
        this->adjMatrix->Set(weight, vert2, vert1);
    }

};