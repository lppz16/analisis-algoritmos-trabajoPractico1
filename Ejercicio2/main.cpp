#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

class GraphColoring {
private:
    int n, k;
    vector<vector<int>> adj;

    // Backtracking
    vector<int> colorBT;
    vector<int> firstSolutionBT;
    long long totalBT;
    bool firstSavedBT;
    long long nodesBT; // llamadas recursivas / estados explorados

    // Fuerza Bruta
    vector<int> colorFB;
    vector<int> firstSolutionFB;
    long long totalFB;
    bool firstSavedFB;
    long long nodesFB; // asignaciones parciales o completas exploradas

public:
    GraphColoring(int n, int k, const vector<vector<int>>& adj)
        : n(n), k(k), adj(adj) {
        colorBT.assign(n, 0);
        firstSolutionBT.assign(n, 0);
        totalBT = 0;
        firstSavedBT = false;
        nodesBT = 0;

        colorFB.assign(n, 0);
        firstSolutionFB.assign(n, 0);
        totalFB = 0;
        firstSavedFB = false;
        nodesFB = 0;
    }

    bool isSafe(int v, int c) {
        for (int u = 0; u < n; u++) {
            if (adj[v][u] == 1 && colorBT[u] == c) {
                return false;
            }
        }
        return true;
    }

    void backtracking(int v) {
        nodesBT++;

        if (v == n) {
            totalBT++;
            if (!firstSavedBT) {
                firstSolutionBT = colorBT;
                firstSavedBT = true;
            }
            return;
        }

        for (int c = 1; c <= k; c++) {
            if (isSafe(v, c)) {
                colorBT[v] = c;
                backtracking(v + 1);
                colorBT[v] = 0;
            }
        }
    }

    bool isValidFullAssignment(const vector<int>& assignment) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (adj[i][j] == 1 && assignment[i] == assignment[j]) {
                    return false;
                }
            }
        }
        return true;
    }

    void bruteForce(int pos) {
        nodesFB++;

        if (pos == n) {
            if (isValidFullAssignment(colorFB)) {
                totalFB++;
                if (!firstSavedFB) {
                    firstSolutionFB = colorFB;
                    firstSavedFB = true;
                }
            }
            return;
        }

        for (int c = 1; c <= k; c++) {
            colorFB[pos] = c;
            bruteForce(pos + 1);
        }
    }

    void solveAndPrint() {
        auto startBT = high_resolution_clock::now();
        backtracking(0);
        auto endBT = high_resolution_clock::now();
        auto durationBT = duration_cast<microseconds>(endBT - startBT).count();

        auto startFB = high_resolution_clock::now();
        bruteForce(0);
        auto endFB = high_resolution_clock::now();
        auto durationFB = duration_cast<microseconds>(endFB - startFB).count();

        cout << "\n===== RESULTADOS =====\n";

        if (totalBT == 0) {
            cout << "No existe una " << k << "-coloracion valida.\n";
        } else {
            cout << "Total de " << k << "-coloraciones (Backtracking): " << totalBT << "\n";
            cout << "Primera solucion encontrada por Backtracking:\n";
            for (int v = 0; v < n; v++) {
                cout << "color[" << v << "] = " << firstSolutionBT[v] << "\n";
            }
        }

        cout << "\nFuerza Bruta confirma: " << totalFB << "\n";

        if (totalFB > 0) {
            cout << "Primera solucion encontrada por Fuerza Bruta:\n";
            for (int v = 0; v < n; v++) {
                cout << "color[" << v << "] = " << firstSolutionFB[v] << "\n";
            }
        }

        cout << "\nVerificacion de conteo: "
             << (totalBT == totalFB ? "COINCIDE" : "NO COINCIDE") << "\n";

        cout << "\nEstados explorados:\n";
        cout << "Backtracking: " << nodesBT << "\n";
        cout << "Fuerza Bruta: " << nodesFB << "\n";

        cout << "\nTiempos de ejecucion:\n";
        cout << "Backtracking: " << durationBT << " microsegundos\n";
        cout << "Fuerza Bruta: " << durationFB << " microsegundos\n";
    }
};

int main() {
    int n, k;
    cout << "Ingrese numero de vertices n: ";
    cin >> n;
    cout << "Ingrese numero de colores k: ";
    cin >> k;

    vector<vector<int>> adj(n, vector<int>(n));
    cout << "Ingrese la matriz de adyacencia (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> adj[i][j];
        }
    }

    GraphColoring solver(n, k, adj);
    solver.solveAndPrint();

    return 0;
}