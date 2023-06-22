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
    auto duration = duration_cast<microseconds>(stop - start);

    piApproximation = 4.0 * pointsInsideCircle / numPoints;

    cout << fixed << setprecision(6);
    cout << "El valor aproximado de pi es: " << piApproximation << endl;
    cout << "Tiempo de ejecución: " << duration.count() << "microsegundos" << endl;

}
void monteCarloParallel() {
    cout << "Haz seleccionado el metodo de Monte Carlo paralelizado.\n";
    int numPoints;
    double x, y, distance, piApproximation;
    cout << "Ingrese la cantidad de puntos a generar: ";
    cin >> numPoints;

    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0, 1.0);

    int pointsInsideCircle = 0;

    auto start = high_resolution_clock::now(); // Inicio del cronómetro

    #pragma omp parallel
{
    #pragma omp for private(x, y, distance) reduction(+:pointsInsideCircle) schedule(static)
    for (int i = 0; i < numPoints; ++i) {
        x = distribution(generator);
        y = distribution(generator);
        distance = x * x + y * y;

        if (distance <= 1)
            pointsInsideCircle++;
    }
}

    auto stop = high_resolution_clock::now(); // Fin del cronómetro
    auto duration = duration_cast<microseconds>(stop - start);

    piApproximation = 4.0 * pointsInsideCircle / numPoints;

    cout << fixed << setprecision(6);

    cout << "El valor aproximado de pi es: " << piApproximation << endl;
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;
}
double calcularPi_serial(int iteraciones) {
    double pi = 0.0;
    double signo = 1.0;

    for (int i = 0; i < iteraciones; i++) {
        pi += signo / (2.0 * i + 1.0);
        signo *= -1.0;
    }

    return pi * 4.0;
}
void leibnizSeries() {
    cout << "Haz seleccionado el metodo de series de Leibniz (no paralelizado).\n";
    int iteraciones;
    cout << "Ingrese el número de iteraciones para aproximar PI: ";
    cin >> iteraciones;

    auto start = high_resolution_clock::now();
    double pi = calcularPi_serial(iteraciones);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Valor aproximado de PI: " << pi << endl;
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;
}
double calcularPi_paralelo(int iteraciones) {
    double pi = 0.0;
    double signo = 1.0;

    #pragma omp parallel
    {
        #pragma omp for reduction(+:pi) schedule(static) num_threads(omp_get_max_threads())
        for (int i = 0; i < iteraciones; i++) {
            double term = signo / (2.0 * i + 1.0);
            pi += term;
            signo *= -1.0;
        }
    }

    return pi * 4.0;
}
void leibnizParallel() {
    cout << "Haz seleccionado el metodo de series de Leibniz (paralelizado).\n";
    int iteraciones;
    cout << "Ingrese el número de iteraciones para aproximar PI: ";
    cin >> iteraciones;

    auto start = high_resolution_clock::now();
    double pi = calcularPi_paralelo(iteraciones);
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Valor aproximado de PI: " << pi << endl;
    cout << "Tiempo de ejecucion: " << duration.count() << " microsegundos" << endl;
}
void banner(){
    std::cout << "***************************************" << std::endl;
    std::cout << "*                                     *" << std::endl;
    std::cout << "*       Kevin Andres Labra Soto       *" << std::endl;
    std::cout << "*             18.355.485-9            *" << std::endl;
    std::cout << "*             Estudiante              *" << std::endl;
    std::cout << "*                                     *" << std::endl;
    std::cout << "***************************************" << std::endl;
}



int main() {
    banner();
    int choice;

    while (true) {
        // Display the menu
        cout << "Menu:\n";
        cout << "1. Metodo de Monte Carlo serializado\n";
        cout << "2. Metodo de Monte Carlo paralelizado\n";
        cout << "3. Series de Leibniz (serializado)\n";
        cout << "4. Series de Leibniz (paralelizado)\n";
        cout << "5. Salir\n";
        cout << "Seleccione su opcion: ";

        cin >> choice;

        // Execute the corresponding option based on the user's choice
        switch (choice) {
            case 1:
                monteCarloSeries();
                break;

            case 2:
                monteCarloParallel();
                break;

            case 3:
                leibnizSeries();
                break;

            case 4:
                leibnizParallel();
                break;

            case 5:
                cout << "Saliendo...\n";
                return 0;

            default:
                cout << "Opcion invalida , porfavor intentelo denuevo.\n";
        }

        cout << endl;
    }

    return 0;
}

