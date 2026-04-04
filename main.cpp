#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// Verifica si una permutacion cumple la restriccion P[i] <= 2 * P[i+1]
bool esValida(const vector<int>& perm) {
    for (int i = 0; i < (int)perm.size() - 1; i++) {
        if (perm[i] > 2 * perm[i + 1]) {
            return false;
        }
    }
    return true;
}

// Imprime una permutacion en formato legible
void imprimirPerm(const vector<int>& perm) {
    cout << "[ ";
    for (int x : perm) cout << x << " ";
    cout << "]" << endl;
}

// Genera todas las permutaciones por fuerza bruta usando next_permutation
void fuerzaBruta(vector<int> A, bool imprimirValidas = true) {
    sort(A.begin(), A.end()); // Garantiza empezar desde la menor permutacion

    long long totalGeneradas = 0;
    long long totalValidas   = 0;

    if (imprimirValidas) {
        cout << "\nPermutaciones validas:" << endl;
    }

    do {
        totalGeneradas++;
        if (esValida(A)) {
            totalValidas++;
            if (imprimirValidas) imprimirPerm(A);
        }
    } while (next_permutation(A.begin(), A.end()));

    if (imprimirValidas) {
        cout << "\nTotal permutaciones generadas : " << totalGeneradas << endl;
        cout << "Total permutaciones validas   : " << totalValidas   << endl;
    }
}

// Version solo para medir tiempo (sin imprimir permutaciones)
double medirTiempo(vector<int> A) {
    auto inicio = high_resolution_clock::now();
    fuerzaBruta(A, false);
    auto fin = high_resolution_clock::now();
    return duration<double, milli>(fin - inicio).count();
}

int main() {
    // --- Modo interactivo ---
    int n;
    cout << "Ingrese n (cantidad de elementos): ";
    cin >> n;

    vector<int> A(n);
    cout << "Ingrese los " << n << " elementos distintos: ";
    for (int i = 0; i < n; i++) cin >> A[i];

    cout << "\n=== FUERZA BRUTA: Permutaciones con restriccion P[i] <= 2*P[i+1] ===" << endl;
    fuerzaBruta(A, true);

    // --- Medicion experimental de tiempos ---
    cout << "\n=== MEDICION DE TIEMPOS (ms) ===" << endl;
    cout << left << setw(6) << "n" << setw(15) << "Permutaciones" << "Tiempo (ms)" << endl;
    cout << string(40, '-') << endl;

    // Probamos con n = 8, 10, 11, 12 usando {1,2,...,n}
    vector<int> ns = {8, 10, 11, 12};
    for (int ni : ns) {
        vector<int> prueba(ni);
        for (int i = 0; i < ni; i++) prueba[i] = i + 1;

        // Calcular n!
        long long fact = 1;
        for (int i = 1; i <= ni; i++) fact *= i;

        double tiempo = medirTiempo(prueba);
        cout << left << setw(6) << ni << setw(15) << fact << fixed << setprecision(2) << tiempo << " ms" << endl;
    }

    return 0;
}