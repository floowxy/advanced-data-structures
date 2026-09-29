#ifndef SUFFIX_ARRAY_H
#define SUFFIX_ARRAY_H

#include <cstddef>
#include <string>
#include <vector>

class SuffixArray {
public:
    explicit SuffixArray(const std::string& texto);
    std::vector<std::size_t> buscar(const std::string& patron) const;
    void mostrar() const;

private:
    std::string texto_;
    std::vector<std::size_t> sufijos_;
    std::vector<std::size_t> lcp_;

    void construirLCP();
    std::size_t buscarLimite(const std::string& patron, bool superior) const;
};

#endif
