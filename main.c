#include "bst.h"

#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

/*
	printTestResult: function to print the result of a test function
	param1: predicate - the result of the test
	param2: nameTestFunction - name of the function being tested
	param3: message - message passed to the test function
	post: result is printed to standard output
*/
void printTestResult(int predicate, char *message) {
	if (predicate) {
	   printf("%s: PASS\n", message);
    } else {
	   printf("%s: FAIL\n", message);
	}
}


/* Main function for testing different functions of the assignment */
int main() {
    struct BSTree *tree = malloc(sizeof(struct BSTree));
    initBSTree(tree);

    printf("------------------Testing addBSTree------------------\n");

    addBSTree(tree, 55);
    printTestResult((tree->root->val == 55) && (tree->sz == 1), "addBSTree(55)");
    printTestResult((tree->sz == 1), "tree->sz == 1");

    addBSTree(tree, 36);
    printTestResult((tree->root->left->val == 36), "addBSTree(36)");
    printTestResult((sizeBSTree(tree) == 2), "sizeBSTree() == 2");

    addBSTree(tree, 78);
    printTestResult((tree->root->right->val == 78), "addBSTree(78)");

	addBSTree(tree, 20);
	printTestResult((tree->root->left->left->val == 20), "addBSTree(20)");

	addBSTree(tree, 85);
	printTestResult((tree->root->right->right->val == 85), "addBSTree(85)");

	addBSTree(tree, 49);
	printTestResult((tree->root->left->right->val == 49), "addBSTree(49)");

	addBSTree(tree, 67);
    printTestResult((tree->root->right->left->val == 67), "addBSTree(67)");
    printTestResult((sizeBSTree(tree) == 7), "sizeBSTree() == 7");

    printf("------------------testing containsBST-------------------\n");

    printTestResult(containsBSTree(tree, 55), "containsBSTree(55)");
    printTestResult(containsBSTree(tree, 36), "containsBSTree(36)");
    printTestResult(containsBSTree(tree, 20), "containsBSTree(20)");
    printTestResult(containsBSTree(tree, 85), "containsBSTree(85)");
    printTestResult(!containsBSTree(tree, 88), "containsBSTree(88)");
    printTestResult(!containsBSTree(tree, 1), "containsBSTree(1)");


    printf("------------------testing testLeftMostValue-------------------\n");

	printTestResult(_leftMostValue(tree->root) == 20, "_leftMostValue(root)");
	printTestResult(_leftMostValue(tree->root->left) == 20, "_leftMostValue(root->left)");
	printTestResult(_leftMostValue(tree->root->right) == 67, "_leftMostValue(root->right)");


    printf("------------------testing removeNode-------------------\n");

    removeNodeFromTree(tree, 20);
    printTestResult((tree->root->val == 55) && (!containsBSTree(tree, 20)), "removeNodeFromTree(20)");

    removeNodeFromTree(tree, 67);
    printTestResult((tree->root->val == 55)  && (!containsBSTree(tree, 67)), "removeNodeFromTree(67)");

    removeNodeFromTree(tree, 55);
    printTestResult((tree->root->val == 78) && (!containsBSTree(tree, 55)), "removeNodeFromTree(55)");

    printf("\n------------printing in-order traversal------------ \n");
    inorderTraversal(tree->root);

    printf("\n------------printing pre-order traversal------------ \n");
    preorderTraversal(tree->root);

    printf("\n------------printing post-order traversal------------ \n");
    postorderTraversal(tree->root);
    printf("\n");

    freeBSTree(tree);

	return 0;
}

