#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

// ============================================================================
// HEUN METHOD (RK2) - Método de Heun para ecuaciones diferenciales ordinarias
// dy/dx = f(x,y)  con condición inicial y(a) = y0
// Orden de error: O(h³) local, O(h²) global
// ============================================================================

// EDITA AQUÍ: Define tu función f(x,y)
// Por defecto: dy/dx = -2xy
double f(double x, double y) {
    return -2.0 * x * y;
}

// Solución exacta (si existe) para comparación de errores
// Para dy/dx = -2xy, la solución exacta es y(x) = y0 * exp(-x²)
// Si no existe solución exacta, retorna NAN
double solucion_exacta(double x, double y0) {
    return y0 * exp(-x * x);
}

void heun_metodo(double a, double b, int n, double y0) {
    // Validaciones de entrada
    if (a >= b) {
        cerr << "Error: El límite inferior (a) debe ser menor que el superior (b)." << endl;
        return;
    }
    if (n <= 0) {
        cerr << "Error: El número de pasos (n) debe ser positivo." << endl;
        return;
    }

    double h = (b - a) / n;
    vector<double> x(n+1), y(n+1), y_exacta(n+1);
    
    x[0] = a;
    y[0] = y0;
    y_exacta[0] = solucion_exacta(a, y0);

    // Método de Heun (RK2):
    // Predictor: y_pred = y[i] + h*f(x[i], y[i])
    // Corrector: y[i+1] = y[i] + h*(f(x[i], y[i]) + f(x[i+1], y_pred))/2
    for (int i = 0; i < n; i++) {
        double k1 = f(x[i], y[i]);
        double y_pred = y[i] + h * k1;
        double k2 = f(x[i] + h, y_pred);
        
        x[i+1] = x[i] + h;
        y[i+1] = y[i] + h * (k1 + k2) / 2.0;
        y_exacta[i+1] = solucion_exacta(x[i+1], y0);

        // Validación numérica
        if (!isfinite(y[i+1])) {
            cerr << "Advertencia: Valor no finito en paso " << i+1 << ". Inestabilidad numérica detectada." << endl;
            return;
        }
    }

    // Mostrar resultados
    cout << fixed << setprecision(10);
    cout << "\n" << string(100, '=') << endl;
    cout << "MÉTODO DE HEUN (RK2) - Ecuación diferencial: dy/dx = -2xy" << endl;
    cout << "Intervalo: [" << a << ", " << b << "]  |  Pasos: " << n << "  |  h = " << h << endl;
    cout << "Condición inicial: y(" << a << ") = " << y0 << endl;
    cout << "Orden de error local: O(h³)  |  Orden global: O(h²)" << endl;
    cout << string(100, '=') << endl;

    // Encabezado de tabla
    cout << setw(6) << "i"
         << setw(14) << "x"
         << setw(18) << "y (Heun)"
         << setw(18) << "y (Exacta)"
         << setw(16) << "Error Absoluto"
         << endl;
    cout << string(100, '-') << endl;

    // Lambda para decidir qué filas mostrar: primeras 3, últimas 2, cada 10%
    auto debe_mostrar = [&](int i) -> bool {
        // Primeras 3 filas
        if (i < 3) return true;
        // Últimas 2 filas
        if (i > n - 3) return true;
        // Cada 10% del total
        if (n % 10 == 0) {
            if (i % (n / 10) == 0) return true;
        }
        return false;
    };

    // Mostrar tabla
    for (int i = 0; i <= n; i++) {
        if (debe_mostrar(i)) {
            double error = fabs(y[i] - y_exacta[i]);
            cout << setw(6) << i
                 << setw(14) << x[i]
                 << setw(18) << y[i]
                 << setw(18) << y_exacta[i]
                 << setw(16) << error
                 << endl;
        }
    }
    cout << string(100, '=') << endl;

    // Estadísticas de error
    double error_max = 0.0, error_promedio = 0.0;
    for (int i = 0; i <= n; i++) {
        double error = fabs(y[i] - y_exacta[i]);
        error_max = max(error_max, error);
        error_promedio += error;
    }
    error_promedio /= (n + 1);

    cout << "\nESTADÍSTICAS DE ERROR:" << endl;
    cout << "  Error máximo:   " << error_max << endl;
    cout << "  Error promedio: " << error_promedio << endl;
    cout << "\nNota: Heun es orden O(h²) global. Es mejor que Euler pero menos preciso que RK4." << endl;

    // ========== GUARDAR EN ARCHIVO ==========
    // Crear nombre de archivo: heun_h.txt (ej: heun_0.01.txt)
    ostringstream filename_stream;
    filename_stream << fixed << setprecision(2) << "heun_" << h << ".txt";
    string filename = filename_stream.str();
    
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "\nError: No se pudo crear el archivo " << filename << endl;
        return;
    }
    
    // Escribir encabezado
    outfile << "x,y\n";
    
    // Escribir datos
    outfile << fixed << setprecision(10);
    for (int i = 0; i <= n; i++) {
        outfile << x[i] << "," << y[i] << "\n";
    }
    
    outfile.close();
    cout << "\n✓ Datos guardados en: " << filename << "\n";
}

int main() {
    double a, b, y0;
    int opcion;

    cout << "\n" << string(100, '=') << endl;
    cout << "MÉTODO DE HEUN (RK2) PARA ECUACIONES DIFERENCIALES ORDINARIAS" << endl;
    cout << string(100, '=') << endl;

    // Entrada de parámetros
    cout << "\nIngrese el intervalo [a, b]:" << endl;
    cout << "  a = ";
    if (!(cin >> a)) {
        cerr << "Error: Entrada inválida para a." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }

    cout << "  b = ";
    if (!(cin >> b)) {
        cerr << "Error: Entrada inválida para b." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }

    cout << "\nIngrese la condición inicial y(a) = ";
    if (!(cin >> y0)) {
        cerr << "Error: Entrada inválida para y0." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }

    // Opción: ingresar h o n
    cout << "\n¿Desea ingresar el tamaño de paso (h) o el número de pasos (n)?" << endl;
    cout << "  1) Ingresar h (tamaño de paso)" << endl;
    cout << "  2) Ingresar n (número de pasos)" << endl;
    cout << "  Seleccione (1 o 2): ";
    if (!(cin >> opcion)) {
        cerr << "Error: Entrada inválida." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }

    int n;
    if (opcion == 1) {
        double h;
        cout << "  Ingrese h: ";
        if (!(cin >> h)) {
            cerr << "Error: Entrada inválida para h." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return 1;
        }
        if (h <= 0) {
            cerr << "Error: h debe ser positivo." << endl;
            return 1;
        }
        n = (int)ceil((b - a) / h);
    } else if (opcion == 2) {
        cout << "  Ingrese n: ";
        if (!(cin >> n)) {
            cerr << "Error: Entrada inválida para n." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return 1;
        }
        if (n <= 0) {
            cerr << "Error: n debe ser positivo." << endl;
            return 1;
        }
    } else {
        cerr << "Error: Opción no válida." << endl;
        return 1;
    }

    // Resolver y mostrar resultados
    heun_metodo(a, b, n, y0);

    return 0;
}
