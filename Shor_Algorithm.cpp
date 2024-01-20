#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <complex>
#include <algorithm>
#include <qiskit/qiskit.h>
void quantumFourierTransform(qiskit::QuantumCircuit& circuit, int n) {
    for (int j = n - 1; j >= 0; --j) {
        circuit.h(j);
        for (int k = j - 1; k >= 0; --k) {
            circuit.cu1(2 * M_PI / std::pow(2, j - k + 1), k, j);
        }
    }
}
std::vector<int> shorsAlgorithm(int N, int a, int numBits) {
    qiskit::QuantumRegister qreg(numBits, "qreg");
    qiskit::ClassicalRegister creg(numBits, "creg");
    qiskit::QuantumCircuit circuit(qreg, creg);
    circuit.h(qreg);
    for (int i = 0; i < numBits; ++i) {
        circuit.x(qreg[0]);
        for (int j = 0; j < (1 << i); ++j) {
            circuit.cx(qreg[j], qreg[numBits - 1]);
        }
        circuit.x(qreg[numBits - 1]);
        for (int k = 0; k < numBits; ++k) {
            circuit.cu1(M_PI / (1 << k), qreg[k], qreg[numBits - 1]);
        }
        circuit.x(qreg[numBits - 1]);
    }
    quantumFourierTransform(circuit, numBits);
    circuit.measure(qreg, creg);
    qiskit::QuantumSimulator simulator;
    auto result = simulator.execute(circuit, 1024);
    auto counts = result.getCounts();
    int r = -1;
    for (const auto& count : counts) {
        int measuredValue = std::stoi(count.first, nullptr, 2);
        if (r == -1 || measuredValue % 2 != 0) {
            r = measuredValue;
        }
    }
    int x = std::pow(a, r / 2);
    int factor1 = std::gcd(x + 1, N);
    int factor2 = std::gcd(x - 1, N);
    return {factor1, factor2};
}
int main() {
    int N = 21;
    int a = 2;
    int numBits = 4;
    std::vector<int> factors = shorsAlgorithm(N, a, numBits);
    std::cout << "Factors of " << N << ": " << factors[0] << ", " << factors[1] << std::endl;
    return 0;
}
