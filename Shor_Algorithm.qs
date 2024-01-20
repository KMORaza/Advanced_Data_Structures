namespace ShorsAlgorithm {
    open Microsoft.Quantum.Arithmetic;
    open Microsoft.Quantum.Convert;
    open Microsoft.Quantum.Math;
    open Microsoft.Quantum.Arrays;
    operation ApplyPeriodFindingAlgorithm(a : Int, N : Int) : Int {
        let numBits = 4;
        using ((x, q) = (Qubit[numBits], Qubit[numBits])) {
            ApplyToEach(H, x);
            ModularExp(a, _, N, x, q);
            QuantumFourierTransform(x);
            let measurements = ForEach(M, MeasureInteger(LittleEndian(x)));
            let r = IntAsDouble(ResultArrayAsInt(measurements));
            return r;
        }
    }
    operation ShorsAlgorithm(N : Int) : (Int, Int) {
        mutable factor1 = -1;
        mutable factor2 = -1;
        repeat {
            let a = RandomInt(2, N - 1);
            let r = ApplyPeriodFindingAlgorithm(a, N);
            if (r % 2 == 0 && ModExp(a, r / 2, N) != 1) {
                factor1 = GCD(ModExp(a, r / 2, N) + 1, N);
                factor2 = GCD(ModExp(a, r / 2, N) - 1, N);
            }
        }
        until (factor1 > 1 and factor2 > 1);
        return (factor1, factor2);
    }
}
