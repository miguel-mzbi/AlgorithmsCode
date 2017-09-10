#include <iostream>
#include <ctime>
#include <random>
#include <limits.h>

using namespace std;

clock_t start,finish;

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(int arr[], int n, int exp) {
    int output[n];
    int i;
    int count[10] = {0};
 
    for (i = 0; i < n; i++) {
        count[(arr[i]/exp)%10]++;
    }
 
    for (i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }
 
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i]/exp)%10] - 1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }

    for (i = 0; i < n; i++) {
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n) {
    int max = getMax(arr, n);
    for (int exp = 1; max/exp > 0; exp *= 10) {
        countSort(arr, n, exp);        
    }
}

void worstCase(int n) {
    int array[n];

    for(int i = 0; i < n; i++){
        array[i] = 999;
    }

    start = clock();
    radixSort(array, n);
    finish = clock();
    cout << "Worst case. Time = " << finish - start << endl;
}

void averageCase(int n) {
    int array[n];
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 999);
    
    for(int i = 0; i < n; i++){
        array[i] = dis(gen);
    }

    start = clock();
    radixSort(array, n);
    finish = clock();
    cout << "Average case. Time = " << finish - start << endl;
}

void bestCase(int n) {
    int array[n];
    
    for(int i = 0; i < n; i ++){
        array[i] = i;
    }

    start = clock();
    radixSort(array, n);
    finish = clock();
    cout << "Best case. Time = " << finish - start << endl;
}

int main(){
    int test_size = 1000000;
    
    worstCase(test_size);
    averageCase(test_size);  
    bestCase(test_size);
}