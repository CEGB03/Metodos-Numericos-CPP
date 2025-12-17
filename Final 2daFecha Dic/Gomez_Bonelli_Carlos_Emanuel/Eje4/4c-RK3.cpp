#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;
double f1(double /*x*/, double /*y1*/, double y2) {
    // y1' = y2
    return y2;
}

double f2(double x, double y1, double y2) {
    // y2' = x - 5 y2 - 4 y1
    return x - 5.0*y2 - 4.0*y1;
}
double y_exacta(double x) {
    return -(17.0/48.0)*exp(-4.0*x)
           + (5.0/3.0)*exp(-x)
           + x/4.0
           - 5.0/16.0;
}


void rk3_sistema(double a, double b, int n, double y10, double y20) {
    double h = (b - a) / n;
    vector<double> x(n+1), y1(n+1), y2(n+1);
    x[0]=a; y1[0]=y10; y2[0]=y20;

    cout << fixed << setprecision(10);

    cout << "\n╔═══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║  RK3 SISTEMA 2×2  │  h = " << setw(12) << h << "  │  pasos = " << setw(6) << n << "         ║\n";
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
    vector<double> puntos_interes = {0.4, 5.0};
    
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
        double k11=h*f1(x[i],y1[i],y2[i]);
        double k12=h*f2(x[i],y1[i],y2[i]);

        double k21=h*f1(x[i]+h/2, y1[i]+k11/2, y2[i]+k12/2);
        double k22=h*f2(x[i]+h/2, y1[i]+k11/2, y2[i]+k12/2);

        double k31=h*f1(x[i]+h, y1[i]-k11+2*k21, y2[i]-k12+2*k22);
        double k32=h*f2(x[i]+h, y1[i]-k11+2*k21, y2[i]-k12+2*k22);

        x[i+1]  = x[i] + h;
        y1[i+1]= y1[i] + (1.0/6.0)*(k11 + 4*k21 + k31);
        y2[i+1]= y2[i] + (1.0/6.0)*(k12 + 4*k22 + k32);

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
            cout << "  V(" << setw(4) << xtarget << ") = " << setw(16) << y1[idx] << "\n";
        }
    };
    cout << "\n╔═══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║  VALORES SOLICITADOS                                                          ║\n";
    cout << "╚═══════════════════════════════════════════════════════════════════════════════╝\n";
    print_at(0.4);
    //print_at(5.0);
    //print_at(20.0);

    // ========== GUARDAR EN ARCHIVO ==========
    // Crear nombre de archivo: rk3_h.txt (ej: rk3_0.01.txt)
    ostringstream filename_stream;
    filename_stream << fixed << setprecision(2) << "rk3_" << h << ".txt";
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

        // ========== GUARDAR SOLUCIÓN EXACTA ==========
    ostringstream filename_exact_stream;
    filename_exact_stream << fixed << setprecision(2) << "exacta_" << h << ".txt";
    string filename_exact = filename_exact_stream.str();

    ofstream outfile_exact(filename_exact);
    if (!outfile_exact.is_open()) {
        cerr << "Error: No se pudo crear el archivo " << filename_exact << endl;
        return;
    }

    outfile_exact << "x,y\n";
    outfile_exact << fixed << setprecision(10);

    for (int i = 0; i <= n; i++) {
        outfile_exact << x[i] << "," << y_exacta(x[i]) << "\n";
    }

    outfile_exact.close();
    cout << "✓ Solución exacta guardada en: " << filename_exact << "\n";

}

int main() {
    double a=0,b=1,y10=1.0,y20=0.0,h=0.01; int n;
    n=(b-a)/h;
    cout << "a=0  b=5: "; /*cin>>a>>b; if (b<=a) return 0;*/
    cout << "y1(a) y2(a): ";/*  cin>>y10>>y20; */
    cout << "¿ingresar n (n) o h (h)? ";/*  cin>>modo; */
    /* if (modo=='h') { cin>>h; n = (int)ceil((b-a)/h); h=(b-a)/n; }
    else { cin>>n; if (n<=0) return 0; h=(b-a)/n; } */
    rk3_sistema(a,b,n,y10,y20);
}