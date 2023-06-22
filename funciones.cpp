#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include "funciones.h"


using namespace std;
using namespace std::chrono;

// Function definitions
void monteCarloSeries() {
    cout << "Haz seleccionado el metodo de Montecarlo (solucion en serie).\n";
    int numPoints;
    double x, y, distance, piApproximation;

    cout << "Ingrese la cantidad de puntos a generar: ";
    cin >> numPoints;

    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);

    int pointsInsideCircle = 0;

    auto start = high_resolution_clock::now(); // Inicio del cronómetro

    for (int i = 0; i < numPoints; ++i) {
        x = distribution(generator);
        y = distribution(generator);
        distance = x * x + y * y;

        if (distance <= 1)
            pointsInsideCircle++;
    }

    auto stop = high_resolution_clock::now(); // Fin del cronómetro
    auto duration = duration_cast<milliseconds>(stop - start);

    piApproximation = 4.0 * pointsInsideCircle / numPoints;

    cout << fixed << setprecision(6);
    cout << "El valor aproximado de pi es: " << piApproximation << endl;
    cout << "Tiempo de ejecución: " << duration.count() << "milisegundos" << endl;

}

void monteCarloParallel() {
    cout << "Monte Carlo parallel selected.\n";
    // Add your implementation for Monte Carlo parallel here
}

void leibnizSeries() {
    cout << "Leibniz series selected.\n";
    // Add your implementation for Leibniz series here
}

void leibnizParallel() {
    cout << "Leibniz parallel selected.\n";
    // Add your implementation for Leibniz parallel here
}
