#include "SuffixTree.h"
#include <iostream>
#include <stdexcept>

std::vector<std::size_t> SuffixTree::buscar(const std::string &patron) const {
  if (patron.empty() || patron.find('$') != std::string::npos)
    return {};

  std::size_t actual = 0;
  std::size_t posicion = 0;
  while (posicion < patron.size()) {
    auto encontrado = nodos_[actual].hijos.find(patron[posicion]);
    if (encontrado == nodos_[actual].hijos.end())
      return {};

    const auto hijo = encontrado->second;
    for (auto i = nodos_[hijo].inicio;
         i < nodos_[hijo].fin && posicion < patron.size(); ++i) {
      if (texto_[i] != patron[posicion])
        return {};
      ++posicion;
    }
    actual = hijo;
  }

  // El patron puede terminar dentro de la arista que lleva a este nodo.
  std::vector<std::size_t> posiciones;
  recolectar(actual, posiciones);
  return posiciones;
}

void SuffixTree::recolectar(std::size_t nodo,std::vector<std::size_t> &posiciones) const {
  if (nodos_[nodo].hijos.empty()) {
    posiciones.push_back(nodos_[nodo].sufijo);
    return;
  }
  for (const auto &hijo : nodos_[nodo].hijos) {
    recolectar(hijo.second, posiciones);
  }
}

std::vector<std::size_t> SuffixTree::sufijosOrdenados() const {
  std::vector<std::size_t> posiciones;
  // map ordena los hijos por su primera letra.
  recolectar(0, posiciones);
  return posiciones;
}

void SuffixTree::mostrar() const {
  std::cout << "(raiz)\n";
  for (const auto &hijo : nodos_[0].hijos)
    mostrarNodo(hijo.second, 0);
}

void SuffixTree::mostrarNodo(std::size_t nodo, std::size_t nivel) const {
  const auto &dato = nodos_[nodo];
  std::cout << std::string(nivel * 3, ' ') << "|- "
            << texto_.substr(dato.inicio, dato.fin - dato.inicio) << " ["
            << dato.inicio << ',' << dato.fin << ')';
  if (dato.hijos.empty())
    std::cout << " -> sufijo " << dato.sufijo;
  std::cout << '\n';
  for (const auto &hijo : dato.hijos)
    mostrarNodo(hijo.second, nivel + 1);
}

std::string SuffixTree::subcadenaComun(const std::string &texto1,const std::string &texto2) {
  if (texto1.find_first_of("#$") != std::string::npos ||
      texto2.find_first_of("#$") != std::string::npos) {
    throw std::invalid_argument("Los textos no deben contener '#' ni '$'.");
  }
  const SuffixTree conjunto(texto1 + '#' + texto2);
  std::size_t inicio = 0;
  std::size_t longitud = 0;
  conjunto.marcarOrigenes(0, 0, texto1.size(), inicio, longitud);
  return conjunto.texto_.substr(inicio, longitud);
}

int SuffixTree::marcarOrigenes(std::size_t nodo, std::size_t profundidad,std::size_t separador, std::size_t &mejorInicio,std::size_t &mejorLongitud) const {
  const auto &dato = nodos_[nodo];
  if (dato.hijos.empty()) {
    if (dato.sufijo < separador)
      return 1;
    if (dato.sufijo > separador && dato.sufijo < texto_.size() - 1)
      return 2;
    return 0; // Las hojas que empiezan en '#' o '$' no pertenecen a un texto.
  }

  int origenes = 0;
  for (const auto &hijo : dato.hijos) {
    const auto &siguiente = nodos_[hijo.second];
    origenes |= marcarOrigenes(hijo.second,profundidad + siguiente.fin - siguiente.inicio,separador, mejorInicio, mejorLongitud);
  }
  // Union de marcas: 1 | 2 = 3 significa que aparece en ambos textos.
  if (origenes == 3 && profundidad > mejorLongitud) {
    mejorLongitud = profundidad;
    mejorInicio = dato.fin - profundidad;
  }
  return origenes;
}
