#include <iostream>
#include <random>

using namespace std;

class DisjointSet {
private:
    int *rank;
    int *parent;
    int *size;
    int n;
    void makeSet();
public:
    DisjointSet(const int);
    int findWeighted(const int);
    int findPath(const int);
    void unionWeighted(const int, const int);
    void unionPath(const int, const int);
    void printSet();
};

DisjointSet::DisjointSet(const int n) {
    this->rank = new int[n];
    this->parent = new int[n];
    this->n = n;
    this->size = new int[n];
    makeSet();
}

void DisjointSet::makeSet() {
    for(int i = 0; i <this->n; i++) {
        this->parent[i] = i;
        this->size[i] = 1;
    }
}

int DisjointSet::findWeighted(const int x) {
    if(this->parent[x] == x) {
        return x;
    }
    return findWeighted(this->parent[x]);
}

int DisjointSet::findPath(const int x) {
    if(this->parent[x] != x){
        this->parent[x] = findPath(this->parent[x]);
    }
    return this->parent[x];
}

void DisjointSet::unionWeighted(const int x, const int y) {
    int xRep = this->findWeighted(x);
    int yRep = this->findWeighted(y);
    if(xRep == yRep) {
        return;
    }
    else if(this->rank[xRep] < this->rank[yRep]) {
        this->parent[xRep] = yRep;
        this->size[yRep] += this->size[xRep];
    }
    else if(this->rank[xRep] > this->rank[yRep]) {
        this->parent[yRep] = xRep;
        this->size[xRep] += this->size[yRep];
    }
    else {
        this->parent[yRep] = xRep;
        this->size[xRep] += this->size[yRep];
        this->rank[xRep]++;
    }
}

void DisjointSet::unionPath(const int x, const int y) {
    int xRep = this->findPath(x);
    int yRep = this->findPath(y);
    if(xRep == yRep) {
        return;
    }
    else if(this->rank[xRep] < this->rank[yRep]) {
        this->parent[xRep] = yRep;
        this->size[yRep] += this->size[xRep];
    }
    else if(this->rank[xRep] > this->rank[yRep]) {
        this->parent[yRep] = xRep;
        this->size[xRep] += this->size[yRep];
    }
    else {
        this->parent[yRep] = xRep;
        this->size[xRep] += this->size[yRep];
        this->rank[xRep]++;
    }
}

void DisjointSet::printSet() {
    cout << "Parents:" << endl;
    for(int i = 0; i < this->n; i++) {
        cout << "[" << this->parent[i] << "]";
    }
    cout << endl;
    cout << "Size:" << endl;
    for(int i = 0; i < this->n; i++) {
        cout << "[" << this->size[i] << "]";
    }
    cout << endl;
    cout << "Rank:" << endl;
    for(int i = 0; i < this->n; i++) {
        cout << "[" << this->rank[i] << "]";
    }
    cout << endl;
}

void testWithoutCompression() {
    clock_t begin, end;
    for(int n = 10; n < 1000; n++){
  
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(-1,n-1);
    
        DisjointSet *setC = new DisjointSet(n);

        begin = clock();
        for(int i = 0; i < n - 1; i++)
            setC->unionWeighted(dis(gen),dis(gen));
        end = clock();
        double ex_time = (end - begin);
        cout << n << "," << ex_time << endl;

        delete(setC);
    }
}

void testWithCompression() {
    clock_t begin, end;
    for(int n = 10; n < 1000; n++){
  
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(-1,n-1);
    
        DisjointSet *setC = new DisjointSet(n);

        begin = clock();
        for(int i = 0; i < n - 1; i++)
            setC->unionPath(dis(gen),dis(gen));
        end = clock();
        double ex_time = (end - begin);
        cout << n << "," << ex_time << endl;

        delete(setC);
    }
}

int main() {
    cout << "Without Compression:" << endl;
    testWithoutCompression();
    string x;
    cin >> x;
    cout << "With Compression:" << endl;
    testWithCompression();
}