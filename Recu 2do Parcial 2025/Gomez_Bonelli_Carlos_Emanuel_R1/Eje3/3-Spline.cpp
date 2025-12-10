#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

const int N = 5; // Número de puntos

// Estructura para almacenar coeficientes del spline
struct Spline {
    double a, b, c, d; // Coeficientes: a + b(x-xi) + c(x-xi)² + d(x-xi)³
};

void splineCubicaNatural(double x[], double y[], int n, Spline splines[]) {
    double h[N-1], alpha[N-1], l[N], mu[N], z[N];
    
    // Paso 1: Calcular diferencias h[i] = x[i+1] - x[i]
    for (int i = 0; i < n-1; i++) {
        h[i] = x[i+1] - x[i];
    }
    
    // Paso 2: Calcular alpha[i]
    for (int i = 1; i < n-1; i++) {
        alpha[i] = (3.0/h[i])*(y[i+1]-y[i]) - (3.0/h[i-1])*(y[i]-y[i-1]);
    }
    
    // Paso 3: Resolver sistema tridiagonal
    l[0] = 1.0;
    mu[0] = 0.0;
    z[0] = 0.0;
    
    for (int i = 1; i < n-1; i++) {
        l[i] = 2.0*(x[i+1]-x[i-1]) - h[i-1]*mu[i-1];
        mu[i] = h[i]/l[i];
        z[i] = (alpha[i] - h[i-1]*z[i-1])/l[i];
    }
    
    l[n-1] = 1.0;
    z[n-1] = 0.0;
    
    // Paso 4: Calcular coeficientes c (segundas derivadas)
    double c[N] = {0.0};
    c[n-1] = 0.0;
    
    for (int j = n-2; j >= 0; j--) {
        c[j] = z[j] - mu[j]*c[j+1];
    }
    
    // Paso 5: Calcular coeficientes a, b, d
    for (int i = 0; i < n-1; i++) {
        splines[i].a = y[i];
        splines[i].b = (y[i+1]-y[i])/h[i] - h[i]*(c[i+1]+2.0*c[i])/3.0;
        splines[i].c = c[i];
        splines[i].d = (c[i+1]-c[i])/(3.0*h[i]);
    }
}

// Función para evaluar el spline en un punto x
double evaluarSpline(double x, double x_data[], Spline splines[], int n) {
    // Encontrar el intervalo correcto
    int intervalo = 0;
    for (int i = 0; i < n-1; i++) {
        if (x >= x_data[i] && x <= x_data[i+1]) {
            intervalo = i;
            break;
        }
    }
    
    double dx = x - x_data[intervalo];
    Spline s = splines[intervalo];
    
    return s.a + s.b*dx + s.c*dx*dx + s.d*dx*dx*dx;
}

// Función para mostrar los polinomios del spline
void mostrarPolinomiosSpline(double x[], Spline splines[], int n) {
    cout << "\n=== POLINOMIOS SPLINE CÚBICA NATURAL ===" << endl;
    
    for (int i = 0; i < n-1; i++) {
        cout << "Para t ∈ [" << x[i] << ", " << x[i+1] << "]:" << endl;
        cout << "S" << i << "(t) = ";
        
        cout << splines[i].a;
        
        if (splines[i].b >= 0) cout << " + " << splines[i].b;
        else cout << " - " << -splines[i].b;
        cout << "(t - " << x[i] << ")";
        
        if (splines[i].c >= 0) cout << " + " << splines[i].c;
        else cout << " - " << -splines[i].c;
        cout << "(t - " << x[i] << ")²";
        
        if (splines[i].d >= 0) cout << " + " << splines[i].d;
        else cout << " - " << -splines[i].d;
        cout << "(t - " << x[i] << ")³";
        
        cout << endl << endl;
    }
}

int main() {
    cout << "=== PROBLEMA 3 - INTERPOLACIÓN SPLINE CÚBICA ===" << endl;
    cout << "Estimación de velocidad en t = 10s" << endl << endl;
    
    // Datos de la tabla
    double tiempo[N] = {1, 3, 5, 7, 13};
    double velocidad[N] = {800, 2310, 3090, 3940, 4755};
    
    cout << "TABLA DE DATOS:" << endl;
    cout << "Tiempo (s)\tVelocidad (cm/s)" << endl;
    cout << "-------------------------------" << endl;
    for (int i = 0; i < N; i++) {
        cout << tiempo[i] << "\t\t" << velocidad[i] << endl;
    }
    
    // Calcular spline cúbica natural
    Spline splines[N-1];
    splineCubicaNatural(tiempo, velocidad, N, splines);
    
    // Mostrar polinomios
    mostrarPolinomiosSpline(tiempo, splines, N);
    
    // Estimar velocidad en t = 10s
    double t_estimado = 10.0;
    double v_estimado = evaluarSpline(t_estimado, tiempo, splines, N);
    
    cout << "=== ESTIMACIÓN EN t = 10s ===" << endl;
    cout << "Tiempo: " << t_estimado << " s" << endl;
    cout << "Velocidad estimada: " << fixed << setprecision(2) << v_estimado << " cm/s" << endl;
    
    // Determinar qué polinomio se usa
    int intervalo_usado = 0;
    for (int i = 0; i < N-1; i++) {
        if (t_estimado >= tiempo[i] && t_estimado <= tiempo[i+1]) {
            intervalo_usado = i;
            break;
        }
    }
    
    cout << "\nPolinomio usado: S" << intervalo_usado << "(t). Y desarrollado a mano en papel." << endl;
    cout << "Intervalo: [" << tiempo[intervalo_usado] << ", " << tiempo[intervalo_usado+1] << "]" << endl;
    
    // Verificación con puntos conocidos
    cout << "\n=== VERIFICACIÓN CON PUNTOS CONOCIDOS ===" << endl;
    cout << "Tiempo\tVelocidad Real\tVelocidad Spline\tError" << endl;
    cout << "------------------------------------------------" << endl;
    
    for (int i = 0; i < N; i++) {
        double v_spline = evaluarSpline(tiempo[i], tiempo, splines, N);
        double error = fabs(v_spline - velocidad[i]);
        cout << tiempo[i] << "\t" << velocidad[i] << "\t\t" 
            << fixed << setprecision(2) << v_spline << "\t\t" << error << endl;
    }
    
    return 0;
}

void mostrarPolinomiosExpandido(double x[], Spline splines[], int n) {
    cout << "\n=== POLINOMIOS EXPANDIDOS EN FUNCION DE t ===\n";

    for (int i = 0; i < n-1; i++) {
        double xi = x[i];
        double a = splines[i].a;
        double b = splines[i].b;
        double c = splines[i].c;
        double d = splines[i].d;

        // Coeficientes expandidos
        double A = d;
        double B = c - 3*d*xi;
        double C = b - 2*c*xi + 3*d*xi*xi;
        double D = a - b*xi + c*xi*xi - d*xi*xi*xi;

        cout << "Intervalo t ∈ [" << x[i] << ", " << x[i+1] << "]\n";
        cout << "S" << i << "(t) = "
             << A << "·t^3  "
             << (B>=0?" + ":" - ") << fabs(B) << "·t^2  "
             << (C>=0?" + ":" - ") << fabs(C) << "·t  "
             << (D>=0?" + ":" - ") << fabs(D);
        cout << "\n\n";
    }
}
