#include <iostream>
#include <cmath>
#include <random>
#include <limits.h>
#include <string>
#include <bitset>
#include <ctime>

using namespace std;

clock_t start, finish;

struct node{
    int key;
    int value;
    node *next;
};

class HashTable{
private:
    node **table;
    double A;
    int n;
    int m;
    int **rMatrix;
    int b;
public:
    HashTable(int buckets);

    int product(int row, int v);
    int hashMatrix(int key);
    void insertMatrix(int key, int value);
    int searchMatrix(int key);
    int deleteMatrix(int key);

    int hashDivision(int key);
    void insertDivision(int key, int value);
    int searchDivision(int key);
    int deleteDivision(int key);

    int hashMultiplication(int key);
    void insertMultiplication(int key, int value);
    int searchMultiplication(int key);
    int deleteMultiplication(int key);
};

HashTable:: HashTable(int buckets) {
    table = new node*[buckets];
    for (int i = 0; i < buckets; i++) {
        table[i] = NULL;        
    }

    m = buckets;
    n = 0;
    A = (sqrt(5)-1.0)/2.0;
    b = log(m);
    int j = 1;

    rMatrix = new int*[b];
    for(int i = 0; i < b; ++i){
        rMatrix[i] = new int[16];
    }
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 1);
    for(int i = 0; i < b; i++ ) {
        for ( int j = 0; j < 16; j++) {
          rMatrix[i][j] = dis(gen);
        }
    }
}

int HashTable::product(int row, int v) {
    int i = row & v;
    i = i -((i >> 1) & 0x55555555);
    i = ((i & 0x33333333) + ((i >> 2) & 0x33333333));
    i = (((i + (i >> 4)) & 0x0F0F0F0F) * 0x01010101) >> 24;
    return i & 0x00000001;
}

int HashTable::hashMatrix(int key){
    string hashBits;
    string row;
    int result;
    for(int i = 0; i < b; i++) {
        for(int j = 0; j < 16; j++) {
            row += to_string(rMatrix[i][j]);
        }
        bitset<16> bits(row);
        int rowInt = bits.to_ulong();
        hashBits += to_string(product(rowInt, key ));
        row = "";
    }
    bitset<16> bitR(hashBits);
    result = bitR.to_ulong();
    return result;
}

void HashTable::insertMatrix(int key, int value){
    int hash = hashMatrix(key);    
    if(table[hash] == NULL){
        node *entry = new node;
        entry->key = key;
        entry->value = value;
        entry->next = NULL;
        table[hash] = entry;        
    }
    else{
        node *entry = table[hash];
        while(entry->next != NULL){
            entry = entry->next;
            if(entry->key == key){
                entry->value = value;
            }
            else {
                node *temp = new node;
                temp->key = key;
                temp->value = value;
                temp->next = NULL;
                entry->next = temp;                
            }  
        } 
    }
}

int HashTable::searchMatrix(int key){
    int hash = hashMatrix(key);
    if(table[hash] == NULL){
        cout << "Unsuccessful search ";        
        return -1;
    }
    else {
        node *entry = table[hash];
        while(entry->next != NULL && entry->key != key) {
            entry = entry ->next;
        }
        if(entry == NULL) {
            cout << "Unsuccessful search ";
            return -1; 
        }
        else {
            cout << "Successful search ";            
            return entry->value;
        }
    }
}

int HashTable::deleteMatrix(int key){
    int hash = hashMatrix(key);
    if(table[hash] != NULL) {
        node *prevEntry = NULL;
        node *entry = table[hash];
        while(entry->next != NULL && entry->key != key) {
            prevEntry = entry;
            entry = entry->next;
        }
        if(entry->key == key){
            if(prevEntry == NULL) {
                node *nextEntry = entry->next;
                table[hash] = nextEntry;
                return entry->value;
            }
            else {
                node *next = entry->next;
                prevEntry->next = next;
                return entry->value;                
            }
        }
    }
}

int HashTable::hashDivision(int key){
    return key%m;
}

void HashTable::insertDivision(int key, int value){
    int hash = hashDivision(key);    
    if(table[hash] == NULL){
        node *entry = new node;
        entry->key = key;
        entry->value = value;
        entry->next = NULL;
        table[hash] = entry;        
    }
    else{
        node *entry = table[hash];
        while(entry->next != NULL){
            entry = entry->next;
            if(entry->key == key){
                entry->value = value;
            }
            else {
                node *temp = new node;
                temp->key = key;
                temp->value = value;
                temp->next = NULL;
                entry->next = temp;                
            }  
        } 
    }
}

int HashTable::searchDivision(int key){
    int hash = hashDivision(key);
    if(table[hash] == NULL){
        cout << "Unsuccessful search ";        
        return -1;
    }
    else {
        node *entry = table[hash];
        while(entry->next != NULL && entry->key != key) {
            entry = entry ->next;
        }
        if(entry == NULL) {
            cout << "Unsuccessful search ";
            return -1; 
        }
        else {
            cout << "Successful search ";            
            return entry->value;
        }
    }
}

int HashTable::deleteDivision(int key){
    int hash = hashDivision(key);
    if(table[hash] != NULL) {
        node *prevEntry = NULL;
        node *entry = table[hash];
        while(entry->next != NULL && entry->key != key) {
            prevEntry = entry;
            entry = entry->next;
        }
        if(entry->key == key){
            if(prevEntry == NULL) {
                node *nextEntry = entry->next;
                table[hash] = nextEntry;
                return entry->value;
            }
            else {
                node *next = entry->next;
                prevEntry->next = next;
                return entry->value;                
            }
        }
    }
}

int HashTable::hashMultiplication(int key){
    return floor(m*(fmod(key*A,1)));
}

void HashTable::insertMultiplication(int key, int value){
    int hash = hashMultiplication(key);    
    if(table[hash] == NULL){
        node *entry = new node;
        entry->key = key;
        entry->value = value;
        entry->next = NULL;
        table[hash] = entry;        
    }
    else{
        node *entry = table[hash];
        while(entry->next != NULL){
            entry = entry->next;
            if(entry->key == key){
                entry->value = value;
            }
            else {
                node *temp = new node;
                temp->key = key;
                temp->value = value;
                temp->next = NULL;
                entry->next = temp;                
            }  
        } 
    }
}

int HashTable::searchMultiplication(int key){
    int hash = hashMultiplication(key);
    if(table[hash] == NULL){
        cout << "Unsuccessful search ";        
        return -1;
    }
    else {
        node *entry = table[hash];
        while(entry->next != NULL && entry->key != key) {
            entry = entry ->next;
        }
        if(entry == NULL) {
            cout << "Unsuccessful search ";
            return -1; 
        }
        else {
            cout << "Successful search ";            
            return entry->value;
        }
    }
}

int HashTable::deleteMultiplication(int key){
    int hash = hashMultiplication(key);
    if(table[hash] != NULL) {
        node *prevEntry = NULL;
        node *entry = table[hash];
        while(entry->next != NULL && entry->key != key) {
            prevEntry = entry;
            entry = entry->next;
        }
        if(entry->key == key){
            if(prevEntry == NULL) {
                node *nextEntry = entry->next;
                table[hash] = nextEntry;
                return entry->value;
            }
            else {
                node *next = entry->next;
                prevEntry->next = next;
                return entry->value;                
            }
        }
    }
}

void matrix(int m, int n) {
    cout << endl;
    cout << "Matrix Method UNIFORM" << endl;
    HashTable matrixHT(m);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,100);

    int key;
    for(int i = 0; i < n; i++){
        key = dis(gen);
        matrixHT.insertMatrix(key, key);
    }
    for(int i = 0; i < 100; i++){
        key = dis(gen);
        start = clock();
        cout << matrixHT.searchMatrix(key) << " ";
        finish = clock();
        cout << "Time for search = " << finish-start << endl;
    }
    cout << endl;

    cout << "Matrix Method GAUSSIAN" << endl;
    HashTable matrixHTG(m);

    normal_distribution<> disG(1,100);

    for(int i = 0; i < n; i++){
        key = disG(gen);
        matrixHTG.insertMatrix(key, key);
    }
    for(int i = 0; i < 100; i++){
        key = disG(gen);
        start = clock();
        cout << matrixHTG.searchMatrix(key) << " ";
        finish = clock();
        cout << "Time for search = " << finish-start << endl;
    }
    cout << endl;
    
}

void division(int m, int n) {
    cout << "Division Method UNIFORM" << endl;
    HashTable divisionHT(m);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,100);

    int key;
    for(int i = 0; i < n; i++){
        key = dis(gen);
        divisionHT.insertMatrix(key, key);
    }
    for(int i = 0; i < 100; i++){
        key = dis(gen);
        start = clock();
        cout << divisionHT.searchMatrix(key) << " ";
        finish = clock();
        cout << "Time for search = " << finish-start << endl;
    }
    cout << endl;

    cout << "Division Method GAUSSIAN" << endl;
    HashTable divisionHTG(m);

    normal_distribution<> disG(1,100);

    for(int i = 0; i < n; i++){
        key = disG(gen);
        divisionHTG.insertMatrix(key, key);
    }
    for(int i = 0; i < 100; i++){
        key = disG(gen);
        start = clock();
        cout << divisionHTG.searchMatrix(key) << " ";
        finish = clock();
        cout << "Time for search = " << finish-start << endl;
    }
    cout << endl; 
}

void multiplication(int m, int n) {
    cout << "Multiplication Method UNIFORM" << endl;
    HashTable multiplicationHT(m);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,100);

    int key;
    for(int i = 0; i < n; i++){
        key = dis(gen);
        multiplicationHT.insertMatrix(key, key);
    }
    for(int i = 0; i < 100; i++){
        key = dis(gen);
        start = clock();
        cout << multiplicationHT.searchMatrix(key) << " ";
        finish = clock();
        cout << "Time for search = " << finish-start << endl;
    }
    cout << endl;

    cout << "Multiplication Method GAUSSIAN" << endl;
    HashTable multiplicationHTG(m);

    normal_distribution<> disG(1,100);

    for(int i = 0; i < n; i++){
        key = disG(gen);
        multiplicationHTG.insertMatrix(key, key);
    }
    for(int i = 0; i < 100; i++){
        key = disG(gen);
        start = clock();
        cout << multiplicationHTG.searchMatrix(key) << " ";
        finish = clock();
        cout << "Time for search = " << finish-start << endl;
    }
}

int main(){
    int m = 100;
    int n = 100;

    division(m, n);
    multiplication(m, n);
    matrix(m, n);
}