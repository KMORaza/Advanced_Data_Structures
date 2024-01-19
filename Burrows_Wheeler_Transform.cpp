#include <iostream>
#include <vector>
#include <algorithm>
struct Rotation {
    std::string rotation;
    int index;
    Rotation(const std::string& s, int i) : rotation(s), index(i) {}
};
std::string burrowsWheelerTransform(const std::string& input) {
    std::vector<Rotation> rotations;
    for (int i = 0; i < input.length(); ++i) {
        std::string rotation = input.substr(i) + input.substr(0, i);
        rotations.emplace_back(rotation, i);
    }
    std::sort(rotations.begin(), rotations.end(), [](const Rotation& a, const Rotation& b) {
        return a.rotation < b.rotation;
    });
    std::string result;
    for (const Rotation& rotation : rotations) {
        result += rotation.rotation.back();
    }
    return result;
}
int main() {
    std::string input;
    std::cout << "Enter a string: ";
    std::cin >> input;
    input += '$';
    std::string bwtResult = burrowsWheelerTransform(input);
    std::cout << "BWT Output: " << bwtResult << std::endl;
    return 0;
}
