#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <cmath>
class LSHHashFunction {
private:
    std::vector<double> coefficients;
    double bias;
public:
    LSHHashFunction(int dimensions) : coefficients(dimensions), bias(0.0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::normal_distribution<double> distribution(0.0, 1.0);
        for (int i = 0; i < dimensions; ++i) {
            coefficients[i] = distribution(gen);
        }
        bias = distribution(gen);
    }
    int hash(const std::vector<double>& vector) const {
        double dotProduct = 0.0;
        for (std::size_t i = 0; i < coefficients.size(); ++i) {
            dotProduct += coefficients[i] * vector[i];
        }
        return (dotProduct + bias >= 0) ? 1 : 0;
    }
};
class LocalitySensitiveHashing {
private:
    int numHashFunctions;
    int numBuckets;
    int dimensions;
    std::vector<std::vector<int>> hashTables;
    std::vector<LSHHashFunction> hashFunctions;
public:
    LocalitySensitiveHashing(int numHashFunctions, int numBuckets, int dimensions)
        : numHashFunctions(numHashFunctions), numBuckets(numBuckets), dimensions(dimensions),
          hashTables(numHashFunctions, std::vector<int>(numBuckets)), hashFunctions(numHashFunctions, LSHHashFunction(dimensions)) {}
    void insert(const std::vector<double>& vector) {
        for (int i = 0; i < numHashFunctions; ++i) {
            int hashValue = hashFunctions[i].hash(vector);
            hashTables[i][hashValue]++;
        }
    }
    std::vector<std::vector<double>> query(const std::vector<double>& queryVector) const {
        std::vector<std::vector<double>> candidates;
        for (int i = 0; i < numHashFunctions; ++i) {
            int hashValue = hashFunctions[i].hash(queryVector);
            for (std::size_t j = 0; j < hashTables[i].size(); ++j) {
                if (hashTables[i][j] > 0 && j != hashValue) {
                    candidates.push_back(std::vector<double>(1, j));
                }
            }
        }
        return candidates;
    }
};
int main() {
    int numHashFunctions = 5;
    int numBuckets = 10;
    int dimensions = 20;
    LocalitySensitiveHashing lsh(numHashFunctions, numBuckets, dimensions);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> distribution(0.0, 1.0);
    for (int i = 0; i < 100; ++i) {
        std::vector<double> vector(dimensions);
        for (int j = 0; j < dimensions; ++j) {
            vector[j] = distribution(gen);
        }
        lsh.insert(vector);
    }
    std::vector<double> queryVector(dimensions);
    for (int j = 0; j < dimensions; ++j) {
        queryVector[j] = distribution(gen);
    }
    std::vector<std::vector<double>> candidates = lsh.query(queryVector);
    std::cout << "Candidates for query vector:\n";
    for (const auto& candidate : candidates) {
        std::cout << "Bucket Index: " << candidate[0] << "\n";
    }
    return 0;
}
