#include "murmur3.h"

// Rotacion circular a la izquierda de 32 bits
static inline uint32_t rotl32(uint32_t x, int8_t r) {
    return (x << r) | (x >> (32 - r));
}

// Implementacion limpia de MurmurHash3_x86_32 para enteros de 4 bytes
uint32_t murmur3_32(uint32_t x, uint32_t seed) {
    // 1. Multiplicacion y rotacion (de ahi el nombre Mur-mur)
    uint32_t k1 = x * 0xcc9e2d51;
    k1 = rotl32(k1, 15) * 0x1b873593;

    uint32_t h = seed ^ k1;
    h = rotl32(h, 13) * 5 + 0xe6546b64;

    // 2. Mezcla final (Avalancha: desordena completamente los 32 bits)
    h ^= 4; // longitud fija de 4 bytes
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;

    return h;
}
