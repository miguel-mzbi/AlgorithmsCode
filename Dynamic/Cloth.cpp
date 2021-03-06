#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

int X, Y;
vector<vector<int> > figures;
vector<vector<int> > F;
vector<vector<int> > G;

void setF() {
    int minW = figures[0][0];
    int minH = figures[0][1];
    for(int i = 1; i < figures.size(); i++) { // Find smallest dimensions for x and y
        if(figures[i][0] < minW) {
            minW = figures[i][0];
        }
        if(figures[i][1] < minH) {
            minH = figures[i][1];
        }
    }
    for(int i = 0; i < Y+1; i++) { // Set as 0 every possible rectangle that will not fit a sellable rectangle
        F.push_back(vector<int>(X+1));
        G.push_back(vector<int>(X+1));
        for(int j = 0; j < X+1; j++) {
            if(i < minH || j < minW) {
                G[i][j] = figures.size()+11;                
                F[i][j] = 0;
            }
            else if(i >= minH || j >= minW) {
                F[i][j] = -1;
                G[i][j] = 0;                
            }
        }
    }

}

int optimizing(int x, int y) {
    if(F[y][x] >= 0) { // If max was already found
        return F[y][x];        
    }
    else {
        F[y][x] = 0;
        for(int i = 0; i < figures.size(); i++) {
            if(figures[i][0] > x || figures[i][1] > y) { // If size doesn't fit
                continue;
            }
            int u, v, maxI;
            u = optimizing(x-figures[i][0], figures[i][1]) + optimizing(x, y-figures[i][1]) + figures[i][2]; // Horizontal cut
            if(F[y][x] < u) { // Save to table if it's bigger (Future overlapping case won't have to recurse)
                F[y][x] = u;
                G[y][x] = i+1;
            }
            v = optimizing(figures[i][0], y-figures[i][1]) + optimizing(x-figures[i][0], y) + figures[i][2]; // Vertical cut
            if(F[y][x] < v) { // Save to table if it's bigger (Future overlapping case won't have to recurse)
                F[y][x] = maxI;
                G[y][x] = -(i+1);                
            }
        }
    }
    return F[y][x];    
}

int main(){

    ifstream myFile;
    myFile.open("cloth.txt");
    string line;
    int a, b, c;

    getline(myFile, line);
    stringstream iss(line);
    if(iss >> a >> b) {        
        X = a;
        Y = b;
    }

    while(getline(myFile, line)) {
        stringstream iss(line);
        if(iss >> a >> b >> c) {            
            vector<int> temp(3);
            temp[0] = a;
            temp[1] = b;
            temp[2] = c;
            figures.push_back(temp);
        }
    }

    setF();
    int maxValue = 0;
    maxValue = optimizing(X, Y);
    cout << "First line of cloth.txt represents size of cloth. Has the format X Y" << endl;
    cout << "Next lines represent available rectangles with a prize. Have the format x y cost" << endl;
    cout << "G[y][x], represents the optimum piece i, that was used for a cloth of size x*y" << endl;
    cout << "If value = " << figures.size()+11 << " means size can't be used" << endl;
    for(int j = 0; j <= Y+1; j++) {
        for(int i = 0; i <= X; i++) {

            if(i == 0 && j != 0 && j != 1) {
                cout << j-1 << " | \t";
            }
            else if(j == 0) {
                if(i != 0) {
                    cout << i << "\t";
                }
                else {
                    cout << "\t";
                }
            }
            else if(j == 1) {
                if(i != 0) {
                    cout << "-\t";                    
                }
                else {
                    cout << "\t";
                }
            }
            else {
                cout << G[j-1][i] << "\t";
            }
        }
        cout << endl;
    }
    cout << endl << "F[y][x]" << endl << "If value = -1 means size wasn't processed" << endl;
    for(int j = 0; j <= Y+1; j++) {
        for(int i = 0; i <= X; i++) {

            if(i == 0 && j != 0 && j != 1) {
                cout << j-1 << " | \t";
            }
            else if(j == 0) {
                if(i != 0) {
                    cout << i << "\t";
                }
                else {
                    cout << "\t";
                }
            }
            else if(j == 1) {
                if(i != 0) {
                    cout << "-\t";                    
                }
                else {
                    cout << "\t";
                }
            }
            else {
                cout << F[j-1][i] << "\t";
            }
        }
        cout << endl;
    }
    cout  << endl << "Max revenue of cloth of size " << X << "x" << Y << " is: " << maxValue << endl;

    for(int j = 0; j <= Y; j++) {
        F[j].clear();
        G[j].clear();
    }
    int z = figures.size();
    for(int i = 0; i < z; i++) {
        figures[i].clear();
    }
    F.clear();
    G.clear();
    figures.clear();
    maxValue = 0;
}