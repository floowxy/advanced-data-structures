#ifndef HYPERLOGLOG_H
#define HYPERLOGLOG_H

#include <vector>
#include <cstdint>
#include "murmur3.h"

class HyperLogLog {
private:
    int p;                         // Bits de precision (4 a 16). Cantidad de registros m = 2^p
    int m;                         // m = 2^p
    uint32_t seed;                 // Semilla para MurmurHash3
    std::vector<uint8_t> M;        // Arreglo de m registros inicializados en 0

    // Funcion hash: utiliza MurmurHash3_32
    uint32_t hash32(uint32_t x) const { return murmur3_32(x, seed); }

public:
    // 1. CREATE(p): constructor
    HyperLogLog(int p = 4, uint32_t seed = 0);

    // 2. RHO(w): cuenta ceros iniciales de w + 1
    static int rho(uint32_t w, int p);

    // 3. INSERT(x): calcula hash, registro j, w, y actualiza M[j] = max(M[j], rho)
    void insert(uint32_t id, bool verbose = false);

    // 4. ALPHA(m): constante de correccion de sesgo
    static double alpha(int m);

    // 5. ESTIMATE: estimacion con correccion Linear Counting
    double estimate() const;

    // 6. MERGE: combina dos sketches compatibles mediante el maximo
    HyperLogLog merge(const HyperLogLog& other) const;

    // Metodos de apoyo para la exposicion
    int get_m() const { return m; }
    int get_register(int j) const { return M[j]; }
    const std::vector<uint8_t>& get_registers() const { return M; }
    double standard_error() const;
};

#endif // HYPERLOGLOG_H
