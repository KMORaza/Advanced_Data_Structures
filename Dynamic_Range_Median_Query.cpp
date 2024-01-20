// Dynamic Range Median Query using Fenwick tree
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class FenwickTree {
private:
    vector<int> BIT;
public:
    FenwickTree(int size) : BIT(size + 1, 0) {}
    void update(int index, int delta) {
        for (; index < BIT.size(); index += index & -index) {
            BIT[index] += delta;
        }
    }
    int query(int index) {
        int sum = 0;
        for (; index > 0; index -= index & -index) {
            sum += BIT[index];
        }
        return sum;
    }
};
class DynamicRangeMedian {
private:
    FenwickTree fenwickTree;
    vector<int> elements;
public:
    DynamicRangeMedian(const vector<int>& arr) : fenwickTree(arr.size()), elements(arr) {
        for (int i = 1; i <= arr.size(); ++i) {
            fenwickTree.update(i, 1);
        }
        sort(elements.begin(), elements.end());
    }
    void update(int index, int newValue) {
        int oldValue = elements[index];
        elements[index] = newValue;
        fenwickTree.update(index + 1, 1);
        fenwickTree.update(lower_bound(elements.begin(), elements.end(), oldValue) - elements.begin() + 1, -1);
    }
    int query(int left, int right) {
        int total = right - left + 1;
        int medianIndex = (total + 1) / 2;
        int low = 1, high = elements.size();
        while (low < high) {
            int mid = (low + high) / 2;
            int count = fenwickTree.query(mid);
            if (count < medianIndex) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }
        return elements[low - 1];
    }
};
int main() {
    vector<int> initialArray = {5, 2, 7, 1, 9, 3};
    DynamicRangeMedian drm(initialArray);
    cout << "Initial array: ";
    for (int num : initialArray) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Median in the range [1, 4]: " << drm.query(0, 3) << endl;
    drm.update(2, 10); 
    cout << "Array after update: ";
    for (int num : initialArray) {
        cout << num << " ";
    }
    cout << endl;
    cout << "Median in the range [1, 4] after update: " << drm.query(0, 3) << endl;
    return 0;
}
