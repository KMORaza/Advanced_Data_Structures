#include <iostream>
#include <string>
using namespace std;
const int prime = 31; 
const int mod = 1e9 + 9;  
int calculateHash(const string& str) {
    int hashValue = 0;
    int power = 1;
    for (char c : str) {
        hashValue = (hashValue + (c - 'a' + 1) * power) % mod;
        power = (power * prime) % mod;
    }
    return hashValue;
}
int main() {
    string text, pattern;
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern to search: ";
    getline(cin, pattern);
    int patternHash = calculateHash(pattern);
    size_t n = text.length();
    size_t m = pattern.length();
    if (n < m) {
        cout << "Pattern not found in the text." << endl;
        return 0;
    }
    int windowHash = calculateHash(text.substr(0, m));
    for (size_t i = 0; i <= n - m; ++i) {
        if (windowHash == patternHash && text.substr(i, m) == pattern) {
            cout << "Pattern found at index " << i << endl;
        }
        if (i + m < n) {
            windowHash = (windowHash - (text[i] - 'a' + 1) + mod) % mod;
            windowHash = (windowHash * prime) % mod;
            windowHash = (windowHash + (text[i + m] - 'a' + 1)) % mod;
        }
    }
    return 0;
}
