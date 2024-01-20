#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <numeric> 
struct Point {
    long long x, y;
};
struct EllipticCurve {
    long long a, b; 
    long long p;    
};
Point addPoints(Point P, Point Q, EllipticCurve curve) {
    Point result;
    if (P.x == Q.x && P.y == Q.y) {
        long long slope = (3 * P.x * P.x + curve.a) * static_cast<long long>(std::pow(2 * P.y, curve.p - 2)) % curve.p;
        result.x = (slope * slope - 2 * P.x) % curve.p;
        result.y = (slope * (P.x - result.x) - P.y) % curve.p;
    } else {
        long long slope = (Q.y - P.y) * static_cast<long long>(std::pow(Q.x - P.x, curve.p - 2)) % curve.p;
        result.x = (slope * slope - P.x - Q.x) % curve.p;
        result.y = (slope * (P.x - result.x) - P.y) % curve.p;
    }
    result.x = (result.x + curve.p) % curve.p;
    result.y = (result.y + curve.p) % curve.p;
    return result;
}
long long ellipticCurveFactorization(long long n, long long iterations) {
    EllipticCurve curve;
    curve.a = 2;
    curve.b = 2;
    curve.p = n;
    Point P;
    P.x = 0;
    P.y = 1;
    for (long long i = 0; i < iterations; ++i) {
        long long x = rand() % n;
        Point Q = P;
        for (long long j = 0; j < x; ++j) {
            Q = addPoints(Q, P, curve);
        }
        long long factor = std::gcd(n, Q.x);
        if (factor > 1 && factor < n) {
            return factor;
        }
    }
    return -1; 
}
int main() {
    srand(time(0));
    long long number;
    std::cout << "Enter a number to factorize: ";
    std::cin >> number;
    long long factor = ellipticCurveFactorization(number, 1000);
    if (factor != -1) {
        std::cout << "Found factor: " << factor << std::endl;
        std::cout << "Other factor: " << number / factor << std::endl;
    } else {
        std::cout << "Failed to perform factorization!\nTry increasing the number of iterations." << std::endl;
    }
    return 0;
}
