#include <iostream>
#include <queue>
#include <cmath>

using namespace std;

struct Node {
    Node *left;
    Node *right;
    double frequency;
    char character;

    Node(char character, double freq){
        this->left = this->right = NULL;
        this->character = character;
        this->frequency = freq;
    }
};

struct Compare {
    bool operator()(Node *l, Node *r) {
        return(l->frequency > r->frequency);
    }
};

Node* huffManStart(priority_queue<Node*, vector<Node*>, Compare> &minHeap) {
    priority_queue<Node*, vector<Node*>, Compare> mH = minHeap;

    while(mH.size() != 1) {
        Node *first = mH.top();
        mH.pop();
        Node *second = mH.top();
        mH.pop();

        Node *parent = new Node('\0', first->frequency + second->frequency);
        parent->left = first;
        parent->right = second;

        mH.push(parent);
    }
    return mH.top();
}

void printHuffManCodes(Node *node, string str) {
    if(node == NULL) {
        return;
    }
    if(node->character != '\0') {
        cout << node->character << ": " << str << endl;
    }

    printHuffManCodes(node->left, str+"0");
    printHuffManCodes(node->right, str+"1");
}

int height(Node *node){
    if(node==NULL) {
        return 0;
    }
    else {
        int lheight = height(node->left);
        int rheight = height(node->right);
        if (lheight > rheight){
            return(lheight+1);
        }
        else{
            return(rheight+1);
        }
    }
}

void printLevel(Node *node, int level, string str) {
    if(node == NULL) {
        return;
    }
    if(level == 0 && node->character != '\0') {
        cout << node->character << ": " << str << endl;
    }
    else if(level > 0) {
        printLevel(node->left, level -1, str+"0");
        printLevel(node->right, level-1, str+"1");
    }
}

void printByLevels(Node *root) {
    int h = height(root);
    for(int i = 0; i < h; i++) {
        cout << "Lvl: " << i << endl;
        printLevel(root, i, "");
        cout << endl;
    }
}

void getEaE(Node *node, int level, double *vals) {
    if(node == NULL) {
        return;
    }
    if(node->character != '\0') {
        double frequency = node->frequency/100.0;
        double dLevel = double(level);
        vals[0] += frequency*dLevel;
        vals[1] += frequency*log2(1/frequency);
    }
    else {
        getEaE(node->left, level+1, vals);
        getEaE(node->right, level+1, vals);
    }
}

void getExpectedAndEntropy(Node *root) {
    double vals[2] = {0.000, 0.000};
    getEaE(root, 0, vals);
    cout.precision(5);
    cout << "Expected number of bits per letter = " << vals[0] << endl;
    cout << "Entropy = " << vals[1] << endl;
    
}

priority_queue<Node*, vector<Node*>, Compare> createMinHeap(char *chars, double *freq, int size) {

    priority_queue<Node*, vector<Node*>, Compare> minHeap;
    for(int i = 0; i < size; i++) {
        minHeap.push(new Node(chars[i], freq[i]));
    }
    return minHeap;
}

int main() {

    char chars[] = {' ','e','t','a','o','i','n','s','h','r','d','l','c','u','m','w','f','g','y','p','b','v','k','j','x','q','z'};
    double freq[] = {18.3,10.2,7.7,6.8,5.9,5.8,5.5,5.1,4.9,4.8,3.5,3.4,2.6,2.4,2.1,1.9,1.8,1.7,1.6,1.6,1.3,.9,.6,.2,.2,.1,.1};
    int size = sizeof(chars)/sizeof(chars[0]);

    priority_queue<Node*, vector<Node*>, Compare> minHeap = createMinHeap(chars, freq, size);

    Node *encoding = huffManStart(minHeap);
    //cout << "~~~~~~~~~~In-Order~~~~~~~~~~" << endl;
    //  printHuffManCodes(encoding, "");
    cout << "~~~~~~~~~~By-Level~~~~~~~~~~" << endl;
    printByLevels(encoding);

    getExpectedAndEntropy(encoding);
}