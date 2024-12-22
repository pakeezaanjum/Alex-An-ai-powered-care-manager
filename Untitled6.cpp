struct AVLNode {
    int key;
    string category;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int k, string cat) : key(k), category(cat), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
private:
    AVLNode* root;

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int getBalance(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T = x->right;
        x->right = y;
        y->left = T;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T = y->left;
        y->left = x;
        x->right = T;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    AVLNode* insert(AVLNode* node, int key, string category) {
        if (!node) return new AVLNode(key, category);

        if (key < node->key)
            node->left = insert(node->left, key, category);
        else if (key > node->key)
            node->right = insert(node->right, key, category);
        else
            return node;

        node->height = 1 + max(height(node
