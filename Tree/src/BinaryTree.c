#include <stdio.h>
#include <stdlib.h>
#include "BinaryTree.h"

#define MAX(_A, _B) ({__typeof__ (_A) a=(_A); __typeof__ (_B) b=(_B);(a<b)?b:a;})

BinaryTree empty() {
    BinaryTree tree = (BinaryTree) malloc(sizeof(*tree));
    tree->left_child = NULL;
    tree->right_child = NULL;
    tree->current = NULL;
    tree->parent = NULL;
    return tree;
}

Element *makeElement(int value) {
    Element *element = (Element *) malloc(sizeof(element));
    element->value = value;
    return element;
}

BinaryTree makeRoot(BinaryTree left, Element *root, BinaryTree right, BinaryTree parent) {
    BinaryTree tree = empty();
    tree->current = root;
    tree->parent = parent;
    tree->left_child = left;
    tree->left_child->parent = tree;
    tree->right_child = right;
    tree->right_child->parent = tree;
    return tree;
}

int isEmpty(BinaryTree tree) {
    return tree->current == NULL && tree->right_child == NULL && tree->left_child == NULL;
}

int hasLeft(BinaryTree tree) {
    return tree->left_child != NULL;
}

int hasRight(BinaryTree tree) {
    return tree->right_child != NULL;
}

int hasParent(BinaryTree tree) {
    return tree->parent != NULL;
}

int has(BinaryTree tree, Element element) {
    if (isEmpty(tree)) {
        return 0;
    }
    if (areElementsEquals(value(tree), element)) {
        return 1;
    }
    return has(tree->left_child, element) || has(tree->right_child, element);
}

int areElementsEquals(Element element1, Element element2) {
    return element1.value == element2.value;
}

Element value(BinaryTree tree) {
    return *tree->current;
}

BinaryTree left(BinaryTree tree) {
    return tree->left_child;
}

BinaryTree right(BinaryTree tree) {
    return tree->right_child;
}

BinaryTree parent(BinaryTree tree) {
    return tree->parent;
}

int height(BinaryTree tree) {
    if (isEmpty(tree)) {
        return 0;
    }
    return 1 + MAX(height(tree->right_child), height(tree->left_child));
}

int count(BinaryTree tree) {
    if (isEmpty(tree)) {
        return 0;
    }
    return 1 + count(tree->right_child) + count(tree->left_child);
}

void printElement(Element *element) {
    printf("%d ", element->value);
}


void printPrefix(BinaryTree tree) {
    if (isEmpty(tree)) {
        return;
    }
    printElement(tree->current);
    printPrefix(tree->left_child);
    printPrefix(tree->right_child);
}

void printInfix(BinaryTree tree) {
    if (isEmpty(tree)) {
        return;
    }
    printInfix(tree->left_child);
    printElement(tree->current);
    printInfix(tree->right_child);
}

void printPostfix(BinaryTree tree) {
    if (isEmpty(tree)) {
        return;
    }
    printPostfix(tree->left_child);
    printPostfix(tree->right_child);
    printElement(tree->current);
}

int prefix(BinaryTree tree, Element *element, int nbr) {
    if (isEmpty(tree)) {
        return 0;
    }
    element[nbr-1]=*tree->current;
    element = realloc(element, sizeof(Element) * (++nbr));
    return 1+prefix(tree->left_child,element,nbr)+prefix(tree->right_child,element,nbr);

}


Element *infix(BinaryTree tree, Element *element, int nbr);

Element *postfix(BinaryTree tree, Element *element, int nbr);