# Suffix Trees (C++)

Implementación de Suffix Trees usando el algoritmo de Ukkonen en tiempo lineal $O(n)$ y Suffix Array con cálculo del arreglo LCP mediante el algoritmo de Kasai y búsqueda binaria.

## Trabajo Grupal / Presenters
- **Gonzales Hernandez, Alexis Orlando**
- **Salazar Zapata, Alvaro Matias**
- **Sotelo Atuncar, Diego Alejandro**
- **Villavicencio Merella, Paolo Alonso**

---

## Estructura del Proyecto

```text
SuffixTrees/
├── APPS/
│   └── main.cpp          # Punto de entrada principal
├── INCLUDE/
│   ├── Aplicacion.h      # Declaración de la interfaz CLI
│   ├── SuffixArray.h     # Declaración del Suffix Array y LCP
│   └── SuffixTree.h      # Declaración del Suffix Tree y nodo
├── SRC/
│   ├── Aplicacion.cpp    # Flujo interactivo y resumen de complejidades
│   ├── SuffixArray.cpp   # Construcción de Suffix Array, Kasai (LCP) y búsqueda
│   ├── SuffixTree.cpp    # Búsqueda, visualización y LCS en Suffix Tree
│   └── Ukkonen.cpp       # Construcción lineal O(n) con el algoritmo de Ukkonen
└── makefile              # Script de compilación y ejecución
```

## Compilación y Ejecución

Para compilar el proyecto:
```bash
cd SuffixTrees
make
```

Para compilar y ejecutar directamente la aplicación interactiva:
```bash
cd SuffixTrees
make run
```

Para limpiar los binarios compilados:
```bash
cd SuffixTrees
make clean
```

## Funcionalidades Implementadas

1. **Construcción con Ukkonen**: Construcción del árbol de sufijos en tiempo lineal $O(n)$ para alfabetos acotados, empleando punteros implícitos, enlaces de sufijo y las tres reglas canónicas de extensión.
2. **Búsqueda de Patrones**: Localización de todas las ocurrencias de un patrón en el texto en tiempo $O(m + k)$.
3. **Subcadena Común Más Larga (LCS)**: Búsqueda de la subcadena común más larga entre dos cadenas en $O(n_1 + n_2)$ mediante el árbol de sufijos generalizado.
4. **Suffix Array y LCP**: Generación del arreglo de sufijos y cálculo del arreglo LCP en tiempo $O(n)$ utilizando el algoritmo de Kasai.
5. **Búsqueda Binaria en Suffix Array**: Búsqueda en tiempo $O(m \log n + k)$.

## Resumen de Complejidades

| Estructura / Operación | Complejidad Temporal | Espacio Auxiliar |
| :--- | :--- | :--- |
| **Suffix Tree (Construcción con Ukkonen)** | $O(n)$ | $O(n)$ |
| **Búsqueda en Suffix Tree** | $O(m + k)$ | $O(1)$ |
| **Longest Common Substring (LCS)** | $O(n_1 + n_2)$ | $O(n_1 + n_2)$ |
| **Suffix Array (Espacio)** | — | $O(n)$ |
| **LCP (Algoritmo de Kasai)** | $O(n)$ | $O(n)$ |
| **Búsqueda en Suffix Array** | $O(m \log n + k)$ | $O(1)$ |

*Donde $n$ es la longitud del texto, $m$ la longitud del patrón y $k$ la cantidad de ocurrencias.*
