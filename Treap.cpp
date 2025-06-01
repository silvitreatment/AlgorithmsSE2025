#include <iostream>
#include <random>
#include <queue>
using namespace std;

mt19937 rng;

class Treap {
private:
    struct Node {
        int key;
        int priority;
        Node* left;
        Node* right;
        Node(int _key) : key(_key), priority(rng()), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;
    
    void split(Node* node, int key, Node*& left, Node*& right) {
        if (!node) {
            left = right = nullptr;
        } else if (key < node->key) {
            split(node->left, key, left, node->left);
            right = node;
        } else {
            split(node->right, key, node->right, right);
            left = node;
        }
    }
    
    Node *merge(Node* left, Node* right) {
        if (!left || !right) {
            return left ? left : right;
        } 
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            return left;
        } else {
            right->left = merge(right->left, left);
            return right;
        }
    }

    void insert(Node*& root, int key) {
        Node* newNode = new Node(key);
        Node* left;
        Node* right;
        split(root, key, left, right);
        root = merge(merge(left, newNode), right);
    }

    void erase(Node*& root, int key) {
        if (!root) {
            return;
        } 
        if (root->key == key) {
            Node* temp = merge(root->left, root->right);
            delete root;
            root = temp;
        } else if (key < root->key) {
            erase(root->left, key);
        } else {
            erase(root->right, key);
        }
    }

    void bfs(Node* root) {
        if (!root) {
            return;
        }
        queue<Node*> q;
        q.push(root);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            cout << current->key << " ";
            if (current->left) {
                q.push(current->left);
            } 
            if (current->right) {
                q.push(current->right);
            }
        }
    }
public: 
    void insert(int key) {
        insert(root, key);
    }

    void erase(int key) {
        erase(root, key);
    }
    
    void print() {
        bfs(root);
    }
};

int main() {
    Treap tree;

    tree.insert(5);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(3);

    tree.print();

    tree.erase(2);

    tree.print();

    return 0;
}


