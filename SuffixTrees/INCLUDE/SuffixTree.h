#ifndef SUFFIX_TREE_H
#define SUFFIX_TREE_H

#include <cstddef>
#include <map>
#include <string>
#include <vector>

class SuffixTree {
public:
    explicit SuffixTree(const std::string& texto);
    std::vector<std::size_t> buscar(const std::string& patron) const;
    std::vector<std::size_t> sufijosOrdenados() const;
    void mostrar() const;

    static std::string subcadenaComun(const std::string& texto1,
                                     const std::string& texto2);

private:
    struct Nodo {
        std::size_t inicio;
        std::size_t fin;     // Arista entrante: [inicio, fin).
        std::size_t sufijo;  // Posicion original, solo para hojas.
        std::size_t enlace; // Enlace de sufijo; 0 representa la raiz.
        std::map<unsigned char, std::size_t> hijos;
    };

    std::string texto_;
    std::vector<Nodo> nodos_;

    std::size_t nodoActivo_ = 0;
    std::size_t aristaActiva_ = 0;
    std::size_t longitudActiva_ = 0;
    std::size_t extensionesPendientes_ = 0;
    std::size_t finHojas_ = 0;

    std::size_t crearNodo(std::size_t inicio, std::size_t fin,
                         std::size_t sufijo);
    std::size_t longitudArista(std::size_t nodo) const;
    void extender(std::size_t posicion);
    void recolectar(std::size_t nodo, std::vector<std::size_t>& posiciones) const;
    void mostrarNodo(std::size_t nodo, std::size_t nivel) const;
    int marcarOrigenes(std::size_t nodo, std::size_t profundidad,
                       std::size_t separador, std::size_t& mejorInicio,
                       std::size_t& mejorLongitud) const;
};

#endif
