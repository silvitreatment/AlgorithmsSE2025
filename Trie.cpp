#include <iostream>
#include <map>
using namespace std;



class Trie {
private:
    struct TrieNode {
        map<char, TrieNode*> children;
        bool isEndOfWord;

        TrieNode() {
            isEndOfWord = false;
        }
    };

    TrieNode* root;

    void _clear(TrieNode* node) {
        for (auto& pair : node->children) {
            clear(pair.second);
        }
        delete node;
    }

    void _insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch)) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    bool _find(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (!node->children.count(ch)) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }

    bool _start(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (!node->children.count(ch)) {
                return false;
            }
            node = node->children[ch];
        }
        return true;
    }

public:

    bool start(const string& prefix) {
        return _start(prefix);
    }

    bool find(const string& prefix) {
        return _find(prefix);
    }
    Trie() {
        root = new TrieNode();
    }
    void insert(const string& word) {
        _insert(word);
    }

    void clear(TrieNode* node) {
        _clear(node);
    }

    ~Trie() {
        _clear(root);
    }

    
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");

    cout << boolalpha;
    cout << trie.find("apple") << endl;  
    cout << trie.find("app") << endl;      
    cout << trie.find("appl") << endl;      
    cout << trie.start("appl") << endl;  
    cout << trie.start("banana") << endl;

    return 0;
}
