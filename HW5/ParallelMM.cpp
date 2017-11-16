#include <omp.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <random>

using namespace std;

#define max 1023

ofstream myfile;

int a[max][max];
int b[max][max];

int c[max][max];
int d[max][max];

void generateMatrices(int n) {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
            random_device rd;
            mt19937 gen(rd());
            uniform_int_distribution<> dis(0, 100);
			a[i][j] = dis(gen);
			b[i][j] = dis(gen);
		}
	}
}

void matrixOneThread(int n) {

    memset(c, 0, sizeof c);

	int i,j,k;
    double startT = omp_get_wtime();
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++) {
			for(k = 0; k < n; k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
    double endT = omp_get_wtime();
    
	double executionTime = endT-startT;
    cout << n << "," << executionTime << endl;
    myfile.open("MatrixOne.txt", std::ofstream::app);
    myfile << n << "," << executionTime << "\n";
    myfile.close();
}

void matrixMultiThread(int n) {

    int i, j, k;
    memset(d, 0, sizeof d);
    
    double startT = omp_get_wtime();
    
    # pragma omp parallel \
    private(i,j,k) \
    shared(a,b,c,n) 
    
    # pragma omp for
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            for(k = 0; k < n; k++) {
                d[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    double endT = omp_get_wtime();
    double executionTime = endT-startT;
    cout << n << "," << executionTime << endl;
    myfile.open("MatrixMulti.txt", std::ofstream::app);
    myfile << n << "," << executionTime << "\n";
    myfile.close();
    
}

int main() {

	for(int i = 10; i <= 500; i++) {
        generateMatrices(i);
	    matrixOneThread(i);
	    matrixMultiThread(i);
    }
	
	return 0;
	
}