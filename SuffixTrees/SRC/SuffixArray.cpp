#include "SuffixArray.h"
#include "SuffixTree.h"

#include <iostream>

SuffixArray::SuffixArray(const std::string &texto) : texto_(texto + '$') {
  sufijos_ = SuffixTree(texto).sufijosOrdenados();
  construirLCP();
}

void SuffixArray::construirLCP() {
  // Kasai calcula el prefijo comun entre sufijos consecutivos del arreglo.
  const std::size_t n = texto_.size();
  std::vector<std::size_t> rango(n);
  lcp_.resize(n, 0);
  for (std::size_t i = 0; i < n; ++i)
    rango[sufijos_[i]] = i;

  std::size_t iguales = 0;
  for (std::size_t inicio = 0; inicio < n; ++inicio) {
    const auto lugar = rango[inicio];
    if (lugar == 0) {
      iguales = 0;
      continue;
    }
    const auto anterior = sufijos_[lugar - 1];
    while (inicio + iguales < n && anterior + iguales < n &&
           texto_[inicio + iguales] == texto_[anterior + iguales]) {
      ++iguales;
    }
    lcp_[lugar] = iguales;
    // Kasai reutiliza al menos h-1 letras al pasar al siguiente sufijo.
    if (iguales > 0)
      --iguales;
  }
}

std::size_t SuffixArray::buscarLimite(const std::string &patron,bool superior) const {
  // Busqueda binaria normal: no usa LCP para acelerar las comparaciones.
  std::size_t izquierda = 0;
  std::size_t derecha = sufijos_.size();
  while (izquierda < derecha) {
    const auto medio = izquierda + (derecha - izquierda) / 2;
    const int comparacion =
        texto_.compare(sufijos_[medio], patron.size(), patron);
    // Inferior: primera comparacion >= 0. Superior: primera > 0.
    if (comparacion < 0 || (superior && comparacion == 0)) {
      izquierda = medio + 1;
    } else {
      derecha = medio;
    }
  }
  return izquierda;
}

std::vector<std::size_t> SuffixArray::buscar(const std::string &patron) const {
  if (patron.empty() || patron.find('$') != std::string::npos)
    return {};
  const auto primero = buscarLimite(patron, false);
  const auto ultimo = buscarLimite(patron, true);
  // Todos los sufijos del intervalo comienzan con el patron.
  return {sufijos_.begin() + primero, sufijos_.begin() + ultimo};
}

void SuffixArray::mostrar() const {
  // LCP muestra cuantos caracteres iniciales comparte con el sufijo anterior.
  std::cout << "Indice | Posicion | LCP | Sufijo\n";
  for (std::size_t i = 0; i < sufijos_.size(); ++i) {
    std::cout << i << " | " << sufijos_[i] << " | " << lcp_[i] << " | "
              << texto_.substr(sufijos_[i]) << '\n';
  }
}
