#include <iostream>
#include <random>
#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> WV;

class Graph {
    int V;
    list<pair<int, int> > *adj;
public:
    Graph(int);
    void addEdge(int, int, int);
    void dijkstra(int);
};

Graph::Graph(int v) {
    this->V = v;
    adj = new list<WV>[v];
}

void Graph::addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(w, v));
    adj[v].push_back(make_pair(w, u));
}

void Graph::dijkstra(int src) {
    priority_queue<WV, vector<WV>, greater<WV> > PQ;
    vector<int> distances(this->V, numeric_limits<int>::max());
    PQ.push(make_pair(0, src));
    distances[src] = 0;
    while(!PQ.empty()) {
        int u = PQ.top().second;
        PQ.pop();
        list<pair<int, int> >::iterator i;
        for(i = this->adj[u].begin(); i != this->adj[u].end(); ++i) {
            int v = (*i).second;
            int w = (*i).first;
            if(distances[v] > distances[u] + w) {
                distances[v] = distances[u] + w;
                PQ.push(make_pair(distances[v], v));
            }
        }
    }
    //printf("Vertex   Distance from Source\n");
    //for (int i = 0; i < V; ++i)
    //    printf("%d \t\t %d\n", i, distances[i]);
}

int main() {
    for(int n = 10; n < 1000; n++) {
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
                    uniform_int_distribution<> dis(0, 100);
                    int w = dis(gen);
            
                    graph->addEdge(i, j, w);
                }
            }
        }
    
        clock_t begin, end;
    
        begin = clock();
        graph->dijkstra(0);
        end = clock();
    
        double executionTime = (end - begin);
    
        cout << n << "," << executionTime << endl;
    
        delete(graph);
    }
}