#include "SuffixTree.h"
#include <stdexcept>

SuffixTree::SuffixTree(const std::string &texto) : texto_(texto) {
  if (texto.find('$') != std::string::npos) {
    throw std::invalid_argument("El texto no puede contener '$'.");
  }
  texto_ += '$';
  crearNodo(0, 0, 0); // Nodo 0: raiz, sin arista entrante.
  for (std::size_t i = 0; i < texto_.size(); ++i) {
    extender(i);
  }
  // Al terminar, todas las hojas dejan de crecer.
  for (auto &nodo : nodos_) {
    if (nodo.fin == std::string::npos)
      nodo.fin = finHojas_;
  }
}

std::size_t SuffixTree::crearNodo(std::size_t inicio, std::size_t fin,std::size_t sufijo) {
  nodos_.push_back({inicio, fin, sufijo, 0, {}});
  return nodos_.size() - 1;
}

std::size_t SuffixTree::longitudArista(std::size_t nodo) const {
  // npos indica que la hoja usa el fin compartido finHojas_.
  const auto fin =
      nodos_[nodo].fin == std::string::npos ? finHojas_ : nodos_[nodo].fin;
  return fin - nodos_[nodo].inicio;
}

void SuffixTree::extender(std::size_t posicion) {
  finHojas_ = posicion + 1; // Regla 1: extender las hojas.
  ++extensionesPendientes_;
  std::size_t ultimoInterno = 0;

  while (extensionesPendientes_ > 0) {
    if (longitudActiva_ == 0)
      aristaActiva_ = posicion;
    const char letra = texto_[aristaActiva_];
    auto encontrado = nodos_[nodoActivo_].hijos.find(letra);

    if (encontrado == nodos_[nodoActivo_].hijos.end()) {
      // Regla 2: crear una nueva hoja.
      const auto hoja = crearNodo(posicion, std::string::npos,
                                  posicion - extensionesPendientes_ + 1);
      nodos_[nodoActivo_].hijos[letra] = hoja;
      if (ultimoInterno != 0) {
        nodos_[ultimoInterno].enlace = nodoActivo_;
        ultimoInterno = 0;
      }
    } else {
      const auto hijo = encontrado->second;
      const auto longitud = longitudArista(hijo);
      // Saltar una arista completa sin comparar todas sus letras.
      if (longitudActiva_ >= longitud) {
        aristaActiva_ += longitud;
        longitudActiva_ -= longitud;
        nodoActivo_ = hijo;
        continue;
      }

      if (texto_[nodos_[hijo].inicio + longitudActiva_] == texto_[posicion]) {
        // Regla 3: el camino ya existe; terminar esta fase.
        if (ultimoInterno != 0)
          nodos_[ultimoInterno].enlace = nodoActivo_;
        ++longitudActiva_;
        break;
      }

      // Dividir la arista donde aparece la diferencia.
      const auto inicio = nodos_[hijo].inicio;
      const auto intermedio = crearNodo(inicio, inicio + longitudActiva_, 0);
      nodos_[nodoActivo_].hijos[letra] = intermedio;
      nodos_[hijo].inicio += longitudActiva_;
      nodos_[intermedio].hijos[texto_[nodos_[hijo].inicio]] = hijo;
      const auto hoja = crearNodo(posicion, std::string::npos,posicion - extensionesPendientes_ + 1);
      nodos_[intermedio].hijos[texto_[posicion]] = hoja;
      if (ultimoInterno != 0)
        nodos_[ultimoInterno].enlace = intermedio;
      ultimoInterno = intermedio;
    }

    --extensionesPendientes_;
    if (nodoActivo_ == 0 && longitudActiva_ > 0) {
      // Desde la raiz, quitar la primera letra del sufijo activo.
      --longitudActiva_;
      aristaActiva_ = posicion - extensionesPendientes_ + 1;
    } else if (nodoActivo_ != 0) {
      // Seguir el enlace de sufijo.
      nodoActivo_ = nodos_[nodoActivo_].enlace;
    }
  }
}
