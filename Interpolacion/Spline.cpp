// spline cubica

#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

// Estructura para almacenar coeficientes del spline
struct Spline {
    double a, b, c, d; // a + b(x-xi) + c(x-xi)^2 + d(x-xi)^3
};

// Calcula spline cúbica natural (x creciente)
bool splineCubicaNatural(const vector<double>& x,
                         const vector<double>& y,
                         vector<Spline>& splines) {
    int n = static_cast<int>(x.size());
    if (n < 2 || y.size() != x.size()) return false;

    // x creciente
    for (int i = 1; i < n; ++i) if (x[i] <= x[i-1]) return false;

    vector<double> h(n-1), alpha(n-1), l(n), mu(n), z(n), c(n, 0.0);

    for (int i = 0; i < n-1; ++i) h[i] = x[i+1] - x[i];
    for (int i = 1; i < n-1; ++i)
        alpha[i] = (3.0/h[i])*(y[i+1]-y[i]) - (3.0/h[i-1])*(y[i]-y[i-1]);

    l[0] = 1.0; mu[0] = 0.0; z[0] = 0.0;
    for (int i = 1; i < n-1; ++i) {
        l[i] = 2.0*(x[i+1]-x[i-1]) - h[i-1]*mu[i-1];
        if (fabs(l[i]) < 1e-14) return false;
        mu[i] = h[i]/l[i];
        z[i] = (alpha[i] - h[i-1]*z[i-1]) / l[i];
    }
    l[n-1] = 1.0; z[n-1] = 0.0; c[n-1] = 0.0;
    for (int j = n-2; j >= 0; --j) c[j] = z[j] - mu[j]*c[j+1];

    splines.resize(n-1);
    for (int i = 0; i < n-1; ++i) {
        splines[i].a = y[i];
        splines[i].b = (y[i+1]-y[i])/h[i] - h[i]*(c[i+1] + 2.0*c[i]) / 3.0;
        splines[i].c = c[i];
        splines[i].d = (c[i+1]-c[i]) / (3.0*h[i]);
    }
    return true;
}

// Evalúa el spline, con aviso de extrapolación
double evaluarSpline(double xq, const vector<double>& x, const vector<Spline>& s) {
    int n = static_cast<int>(x.size());
    if (xq < x.front() || xq > x.back()) {
        cerr << "⚠️  x fuera de rango, extrapolando.\n";
    }
    int intervalo = n - 2;
    for (int i = 0; i < n-1; ++i) {
        bool in = (i == n-2) ? (xq >= x[i] && xq <= x[i+1])
                             : (xq >= x[i] && xq < x[i+1]);
        if (in) { intervalo = i; break; }
    }
    double dx = xq - x[intervalo];
    const Spline& sp = s[intervalo];
    return sp.a + sp.b*dx + sp.c*dx*dx + sp.d*dx*dx*dx;
}

void mostrarPolinomiosSpline(const vector<double>& x, const vector<Spline>& s) {
    cout << "\n=== POLINOMIOS SPLINE CUBICA NATURAL ===\n";
    for (size_t i = 0; i + 1 < x.size(); ++i) {
        cout << "Para t en [" << x[i] << ", " << x[i+1] << "]:\nS" << i << "(t) = ";
        cout << s[i].a
             << (s[i].b >= 0 ? " + " : " - ") << fabs(s[i].b) << "(t - " << x[i] << ")"
             << (s[i].c >= 0 ? " + " : " - ") << fabs(s[i].c) << "(t - " << x[i] << ")^2"
             << (s[i].d >= 0 ? " + " : " - ") << fabs(s[i].d) << "(t - " << x[i] << ")^3\n\n";
    }
}

void mostrarPolinomiosExpandido(const vector<double>& x, const vector<Spline>& s) {
    cout << "\n=== POLINOMIOS EXPANDIDOS EN t ===\n";
    for (size_t i = 0; i + 1 < x.size(); ++i) {
        double xi = x[i];
        double a = s[i].a, b = s[i].b, c = s[i].c, d = s[i].d;
        double A = d;
        double B = c - 3.0*d*xi;
        double C = b - 2.0*c*xi + 3.0*d*xi*xi;
        double D = a - b*xi + c*xi*xi - d*xi*xi*xi;
        cout << "Intervalo t en [" << x[i] << ", " << x[i+1] << "]\n";
        cout << "S" << i << "(t) = "
             << A << "*t^3  "
             << (B>=0 ? " + " : " - ") << fabs(B) << "*t^2  "
             << (C>=0 ? " + " : " - ") << fabs(C) << "*t  "
             << (D>=0 ? " + " : " - ") << fabs(D) << "\n\n";
    }
}

int main() {
    cout << "=== PROBLEMA 3 - INTERPOLACION SPLINE CUBICA ===\n";
    vector<double> tiempo = {1, 3, 5, 7, 13};
    vector<double> velocidad = {800, 2310, 3090, 3940, 4755};

    cout << "TABLA DE DATOS:\nTiempo (s)\tVelocidad (cm/s)\n-------------------------------\n";
    for (size_t i = 0; i < tiempo.size(); ++i)
        cout << tiempo[i] << "\t\t" << velocidad[i] << "\n";

    vector<Spline> splines;
    if (!splineCubicaNatural(tiempo, velocidad, splines)) {
        cerr << "Error al construir el spline (x no creciente o división por cero).\n";
        return 1;
    }

    mostrarPolinomiosSpline(tiempo, splines);
    mostrarPolinomiosExpandido(tiempo, splines);

    double t_estimado = 10.0;
    double v_estimado = evaluarSpline(t_estimado, tiempo, splines);
    cout << "=== ESTIMACION EN t = " << t_estimado << " ===\n";
    cout << "Velocidad estimada: " << fixed << setprecision(2) << v_estimado << " cm/s\n";

    // Verificación en nodos
    cout << "\n=== VERIFICACION EN NODOS ===\n";
    cout << "Tiempo\tVel Real\tVel Spline\tError\n";
    cout << "-----------------------------------------\n";
    double max_err = 0.0;
    for (size_t i = 0; i < tiempo.size(); ++i) {
        double v_spline = evaluarSpline(tiempo[i], tiempo, splines);
        double err = fabs(v_spline - velocidad[i]);
        max_err = max(max_err, err);
        cout << tiempo[i] << "\t" << velocidad[i] << "\t\t"
             << fixed << setprecision(2) << v_spline << "\t\t" << err << "\n";
    }
    cout << "Error maximo en nodos: " << max_err << "\n";
    return 0;
}
