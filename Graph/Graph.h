#include <vector>
#include <map>
#include <string>
#include <limits>
#include <iostream>

using namespace std;

enum Color {WHITE, BLACK};

struct Edge;

struct Vertex {
    string name;
    vector<Edge> adjacencyList;
    Vertex *pi;
    double d;
    bool color;
};

struct Edge {
    Vertex *destination;
    double distance;
};

class MinHeap {
private:
    Vertex *priorityQueue;
    int n;
public:
    MinHeap(int);
    void minHeapify(int);
    Vertex extractMin();
    void decreaseKey(int, Vertex*);
    void insert(Vertex*);
    bool isEmpty();
};

class Graph {
public:
    map<string, Vertex> Vertices;
    Graph();
    Vertex* getVertex(string);
    void addEdge(string, string, double);
    void relax(string, string, double);
    void printEdges();
    void printEdgesD();
};

MinHeap::MinHeap(int c) {
    this->n = 0;
    this->priorityQueue = new Vertex[c+1];
}

void MinHeap::minHeapify(int i) {
    int left = 2*i;
    int right = left+1;
    int min = 0;
    if(left <= this->n && this->priorityQueue[left].d < this->priorityQueue[i].d) {
        min = left;
    }
    else {
        min = i;
    }
    if(right <= this->n && this->priorityQueue[right].d < this->priorityQueue[min].d) {
        min = right;
    }
    if(min != i) {
        Vertex temp = this->priorityQueue[i];
        this->priorityQueue[i] = this->priorityQueue[min];
        this->priorityQueue[min] = temp;
        minHeapify(min);
    }
}

Vertex MinHeap::extractMin() {
    Vertex min = this->priorityQueue[1];
    this->priorityQueue[1] = this->priorityQueue[this->n];
    this->n--;
    minHeapify(1);
    return min;
}

void MinHeap::decreaseKey(int i, Vertex* item) {
    if(item->d > this->priorityQueue[i].d) {
        return;
    }
    this->priorityQueue[i] = *item;
    while(i > 1 && this->priorityQueue[i/2].d > this->priorityQueue[i].d) {
        Vertex temp = this->priorityQueue[i];
        this->priorityQueue[i] = this->priorityQueue[i/2];
        this->priorityQueue[i/2] = temp;
        i = i/2;
    }
}

void MinHeap::insert(Vertex *item) {
    this->n++;
    Vertex *temp = new Vertex;
    temp->d = numeric_limits<double>::infinity();
    this->priorityQueue[this->n] = *temp;
    decreaseKey(this->n, item);
}

bool MinHeap::isEmpty() {
    return this->n == 0;
}

Graph::Graph() {}

Vertex* Graph::getVertex(string name) {
    if(this->Vertices.find(name) == this->Vertices.end()) {
        Vertex *node = new Vertex;
        node->name = name;
        node->d = 0;
        node->color = WHITE;
        this->Vertices[name] = *node;
        cout << "Creating " << name << endl;
        return node;
    }
    else {
        return &this->Vertices[name];
    }
}

void Graph::addEdge(string src, string end, double dist) {
    Vertex *o = getVertex(src);
    Vertex *f = getVertex(end);
    Edge *e = new Edge;
    e->destination = f;
    e->distance = dist;
    o->adjacencyList.push_back(*e);
    this->Vertices[src] = *o;
    this->Vertices[end] = *f;
}
void Graph::relax(string u, string v, double w) {
    if(this->Vertices[v].d > this->Vertices[u].d + w) {
        Vertex *temp = new Vertex();
        temp = getVertex(u);
        this->Vertices[v].d = this->Vertices[u].d + w;
        this->Vertices[v].pi = temp;
    }
}

void Graph::printEdges() {
    for(map<string, Vertex>::iterator it = this->Vertices.begin(); it != this->Vertices.end(); ++it ) {
        cout << "Vertex: " <<  it->second.name << " -- Adjacency List:" << endl;
        for(int i = 0; i < it->second.adjacencyList.size(); i++ ) {
            cout << it->second.adjacencyList[i].destination->name << "\tWeight: " << it->second.adjacencyList[i].distance << endl;
        }
    }
}

void Graph::printEdgesD() {
    cout << this->Vertices.size() << endl;
    for(map<string, Vertex>::iterator it = this->Vertices.begin(); it != this->Vertices.end(); ++it ) {
        cout << "Vertex: " <<  it->second.name << " -- D:" << it->second.d << endl;
    }
}