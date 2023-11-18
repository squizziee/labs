#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
double f(double pi, double m, int k = 8) {
    return pi + pow(-1, k) * m;
}

double Lagrange(double x, int n, double x_arr[], double y_arr[]) {

    double sum = 0;
    for (int i = 0; i < n; ++i) {

        double l = 1;
        for (int j = 0; j < n; ++j)
            if (j != i)
                l *= (x - x_arr[j]) / (x_arr[i] - x_arr[j]);
        sum += y_arr[i] * l;
    }

    return sum;
}

double Newton(double x, int n, double x_arr[], double y_arr[]) {

    double sum = y_arr[0];
    for (int i = 1; i < n; ++i) {

        double F = 0;
        for (int j = 0; j <= i; ++j) {

            double den = 1;
            for (int k = 0; k <= i; ++k)
                if (k != j)
                    den *= (x_arr[j] - x_arr[k]);
            F += y_arr[j] / den;
        }

        for (int k = 0; k < i; ++k)
            F *= (x - x_arr[k]);
        sum += F;
    }
    return sum;
}

int main() {
    setlocale(LC_ALL, "Rus");
    const int N = 11;
    double p[N] = { 0.0, 0.41, 0.79, 1.13, 1.46, 1.76, 2.04, 2.30, 2.55, 2.79, 3.01 };
    double m = 4;

    double x_arr[N], y_arr[N];

    for (int i = 0; i < N; ++i) {
            x_arr[i] = i * 0.1;
        y_arr[i] = f(p[i], m);
    }

    cout << "Значение в точке 0,47(многочлен Лагранжа):" << endl << fixed << setprecision(15) << Lagrange(0.47, N, x_arr, y_arr) << endl;
    cout << endl;
    cout << "Значение в точке 0,47(многочлен Ньютона):" << endl << fixed << setprecision(15) << Newton(0.47, N, x_arr, y_arr) << endl;
}