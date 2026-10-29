#include "../include/algoritmos.hpp"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main() {
    vector<int> tamanios = {1000, 10000, 100000};
    vector<string> patrones = {"Aleatorio", "Ascendente", "Descendente", "CasiOrdenado", "Duplicados"};
    int repeticiones = 30;
    unsigned int semilla_base = 42;

    ofstream archivo("results/resultados_mediciones.csv");
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo crear el archivo CSV en results/" << endl;
        return 1;
    }

    archivo << "algoritmo,n,patron,repeticion,tiempo_ms,comparaciones,intercambios,profundidad_recursion,semilla\n";

    for (int n : tamanios) {
        for (const string& patron : patrones) {
            for (int rep = 1; rep <= repeticiones; rep++) {
                unsigned int semilla = semilla_base + rep + n;
                vector<int> original;

                if (patron == "Aleatorio") original = generarAleatorio(n, semilla);
                else if (patron == "Ascendente") original = generarAscendente(n);
                else if (patron == "Descendente") original = generarDescendente(n);
                else if (patron == "CasiOrdenado") original = generarCasiOrdenado(n, semilla);
                else if (patron == "Duplicados") original = generarConDuplicados(n, semilla);

                // Shellsort
                {
                    vector<int> copia = original;
                    Metricas m;
                    auto inicio = chrono::high_resolution_clock::now();
                    shellSort(copia, m);
                    auto fin = chrono::high_resolution_clock::now();
                    m.tiempo_ms = chrono::duration<double, milli>(fin - inicio).count();

                    archivo << "Shellsort," << n << "," << patron << "," << rep << ","
                            << m.tiempo_ms << "," << m.comparaciones << "," << m.intercambios << ","
                            << m.profundidad_recursion << "," << semilla << "\n";
                }

                // Quicksort
                {
                    vector<int> copia = original;
                    Metricas m;
                    auto inicio = chrono::high_resolution_clock::now();
                    quickNut(copia, 0, n - 1, m, 0);
                    auto fin = chrono::high_resolution_clock::now();
                    m.tiempo_ms = chrono::duration<double, milli>(fin - inicio).count();

                    archivo << "Quicksort," << n << "," << patron << "," << rep << ","
                            << m.tiempo_ms << "," << m.comparaciones << "," << m.intercambios << ","
                            << m.profundidad_recursion << "," << semilla << "\n";
                }
            }
        }
        cout << "[Completado] Procesado n = " << n << endl;
    }

    archivo.close();
    cout << "¡Experimentos finalizados! Datos guardados en results/resultados_mediciones.csv" << endl;
    return 0;
}