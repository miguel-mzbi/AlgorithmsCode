#include <iostream>
#include <random>

using namespace std;

enum Color {RED, BLACK};

struct Node {
    int key;
    bool color;
    Node *left;
    Node *right;
    Node *parent;

    Node(int k) {
        key = k;
        left = right = parent = NULL;
        color = RED;
    }

    Node() {
        left = right = parent = NULL;
        color = BLACK;
    }
};

// Class to represent Red-Black Tree
class RBTree {
private:
    int size;
    Node *root;
    Node *nil;

    void rotateLeft(Node *);
    void rotateRight(Node *);
    void fixViolationInsert(Node *);
    void fixViolationRemove(Node *);
    void inOrderH(Node *, int);
    void transplant(Node *, Node *);
    Node* minimum(Node *);
public:
    RBTree();
    void insert(const int);
    void inOrder();
    void remove(Node *);
    int getSize();
    Node* get(int);
};

RBTree::RBTree() {
    this->size = 0;
    this->nil = new Node();
    this->nil->color = BLACK;
    this->root = this->nil;
    this->nil->parent = this->nil;
}

int RBTree::getSize() {
    return this->size;
}

void RBTree::inOrder() {
    inOrderH(this->root, 1);
}

void RBTree::inOrderH(Node *r, int lvl) {
    if (r->right != NULL) {
        inOrderH(r->right, lvl+1);
    }
    for(int i = 1; i < lvl; i++){
        cout << "\t";
    }
    cout << "[" << r->key << ", ";
    if(r->color){
        cout << "B";
    }
    else {
        cout << "R";
    }
    cout << "]" << endl;
    if (r->left != NULL) {
        inOrderH(r->left, lvl+1);
    }
}

Node* RBTree::get(int key) {
    Node *temp = this->root;
    while(temp->key != key && temp != this->nil) {
        if(key < temp->key) {
            temp = temp->left;
        }
        else {
            temp = temp->right;
        }
    }
    return temp;
}

void RBTree::insert(const int key) {
    Node *newNode = new Node(key);
    Node *y = this->nil;
    Node *x = this->root;
    while(x != this->nil) {
        y = x;
        if(newNode->key < x->key) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    newNode->parent = y;
    if(y == this->nil) {
        this->root = newNode;
    }
    else if(newNode->key < y->key) {
        y->left = newNode;
    }
    else {
        y->right = newNode;
    }
    newNode->left = this->nil;
    newNode->right = this->nil;
    newNode->color = RED;
    this->size++;
    fixViolationInsert(newNode);
}

void RBTree::fixViolationInsert(Node *nodeRB){
    Node *uncle;
    while(nodeRB->parent->color == RED){
        // Case A: Parent of nodeRB is left child of grand-parent of nodeRB
        if(nodeRB->parent == nodeRB->parent->parent->left) {
            uncle = nodeRB->parent->parent->right;
            // Case A1: The uncle of nodeRB is also red (Only recoloring)
            if(uncle->color == RED) {
                nodeRB->parent->color = BLACK;
                uncle->color = BLACK;
                nodeRB->parent->parent->color = RED;
                nodeRB = nodeRB->parent->parent;
            }
            else {
                // Case A2a: nodeRB is right child of its parent (Left-rotation)
                if(nodeRB == nodeRB->parent->right) {
                    nodeRB = nodeRB->parent;
                    rotateLeft(nodeRB);
                }
                // Case A2b: nodeRB is left child of its parent (Right-rotation)
                nodeRB->parent->color = BLACK;
                nodeRB->parent->parent->color = RED;
                rotateRight(nodeRB->parent->parent);
            }
        }
        // Case B: Parent of nodeRB is right child of grand-parent of nodeRB
        else {
            uncle = nodeRB->parent->parent->left;
            // Case B1: The uncle of nodeRB is also red (Only recoloring)
            if(uncle->color == RED) {
                nodeRB->parent->color = BLACK;
                uncle->color = BLACK;
                nodeRB->parent->parent->color = RED;
                nodeRB = nodeRB->parent->parent;
            }
            else {
                // Case B2a: nodeRB is left child of its parent (Right-rotation)
                if(nodeRB == nodeRB->parent->left) {
                    nodeRB = nodeRB->parent;
                    rotateRight(nodeRB);
                }
                // Case B2b: nodeRB is right child of its parent (Left-rotation)
                nodeRB->parent->color = BLACK;
                nodeRB->parent->parent->color = RED;
                rotateLeft(nodeRB->parent->parent);
            }
        }
    }
    this->root->color = BLACK;
}

void RBTree::rotateLeft(Node *nodeRB) {
    Node *nodeRBRight = nodeRB->right;
    nodeRB->right = nodeRBRight->left;
    if(nodeRBRight->left != this->nil) {
        nodeRBRight->left->parent = nodeRB;
    }
    nodeRBRight->parent = nodeRB->parent;
    if(nodeRB->parent == this->nil) {
        root = nodeRBRight;
    }
    else if(nodeRB == nodeRB->parent->left) {
        nodeRB->parent->left = nodeRBRight;
    }
    else {
        nodeRB->parent->right = nodeRBRight;
    }
    nodeRBRight->left = nodeRB;
    nodeRB->parent = nodeRBRight;
}

void RBTree::rotateRight(Node *nodeRB) {
    Node *nodeRBLeft = nodeRB->left;
    nodeRB->left = nodeRBLeft->right;
    if (nodeRBLeft->right != this->nil) {
        nodeRB->left->parent = nodeRB;
    }
    nodeRBLeft->parent = nodeRB->parent;
    if (nodeRB->parent == this->nil) {
        root = nodeRBLeft;
    }
    else if (nodeRB == nodeRB->parent->left) {
        nodeRB->parent->left = nodeRBLeft;
    }
    else {
        nodeRB->parent->right = nodeRBLeft;
    }
    nodeRBLeft->right = nodeRB;
    nodeRB->parent = nodeRBLeft;
}

void RBTree::transplant(Node *x, Node *y) {
    if(x->parent == this->nil) {
        this->root = y;
    }
    else if(x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->parent = x->parent;
}

Node* RBTree::minimum(Node *t) {
    Node *min = t;
    while(min->left != this->nil) {
        min = min->left;
    }
    return min;
}

void RBTree::remove(Node *toRemove) {
    Node *x;
    Node *y = toRemove;
    bool originalColor = y->color;
    if(toRemove->left == this->nil) {
        x = toRemove->right;
        transplant(toRemove, toRemove->left);
    }
    else if(toRemove->right == this->nil) {
        x = toRemove->left;
        transplant(toRemove, toRemove->left);
    }
    else {
        y = minimum(toRemove->right);
        originalColor = y->color;
        x = y->right;
        if(y->parent == toRemove) {
            x->parent = y;
        }
        else {
            transplant(y, y->right);
            y->right = toRemove->right;
            y->right->parent = y;
        }
        transplant(toRemove, y);
        y->left = toRemove->left;
        y->left->parent = y;
        y->color = toRemove->color;
    }
    if(originalColor == BLACK) {
        fixViolationRemove(x);
    }
}

void RBTree::fixViolationRemove(Node *) {
    //To continue
}

void generateUniformArray(int *a, int n){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1,100);
    for(int i = 0; i < n; i++){
        a[i] = dis(gen);
    }
}

void randomTree() {
    clock_t begin, end;
    for(int n = 1; n <= 1000; n++){
        int values[n];
        generateUniformArray(values, n);
        RBTree *tree = new RBTree();
    
        begin = clock();
        for(int i = 0; i < n; i++){
            tree->insert(values[i]);
        }
        end = clock();

        double execution = end - begin;
        cout << n << "," << execution << endl;
        delete(tree);
    }
}

int main() {
    RBTree *tree = new RBTree();
    tree->insert(30);
    tree->insert(20);
    tree->insert(40);
    tree->insert(35);
    tree->insert(34);
    tree->insert(22);
    tree->insert(21);
    tree->insert(21);
    tree->insert(21);
    tree->insert(21);
    tree->insert(23);
    cout << "Inoder Traversal of Created Tree\n";
    tree->inOrder();

    cout << endl << endl << "Testing:" << endl;
    randomTree();
}