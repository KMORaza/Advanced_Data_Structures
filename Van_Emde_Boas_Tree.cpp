#include <iostream>
#include <cmath>
#include <vector>
class VanEmdeBoasTree {
private:
    size_t universeSize;
    size_t min, max;
    VanEmdeBoasTree* summary;
    std::vector<VanEmdeBoasTree*> cluster;
public:
    VanEmdeBoasTree(size_t u) : universeSize(u) {
        if (u > 2) {
            size_t highSize = upperSquareRoot(u);
            size_t lowSize = lowerSquareRoot(u);
            summary = new VanEmdeBoasTree(highSize);
            cluster.resize(highSize);
            for (size_t i = 0; i < highSize; ++i) {
                cluster[i] = new VanEmdeBoasTree(lowSize);
            }
        } else {
            min = max = 0;
            summary = nullptr;
            cluster.clear();
        }
    }
    ~VanEmdeBoasTree() {
        delete summary;
        for (VanEmdeBoasTree* c : cluster) {
            delete c;
        }
    }
    size_t getUniverseSize() const {
        return universeSize;
    }
    void insert(size_t x) {
        if (universeSize == 2) {
            if (min == max) {
                min = max = x;
            } else if (x == 0) {
                min = 0;
            } else {
                max = 1;
            }
        } else {
            size_t highSize = highValue(x);
            size_t lowSize = lowValue(x);
            if (cluster[highSize]->getMin() == universeSize) {
                summary->insert(highSize);
                cluster[highSize]->insert(lowSize);
            } else {
                cluster[highSize]->insert(lowSize);
            }
            updateMinMax();
        }
    }
    void remove(size_t x) {
        if (universeSize == 2) {
            if (x == 0 && min == 0) {
                min = 1;
            } else if (x == 1 && max == 1) {
                max = 0;
            }
        } else {
            size_t highSize = highValue(x);
            size_t lowSize = lowValue(x);

            cluster[highSize]->remove(lowSize);
            if (cluster[highSize]->getMin() == cluster[highSize]->getMax()) {
                summary->remove(highSize);
            }
            updateMinMax();
        }
    }
    bool contains(size_t x) const {
        if (universeSize == 2) {
            return (x == min || x == max);
        } else {
            size_t highSize = highValue(x);
            size_t lowSize = lowValue(x);

            return cluster[highSize]->contains(lowSize);
        }
    }
    size_t getMin() const {
        return min;
    }
    size_t getMax() const {
        return max;
    }
    size_t successor(size_t x) const {
        if (universeSize == 2) {
            if (x == 0 && max == 1) {
                return 1;
            } else {
                return universeSize;
            }
        } else {
            size_t highSize = highValue(x);
            size_t lowSize = lowValue(x);

            if (lowSize < cluster[highSize]->getMax()) {
                size_t offset = cluster[highSize]->successor(lowSize);
                return indexedValue(highSize, offset);
            } else {
                size_t succCluster = summary->successor(highSize);
                if (succCluster == universeSize) {
                    return universeSize;
                } else {
                    size_t offset = cluster[succCluster]->getMin();
                    return indexedValue(succCluster, offset);
                }
            }
        }
    }
    size_t predecessor(size_t x) const {
        if (universeSize == 2) {
            if (x == 1 && min == 0) {
                return 0;
            } else {
                return universeSize;
            }
        } else {
            size_t highSize = highValue(x);
            size_t lowSize = lowValue(x);
            if (lowSize > cluster[highSize]->getMin()) {
                size_t offset = cluster[highSize]->predecessor(lowSize);
                return indexedValue(highSize, offset);
            } else {
                size_t predCluster = summary->predecessor(highSize);
                if (predCluster == universeSize) {
                    if (min < x) {
                        return min;
                    } else {
                        return universeSize;
                    }
                } else {
                    size_t offset = cluster[predCluster]->getMax();
                    return indexedValue(predCluster, offset);
                }
            }
        }
    }
private:
    size_t highValue(size_t x) const {
        return x / lowerSquareRoot(universeSize);
    }
    size_t lowValue(size_t x) const {
        return x % lowerSquareRoot(universeSize);
    }
    size_t indexedValue(size_t highSize, size_t lowSize) const {
        return highSize * lowerSquareRoot(universeSize) + lowSize;
    }
    size_t upperSquareRoot(size_t x) const {
        return static_cast<size_t>(std::ceil(std::sqrt(static_cast<double>(x))));
    }
    size_t lowerSquareRoot(size_t x) const {
        return static_cast<size_t>(std::floor(std::sqrt(static_cast<double>(x))));
    }
    void updateMinMax() {
        min = universeSize;
        max = 0;
        for (size_t i = 0; i < cluster.size(); ++i) {
            if (cluster[i]->getMin() < cluster[i]->getMax()) {
                min = std::min(min, indexedValue(i, cluster[i]->getMin()));
                max = std::max(max, indexedValue(i, cluster[i]->getMax()));
            }
        }
    }
};
int main() {
    VanEmdeBoasTree vebTree(16);
    vebTree.insert(2);
    vebTree.insert(5);
    vebTree.insert(11);
    vebTree.insert(4);
    vebTree.insert(7);
    std::cout << "Min: " << vebTree.getMin() << std::endl; 
    std::cout << "Max: " << vebTree.getMax() << std::endl; 
    std::cout << "Successor of 5: " << vebTree.successor(5) << std::endl; 
    std::cout << "Predecessor of 7: " << vebTree.predecessor(7) << std::endl;
    vebTree.remove(5);
    std::cout << "Min after removal: " << vebTree.getMin() << std::endl; 
    return 0;
}
