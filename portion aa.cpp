#include <iostream>
#include <vector>
#include <string>
using namespace std;

// AVL Tree Node structure
struct AVLNode {
    string date;
    int taskCompletionScore;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(string d, int score) : date(d), taskCompletionScore(score), left(nullptr), right(nullptr), height(1) {}
};

// Function to get the height of a node
int height(AVLNode* node) {
    return node ? node->height : 0;
}

// Function to perform a right rotation
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right) + 1);
    x->height = max(height(x->left), height(x->right) + 1);

    return x;
}

// Function to perform a left rotation
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right) + 1);
    y->height = max(height(y->left), height(y->right) + 1);

    return y;
}

// Function to get the balance factor of a node
int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Function to insert a node into the AVL tree and balance it
AVLNode* insert(AVLNode* node, string date, int score) {
    if (!node)
        return new AVLNode(date, score);

    if (date < node->date)
        node->left = insert(node->left, date, score);
    else if (date > node->date)
        node->right = insert(node->right, date, score);
    else
        return node;  // Duplicate dates not allowed

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Balancing the tree if needed
    if (balance > 1 && date < node->left->date)
        return rightRotate(node);

    if (balance < -1 && date > node->right->date)
        return leftRotate(node);

    if (balance > 1 && date > node->left->date) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && date < node->right->date) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to do an in-order traversal of the AVL tree and store the data in an array
void inOrder(AVLNode* node, vector<pair<string, int>>& data) {
    if (node) {
        inOrder(node->left, data);
        data.push_back({node->date, node->taskCompletionScore});
        inOrder(node->right, data);
    }
}

// Bubble sort function to sort the task completion data by score
void bubbleSort(vector<pair<string, int>>& data) {
    int n = data.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (data[j].second < data[j + 1].second) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

// HighScore function that balances the AVL tree, sorts the data, and prints the results
void HighScore() {
    // Sample task completion data (date, score)
    vector<pair<string, int>> taskData = {{"2024-12-20", 5}, {"2024-12-21", 8}, {"2024-12-22", 10}};
    
    AVLNode* root = nullptr;
    
    // Inserting the task completion data into the AVL tree
    for (auto& task : taskData) {
        root = insert(root, task.first, task.second);
    }

    // In-order traversal to get sorted data from AVL tree
    vector<pair<string, int>> sortedData;
    inOrder(root, sortedData);

    // Apply bubble sort to order by task completion score
    bubbleSort(sortedData);

    // Print sorted task completion data
    cout << "Alex: Here are the sorted task completion scores:" << endl;
    for (auto& task : sortedData) {
        cout << "Date: " << task.first << ", Task Completion Score: " << task.second << endl;
    }

    // Example output to find the high score day
    cout << "Alex: The highest task completion score was " << sortedData.front().second
         << " on " << sortedData.front().first << "!" << endl;
}

int main() {
    // Calling HighScore function
    HighScore();
    
    return 0;
}
