#ifndef ALGORITMOS_HPP
#define ALGORITMOS_HPP

#include <vector>
#include <string>
#include <chrono>
#include <random>

using namespace std;

// Estructura para registrar las métricas del experimento
struct Metricas {
    double tiempo_ms;
    long long comparaciones;
    long long intercambios;
    int profundidad_recursion;
};

// Declaración de los algoritmos
void shellSort(vector<int>& arr, Metricas& m);
void quickNut(vector<int>& arr, int low, int high, Metricas& m, int profundidad_actual);

// Funciones para generar los patrones de entrada
vector<int> generarAleatorio(int n, unsigned int semilla);
vector<int> generarAscendente(int n);
vector<int> generarDescendente(int n);
vector<int> generarCasiOrdenado(int n, unsigned int semilla);
vector<int> generarConDuplicados(int n, unsigned int semilla);

#endif