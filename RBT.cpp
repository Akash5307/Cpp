/*
A Red-Black Tree is a BST with the following additional properties:

    Node Color: Each node is either red or black.

    Root Property: The root is always black.

    Leaf Property: All leaves (null pointers) are considered black.

    Red Property: If a red node has children, the children are always black (no two red nodes can be adjacent).

    Depth Property: Every path from a node to its descendant null pointers has the same number of black nodes (this ensures balance).
*/ 

#include <iostream>
using namespace std;

// Enum to represent the color of a node (RED or BLACK)
enum Color { RED, BLACK };

// Red-Black Tree Node Structure
struct RBNode {
    int key;         // Key value stored in the node
    RBNode* left;    // Pointer to the left child
    RBNode* right;   // Pointer to the right child
    RBNode* parent;  // Pointer to the parent node
    Color color;     // Color of the node (RED or BLACK)

    // Constructor to initialize a node with a key
    RBNode(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

// Red-Black Tree Class
class RBTree {
private:
    RBNode* root; // Pointer to the root of the tree
    RBNode* nil;  // Sentinel node to represent null pointers (leaves)

    // Helper functions
    void leftRotate(RBNode* x);       // Perform a left rotation around node x
    void rightRotate(RBNode* y);      // Perform a right rotation around node y
    void insertFixup(RBNode* z);      // Fix the tree after insertion to maintain Red-Black properties
    void deleteFixup(RBNode* x);      // Fix the tree after deletion to maintain Red-Black properties
    void transplant(RBNode* u, RBNode* v); // Replace subtree rooted at u with subtree rooted at v
    RBNode* minimum(RBNode* node);    // Find the node with the minimum key in the subtree rooted at node
    void inorderHelper(RBNode* node); // Helper function for inorder traversal

public:
    // Constructor to initialize the Red-Black Tree
    RBTree() {
        nil = new RBNode(-1);  // Sentinel node is initialized with key -1
        nil->color = BLACK;    // Sentinel node is always black
        root = nil;            // Initially, the tree is empty, so root points to nil
    }

    // Public functions
    void insert(int key);      // Insert a key into the tree
    void deleteNode(int key);  // Delete a key from the tree
    void inorder();            // Perform an inorder traversal of the tree
};

// Left Rotation: Rotate the subtree rooted at node x to the left
void RBTree::leftRotate(RBNode* x) {
    RBNode* y = x->right;  // y is the right child of x
    x->right = y->left;    // Turn y's left subtree into x's right subtree

    if (y->left != nil) {
        y->left->parent = x;  // If y's left child is not nil, set its parent to x
    }

    y->parent = x->parent;  // Set y's parent to x's parent

    if (x->parent == nil) {
        root = y;  // If x was the root, set y as the new root
    } else if (x == x->parent->left) {
        x->parent->left = y;  // If x was a left child, set y as the left child of x's parent
    } else {
        x->parent->right = y; // If x was a right child, set y as the right child of x's parent
    }

    y->left = x;  // Set x as y's left child
    x->parent = y; // Set y as x's parent
}

// Right Rotation: Rotate the subtree rooted at node y to the right
void RBTree::rightRotate(RBNode* y) {
    RBNode* x = y->left;   // x is the left child of y
    y->left = x->right;    // Turn x's right subtree into y's left subtree

    if (x->right != nil) {
        x->right->parent = y;  // If x's right child is not nil, set its parent to y
    }

    x->parent = y->parent;  // Set x's parent to y's parent

    if (y->parent == nil) {
        root = x;  // If y was the root, set x as the new root
    } else if (y == y->parent->right) {
        y->parent->right = x;  // If y was a right child, set x as the right child of y's parent
    } else {
        y->parent->left = x;   // If y was a left child, set x as the left child of y's parent
    }

    x->right = y;  // Set y as x's right child
    y->parent = x; // Set x as y's parent
}

// Fix Red-Black Tree properties after insertion
void RBTree::insertFixup(RBNode* z) {
    while (z->parent->color == RED) {  // Continue fixing until z's parent is no longer red
        if (z->parent == z->parent->parent->left) {  // If z's parent is a left child
            RBNode* y = z->parent->parent->right;  // y is z's uncle

            if (y->color == RED) {
                // Case 1: Recolor (z's parent and uncle are red)
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;  // Move z up the tree
            } else {
                if (z == z->parent->right) {
                    // Case 2: Left Rotation (z is a right child)
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3: Recolor and Right Rotation (z is a left child)
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {  // If z's parent is a right child
            RBNode* y = z->parent->parent->left;  // y is z's uncle

            if (y->color == RED) {
                // Case 1: Recolor (z's parent and uncle are red)
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;  // Move z up the tree
            } else {
                if (z == z->parent->left) {
                    // Case 2: Right Rotation (z is a left child)
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3: Recolor and Left Rotation (z is a right child)
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;  // Ensure the root is always black
}

// Insert a key into the Red-Black Tree
void RBTree::insert(int key) {
    RBNode* z = new RBNode(key);  // Create a new node with the given key
    RBNode* y = nil;              // y will be the parent of z
    RBNode* x = root;             // Start at the root

    // Traverse the tree to find the correct position for z
    while (x != nil) {
        y = x;
        if (z->key < x->key) {
            x = x->left;
        } else {
            x = x->right;
        }
    }

    z->parent = y;  // Set y as z's parent

    if (y == nil) {
        root = z;  // If the tree was empty, set z as the root
    } else if (z->key < y->key) {
        y->left = z;  // If z's key is less than y's key, set z as y's left child
    } else {
        y->right = z; // Otherwise, set z as y's right child
    }

    z->left = nil;   // Set z's left child to nil
    z->right = nil;  // Set z's right child to nil
    z->color = RED;  // New nodes are always red

    insertFixup(z);  // Fix the tree to maintain Red-Black properties
}

// Fix Red-Black Tree properties after deletion
void RBTree::deleteFixup(RBNode* x) {
    while (x != root && x->color == BLACK) {  // Continue fixing until x is the root or x is red
        if (x == x->parent->left) {  // If x is a left child
            RBNode* w = x->parent->right;  // w is x's sibling

            if (w->color == RED) {
                // Case 1: Recolor and Left Rotation (w is red)
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                // Case 2: Recolor (w's children are black)
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    // Case 3: Recolor and Right Rotation (w's right child is black)
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // Case 4: Recolor and Left Rotation (w's right child is red)
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {  // If x is a right child
            RBNode* w = x->parent->left;  // w is x's sibling

            if (w->color == RED) {
                // Case 1: Recolor and Right Rotation (w is red)
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                // Case 2: Recolor (w's children are black)
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    // Case 3: Recolor and Left Rotation (w's left child is black)
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                // Case 4: Recolor and Right Rotation (w's left child is red)
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;  // Ensure x is black
}

// Transplant a subtree rooted at u with a subtree rooted at v
void RBTree::transplant(RBNode* u, RBNode* v) {
    if (u->parent == nil) {
        root = v;  // If u was the root, set v as the new root
    } else if (u == u->parent->left) {
        u->parent->left = v;  // If u was a left child, set v as the left child of u's parent
    } else {
        u->parent->right = v; // If u was a right child, set v as the right child of u's parent
    }
    v->parent = u->parent;  // Set v's parent to u's parent
}

// Delete a key from the Red-Black Tree
void RBTree::deleteNode(int key) {
    RBNode* z = root;
    // Traverse the tree to find the node with the given key
    while (z != nil) {
        if (key == z->key) {
            break;
        } else if (key < z->key) {
            z = z->left;
        } else {
            z = z->right;
        }
    }

    if (z == nil) return; // Key not found, nothing to delete

    RBNode* y = z;  // y will be the node to delete
    RBNode* x;      // x will be the node that replaces y
    Color yOriginalColor = y->color;  // Save the original color of y

    if (z->left == nil) {
        // If z has no left child, replace z with its right child
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        // If z has no right child, replace z with its left child
        x = z->left;
        transplant(z, z->left);
    } else {
        // If z has two children, find the minimum node in the right subtree
        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;  // Delete the node

    if (yOriginalColor == BLACK) {
        // If the original color of y was black, fix the tree
        deleteFixup(x);
    }
}

// Find the node with the minimum key in the subtree rooted at node
RBNode* RBTree::minimum(RBNode* node) {
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}

// Inorder traversal of the Red-Black Tree (left, root, right)
void RBTree::inorderHelper(RBNode* node) {
    if (node == nil) return;
    inorderHelper(node->left);
    cout << node->key << " ";
    inorderHelper(node->right);
}

// Perform an inorder traversal of the tree
void RBTree::inorder() {
    inorderHelper(root);
    cout << endl;
}

// Main function to test the Red-Black Tree
int main() {
    RBTree tree;

    // Insert some keys into the tree
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);

    // Print the inorder traversal of the tree
    cout << "Inorder traversal of the Red-Black Tree: ";
    tree.inorder();

    // Delete a key from the tree
    tree.deleteNode(20);
    cout << "Inorder traversal after deleting 20: ";
    tree.inorder();

    return 0;
}