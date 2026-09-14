# HyperLogLog en C++ (32 bits) — Estructuras de Datos Avanzadas

Implementación simple, directa y didáctica del algoritmo **HyperLogLog** (Flajolet et al., 2007) para la estimación de cardinalidad en flujos masivos de datos.

Diseñado con el mismo enfoque minimalista y pedagógico que el proyecto de **LSH** del grupo.

---

## 👥 Equipo 4
* **Alexis Gonzales** — 24200201
* **Alvaro Salazar** — 24200205
* **Diego Sotelo** — 24200208
* **Paolo Villavicencio** — 24200210
* **Profesor:** Dr. Herminio Paucar (UNMSM - FISI)

---

## 📂 Estructura del Proyecto
```text
advanced-data-structures/
├── apps/
│   └── app_main.cpp        # Demostración en terminal (Demos A, B, C, D)
├── include/
│   ├── hyperloglog.h       # Definición de la clase HyperLogLog (~40 líneas)
│   └── murmur3.h          # Hash determinista de 32 bits
├── src/
│   ├── hyperloglog.cpp     # Métodos de HLL: rho, insert, estimate, merge (~90 líneas)
│   └── murmur3.cpp        # Implementación de MurmurHash3_x86_32
├── Makefile                # Compilación y ejecución simple
└── README.md
```

---

## 🚀 Compilar y Ejecutar

Todo se compila y ejecuta localmente con `make`:

```bash
make
./bin/app_hll

# O directamente:
make run
```

Para limpiar los archivos objeto y el ejecutable:
```bash
make clean
```

---

## 💡 Cómo Funciona HyperLogLog (Explicación para Exposición)

1. **`CREATE(p)`**: Crea $m = 2^p$ registros inicializados en cero. (Ej. con $p=4$, $m=16$).
2. **`INSERT(x)`**:
   * Calcula un hash de 32 bits $h(x)$.
   * Toma los primeros $p$ bits más significativos para seleccionar el **registro $j$**.
   * Toma los $32 - p$ bits restantes ($w$) y cuenta sus ceros iniciales más 1 (**$\rho(w)$**).
   * Actualiza el registro reteniendo el máximo: $M[j] = \max(M[j], \rho(w))$.
   * **Colisiones:** Si dos elementos caen en el mismo registro, **NO** se usa lista enlazada; solo se conserva la observación más extrema ($\max$).
3. **`ESTIMATE`**:
   * Promedia los registros usando la media armónica: $E = \alpha_m \cdot m^2 / \sum 2^{-M[j]}$.
   * Si la cardinalidad es pequeña ($E \le 2.5m$), aplica la corrección *Linear Counting*: $m \cdot \ln(m / V)$, donde $V$ es la cantidad de registros en cero.
4. **`MERGE` (Cómputo Distribuido)**:
   * Para unir la información de dos servidores, simplemente se toma el máximo registro a registro: $M_{\text{union}}[j] = \max(M_A[j], M_B[j])$.
   * No requiere transferir datos crudos por la red, solo el arreglo de registros ($16\text{ KB}$ para $p=14$).

---

## ⏱️ Complejidad
* **Inserción:** $O(1)$
* **Estimación:** $O(m)$
* **Unión (Merge):** $O(m)$
* **Memoria:** $O(m)$ fija (apenas $m$ bytes en RAM, independiente de cuántos millones de elementos se inserten).
