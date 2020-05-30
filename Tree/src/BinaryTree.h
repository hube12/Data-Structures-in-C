#ifndef LAB3_KESSLER47U_BINARYTREE_H
#define LAB3_KESSLER47U_BINARYTREE_H


typedef struct {
    int value;
} Element;
typedef struct node {
    struct node *parent;
    Element *current;
    struct node *left_child;
    struct node *right_child;
} node;

typedef node *BinaryTree;

BinaryTree empty();

BinaryTree makeRoot(BinaryTree left, Element *root, BinaryTree right, BinaryTree Parent);

Element *makeElement(int value);

int isEmpty(BinaryTree tree);

int hasLeft(BinaryTree tree);

int hasRight(BinaryTree tree);

int hasParent(BinaryTree tree);

int has(BinaryTree tree, Element element);

int areElementsEquals(Element element1, Element element2);

Element value(BinaryTree tree);

BinaryTree left(BinaryTree tree);

BinaryTree right(BinaryTree tree);

BinaryTree parent(BinaryTree tree);

int height(BinaryTree tree);

int count(BinaryTree tree);

int prefix(BinaryTree tree, Element *element, int nbr);

Element *infix(BinaryTree tree, Element *element, int nbr);

Element *postfix(BinaryTree tree, Element *element, int nbr);

void printPrefix(BinaryTree tree);

void printInfix(BinaryTree tree);

void printPostfix(BinaryTree tree);

#endif //LAB3_KESSLER47U_BINARYTREE_H
