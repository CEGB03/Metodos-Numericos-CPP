#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

/**
 * ═══════════════════════════════════════════════════════════════
 * MODIFICAR ESTA FUNCIÓN SEGÚN EL PARCIAL
 * ═══════════════════════════════════════════════════════════════
 * 
 * Define la ecuación diferencial: dy/dx = f(x, y)
 * 
 * EJEMPLOS DE EDOs:
 * 
 * 1. dy/dx = x*sqrt(y)
 *    return x * sqrt(fabs(y));
 * 
 * 2. dy/dx = x + y
 *    return x + y;
 * 
 * 3. dy/dx = -2*x*y  (solución exacta: y = e^(-x²))
 *    return -2.0 * x * y;
 * 
 * 4. Ley de Enfriamiento de Newton: dT/dt = -k*ln((T-T1)/(T0-T1)) - L
 *    (Necesita parámetros k, L, T0, T1)
 *    return -k * log((T - T1) / (T0 - T1)) - L;
 * 
 * 5. dy/dx = sin(x)*cos(y)
 *    return sin(x) * cos(y);
 * 
 * 6. dy/dx = 1 + y²  (tangente, singularidad en tiempo finito)
 *    return 1.0 + y*y;
 * 
 * ═══════════════════════════════════════════════════════════════
 */
double f(double x, double y) {
    // ═══ EDITA AQUÍ SEGÚN TU PROBLEMA ═══
    // Ejemplo: dy/dx = x*sqrt(y)
    
    if (y < 0) return 0;  // Protección si es necesaria
    return x * sqrt(y);
    
    // Otros ejemplos comentados:
    // return x + y;
    // return -2.0 * x * y;
    // return sin(x) * cos(y);
    // return 1.0 + y*y;
    // return -0.5 * log((y - 20.0) / (100.0 - 20.0)) - 4.0;  // Enfriamiento Newton (k=0.5, L=4, T0=100, T1=20)
}

/**
 * MÉTODO RUNGE-KUTTA ORDEN 4
 * Resuelve: dy/dx = f(x,y) con y(x0) = y0
 * 
 * Parámetros:
 *   a: punto inicial
 *   b: punto final
 *   n: número de pasos
 *   y0: condición inicial y(a)
 */
void rk4(double a, double b, int n, double y0) {
    double h = (b - a) / n;
    
    vector<double> x(n + 1), y(n + 1);
    x[0] = a;
    y[0] = y0;
    
    cout << "\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║          MÉTODO RUNGE-KUTTA ORDEN 4 (RK4)                    ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n📊 CONFIGURACIÓN:" << endl;
    cout << "   Intervalo: [" << fixed << setprecision(6) << a << ", " << b << "]" << endl;
    cout << "   Pasos: " << n << endl;
    cout << "   h = " << h << endl;
    cout << "   y(" << a << ") = " << y0 << endl;
    
    cout << "\n" << string(60, '─') << endl;
    cout << "i\t" << "x_i\t\t" << "y_i" << endl;
    cout << string(60, '─') << endl;
    
    cout << "0\t" << x[0] << "\t\t" << y[0] << endl;
    
    // ═══ CICLO RK4 ═══
    for (int i = 0; i < n; i++) {
        double k1 = f(x[i], y[i]);
        double k2 = f(x[i] + h/2.0, y[i] + (h/2.0)*k1);
        double k3 = f(x[i] + h/2.0, y[i] + (h/2.0)*k2);
        double k4 = f(x[i] + h, y[i] + h*k3);
        
        x[i + 1] = x[i] + h;
        y[i + 1] = y[i] + (h/6.0)*(k1 + 2.0*k2 + 2.0*k3 + k4);
        
        // Mostrar primeros, últimos y selectivos
        if (i < 5 || i >= n-5 || i % max(1, n/10) == 0) {
            cout << (i+1) << "\t" << x[i+1] << "\t\t" << y[i+1] << endl;
        }
    }
    
    cout << string(60, '─') << endl;
    
    cout << "\n✅ RESULTADO FINAL:" << endl;
    cout << "   y(" << b << ") = " << y[n] << endl;
    
    // ═══ TABLA RESUMIDA ═══
    cout << "\n📍 PUNTOS CLAVE:" << endl;
    cout << "x\t\t\ty(x)" << endl;
    cout << string(50, '─') << endl;
    
    vector<int> indices = {0, n/4, n/2, 3*n/4, n};
    for (int idx : indices) {
        if (idx >= 0 && idx <= n) {
            cout << x[idx] << "\t\t" << y[idx] << endl;
        }
    }
    
    // ═══ CONSULTA DE PUNTOS ═══
    cout << "\n🔍 CONSULTAR VALORES EN PUNTOS ESPECÍFICOS:" << endl;
    cout << "(Ingrese punto x de interés, o -1 para terminar)" << endl;
    
    double x_consulta;
    while (true) {
        cout << "\nx = ";
        if (!(cin >> x_consulta) || x_consulta == -1) break;
        
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (x_consulta < a || x_consulta > b) {
            cout << "❌ Fuera del intervalo [" << a << ", " << b << "]" << endl;
            continue;
        }
        
        // Buscar índice más cercano
        int idx = (int)round((x_consulta - a) / h);
        idx = max(0, min(n, idx));
        
        cout << "✓ y(" << x_consulta << ") ≈ " << y[idx] << "  (en x = " << x[idx] << ")" << endl;
    }
}

int main() {
    double a, b, y0, h;
    int n;
    char repetir;
    
    do {
        cout << "\n╔════════════════════════════════════════════════════════════════╗" << endl;
        cout << "║     MÉTODO RUNGE-KUTTA ORDEN 4 - PARA ECUACIONES DIFERENCIALES ║" << endl;
        cout << "║              Resuelve: dy/dx = f(x, y)                        ║" << endl;
        cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
        
        // ═══ INTERVALO ═══
        cout << "\n📍 INTERVALO DE INTEGRACIÓN [a, b]:" << endl;
        cout << "   a: ";
        while (!(cin >> a)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Entrada inválida. Ingrese a: ";
        }
        
        cout << "   b: ";
        while (!(cin >> b) || b <= a) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ b debe ser mayor que a (" << a << "): ";
        }
        
        // ═══ CONDICIÓN INICIAL ═══
        cout << "\n📌 CONDICIÓN INICIAL y(" << a << ") = y0:" << endl;
        cout << "   y0: ";
        while (!(cin >> y0)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Entrada inválida. Ingrese y0: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        // ═══ TAMAÑO DE PASO ═══
        cout << "\n📏 TAMAÑO DE PASO:" << endl;
        cout << "   1. Ingresar número de pasos (n)" << endl;
        cout << "   2. Ingresar tamaño de paso (h)" << endl;
        cout << "\n   Opción (1 o 2): ";
        
        char opcion_paso;
        while (!(cin >> opcion_paso) || (opcion_paso != '1' && opcion_paso != '2')) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "❌ Ingrese 1 o 2: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if (opcion_paso == '1') {
            cout << "   n: ";
            while (!(cin >> n) || n <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "❌ n debe ser positivo: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            h = (b - a) / n;
        } else {
            cout << "   h: ";
            while (!(cin >> h) || h <= 0 || h > (b - a)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "❌ h debe estar en (0, " << (b - a) << "]: ";
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            n = (int)ceil((b - a) / h);
            h = (b - a) / n;
        }
        
        // ═══ RESOLVER CON RK4 ═══
        rk4(a, b, n, y0);
        
        // ═══ REPETIR ═══
        cout << "\n¿Resolver otra ecuación? (S/N): ";
        cin >> repetir;
        
    } while (toupper(repetir) == 'S');
    
    cout << "\n¡Gracias por usar RK4!\n" << endl;
    
    return 0;
}

