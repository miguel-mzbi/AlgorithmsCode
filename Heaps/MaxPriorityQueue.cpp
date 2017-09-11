// MaxPriorityQueue.cpp
// Implementation of MaxPriorityQueue using MaxHeap

#include <stdio.h>
#include <math.h>
#include <iostream>
#include <random>
#include <limits.h>
#include <ctime>

using namespace std;

clock_t start,finish;

class PriorityQueue{
private:
    int *heapArray;
    int lenght;
    int size;
    int parent(int i) {return floor(i/2);}
    int left(int i) {return 2*i;}
    int right(int i) {return 2*i+1;}
    void swap(int A, int B);
    void increasePriority(int i);
    void maxHeapify(int i);    
public:
    void printArray();
    PriorityQueue(int capacity);
    int popMax();
    int getMax() {return heapArray[1];}
    bool empty(){return size == 0;};
    int getSize() {return size;}
    void changePriority(int key, int newPriority);
    void insert(int key);
};

PriorityQueue::PriorityQueue(int capacity) {
    lenght = capacity;
    size = 0;
    heapArray = new int[capacity+1];
}

void PriorityQueue::printArray() {
    for(int i = 0; i <= size; i++) {
        cout << heapArray[i] << " ";
    }
    cout<<endl;
    
}

int PriorityQueue::popMax() {
    if(empty()) {
        throw "Empty list. Can't pop max.";
    }
    else if(size == 1) {
        size--;
        return heapArray[1];
    }
    else {
        int root = heapArray[1];
        heapArray[1] = heapArray[size];
        heapArray[size] = -1;
        size--;
        maxHeapify(1);
        return root; 
    }
}

void PriorityQueue::changePriority(int key, int newPriority) {
    int temp = -1;
    int i = 1;
    for(i = 1; i <= size; i++) {
        if(heapArray[i] == key) {
            temp = heapArray[i];
            break;
        }
    }
    if(temp != -1) {
        if(temp == newPriority) {
            cout << "Priority was the same. Nothing changed." << endl;
        }
        else if(temp < newPriority) {
            heapArray[i] = newPriority;
            increasePriority(i);
        }
        else if(temp < newPriority) {
            heapArray[i]= newPriority;          
            maxHeapify(i);
        }
    }
    else {
        throw "Can't find key.";        
    }
}

void PriorityQueue::insert(int key) {
    if(size == lenght) {
        throw "MaxPriorityQueue at max capacity.";
    }
    size++;
    heapArray[size] = key;
    increasePriority(size);
}

void PriorityQueue::swap(int A, int B) {
    int temp = heapArray[A];
    heapArray[A] = heapArray[B];
    heapArray[B] = temp;
}

void PriorityQueue::increasePriority(int i) {
    while(i != 0 && parent(i) != 0 && heapArray[parent(i)] < heapArray[i]) {
        swap(i, parent(i));
        i = parent(i);
    }
}


void PriorityQueue::maxHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int largest = i;

    if(l <= size && heapArray[l] > heapArray[i]) {
        largest = l;
    }
    if(r <= size && heapArray[r] > heapArray[largest]) {
        largest = r;
    }
    if(largest != i) {
        cout << i << " " << largest << endl;
        swap(i, largest);
        maxHeapify(largest);
    }
}

void worstCase(int n) {
    PriorityQueue pq(n);
    
    start = clock();
    for(int i = 0; i < n; i++){
        pq.insert(i);
    }
    finish = clock();
    cout << "Worst case (insert). Time = " << finish - start << endl;
    
    start = clock();
    int max = pq.getMax();
    finish = clock();
    cout << "Get max " << max << ". Time = " << finish - start << endl;
}

void averageCase(int n) {
    PriorityQueue pq(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, n);
    
    start = clock();
    for(int i = 0; i < n; i++){
        pq.insert(dis(gen));
    }
    finish = clock();
    cout << "Average case (insert). Time = " << finish - start << endl;
    
    start = clock();
    int max = pq.getMax();
    finish = clock();
    cout << "Get max " << max << ". Time = " << finish - start << endl;
}

void bestCase(int n) {
    PriorityQueue pq(n);
    
    start = clock();
    for(int i = n; i > 0; i--){
        pq.insert(i);
    }
    finish = clock();
    cout << "Best case (insert). Time = " << finish - start << endl;
    
    start = clock();
    int max = pq.getMax();
    finish = clock();
    cout << "Get max " << max << ". Time = " << finish - start << endl;
}

int main() {
    cout << "n = ";
    int n;
    cin >> n;
    worstCase(n);
    averageCase(n);
    bestCase(n);
}