#include <deepstate/DeepState.hpp>
#include "avl.h"

using namespace deepstate;

TEST(AVLTree, InsertionAndSearch) {
    AVL tree;
    int key = DeepState_IntInRange(0, 100);

    tree.insert(key);

    ASSERT_TRUE(tree.search(key)) << "Key " << key << " was not found after insertion";
}

TEST(AVLTree, Removal) {
    AVL tree;
    int key = DeepState_IntInRange(0, 100);

    tree.insert(key);
    tree.remove(key);

    ASSERT_FALSE(tree.search(key)) << "Key " << key << " was found after removal";
}

TEST(AVLTree, HeightAndBalance) {
    AVL tree;
    int keys[] = {50, 25, 75, 10, 30, 60, 80};

    for (int key : keys) {
        tree.insert(key);
    }

    ASSERT_LE(tree.getHeight(), 4) << "Tree height exceeded expected value";
    ASSERT_LE(abs(tree.getBalanceFactor()), 1) << "Tree balance factor exceeded expected value";
}

TEST(AVLTree, MinAndMaxValue) {
    AVL tree;
    int keys[] = {50, 25, 75, 10, 30, 60, 80};

    for (int key : keys) {
        tree.insert(key);
    }

    ASSERT_EQ(tree.getMinValue(), 10) << "Incorrect minimum value";
    ASSERT_EQ(tree.getMaxValue(), 80) << "Incorrect maximum value";
}
