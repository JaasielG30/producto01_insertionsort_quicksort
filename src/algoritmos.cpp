#include "../include/algoritmos.hpp"
#include <algorithm>

// --- SHELLSORT ---
void shellSort(vector<int>& arr, Metricas& m) {
    int n = arr.size();
    m.comparaciones = 0;
    m.intercambios = 0;
    m.profundidad_recursion = 0;

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            m.comparaciones++;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                m.comparaciones++;
                arr[j] = arr[j - gap];
                m.intercambios++;
            }
            arr[j] = temp;
        }
    }
}

// --- QUICKSORT ---
static void particionYOrdenar(vector<int>& arr, int low, int high, Metricas& m, int profundidad) {
    if (profundidad > m.profundidad_recursion) {
        m.profundidad_recursion = profundidad;
    }
    if (low >= high) return;

    int mid = low + (high - low) / 2;
    int pivot = arr[mid];
    int i = low;
    int j = high;

    while (i <= j) {
        while (true) {
            m.comparaciones++;
            if (arr[i] < pivot) i++;
            else break;
        }
        while (true) {
            m.comparaciones++;
            if (arr[j] > pivot) j--;
            else break;
        }
        if (i <= j) {
            swap(arr[i], arr[j]);
            m.intercambios++;
            i++;
            j--;
        }
    }

    if (low < j) particionYOrdenar(arr, low, j, m, profundidad + 1);
    if (i < high) particionYOrdenar(arr, i, high, m, profundidad + 1);
}

void quickNut(vector<int>& arr, int low, int high, Metricas& m, int profundidad_actual) {
    if (low == 0 && high == (int)arr.size() - 1) {
        m.comparaciones = 0;
        m.intercambios = 0;
        m.profundidad_recursion = 0;
    }
    particionYOrdenar(arr, low, high, m, profundidad_actual);
}

// --- GENERADORES DE PATRONES ---
vector<int> generarAleatorio(int n, unsigned int semilla) {
    vector<int> arr(n);
    mt19937 rng(semilla);
    uniform_int_distribution<int> dist(1, 1000000);
    for (int i = 0; i < n; i++) arr[i] = dist(rng);
    return arr;
}

vector<int> generarAscendente(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = i + 1;
    return arr;
}

vector<int> generarDescendente(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) arr[i] = n - i;
    return arr;
}

vector<int> generarCasiOrdenado(int n, unsigned int semilla) {
    vector<int> arr = generarAscendente(n);
    mt19937 rng(semilla);
    int intercambios = n * 0.05;
    for (int k = 0; k < intercambios; k++) {
        int idx1 = rng() % n;
        int idx2 = rng() % n;
        swap(arr[idx1], arr[idx2]);
    }
    return arr;
}

vector<int> generarConDuplicados(int n, unsigned int semilla) {
    vector<int> arr(n);
    mt19937 rng(semilla);
    uniform_int_distribution<int> dist(1, 15);
    for (int i = 0; i < n; i++) arr[i] = dist(rng);
    return arr;
}