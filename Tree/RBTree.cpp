#include <cstdlib>
#include <iostream>
#include <queue>

using namespace std;

enum Color {RED, BLACK};

struct Node
{
   int key;
   bool color;
   Node *left;
   Node *right;
   Node *parent;

   Node(int key) {
      this->key = key;
      left = right = parent = NULL;
   }
};

// Class to represent Red-Black Tree
class RBTree {
private:
    Node *root;
    void rotateLeft(Node *&, Node *&);
    void rotateRight(Node *&, Node *&);
    void fixViolation(Node *&, Node *&);
    void inOrderH(Node *);
    void levelOrderH(Node *);
    Node *insertH(Node *, Node *);
    Node *findSuccessor(Node *);
public:
    RBTree() { root = NULL; }
    void insert(const int &n);
    void inOrder();
    void levelOrder();
    void remove(const int &n);
};

void RBTree::inOrder() {
    inOrderH(root);
}

void RBTree::levelOrder() {
    levelOrderH(root); 
}

void RBTree::inOrderH(Node *root) {
    if (root == NULL) {
        return;
    }
    inOrderH(root->left);
    cout << root->key << "  ";
    inOrderH(root->right);
}

void RBTree::insert(const int &key) {
   Node *nodeRB = new Node(key);
   root = insertH(root, nodeRB);
   fixViolation(root, nodeRB);
}

Node* RBTree::insertH(Node* root, Node *nodeRB) {
    if (root == NULL) {
        return nodeRB;
    }
    if (nodeRB->key < root->key) {
        root->left  = insertH(root->left, nodeRB);
        root->left->parent = root;
    }
    else if (nodeRB->key > root->key) {
        root->right = insertH(root->right, nodeRB);
        root->right->parent = root;
    }
    return root;
}

void RBTree::levelOrderH(Node *root) {
    if (root == NULL) {
        return;
    }
    queue<Node *> queue;
    queue.push(root);
    while (!queue.empty()) {
        Node *temp = queue.front();
        cout << temp->key << "  ";
        queue.pop();
        if (temp->left != NULL) {
            queue.push(temp->left);
        }
        if (temp->right != NULL) {
            queue.push(temp->right);
        }
    }
}

void RBTree::rotateLeft(Node *&root, Node *&nodeRB) {
    Node *nodeRBRight = nodeRB->right;
    nodeRB->right = nodeRBRight->left;
    if (nodeRB->right != NULL) {
        nodeRB->right->parent = nodeRB;
    }
    nodeRBRight->parent = nodeRB->parent;
    if (nodeRB->parent == NULL) {
        root = nodeRBRight;
    }
    else if (nodeRB == nodeRB->parent->left) {
        nodeRB->parent->left = nodeRBRight;
    }
    else {
        nodeRB->parent->right = nodeRBRight;
    }
    nodeRBRight->left = nodeRB;
    nodeRB->parent = nodeRBRight;
}

void RBTree::rotateRight(Node *&root, Node *&nodeRB) {
    Node *nodeRBLeft = nodeRB->left;
    nodeRB->left = nodeRBLeft->right;
    if (nodeRB->left != NULL) {
        nodeRB->left->parent = nodeRB;
    }
    nodeRBLeft->parent = nodeRB->parent;
    if (nodeRB->parent == NULL) {
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

void RBTree::fixViolation(Node *&root, Node *&nodeRB)
{
    Node *parentNodeRB = NULL;
    Node *grandParentNodeRB = NULL;
    while ((nodeRB != root) && (nodeRB->color != BLACK) && (nodeRB->parent->color == RED)) {
        parentNodeRB = nodeRB->parent;
        grandParentNodeRB = nodeRB->parent->parent;
        // Case A: Parent of nodeRB is left child of grand-parent of nodeRB
        if (parentNodeRB == grandParentNodeRB->left) {
            Node *uncleNodeRB = grandParentNodeRB->right;
            // Case A1: The uncle of nodeRB is also red (Only recoloring)
            if (uncleNodeRB != NULL && uncleNodeRB->color == RED) {
                grandParentNodeRB->color = RED;
                parentNodeRB->color = BLACK;
                uncleNodeRB->color = BLACK;
                nodeRB = grandParentNodeRB;
            }
            else {
                // Case A2a: nodeRB is right child of its parent (Left-rotation)
                if (nodeRB == parentNodeRB->right) {
                    rotateLeft(root, parentNodeRB);
                    nodeRB = parentNodeRB;
                    parentNodeRB = nodeRB->parent;
                }
                // Case A2b: nodeRB is left child of its parent (Right-rotation)
                rotateRight(root, grandParentNodeRB);
                swap(parentNodeRB->color, grandParentNodeRB->color);
                nodeRB = parentNodeRB;
            }
        }
        // Case B: Parent of nodeRB is right child of grand-parent of nodeRB
        else {
            Node *uncleNodeRB = grandParentNodeRB->left;
            // Case B1: The uncle of nodeRB is also red (Only recoloring)
            if ((uncleNodeRB != NULL) && (uncleNodeRB->color == RED)) {
                grandParentNodeRB->color = RED;
                parentNodeRB->color = BLACK;
                uncleNodeRB->color = BLACK;
                nodeRB = grandParentNodeRB;
            }
            else {
                // Case B2a: nodeRB is left child of its parent (Right-rotation)
                if (nodeRB == parentNodeRB->left) {
                    rotateRight(root, parentNodeRB);
                    nodeRB = parentNodeRB;
                    parentNodeRB = nodeRB->parent;
                }
                // Case B2b: nodeRB is right child of its parent (Left-rotation)
                rotateLeft(root, grandParentNodeRB);
                swap(parentNodeRB->color, grandParentNodeRB->color);
                nodeRB = parentNodeRB;
            }
        }
    }
    root->color = BLACK;
}

Node * RBTree::findSuccessor(Node *root) {
    Node *temp = NULL;
    if(root->left != NULL) {
        temp = root->left;
        while(temp->right != NULL) {
            temp = temp->right;
        }
    }
    else {
        temp = root->right;
        while(temp->left != NULL) {
            temp = temp->left;
        }
    }
    return temp;
}

int main() {
    RBTree tree;
    tree.insert(6);
    tree.insert(5);
    tree.insert(4);
    tree.insert(3);
    tree.insert(2);
    tree.insert(1);
    cout << "Inoder Traversal of Created Tree\n";
    tree.inOrder();
    cout << "\nLevel Order Traversal of Created Tree\n";
    tree.levelOrder();
}