#include <iostream>
#include <vector>
#include <ctime>
#include <random>
#include <limits.h>

using namespace std;

clock_t start,finish;

void bucketSort(float a[], int n){
    
    vector<float> buckets[n];

    for(int i = 0; i < n; i++){
        int bucketIndex = n*a[i];
        buckets[bucketIndex].push_back(a[i]);
    }

    for(int i = 0; i < n; i++){
        for(int j = 1; j < buckets[i].size(); j++){
            float key = buckets[i].at(j);
            int h = j-1;
            while(h >= 0 && buckets[i][h] > key){
                buckets[i].at(h+1) = buckets[i].at(h);
                h--;
            }
            buckets[i].at(h+1) = key;
        }
    }

    int index = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < buckets[i].size(); j++){
            a[index++] = buckets[i].at(j);
        }
    }
}

void worstCase(int n) {
    float array[n];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 0.01);
    
    for(int i = 0; i < n; i++){
        array[i] = dis(gen);
    }

    start = clock();
    bucketSort(array, n);
    finish = clock();
    cout << "Worst case. Time = " << finish - start << endl;
}

void averageCase(int n) {
    float array[n];
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 0.999999);
    
    for(int i = 0; i < n; i++){
        array[i] = dis(gen);
    }

    start = clock();
    bucketSort(array, n);
    finish = clock();
    cout << "Average case. Time = " << finish - start << endl;
}

void bestCase(int n) {
    float array[n];
    
    float j = 0.0;
    for(int i = 0; i < n; i ++){
        array[i] = j;
        j+=double(1/n);
    }

    start = clock();
    bucketSort(array, n);
    finish = clock();
    cout << "Best case. Time = " << finish - start << endl;
}

int main(){
    int test_size ;
    cout << "n= ";
    cin >> test_size;
    
    worstCase(test_size);
    averageCase(test_size);  
    bestCase(test_size);
}