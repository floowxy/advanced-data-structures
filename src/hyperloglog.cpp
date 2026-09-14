#include "hyperloglog.h"
#include "murmur3.h"
#include <iostream>
#include <cmath>
#include <bitset>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

using namespace std;

// 1. CREATE(p): Constructor
HyperLogLog::HyperLogLog(int p, uint32_t seed) : p(p), seed(seed) {
    if (p < 4 || p > 16) {
        throw invalid_argument("El parametro p debe estar entre 4 y 16.");
    }
    m = 1 << p;
    M.assign(m, 0); // Registros inicializados en 0
}

// 2. RHO(w): Cuenta ceros iniciales en los (32 - p) bits restantes + 1
int HyperLogLog::rho(uint32_t w, int p) {
    int remaining_bits = 32 - p;
    if (w == 0) return remaining_bits + 1;

    int ceros = 0;
    for (int i = remaining_bits - 1; i >= 0; --i) {
        if ((w >> i) & 1) break;
        ceros++;
    }
    return ceros + 1;
}

// 4. ALPHA(m): Constante de normalizacion
double HyperLogLog::alpha(int m) {
    if (m == 16) return 0.673;
    if (m == 32) return 0.697;
    if (m == 64) return 0.709;
    return 0.7213 / (1.0 + 1.079 / static_cast<double>(m));
}

// 3. INSERT(x): Hashea con MurmurHash3, extrae j y w, calcula rho y actualiza M[j]
void HyperLogLog::insert(uint32_t id, bool verbose) {
    uint32_t h = hash32(id);                                       // MurmurHash3
    int remaining_bits = 32 - p;
    uint32_t j = h >> remaining_bits;                              // Primeros p bits
    uint32_t w = h & ((1U << remaining_bits) - 1);                 // 32 - p bits restantes
    int r = rho(w, p);

    if (verbose) {
        string bin = bitset<32>(h).to_string();
        cout << "  ID: " << setw(2) << id
             << " | Hash: " << bin.substr(0, p) << "|" << bin.substr(p)
             << " | Reg j=" << setw(2) << j
             << " | Ceros=" << setw(2) << (r - 1)
             << " | rho=" << setw(2) << r
             << " | M[" << setw(2) << j << "]: " << (int)M[j]
             << " -> " << max((int)M[j], r)
             << (r > M[j] ? " (Actualizado)" : " (Sin cambios)") << "\n";
    }

    if (r > M[j]) {
        M[j] = r;
    }
}

// 5. ESTIMATE: Media armonica con correccion Linear Counting
double HyperLogLog::estimate() const {
    double sum = 0.0;
    int V = 0; // Cantidad de registros en 0
    for (uint8_t val : M) {
        sum += pow(2.0, -val);
        if (val == 0) V++;
    }

    double E = alpha(m) * m * m / sum;
    const double TWO_32 = 4294967296.0;

    // Rango pequeno: Linear Counting si E <= 2.5*m y hay registros vacios
    if (E <= 2.5 * m && V > 0) {
        return m * log(static_cast<double>(m) / V);
    }
    // Rango intermedio: sin correccion
    if (E <= TWO_32 / 30.0) {
        return E;
    }
    // Rango grande: saturacion 32 bits
    if (E < TWO_32) {
        return -TWO_32 * log(1.0 - (E / TWO_32));
    }
    return TWO_32;
}

// 6. MERGE: Combina dos instancias tomando el maximo
HyperLogLog HyperLogLog::merge(const HyperLogLog& other) const {
    if (p != other.p) {
        throw invalid_argument("No se pueden unir sketches con diferente precision p.");
    }
    if (seed != other.seed) {
        throw invalid_argument("No se pueden unir sketches con diferente semilla de hash.");
    }

    HyperLogLog res(p, seed);
    for (int i = 0; i < m; ++i) {
        res.M[i] = max(M[i], other.M[i]);
    }
    return res;
}

double HyperLogLog::standard_error() const {
    return 1.04 / sqrt(static_cast<double>(m));
}
