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

    // --- Medicion de tiempos ---
    cout << "\n=== MEDICION DE TIEMPOS (ms) ===" << endl;
    double tiempo_actual = medirTiempo(A);
    cout << "Tiempo total (perm. actual): " << fixed << setprecision(2)
         << tiempo_actual << " ms" << endl;
         
    return 0;
}