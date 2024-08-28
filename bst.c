/*
William McClean
CS 260
Lab 6
10/27/2022
*/
#include "bst.h"


/*
	initBSTree: initialize BST members
	param1: tree
	pre: tree is not null
	post: sz is 0
	post: root is null
 */
void initBSTree(struct BSTree *tree) {
    assert(tree != NULL);
	tree->sz  = 0;
	tree->root = NULL;
}


/*
	isEmptyBSTree: function to determine if  a binary search tree is empty
	param: tree - the BST
    return: return 1 if the tree is empty, otherwise return 0
	pre: tree is not null
	post: no changes to the BST
 */
int isEmptyBSTree(struct BSTree *tree) {
    /* FIX ME */
    assert(tree != NULL);

    if(tree -> root -> left == NULL && tree -> root -> right == NULL) {
        return 1;
    }
    return 0;
}

/*
	sizeBSTree: function to determine the size of a binary search tree
	param: tree - the BST
	return: return the size of the tree
	pre: tree is not null
	post: no changes to the BST
*/
int sizeBSTree(struct BSTree *tree) {
    /* FIX ME */
    assert(tree != NULL);

    return tree -> sz;
}


/*
	freeBSTree: function to clear the nodes of a binary search tree
	param: tree a binary search tree
	pre: tree not null
	post: tree is freed
	function calls _freeNodes to free the nodes
 */
void freeBSTree(struct BSTree *tree) {
    assert(tree != NULL);

	_freeNodes(tree->root);
	tree->root = NULL;
	free(tree);
	tree = 0;
	printf("tree freed \n");
}

/*
	_freeBST: recursive helper function to free the nodes of a binary search tree
	param: node - the root node of the tree to be freed
	pre: none
	post: node and all descendants are freed
	called by freeBSTree()
*/
void _freeNodes(struct Node *node) {
	if(node == NULL) {
        return;
	}

    _freeNodes(node->left);
    _freeNodes(node->right);
    free(node);
}


/*
	leftMostValue: recursive helper function to find the left most child of a node
	param: curr - the current node
	return: the value of the left most child of curr
	pre: none
	post: no changes to the tree
	used in certain delete cases
*/
TYPE _leftMostValue(struct Node *curr) {
   if(curr->left == NULL) {
        return curr->val;
   }
   return _leftMostValue(curr->left);
}


/*
	addBSTree: function to add a value to the binary search tree
	param1: tree - the binary search tree
	param2: val	- the value to be added to the tree
	pre: tree is not null
	post: sz is incremented
    post: tree contains one new node
	_addNode handles the actual add
 */
void addBSTree(struct BSTree *tree, TYPE val) {
    assert(tree != NULL);

    tree->root = _addNode(tree->root, val);
    tree->sz++;
}


/*
	_addNode: recursive function to add a value to a BST
	param1: curr - the current node
	param2: val	- the value to be added to the tree
	pre: none
	return: curr - the root of a BST with a new leaf added
	post: memory is allocated for a new node
	post: new node contains specified value
	post new node left and right pointers are NULL
	post: a new node is added the the tree
	HINT: when curr is null create a new node, initialize it and return it
	HINT: set the left or right pointers of curr to the result of the recursive calls
*/
struct Node *_addNode(struct Node *curr, TYPE val) {
    /* FIX ME */

    if(curr == NULL) {
        struct Node *newNode = malloc(sizeof(struct Node));
        newNode -> val = val;
        newNode -> left = NULL;
        newNode -> right = NULL;
        return newNode;
    } else if(curr -> val > val) {
        curr -> left = _addNode(curr -> left, val);
    } else {
        curr -> right = _addNode(curr -> right, val);
    }
    return curr;
}

/*
	containsBSTree: function to determine if the binary search tree contains an element
	param1: tree the BST
	param2: val	- the value to search for in the tree
	return : return 1 if the tree contains the value, otherwise return 0
	pre: tree is not null
	post: no changes to the BST
	calls _contains
 */
int containsBSTree(struct BSTree *tree, TYPE val) {
    assert(tree != NULL);

	return _containsNode(tree->root, val);
}

/*
	_contains: recursive function checks for for the value in a binary search tree
	param1: curr - the current node
	param2: val	- the value to be removed from the tree
	ret: return 1 if found, otherwise return 0
	pre: none
	post: no changes to the BST
	HINT: follow the appropriate pointers until you find NULL or the value
*/
int _containsNode(struct Node *curr, TYPE val) {
    /* FIX ME */

    if(curr -> val == val) {
        return 1;
    } else if(curr -> val > val) {
        if(curr -> left == NULL) {
            return 0;
        }
        return _containsNode(curr -> left, val);
    } else {
        if(curr -> right == NULL) {
            return 0;
        }
        return _containsNode(curr -> right, val);
    }

}


/*
	removeBSTree: function to remove a value from the BST
	param1: tree - the BST
	param2: val	- the value to be removed from the tree
	pre: tree is not null
	pre: val is in the tree
	post: sz is decremented
	post: link is removed from the BST
	calls _removeNode
*/
void removeNodeFromTree(struct BSTree *tree, TYPE val) {
	assert(tree != NULL);
	assert(containsBSTree(tree, val));

    tree->root = _removeNode(tree->root, val);
    tree->sz--;
}

/*
	_removeNode: recursive helper function which removes a node from a BST
	param1: curr - the current node
	param1: val - the value to be removed from the tree
	pre: none
    post: link containing the value is freed
	post: node containing val is removed from the tree and subtrees are updated
	HINT: Use recursion to build a path from the root to the updated subtree - similar to addNode
	HINT: There are 4 cases: the node is a leaf, the node has only one (l or r) subtree, the node has two subtrees
	HINT: Use _leftMostValue() to get the value of the inorder successor when needed
	HINT: This is the most difficult function
 */
struct Node *_removeNode(struct Node *curr, TYPE val) {
	/* FIX ME */

    if(curr == NULL) {
        return curr;
    }

    if(curr -> val > val) {
        curr -> left = _removeNode(curr -> left, val);
    } else if(curr -> val < val) {
        curr -> right = _removeNode(curr -> right, val);
    } else {
        if(curr -> left == NULL && curr -> right == NULL) {
            free(curr);
            curr = 0;
            return NULL;
        } else if(curr -> left == NULL) {
            struct Node *newRight = curr -> right;
            free(curr);
            curr = 0;
            return newRight;
        } else if(curr -> right == NULL) {
            struct Node *newLeft = curr -> left;
            free(curr);
            curr = 0;
            return newLeft;
        }
        struct Node *successor = curr -> right;

        while(successor -> left != NULL) {

            successor = successor -> left;
        }
        curr -> val = successor -> val;
        curr -> right = _removeNode(curr -> right, successor -> val);
        return curr;
    }
	return curr;
}


/*
    inorderTraversal: inorder traversal of tree left-node-right
    param: curr - the current node
    pre: none
    post: in-order traversal s printed
*/
void inorderTraversal(struct Node *curr) {
    /* FIX ME */

    if(curr == NULL) {
        return;
    }
    inorderTraversal(curr -> left);
    printf("%.01f ", curr -> val);
    inorderTraversal(curr -> right);
}

/*
    preorderTraversal: inorder traversal of tree node-left-right
    param: curr - the current node
    pre: none
    post: pre-order traversal s printed
*/
void preorderTraversal(struct Node *curr) {
    /* FIX ME */

    if(curr == NULL) {
        return;
    }
    printf("%.01f ", curr -> val);
    preorderTraversal(curr -> left);
    preorderTraversal(curr -> right);
}

/*
    postorderTraversal: post-order traversal of tree left-right-node
    param: curr - the current node
    pre: none
    post: post-order traversal s printed
*/
void postorderTraversal(struct Node *curr) {
    /* FIX ME */

    if(curr == NULL) {
        return;
    }
    postorderTraversal(curr -> left);
    postorderTraversal(curr -> right);
    printf("%.01f ", curr -> val);
}
