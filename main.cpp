#include <iostream>
#include <string>
#include "Graph.h"

using namespace std;

Graph<int> *getDefaultGraph() {
    Graph<int> *graph = new Graph<int>(8);
    graph->ChangeEdge(0, 1, 5);
    graph->ChangeEdge(0, 2, 9);
    graph->ChangeEdge(1, 2, 3);
    graph->ChangeEdge(1, 4, 1);
    graph->ChangeEdge(2, 3, 2);
    graph->ChangeEdge(3, 4, 5);
    graph->ChangeEdge(3, 7, 4);
    graph->ChangeEdge(4, 5, 9);
    graph->ChangeEdge(1, 5, 8);
    graph->ChangeEdge(5, 6, 3);
    graph->ChangeEdge(6, 7, 4);
    return graph;
}

DirGraph<int> *getDefaultDirGraph() {
    DirGraph<int> *graph = new DirGraph<int>(8);
    graph->ChangeEdge(0, 1, 5);
    graph->ChangeEdge(0, 2, 9);
    graph->ChangeEdge(1, 2, 3);
    graph->ChangeEdge(1, 4, 1);
    graph->ChangeEdge(2, 3, 2);
    graph->ChangeEdge(3, 4, 5);
    graph->ChangeEdge(3, 7, 4);
    graph->ChangeEdge(4, 5, 9);
    graph->ChangeEdge(1, 5, 8);
    graph->ChangeEdge(5, 6, 3);
    graph->ChangeEdge(6, 7, 4);
    return graph;
}

void editGraph(Graph<int> *graph) {
    int choose = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    while (true) {
        cout << "Adjacency matrix:" << endl;
        cout << graph->ToString();
        cout << endl;
        cout << "Enter 1 to add or change an edge" << endl;
        cout << "Enter anything else to continue" << endl;
        cin >> choose;
        cout << endl;
        if (choose == 1) {
                cout << "Enter the first vertex" << endl;
                cin >> vert1;
                cout << endl;
                cout << "Enter the second vertex" << endl;
                cin >> vert2;
                cout << endl;
                cout << "Enter a weight of the edge" << endl;
                cin >> weight;
                cout << endl;
                graph->ChangeEdge(vert1, vert2, weight);
                break;
        }
    }
}

void editDirGraph(DirGraph<int> *graph) {
    int choose = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    while (true) {
        cout << "Adjacency matrix:" << endl;
        cout << graph->ToString();
        cout << endl;
        cout << "Enter 1 to add or change an edge" << endl;
        cout << "Enter anything else to continue" << endl;
        cin >> choose;
        cout << endl;
        if (choose == 1) {
                cout << "Enter the first vertex" << endl;
                cin >> vert1;
                cout << endl;
                cout << "Enter the second vertex" << endl;
                cin >> vert2;
                cout << endl;
                cout << "Enter a weight of the edge" << endl;
                cin >> weight;
                cout << endl;
                graph->ChangeEdge(vert1, vert2, weight);
                break;
        }
    }
}

void interfaceGraph() {
    int choose = 0;
    int i = 0;
    int j = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    Graph<int> *graph;
    ArraySequence<int> *path;

    cout << "Enter 1 to get a default graph" << endl;
    cout << "Enter 2 to create a custom graph" << endl;
    cout << "Enter a different number to quit" << endl;
    cin >> choose;
    cout << endl;
    switch (choose) {
        case 1:
            graph = getDefaultGraph();
            break;
        case 2:
            cout << "Enter a number of vertices" << endl;
            cin >> choose;
            cout << endl;
            graph = new Graph<int>(choose);
            break;
        default:
            return;
    }
    editGraph(graph);
    while (true) {
        cout << "Enter 1 to find a path on the graph:" << endl;
        cout << "Enter 2 to add or change an edge" << endl;
        cout << "Enter a different number to quit" << endl;
        cin >> choose;
        cout << endl;
        switch (choose) {
            case 1:
                cout << "Enter a starting vertex:" << endl;
                cin >> i;
                cout << endl;
                cout << "Enter an ending vertex" << endl;
                cin >> j;
                cout << endl;
                path = graph->GetPath(i, j);
                cout << "The shortest path:" << endl;
                for (i = 0; i < path->GetSize(); i++)
                    cout << path->Get(i) << " ";
                cout << endl;
                cout << "It's weight: " << graph->GetPathWeight(path) << endl;
                break;
            case 2:
                cout << "Enter the first vertex" << endl;
                cin >> vert1;
                cout << endl;
                cout << "Enter the second vertex" << endl;
                cin >> vert2;
                cout << endl;
                cout << "Enter a weight of the edge" << endl;
                cin >> weight;
                cout << endl;
                graph->ChangeEdge(vert1, vert2, weight);
                cout << "Adjacency matrix:" << endl;
                cout << graph->ToString();
                cout << endl;
                break;
            default:
                return;
        }
    }
}

void interfaceDirGraph() {
    int choose = 0;
    int i = 0;
    int j = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    DirGraph<int> *graph;
    ArraySequence<int> *path;
    ArraySequence<int> *ts;

    while (true) {
        cout << "Enter 1 to get a default directed graph" << endl;
        cout << "Enter 2 to create a custom directed graph" << endl;
        cout << "Enter a different number to quit" << endl;
        cin >> choose;
        cout << endl;

        switch (choose) {
            case 1:
                graph = getDefaultDirGraph();
                break;
            case 2:
                cout << "Enter a number of vertices" << endl;
                cin >> choose;
                cout << endl;
                graph = new DirGraph<int>(choose);
                break;
            default:
                return;
        }
        editDirGraph(graph);
        while (true) {
            cout << "Enter 1 to find a path on the directed graph:" << endl;
            cout << "Enter 2 to topologically sort the graph" << endl;
            cout << "Enter 3 to add or change an edge" << endl;
            cout << "Enter a different number to quit" << endl;
            cin >> choose;
            cout << endl;
            switch (choose) {
                case 1:
                    cout << "Enter a starting vertex:" << endl;
                    cin >> i;
                    cout << endl;
                    cout << "Enter an ending vertex" << endl;
                    cin >> j;
                    cout << endl;
                    path = graph->GetPath(i, j);
                    cout << "The shortest path:" << endl;
                    for (i = 0; i < path->GetSize(); i++)
                        cout << path->Get(i) << " ";
                    cout << endl;
                    cout << "It's weight: " << graph->GetPathWeight(path) << endl;
                    break;
                case 2:
                    ts = graph->GetTopologicalSort();
                    cout << "The Topological sort:" << endl;
                    for (i = 0; i < ts->GetSize(); i++)
                        cout << ts->Get(i) << " ";
                    cout << endl;
                    break;
                case 3:
                    cout << "Enter the first vertex" << endl;
                    cin >> vert1;
                    cout << endl;
                    cout << "Enter the second vertex" << endl;
                    cin >> vert2;
                    cout << endl;
                    cout << "Enter a weight of the edge" << endl;
                    cin >> weight;
                    cout << endl;
                    graph->ChangeEdge(vert1, vert2, weight);
                    cout << "Adjacency matrix:" << endl;
                    cout << graph->ToString();
                    cout << endl;
                    break;
                default:
                    return;
            }
        }
    }
}

int main() {
    int choose = 0;

    cout << "Enter 1 to test directed graphs" << endl;
    cout << "Enter 2 to test undirected graphs" << endl;
    cin >> choose;
    cout << endl;

    switch (choose) {
        case 1:
            interfaceDirGraph();
            break;
        case 2:
            interfaceGraph();
            break;
        default:
            break;
    }

    return 0;
}