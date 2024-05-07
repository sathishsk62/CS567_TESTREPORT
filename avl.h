#ifndef AVL_H
#define AVL_H

struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

class AVL {
public:
    AVL();
    ~AVL();
    void insert(int key);
    void remove(int key);
    bool search(int key);
    void printInorder();
    int getHeight();
    int getBalanceFactor();
    int getMinValue();
    int getMaxValue();

private:
    Node* root;

    Node* newNode(int key);
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    int height(Node* node);
    int balanceFactor(Node* node);
    Node* insert(Node* node, int key);
    Node* minValueNode(Node* node);
    Node* remove(Node* node, int key);
    void printInorder(Node* node);
    void deleteTree(Node* node);
    int minValue(Node* node);
    int maxValue(Node* node);
};

#endif
