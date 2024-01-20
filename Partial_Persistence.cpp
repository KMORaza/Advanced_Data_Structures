#include <iostream>
#include <vector>
using namespace std;
class PartiallyPersistentArray {
private:
    int n; 
    int versions; 
    vector<vector<int>> data; 
    vector<int> lastModified; 
public:
    PartiallyPersistentArray(int size, int numVersions) : n(size), versions(numVersions + 1) {
        data.resize(versions, vector<int>(n, 0));
        lastModified.resize(n, -1);
    }
    void update(int version, int index, int value) {
        if (version < 0 || version >= versions) {
            cout << "Invalid version" << endl;
            return;
        }
        data[version][index] = value;
        lastModified[index] = version;
    }
    int query(int version, int index) {
        if (version < 0 || version >= versions) {
            cout << "Invalid version" << endl;
            return -1; 
        }
        int result = 0;
        for (int i = lastModified[index]; i >= 0; --i) {
            result = data[i][index];
            if (i == version) {
                break;
            }
        }
        return result;
    }
};
int main() {
    int n = 5; 
    int numVersions = 3;
    PartiallyPersistentArray ppa(n, numVersions);
    ppa.update(0, 2, 5);
    ppa.update(0, 4, 8);
    ppa.update(1, 1, 3);
    ppa.update(1, 3, 7);
    cout << "Querying array at version 0:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << ppa.query(0, i) << " ";
    }
    cout << endl;
    cout << "Querying array at version 1:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << ppa.query(1, i) << " ";
    }
    cout << endl;
    cout << "Querying array at version 2:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << ppa.query(2, i) << " ";
    }
    cout << endl;
    return 0;
}
