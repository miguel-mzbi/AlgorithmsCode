#include <stdlib.h>
#include <iostream>
#include <random>

using namespace std;

struct Edge {
    int src, dest, weight;
};

class Graph {
private:
    int newEdgeP;
public:
    Graph(int, int);
    void addEdge(int, int, int);
    int V;
    int E;
    Edge *edges;
};

Graph::Graph(int v, int e) {
    this->V = v;
    this->E = e;
    this->newEdgeP = 0;
    this->edges = new Edge[this->E];
}

void Graph::addEdge(int a, int b, int w) {
    this->edges[this->newEdgeP].src = a;
    this->edges[this->newEdgeP].dest = b;
    this->edges[this->newEdgeP].weight = w;
    this->newEdgeP++;
}

int comparation(const void* a, const void* b) {
    Edge *aE = (Edge*)a;
    Edge *bE = (Edge*)b;
    return aE->weight > bE->weight;
}

struct Subset {
    int parent;
    int rank;
};

//Path Compression
int find(Subset *subset, int i) {
    if(subset[i].parent != i) {
        subset[i].parent = find(subset, subset[i].parent);
    }
    return subset[i].parent;
}

//Union by rank
void Union(Subset *subset, int x, int y){
    int xRep = find(subset, x);
    int yRep = find(subset, y);
    if (subset[xRep].rank < subset[yRep].rank)
        subset[xRep].parent = yRep;
    else if (subset[xRep].rank > subset[yRep].rank)
        subset[yRep].parent = xRep;
    else
    {
        subset[yRep].parent = xRep;
        subset[xRep].rank++;
    }
}

void KruskalMSP(Graph *graph) {
    int V = graph->V;
    Edge result[V];
    int e = 0;
    int i = 0;
    qsort(graph->edges, graph->E, sizeof(graph->edges[0]), comparation);
    Subset *subsets = (Subset*) malloc(V * sizeof(subsets));
    for(int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }
    while(e < V-1) {
        Edge nextE = graph->edges[i++];
        int x = find(subsets, nextE.src);
        int y = find(subsets, nextE.dest);
        if(x != y) {
            result[e++] = nextE;
            Union(subsets, x, y);
        }
    }
    //for(i = 0; i < e; i++) {
    //    cout << result[i].src << " --> " << result[i].dest << " == " << result[i].weight << endl;
    //}
}

void test() {
    clock_t begin, end;
    for(int n = 10; n < 1000; n++){
  
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(-1,n-1);

        int V = n;
        int E = n*(n-1)/2;
        Graph *graph = new Graph(V, E);
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < (n-1)/2; j++) {
                graph->addEdge(i, j, dis(gen));
            }
        }

        begin = clock();
        KruskalMSP(graph);
        end = clock();
        double execTime = (end - begin);
        cout << n << "," << execTime << endl;

        delete(graph);
    }
}

int main() {
    test();
}