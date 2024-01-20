#include <iostream>
#include <cmath>
long long cayleyTreeEnumeration(int n) {
    return static_cast<long long>(pow(n, n - 2));
}
int main() {
    int n;
    std::cout << "Enter the number of vertices: ";
    std::cin >> n;
    if (n < 1) {
        std::cerr << "Number of vertices should be at least 1." << std::endl;
        return 1;
    }
    long long result = cayleyTreeEnumeration(n);
    std::cout << "Number of labeled trees with " << n << " vertices: " << result << std::endl;
    return 0;
}
