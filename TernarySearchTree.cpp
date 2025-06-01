#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TernarySearchTree {
private:
    struct Node {
        char character;
        bool isEndOfString;
        string value; 
        Node* left;
        Node* mid;
        Node* right;

        Node(char ch)
            : character(ch), isEndOfString(false), left(nullptr), mid(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    Node* insert(Node* node, const string& word, int index, const string& value) {
        char ch = word[index];

        if (!node)
            node = new Node(ch);

        if (ch < node->character)
            node->left = insert(node->left, word, index, value);
        else if (ch > node->character)
            node->right = insert(node->right, word, index, value);
        else {
            if (index + 1 < word.size())
                node->mid = insert(node->mid, word, index + 1, value);
            else {
                node->isEndOfString = true;
                node->value = value;
            }
        }
        return node;
    }

    bool contains(Node* node, const string& word, int index) const {
        if (!node)
            return false;

        char ch = word[index];

        if (ch < node->character)
            return contains(node->left, word, index);
        else if (ch > node->character)
            return contains(node->right, word, index);
        else {
            if (index + 1 == word.size())
                return node->isEndOfString;
            return contains(node->mid, word, index + 1);
        }
    }

    void traverse(Node* node, string& prefix, vector<string>& results) const {
        if (!node) return;

        traverse(node->left, prefix, results);

        prefix.push_back(node->character);
        if (node->isEndOfString)
            results.push_back(prefix);
        traverse(node->mid, prefix, results);
        prefix.pop_back();

        traverse(node->right, prefix, results);
    }

public:
    void insert(const string& word, const string& value = "") {
        if (!word.empty())
            root = insert(root, word, 0, value);
    }

    bool contains(const string& word) const {
        if (word.empty()) return false;
        return contains(root, word, 0);
    }

    vector<string> allWords() const {
        vector<string> result;
        string prefix;
        traverse(root, prefix, result);
        return result;
    }
};

int main() {
    TernarySearchTree tst;

    tst.insert("cat", "value1");
    tst.insert("car", "value2");
    tst.insert("dog", "value3");
    tst.insert("door", "value4");

    cout << "Words in tree:" << endl;
    for (const string& word : tst.allWords())
        cout << word << endl;

    cout << "Contains 'car'? " << (tst.contains("car") ? "Yes" : "No") << endl;
    cout << "Contains 'cow'? " << (tst.contains("cow") ? "Yes" : "No") << endl;

    return 0;
}
