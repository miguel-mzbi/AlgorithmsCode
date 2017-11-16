#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <random>
#include <fstream>

using namespace std;

struct Edge {
    int src, dest, weight;
    Edge(int s, int d, int w) {
        src = s;
        dest = d;
        weight = w;
    }
};

class Graph {
private:
    int V, E;
    vector<Edge> edges;
public:
    Graph(int);
    void addEdge(int, int, int);
    bool bellman(int);
};

Graph::Graph(int v) {
    this->V = v;
}

void Graph::addEdge(int u, int v, int w) {
    this->edges.push_back(Edge(u, v, w));
}

bool Graph::bellman(int src) {

    int V = this->V;
    int E = this->edges.size();
    int distances[V];

    for(int i = 0; i < V; i++) {
        distances[i] = INT_MAX;
    }
    distances[src] = 0;

    for(int i = 1; i <= V-1; i++) {
        for(int j = 0; j < E; j++) {
            
            int u = this->edges[j].src;
            int v = this->edges[j].dest;
            int weight = this->edges[j].weight;
            if (distances[u] != INT_MAX && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
            }
        }
    }

    for (int i = 0; i < E; i++) {
        int u = this->edges[i].src;
        int v = this->edges[i].dest;
        int weight = this->edges[i].weight;
        if (distances[u] != INT_MAX && distances[u] + weight < distances[v])
            printf("Graph contains negative weight cycles\n");
            return false;
    }

    //printf("Vertex   Distance from Source\n");
    //for (int i = 0; i < V; ++i) {
    //    printf("%d \t\t %d\n", i, distances[i]);
    //}
    
    return true;
}

int main() {

    ofstream myfile;
    myfile.open ("BellmanResults.txt");

    for(int n = 10; n <= 250; n++) {
        Graph *graph = new Graph(n);
    
        double Et = 0.2;
        double a;
    
        for(int i = 0; i < n; i++, i++) {
            for(int j = i; j < n; j++) {
                random_device rd;
                mt19937 gen(rd());
                uniform_real_distribution<> dis(0.0, 1);
                a = dis(gen);
        
                if (a > Et && i != j) {
                    random_device rd;
                    mt19937 gen(rd());
                    uniform_int_distribution<> dis(-100, 100);
                    int w = dis(gen);
            
                    graph->addEdge(i, j, w);
                }
            }
        }
    
        clock_t begin, end;
    
        begin = clock();
        graph->bellman(0);
        end = clock();
    
        double executionTime = (end - begin);
    
        cout << n << "," << executionTime << endl;
        myfile << n << "," << executionTime << "\n";    
        delete(graph);
    }
    myfile.close();
}
