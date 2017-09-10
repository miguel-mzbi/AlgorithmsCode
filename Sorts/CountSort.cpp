#include <iostream>
#include <ctime>
#include <random>
#include <limits.h>

using namespace std;

clock_t start,finish;

void countSort(int arr[], int n, int max) {
    int output[n];
    int i;
    int count[max+1] = {0};
 
    for (i = 0; i < n; i++) {
        count[arr[i]]++;
    }
 
    for (i = 1; i <= max; i++) {
        count[i] += count[i - 1];
    }
 
    for (i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    for (i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void worstCase(int n, int k) {
    int array[n];

    for(int i = 0; i < n; i++){
        array[i] = k;
    }

    start = clock();
    countSort(array, n, k);
    finish = clock();
    cout << "Worst case. Time = " << finish - start << endl;
}

void averageCase(int n, int k) {
    int array[n];
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, k+1);
    
    for(int i = 0; i < n; i++){
        array[i] = dis(gen);
    }

    start = clock();
    countSort(array, n, k);
    finish = clock();
    cout << "Average case. Time = " << finish - start << endl;
}

void bestCase(int n, int k) {
    int array[n];
    
    for(int i = 0; i < n; i ++){
        array[i] = i%k;
    }

    start = clock();
    countSort(array, n, k);
    finish = clock();
    cout << "Best case. Time = " << finish - start << endl;
}

int main(){
    int n = 1000000;
    int k = 9999;

    worstCase(n, k);
    averageCase(n, k);  
    bestCase(n, k);
}