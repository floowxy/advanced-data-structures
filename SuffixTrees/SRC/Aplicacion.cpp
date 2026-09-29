#include "Aplicacion.h"
#include "SuffixArray.h"
#include "SuffixTree.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static void mostrarPosiciones(std::vector<std::size_t> posiciones) {
  // Ordenar es solo presentacion: agrega O(k log k), no pertenece a buscar().
  std::sort(posiciones.begin(), posiciones.end());
  std::cout << "Posiciones:";
  for (auto posicion : posiciones)
    std::cout << ' ' << posicion;
  if (posiciones.empty())
    std::cout << " sin coincidencias";
  std::cout << '\n';
}

static void mostrarComplejidades() {
  std::cout << "\n=== COMPLEJIDADES ===\n"
               "\nSuffix Tree:\n"
               "Construcción con Ukkonen: O(n), considerando alfabeto fijo\n"
               "Búsqueda: O(m + k), considerando alfabeto fijo\n"
               "Espacio: O(n)\n"
               "\nLongest Common Substring:\n"
               "O(n1 + n2) usando el árbol generalizado.\n"
               "\nSuffix Array:\nEspacio: O(n)\n"
               "\nLCP con Kasai:\nO(n)\n"
               "\nBúsqueda binaria en Suffix Array:\nO(m log n + k)\n"
               "\nDonde:\n"
               "n = longitud del texto\n"
               "m = longitud del patrón\n"
               "k = número de coincidencias\n";
}

void ejecutarAplicacion() {
  std::string texto, patron, segundoTexto;
  std::cout << "Texto: ";
  if (!std::getline(std::cin, texto))
    return;
  std::cout << "Patron: ";
  if (!std::getline(std::cin, patron))
    return;
  std::cout << "Segundo texto: ";
  if (!std::getline(std::cin, segundoTexto))
    return;

  if (texto.find_first_of("#$") != std::string::npos ||
      segundoTexto.find_first_of("#$") != std::string::npos ||
      patron.find_first_of("#$") != std::string::npos || patron.empty()) {
    std::cout << "No use '#' ni '$'. El patron no debe estar vacio.\n";
    return;
  }

  const SuffixTree arbol(texto);
  std::cout << "\n=== SUFFIX TREE ===\n";
  arbol.mostrar();

  std::cout << "\n=== BUSQUEDA ===\nPatron: " << patron << '\n';
  mostrarPosiciones(arbol.buscar(patron));

  std::cout << "\n=== SUBCADENA COMUN MAS LARGA ===\n";
  std::cout << SuffixTree::subcadenaComun(texto, segundoTexto) << '\n';

  const SuffixArray arreglo(texto);
  std::cout << "\n=== SUFFIX ARRAY ===\n";
  arreglo.mostrar();

  std::cout << "\n=== BUSQUEDA EN SUFFIX ARRAY ===\n";
  mostrarPosiciones(arreglo.buscar(patron));
  mostrarComplejidades();
}
