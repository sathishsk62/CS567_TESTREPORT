#include "avl.h"
#include <iostream>

AVL::AVL() : root(nullptr) {}

AVL::~AVL() {
    deleteTree(root);
}

Node* AVL::newNode(int key) {
    Node* node = new Node;
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1;
    return node;
}

int AVL::height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

int AVL::balanceFactor(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->left) - height(node->right);
}

Node* AVL::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

Node* AVL::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

Node* AVL::insert(Node* node, int key) {
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVL::insert(int key) {
    root = insert(root, key);
}

Node* AVL::minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

Node* AVL::remove(Node* node, int key) {
    if (node == nullptr)
        return node;

    if (key < node->key)
        node->left = remove(node->left, key);
    else if (key > node->key)
        node->right = remove(node->right, key);
    else {
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;

            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            } else
                *node = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }

    if (node == nullptr)
        return node;

    node->height = 1 + std::max(height(node->left), height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && balanceFactor(node->left) >= 0)
        return rotateRight(node);

    if (balance > 1 && balanceFactor(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && balanceFactor(node->right) <= 0)
        return rotateLeft(node);

    if (balance < -1 && balanceFactor(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void AVL::remove(int key) {
    root = remove(root, key);
}

bool AVL::search(int key) {
    Node* current = root;
    while (current != nullptr) {
        if (current->key == key)
            return true;
        else if (current->key < key)
            current = current->right;
        else
            current = current->left;
    }
    return false;
}

void AVL::printInorder() {
    printInorder(root);
}

void AVL::printInorder(Node* node) {
    if (node == nullptr)
        return;
    printInorder(node->left);
    std::cout << node->key << " ";
    printInorder(node->right);
}

void AVL::deleteTree(Node* node) {
    if (node == nullptr)
        return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int AVL::minValue(Node* node) {
    if (node == nullptr)
        return -1; // Or throw an exception
    while (node->left != nullptr)
        node = node->left;
    return node->key;
}

int AVL::maxValue(Node* node) {
    if (node == nullptr)
        return -1; // Or throw an exception
    while (node->right != nullptr)
        node = node->right;
    return node->key;
}

int AVL::getHeight() {
    return height(root);
}

int AVL::getBalanceFactor() {
    return balanceFactor(root);
}

int AVL::getMinValue() {
    return minValue(root);
}

int AVL::getMaxValue() {
    return maxValue(root);
}
