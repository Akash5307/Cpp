#include <iostream>
#include <algorithm> // for max function
using namespace std;

// AVL Node Structure
struct AVLNode {
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k) : key(k), left(nullptr), right(nullptr), height(1) {}
};

// Function to get the height of a node
int height(AVLNode* node) {
    if (node == nullptr) return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int balanceFactor(AVLNode* node) {
    if (node == nullptr) return 0;
    return height(node->left) - height(node->right);
}

// Function to update the height of a node
void updateHeight(AVLNode* node) {
    if (node == nullptr) return;
    node->height = max(height(node->left), height(node->right)) + 1;
}

// Right Rotation
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    updateHeight(y);
    updateHeight(x);

    return x;
}

// Left Rotation
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    updateHeight(x);
    updateHeight(y);

    return y;
}

// Insert a key into the AVL Tree
AVLNode* insert(AVLNode* root, int key) {
    // Standard BST insertion
    if (root == nullptr) return new AVLNode(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        return root; // Duplicate keys are not allowed
    }

    // Update height of the current node
    updateHeight(root);

    // Get the balance factor to check if the node is unbalanced
    int balance = balanceFactor(root);

    // Perform rotations if the node is unbalanced
    // Left-Left (LL) Case
    if (balance > 1 && key < root->left->key) {
        return rightRotate(root);
    }
    // Right-Right (RR) Case
    if (balance < -1 && key > root->right->key) {
        return leftRotate(root);
    }
    // Left-Right (LR) Case
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right-Left (RL) Case
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Find the node with the minimum key in the tree
AVLNode* minValueNode(AVLNode* node) {
    AVLNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Delete a key from the AVL Tree
AVLNode* deleteNode(AVLNode* root, int key) {
    // Standard BST deletion
    if (root == nullptr) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        // Node with only one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            AVLNode* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else {
                // One child case
                *root = *temp; // Copy the contents of the non-empty child
            }
            delete temp;
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            AVLNode* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node, return
    if (root == nullptr) return root;

    // Update height of the current node
    updateHeight(root);

    // Get the balance factor to check if the node is unbalanced
    int balance = balanceFactor(root);

    // Perform rotations if the node is unbalanced
    // Left-Left (LL) Case
    if (balance > 1 && balanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }
    // Left-Right (LR) Case
    if (balance > 1 && balanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right-Right (RR) Case
    if (balance < -1 && balanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }
    // Right-Left (RL) Case
    if (balance < -1 && balanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Inorder traversal of the AVL Tree
void inorder(AVLNode* root) {
    if (root == nullptr) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

// Main function to test the AVL Tree
int main() {
    AVLNode* root = nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Inorder traversal of the AVL tree: ";
    inorder(root);
    cout << endl;

    root = deleteNode(root, 30);
    cout << "Inorder traversal after deleting 30: ";
    inorder(root);
    cout << endl;

    return 0;
}