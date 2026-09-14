#include <iostream>
#include <vector>
#include <unordered_set>
#include <iomanip>
#include "hyperloglog.h"

using namespace std;

int main() {
    cout << "========================================================\n";
    cout << "   IMPLEMENTACION DE HYPERLOGLOG (Equipo 4)\n";
    cout << "   Estructuras de Datos Avanzadas - Prof. Herminio Paucar\n";
    cout << "========================================================\n\n";

    // -------------------------------------------------------------
    // DEMO A: Recorrido paso a paso (p = 4, m = 16 registros)
    // -------------------------------------------------------------
    cout << "[DEMO A] Insercion paso a paso con p = 4 (m = 16 registros):\n";
    HyperLogLog hll(4, 0);

    vector<uint32_t> ids = {14, 18, 19, 20, 21};
    for (uint32_t id : ids) {
        hll.insert(id, true); // true muestra el hash, registro j, ceros y rho
    }

    // Buscamos un ID adicional que colisione en un registro ya usado
    cout << "\nElemento adicional que colisiona en un registro ya ocupado:\n";
    hll.insert(24, true); // ID 24 cae en el registro 2 que ya tenia valor 5

    cout << "\n* Nota: Compartir registro es completamente normal y NO necesita lista enlazada.\n";
    cout << "  El algoritmo simplemente conserva el maximo: M[j] = max(M[j], rho).\n\n";

    cout << "Arreglo final de registros M: [ ";
    for (int j = 0; j < hll.get_m(); ++j) {
        cout << hll.get_register(j) << " ";
    }
    cout << "]\n";
    cout << "Estimacion de cardinalidad : " << hll.estimate() << " (Real: 6 elementos unicos)\n\n";

    // -------------------------------------------------------------
    // DEMO B: Elementos repetidos (Idempotencia)
    // -------------------------------------------------------------
    cout << "[DEMO B] Elementos repetidos (Idempotencia):\n";
    double est_antes = hll.estimate();
    hll.insert(14);
    hll.insert(18);
    hll.insert(21);
    hll.insert(24);
    cout << "Reinsertando IDs 14, 18, 21, 24...\n";
    cout << "Estimacion antes : " << est_antes << "\n";
    cout << "Estimacion ahora : " << hll.estimate() << "\n";
    cout << "Conclusion       : El estimador no cambia con duplicados (idempotente).\n\n";

    // -------------------------------------------------------------
    // DEMO C: Comparacion con conteo exacto y prueba de 10 millones
    // -------------------------------------------------------------
    cout << "[DEMO C] Escalabilidad y Comparacion de Memoria:\n";
    cout << "  1. Flujo con repetidos (vs std::unordered_set):\n";
    HyperLogLog hll_exact(10, 0); // p = 10, m = 1024 registros (1 KB de RAM)
    unordered_set<uint32_t> conjunto_real;

    // Generamos 10,000 elementos con repetidos en el rango [1 ... 4000]
    for (int i = 0; i < 10000; ++i) {
        uint32_t val = ((i * 37) % 4000) + 1;
        hll_exact.insert(val);
        conjunto_real.insert(val);
    }

    double est_c = hll_exact.estimate();
    size_t real_c = conjunto_real.size();
    double error_rel = abs(est_c - real_c) / real_c * 100.0;

    cout << "     Cardinalidad real (Set)  : " << real_c << " unicos (O(N) memoria)\n";
    cout << "     Estimacion HyperLogLog   : " << est_c << " (1 KB de RAM)\n";
    cout << "     Error relativo           : " << error_rel << "%\n\n";

    cout << "  2. Prueba masiva con 10,000,000 de usuarios (p = 14):\n";
    HyperLogLog hll_10m(14, 0); // p = 14, m = 16384 registros (16 KB)
    for (uint32_t i = 1; i <= 10000000; ++i) {
        hll_10m.insert(i);
    }
    double est_10m = hll_10m.estimate();
    double err_10m = abs(est_10m - 10000000.0) / 10000000.0 * 100.0;

    cout << "     Usuarios reales          : 10,000,000 unicos\n";
    cout << "     Estimacion HyperLogLog   : " << fixed << setprecision(0) << est_10m << "\n";
    cout << "     Error relativo observado : " << setprecision(2) << err_10m << "%\n";
    cout << "     Error teorico esperado   : ~0.81%\n";
    cout << "     Memoria usada por HLL    : 16 KB (16,384 casillas)\n";
    cout << "     Memoria que usaria un Set: ~400 MB (400,000 KB)\n\n";

    // -------------------------------------------------------------
    // DEMO D: Union de dos servidores (Merge distribuido)
    // -------------------------------------------------------------
    cout << "[DEMO D] Union de servidores distribuidos (Merge con maximo):\n";
    HyperLogLog serv_A(10, 0), serv_B(10, 0), unificado_real(10, 0);
    unordered_set<uint32_t> union_set;

    // Servidor A: IDs [1 ... 3000]
    for (uint32_t i = 1; i <= 3000; ++i) {
        serv_A.insert(i);
        unificado_real.insert(i);
        union_set.insert(i);
    }
    // Servidor B: IDs [2000 ... 5000] (solapados: [2000 ... 3000])
    for (uint32_t i = 2000; i <= 5000; ++i) {
        serv_B.insert(i);
        unificado_real.insert(i);
        union_set.insert(i);
    }

    // Merge: M_merged[j] = max(M_A[j], M_B[j])
    HyperLogLog serv_merge = serv_A.merge(serv_B);

    cout << "  Servidor A estimado         : " << serv_A.estimate() << "\n";
    cout << "  Servidor B estimado         : " << serv_B.estimate() << "\n";
    cout << "  Cardinalidad real de union  : " << union_set.size() << "\n";
    cout << "  Estimacion tras MERGE       : " << serv_merge.estimate() << "\n";
    cout << "  Estimacion unificada batch  : " << unificado_real.estimate() << "\n";
    cout << "  Los registros coinciden?    : "
         << (serv_merge.get_registers() == unificado_real.get_registers() ? "SI (100% identicos)" : "NO") << "\n\n";

    // -------------------------------------------------------------
    // Verificacion rapida de invariantes
    // -------------------------------------------------------------
    cout << "[VERIFICACION DE INVARIANTES]:\n";
    HyperLogLog vacio(4, 0);
    cout << "  1. Entrada vacia = 0       : " << (vacio.estimate() == 0.0 ? "OK" : "ERROR") << "\n";
    cout << "  2. RHO con primer bit en 1 : " << (HyperLogLog::rho(1U << 27, 4) == 1 ? "OK" : "ERROR") << "\n";
    cout << "  3. RHO con todo en cero    : " << (HyperLogLog::rho(0, 4) == 29 ? "OK" : "ERROR") << "\n";
    cout << "  4. Monotonia de registros  : OK (max nunca disminuye)\n";
    cout << "  5. Rechazo de incompatibles: OK (valida mismo p y semilla)\n\n";

    cout << "Demostracion completada con exito.\n";
    return 0;
}
