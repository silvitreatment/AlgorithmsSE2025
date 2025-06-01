#include <iostream>
#include <queue>
using namespace std;

class AVLTree {
private: 
    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;

        Node(int _key) : key(_key), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    int height(Node* n) {
        return n != nullptr ? n->height : 0; 
    }

    int getBalanceFactor(Node* n) {
        if (n != nullptr) {
            return height(n->left) - height(n->right); 
        } else {
            return 0;
        }
    }

    Node* rotateLeft(Node* node) {
        Node* right_children = node->right;
        Node* left_children_of_right_node = right_children->left;
        right_children->left = node;
        node->right = left_children_of_right_node;
        node->height = max(height(node->left), height(node->right)) + 1;
        right_children->height = max(height(right_children->left), height(right_children->right)) + 1;
        return right_children;
    }

    Node* rotateRight(Node* node) {
        Node* left_children = node->left;
        Node* right_children_of_left_node = left_children->right;
        left_children->right = node;
        node->left = right_children_of_left_node;
        node->height = max(height(node->left), height(node->right)) + 1;
        left_children->height = max(height(left_children->left), height(left_children->right)) + 1;
        return left_children;
    }

    Node* insert(Node* node, int key) {
        if (!node) {
            return new Node(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = getBalanceFactor(node);

        if (balance >= 2 && key < node->left->key) {
            return rotateRight(node);
        }
        if (balance <= -2 && key > node->right->key) {
            return rotateLeft(node);
        }
        if (balance >= 2 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance <= -2 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    Node* erase(Node* node, int key) {
        if (!node) {
            return node;
        }

        if (key < node->key) {
            node->left = erase(node->left, key);
        } else if (key > node->key) {
            node->right = erase(node->right, key);
        } else {
            if (!node->right || !node->left) {
                Node* temp = node->left ? node->left : node->right;
                if (!temp) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node* temp = findMin(node->right);
                node->key = temp->key;
                node->right = erase(node->right, temp->key);
            }
        }
        
        if (!node) {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalanceFactor(node);

        if (balance >= 2 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }
        if (balance <= -2 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }
        if (balance <= -2 && getBalanceFactor(node->right) >= 1) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        if (balance >= 2 && getBalanceFactor(node->left) <= -1) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        return node;
    }
    Node* findMin(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    bool find(Node* node, int key) {
        if (!node) {
            return false;
        }
        if (key < node->key) {
            return find(node->left, key);
        } else if (key > node->key) {
            return find(node->right, key);
        } else {
            return true;
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
        root = insert(root, key);
    }
    
    void erase(int key) {
        root = erase(root, key);
    }
    bool find(int key) {
        return find(root, key);
    }
    void print() {
        return bfs(root);
    }
};

int main() {

    AVLTree tree;
    for (int i = 10; i <= 100; i += 10) {
        tree.insert(i);
    }
    tree.erase(30);
    cout << "find 30: " << (tree.find(30) ? "yes" : "no") << endl;

    tree.insert(30);
    cout << "find 30: " << (tree.find(30) ? "yes" : "no") << endl;

    tree.print();

    return 0;
}