// Multiple string matching using Aho-Corasixk algortihm
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;
class AhoCorasick {
private:
    struct TrieNode {
        unordered_map<char, TrieNode*> children;
        TrieNode* fail;
        vector<int> output;
        TrieNode() : fail(nullptr) {}
    };
    TrieNode* root;
    vector<int> patternLengths; 
public:
    AhoCorasick() {
        root = new TrieNode();
    }
    void insert(const string& pattern, int patternIndex) {
        TrieNode* node = root;
        for (char ch : pattern) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->output.push_back(patternIndex);
        patternLengths.push_back(pattern.length());
    }
    void buildFailureLinks() {
        queue<TrieNode*> q;
        for (auto& pair : root->children) {
            pair.second->fail = root;
            q.push(pair.second);
        }
        while (!q.empty()) {
            TrieNode* current = q.front();
            q.pop();
            for (auto& pair : current->children) {
                char ch = pair.first;
                TrieNode* child = pair.second;
                q.push(child);
                TrieNode* failLink = current->fail;
                while (failLink != nullptr && failLink->children.find(ch) == failLink->children.end()) {
                    failLink = failLink->fail;
                }
                child->fail = (failLink != nullptr) ? failLink->children[ch] : root;
                child->output.insert(child->output.end(), child->fail->output.begin(), child->fail->output.end());
            }
        }
    }
    vector<int> search(const string& text) {
        vector<int> result;
        TrieNode* currentState = root;
        for (int i = 0; i < text.length(); ++i) {
            char ch = text[i];
            while (currentState != nullptr && currentState->children.find(ch) == currentState->children.end()) {
                currentState = currentState->fail;
            }
            if (currentState == nullptr) {
                currentState = root;
            } else {
                currentState = currentState->children[ch];
                for (int index : currentState->output) {
                    result.push_back(i - patternLengths[index] + 1);
                }
            }
        }
        return result;
    }
};
int main() {
    AhoCorasick ac;
    int numPatterns;
    cout << "Enter the number of patterns: ";
    cin >> numPatterns;
    vector<string> patterns(numPatterns);
    for (int i = 0; i < numPatterns; ++i) {
        cout << "Enter pattern " << i + 1 << ": ";
        cin >> patterns[i];
        ac.insert(patterns[i], i);
    }
    ac.buildFailureLinks();
    string text;
    cout << "Enter the text: ";
    cin >> text;
    vector<int> matches = ac.search(text);
    cout << "Pattern matches found at positions: ";
    for (int match : matches) {
        cout << match << " ";
    }
    cout << endl;
    return 0;
}
