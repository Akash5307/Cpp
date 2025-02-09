#include <iostream>
#include <queue>
#include <map>
using namespace std;

struct AVL{
    AVL* left;
    AVL* right;
    int val;
    int height;
    AVL(int val){
        this->val=val;
        left=nullptr;right=nullptr;
        height=1;
    }
    ~AVL(){
        delete left;delete right;
    };
};
int height(AVL* node) {
    return node ? node->height : 0;
}
int balanceFactor(AVL* node){
    if(node)return height(node->left)-height(node->right);
    return 0;
}
void updateHeight(AVL* node) {
    node->height = 1 + max(height(node->left), height(node->right));
}
AVL* rotateRight(AVL* y) {
    AVL* x = y->left;
    AVL* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}
AVL* rotateLeft(AVL* x) {
    AVL* y = x->right;
    AVL* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}
AVL* balance(AVL* node) {
    if (!node) return nullptr;
    updateHeight(node);
    int bf = balanceFactor(node);
    if (bf > 1) {
        if (balanceFactor(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (bf < -1) {
        if (balanceFactor(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

void insert(AVL** root, int val) {
    if (!*root) {
        *root = new AVL(val);
        return;
    }
    if (val < (*root)->val)
        insert(&(*root)->left, val);
    else
        insert(&(*root)->right, val);
    *root = balance(*root);
}
AVL* findMin(AVL* node) {
    while (node->left) node = node->left;
    return node;
}

AVL* deleteNode(AVL* root, int val) {
    if (!root) return nullptr;
    if (val < root->val)
        root->left = deleteNode(root->left, val);
    else if (val > root->val)
        root->right = deleteNode(root->right, val);
    else {
        if (!root->left || !root->right) {
            AVL* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = nullptr;
            } else {
                *root = *temp;
            }
            delete temp;
        } else {
            AVL* temp = findMin(root->right);
            root->val = temp->val;
            root->right = deleteNode(root->right, temp->val);
        }
    }
    return balance(root);
}

void inorder(AVL* root) {
    if (root) {
        inorder(root->left);
        cout << root->val << " ";
        inorder(root->right);
    }
}

map<int,vector<int>>g;
void print(AVL* root){
    if(!root)return;
    queue<AVL*>q;
    q.push(root);
    while(!q.empty()){
        int sz=q.size();
        while(sz--){
            auto node=q.front();
            q.pop();
            if(node->left){
                q.push(node->left);
                g[node->val].push_back(node->left->val);
            }
            if(node->right){
                g[node->val].push_back(node->right->val);
                q.push(node->right);
            }
        }
    }
}
int main() {
    AVL* root = nullptr;
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 50);
    insert(&root, 25);

    cout << "In-order traversal: ";
    inorder(root); // 10 20 25 30 40 50
    cout << "\n";

    print(root);
    root = deleteNode(root, 30);

    cout << "After deletion: ";
    inorder(root); // 10 20 25 40 50
    cout << "\n";

    delete root;
    return 0;
}

