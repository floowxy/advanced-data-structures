# HyperLogLog en C++ (32 bits)

Implementacion del algoritmo HyperLogLog (Flajolet et al., 2007) para estimacion de cardinalidad en flujos masivos de datos utilizando MurmurHash3.

## Equipo 4
* Alexis Gonzales — 24200201
* Alvaro Salazar — 24200205
* Diego Sotelo — 24200208
* Paolo Villavicencio — 24200210
* Profesor: Dr. Herminio Paucar (UNMSM - FISI)

## Estructura del Proyecto
* apps/app_main.cpp: Demostracion en consola (Demos A, B, C y D).
* include/hyperloglog.h y src/hyperloglog.cpp: Implementacion de la estructura HyperLogLog.
* include/murmur3.h y src/murmur3.cpp: Hash MurmurHash3 de 32 bits determinista.
* Makefile: Compilacion y ejecucion directa.

## Compilacion y Ejecucion
Compilar y ejecutar:
```bash
make run
```

Limpiar archivos generados:
```bash
make clean
```

## Demostraciones en Terminal
* Demo A: Insercion paso a paso con p = 4 (m = 16 registros) y actualizacion por maximo en colisiones.
* Demo B: Idempotencia frente a elementos repetidos (el estimador no cambia).
* Demo C: Comparacion con std::unordered_set y prueba masiva con 10,000,000 de usuarios (16 KB vs ~400 MB).
* Demo D: Union de dos servidores distribuidos (Merge elemento a elemento).
* Invariantes: Verificaciones unitarias de consistencia matematica.

## Complejidad
* Insercion: O(1)
* Estimacion: O(m)
* Union (Merge): O(m)
* Memoria: O(m) fija (independiente del volumen de datos).
