#define SNOW_ENABLED

#include "../src/BinaryTree.h"
#include "../include/snow.h"

describe(test_BinaryTree_creation) {
    it("Initialization Empty Tree") {
        BinaryTree tree = empty();
        assert(isEmpty(tree) == 1, "Empty tree was not correctly created");
    }
    it("Initalization Tree") {
        BinaryTree leftTree = empty();
        assert(isEmpty(leftTree) == 1, "Empty tree was not correctly created");
        BinaryTree rightTree = empty();
        assert(isEmpty(rightTree) == 1, "Empty tree was not correctly created");
        Element *root = makeElement(8);
        assert(root->value == 8, "Making an element failed");
        BinaryTree tree = makeRoot(leftTree, root, rightTree, NULL);
        assert(isEmpty(tree) == 0, "Making a tree from subtrees and root failed");
        assert(hasParent(tree) == 0, "The parent was not correctly initialized for this tree");
        assert(hasLeft(tree) == 1, "The left child tree wasn't correctly created");
        assert(isEmpty(left(tree)) == 1, "The left child tree isn't empty");
        assert(hasRight(tree) == 1, "The right child tree wasn't correctly created");
        assert(isEmpty(right(tree)) == 1, "The right child tree isn't empty");
        Element element = value(tree);
        asserteq_buf(&element, root, sizeof(*root), "The root wasn't correctly copied");
        assert(hasParent(tree->right_child), "Right child tree didn't got the correct assignement of the parent");
        assert(hasParent(tree->left_child), "Left child tree didn't got the correct assignement of the parent");
        asserteq_ptr(parent(tree->left_child), tree, "Left child tree don't have the correct parent tree assigned");
        asserteq_ptr(parent(tree->right_child), tree, "Right child tree don't have the correct parent tree assigned");

    }
    it("Long Tree") {
        BinaryTree rightTree = makeRoot(empty(), makeElement(1), empty(), NULL);
        BinaryTree rightTree2 = makeRoot(rightTree, makeElement(2), empty(), NULL);
        BinaryTree rightTree3 = makeRoot(rightTree2, makeElement(3), empty(), NULL);
        BinaryTree rightTree4 = makeRoot(rightTree3, makeElement(4), empty(), NULL);
        BinaryTree rightTree5 = makeRoot(rightTree4, makeElement(5), empty(), NULL);
        BinaryTree rightTree6 = makeRoot(rightTree5, makeElement(6), empty(), NULL);
        BinaryTree rightTree7 = makeRoot(rightTree6, makeElement(7), empty(), NULL);
        BinaryTree rightTree8 = makeRoot(rightTree7, makeElement(8), empty(), NULL);
        assert(count(rightTree8) == 8, "The count is miscalculated");
        assert(height(rightTree8) == 8, "The height is miscalculated");
    }
    it("Full Tree") {
        BinaryTree rightRightTree = makeRoot(empty(), makeElement(1), empty(), NULL);
        BinaryTree rightLeftTree = makeRoot(empty(), makeElement(2), empty(), NULL);
        BinaryTree leftRightTree = makeRoot(empty(), makeElement(3), empty(), NULL);
        BinaryTree leftLeftTree = makeRoot(empty(), makeElement(4), empty(), NULL);
        BinaryTree rightTree = makeRoot(rightLeftTree, makeElement(5), rightRightTree, NULL);
        BinaryTree leftTree = makeRoot(leftLeftTree, makeElement(6), leftRightTree, NULL);
        BinaryTree tree = makeRoot(leftTree, makeElement(8), rightTree, NULL);
        assert(count(tree) == 7, "The count is miscalculated");
        assert(height(tree) == 3, "The height is miscalculated");
    }
    it("Prefix") {

        BinaryTree RLRR=makeRoot(empty(),makeElement(12),empty(),NULL);
        BinaryTree RLRL=makeRoot(empty(),makeElement(11),empty(),NULL);
        BinaryTree RRR=makeRoot(empty(),makeElement(15),empty(),NULL);
        BinaryTree RRL=makeRoot(empty(),makeElement(14),empty(),NULL);
        BinaryTree RLR=makeRoot(RLRL,makeElement(10),RLRR,NULL);
        BinaryTree LRRR=makeRoot(empty(),makeElement(7),empty(),NULL);
        BinaryTree LRR=makeRoot(empty(),makeElement(6),LRRR,NULL);
        BinaryTree LRL=makeRoot(empty(),makeElement(5),empty(),NULL);
        BinaryTree LLL=makeRoot(empty(),makeElement(3),empty(),NULL);
        BinaryTree RR = makeRoot(RRL, makeElement(13), RRR, NULL);
        BinaryTree RL = makeRoot(empty(), makeElement(9), RLR, NULL);
        BinaryTree LR = makeRoot(LRL, makeElement(4), LRR, NULL);
        BinaryTree LL = makeRoot(LLL, makeElement(2), empty(), NULL);
        BinaryTree R = makeRoot(RL, makeElement(8), RR, NULL);
        BinaryTree L = makeRoot(LL, makeElement(1), LR, NULL);
        BinaryTree tree = makeRoot(L, makeElement(0), R, NULL);
        assert(count(tree) == 16, "The count is miscalculated");
        assert(height(tree) == 5, "The height is miscalculated");
        defer(printf(" \n"));
        defer(printPrefix(tree));
        defer(printf(" \n"));
        defer(printInfix(tree));
        defer(printf(" \n"));
        defer(printPostfix(tree));
    }
    it("Pre"){
        BinaryTree RLRR=makeRoot(empty(),makeElement(12),empty(),NULL);
        BinaryTree RLRL=makeRoot(empty(),makeElement(11),empty(),NULL);
        BinaryTree RRR=makeRoot(empty(),makeElement(15),empty(),NULL);
        BinaryTree RRL=makeRoot(empty(),makeElement(14),empty(),NULL);
        BinaryTree RLR=makeRoot(RLRL,makeElement(10),RLRR,NULL);
        BinaryTree LRRR=makeRoot(empty(),makeElement(7),empty(),NULL);
        BinaryTree LRR=makeRoot(empty(),makeElement(6),LRRR,NULL);
        BinaryTree LRL=makeRoot(empty(),makeElement(5),empty(),NULL);
        BinaryTree LLL=makeRoot(empty(),makeElement(3),empty(),NULL);
        BinaryTree RR = makeRoot(RRL, makeElement(13), RRR, NULL);
        BinaryTree RL = makeRoot(empty(), makeElement(9), RLR, NULL);
        BinaryTree LR = makeRoot(LRL, makeElement(4), LRR, NULL);
        BinaryTree LL = makeRoot(LLL, makeElement(2), empty(), NULL);
        BinaryTree R = makeRoot(RL, makeElement(8), RR, NULL);
        BinaryTree L = makeRoot(LL, makeElement(1), LR, NULL);
        BinaryTree tree = makeRoot(L, makeElement(0), R, NULL);
        assert(prefix(tree,malloc(sizeof(Element)),1)==count(tree));
        Element *element=malloc(sizeof(Element));
        int count=prefix(tree,element,1);
        for (int i=0;i<count;i++){
            defer(printf("%d\n",element[i].value));
        }
    }
}

snow_main();
