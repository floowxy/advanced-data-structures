#ifndef MURMUR3_H
#define MURMUR3_H

#include <cstdint>

// MurmurHash3 de 32 bits (creado por Austin Appleby en 2008)
// Toma un numero entero de 4 bytes y devuelve un hash de 32 bits bien distribuido
uint32_t murmur3_32(uint32_t x, uint32_t seed = 0);

#endif // MURMUR3_H
