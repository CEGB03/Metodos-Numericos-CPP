#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

// Constantes del enunciado (puedes editarlas rápido aquí)
const double L = 4.0;
const double D = 0.1123687877;
const double T0 = 100.0;
const double T1 = 20.0;

// EDITA AQUÍ: sistema dy1/dx = f1(x,y1,y2), dy2/dx = f2(x,y1,y2)
// Para este ejercicio usamos solo y1 (la temperatura T). y2 se deja en cero.
// dato de ingreso para este caso:
//      h=0.1
//  a b: 10 20
//  y1(a) y2(a): 60 0
//  ¿ingresar n (n) o h (h)? h 0.1
//  Valores solicitados:
//      T(15) ≈ 52.788
//      T(20) ≈ 42.6223
//      h=0.01
//  a b: 10 20
//  y1(a) y2(a): 60 0
//  ¿ingresar n (n) o h (h)? h 0.1
//  Valores solicitados:
//      T(15) ≈ 52.788
//      T(20) ≈ 42.6223
double f1(double x, double y1, double /*y2*/) {
    // dT/dt = (L^2/(D*pi^2)) * ln((T0 - T1)/(T(t) - T1)) - t
    // Usamos x como "t" y y1 como T(t)
    double numer = (T0 - T1);
    double denom = (y1 - T1);
    if (denom <= 0) return 0.0; // evita log de valor no positivo
    return (L * L / (D * M_PI * M_PI)) * log(numer / denom) - x;
}

double f2(double /*x*/, double /*y1*/, double /*y2*/) {
    // No se usa en este problema; se mantiene para compatibilidad
    return 0.0;
}

void rk4_sistema(double a, double b, int n, double y10, double y20) {
    double h = (b - a) / n;
    vector<double> x(n+1), y1(n+1), y2(n+1);
    x[0]=a; y1[0]=y10; y2[0]=y20;

    cout << fixed << setprecision(10);

    cout << "\n╔═══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║  RK4 SISTEMA 2×2  │  h = " << setw(12) << h << "  │  pasos = " << setw(6) << n << "         ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════════════════════╝\n\n";
    
    cout << setw(6) << "i" << " │ " 
         << setw(16) << "x[i]" << " │ " 
         << setw(16) << "y1[i]" << " │ " 
         << setw(16) << "y2[i]" << "\n";
    cout << string(80, '-') << "\n";
    
    cout << setw(6) << 0 << " │ " 
         << setw(16) << x[0] << " │ " 
         << setw(16) << y1[0] << " │ " 
         << setw(16) << y2[0] << "\n";

    // Valores de interés (puntos donde queremos ver detalle)
    vector<double> puntos_interes = {15.0, 20.0};
    
    // Lambda para decidir si mostrar una fila
    auto debe_mostrar = [&](int i) -> bool {
        if (i < 3 || i >= n-2) return true;  // Primeros y últimos
        if (i % max(1, n/10) == 0) return true;  // Cada 10%
        
        // Mostrar si está cerca de un punto de interés (±2 pasos)
        for (double punto : puntos_interes) {
            int idx_objetivo = static_cast<int>(round((punto - a) / h));
            if (abs(i - idx_objetivo) <= 2) return true;
        }
        return false;
    };

    for (int i=0;i<n;i++) {
        double k11=f1(x[i],y1[i],y2[i]);
        double k12=f2(x[i],y1[i],y2[i]);
        double k21=f1(x[i]+h/2, y1[i]+h*k11/2, y2[i]+h*k12/2);
        double k22=f2(x[i]+h/2, y1[i]+h*k11/2, y2[i]+h*k12/2);
        double k31=f1(x[i]+h/2, y1[i]+h*k21/2, y2[i]+h*k22/2);
        double k32=f2(x[i]+h/2, y1[i]+h*k21/2, y2[i]+h*k22/2);
        double k41=f1(x[i]+h,   y1[i]+h*k31,   y2[i]+h*k32);
        double k42=f2(x[i]+h,   y1[i]+h*k31,   y2[i]+h*k32);

        x[i+1] = x[i] + h;
        y1[i+1]= y1[i] + (h/6.0)*(k11+2*k21+2*k31+k41);
        y2[i+1]= y2[i] + (h/6.0)*(k12+2*k22+2*k32+k42);

        if (debe_mostrar(i+1))
            cout << setw(6) << i+1 << " │ " 
                 << setw(16) << x[i+1] << " │ " 
                 << setw(16) << y1[i+1] << " │ " 
                 << setw(16) << y2[i+1] << "\n";
    }
    
    cout << string(80, '-') << "\n";

    // Reportar valores en T=15 y T=20 si caen en la malla (h=0.1 o 0.01 los incluye)
    auto print_at = [&](double xtarget){
        if (xtarget < a || xtarget > b) return;
        int idx = static_cast<int>(round((xtarget - a) / h));
        if (idx >=0 && idx < static_cast<int>(y1.size())) {
            cout << "  T(" << setw(4) << xtarget << ") = " << setw(16) << y1[idx] << "\n";
        }
    };
    cout << "\n╔═══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║  VALORES SOLICITADOS                                                          ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════════════════════╝\n";
    print_at(15.0);
    print_at(20.0);

    // ========== GUARDAR EN ARCHIVO ==========
    // Crear nombre de archivo: rk4_h.txt (ej: rk4_0.01.txt)
    ostringstream filename_stream;
    filename_stream << fixed << setprecision(2) << "rk4_" << h << ".txt";
    string filename = filename_stream.str();
    
    ofstream outfile(filename);
    if (!outfile.is_open()) {
        cerr << "Error: No se pudo crear el archivo " << filename << endl;
        return;
    }
    
    // Escribir encabezado
    outfile << "x,y1,y2\n";
    
    // Escribir datos
    outfile << fixed << setprecision(10);
    for (int i = 0; i <= n; i++) {
        outfile << x[i] << "," << y1[i] << "," << y2[i] << "\n";
    }
    
    outfile.close();
    cout << "\n✓ Datos guardados en: " << filename << "\n";
}

int main() {
    double a,b,y10,y20,h; int n; char modo;
    cout << "a b: "; cin>>a>>b; if (b<=a) return 0;
    cout << "y1(a) y2(a): "; cin>>y10>>y20;
    cout << "¿ingresar n (n) o h (h)? "; cin>>modo;
    if (modo=='h') { cin>>h; n = (int)ceil((b-a)/h); h=(b-a)/n; }
    else { cin>>n; if (n<=0) return 0; h=(b-a)/n; }
    rk4_sistema(a,b,n,y10,y20);
}