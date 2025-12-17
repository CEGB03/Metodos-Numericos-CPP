#include <iostream>
#include <math.h>
#include <iomanip>
#define FILAS 20

using namespace std;

/**
 * FUNCIÓN DE PRUEBA
 * Función matemática f(x) = x² + 1 utilizada para demostrar los métodos
 * Su integral exacta es: ∫(x² + 1)dx = x³/3 + x + C
 */
double funcion(double x){
    return (pow(x,2) + 1);
}

// Declaraciones de funciones   
void trapecioTabla();
bool sonEquidistantes(double arreglo[FILAS][2], int filas);
void leerDatos(double m[FILAS][2], int* filas);
void mostrarMenu();
void mostrarDocumentacion();

int main(int argc, char *argv[]) {
    mostrarMenu();
    return 0;
}

void mostrarMenu(){
    int opcion;
    bool salir = false;
    
    while(!salir) {
        cout << "\n╔══════════════════════════════════════════════════╗" << endl;
        cout << "║        INTEGRACIÓN NUMÉRICA (NEWTON-COTES)       ║" << endl;
        cout << "╚══════════════════════════════════════════════════╝" << endl;
        cout << "2. Trapecio - Tabla de datos" << endl;
        trapecioTabla();
        cout << "¡Hasta luego!" << endl; salir = true;
    }
}

/**
 * MÉTODO DEL TRAPECIO CON TABLA DE DATOS
 * Integra usando puntos discretos (x,y)
 * Maneja tanto datos equidistantes como no equidistantes
 */
void trapecioTabla(){
    double m[FILAS][2];
	// Tabla de datos original
	//   x	            T
	m[0][0] = 0;	m[0][1] = 20;
	m[1][0] = 0.5;	m[1][1] = 25;
	m[2][0] = 1;	m[2][1] = 22;
	m[3][0] = 1.5;	m[3][1] = 26;
    int filas=4;
    
    cout << "\n🔧 REGLA DEL TRAPECIO - TABLA DE DATOS" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    // Mostrar datos ingresados
    cout << "\n📋 Datos ingresados:" << endl;
    for(int i = 0; i < filas; i++){
        cout << "(" << m[i][0] << ", " << m[i][1] << ")" << endl;
    }
    
    bool flag = sonEquidistantes(m, filas);
    double suma; 
    
    if(flag){
        cout << "\n✅ Puntos equidistantes - Usando fórmula compuesta" << endl;
        double h = m[1][0] - m[0][0];
        suma = m[0][1] + m[filas-1][1];
        
        cout << "Limites de integracion: [" << m[0][0] << ", " << m[filas-1][0] << "]" << endl;
        cout << "h = " << h << endl;
        cout << "f(x₀) + f(xₙ) = " << m[0][1] << " + " << m[filas-1][1] << " = " << suma << endl;
        
        for(int i = 1; i < filas-1; i++){
            suma += 2 * m[i][1];
            cout << "2·f(x" << i << ") = 2·" << m[i][1] << " = " << (2*m[i][1]) << endl;
        }
        
           double integral = (h/2) * suma;
           cout << "\n📊 Integral ≈ (h/2) × suma = (" << h << "/2) × " << suma << " = " << integral << endl;
           cout << std::fixed << std::setprecision(10)
               << "Integral (10 decimales): " << integral << endl;
    } else {
        cout << "\n⚠️ Puntos NO equidistantes - Usando suma de trapecios individuales" << endl;
        suma = 0; 
        
        for(int i = 0; i < filas-1; i++){
            double h_i = m[i+1][0] - m[i][0];
            double trapecio_i = (h_i/2) * (m[i][1] + m[i+1][1]);
            suma += trapecio_i;
            cout << "Trapecio " << (i+1) << ": [" << m[i][0] << "," << m[i+1][0] 
                 << "] = (" << h_i << "/2)×(" << m[i][1] << "+" << m[i+1][1] << ") = " << trapecio_i << endl;
        }
        
        cout << "\n📊 Integral total ≈ " << suma << endl;
        cout << std::fixed << std::setprecision(10)
             << "Integral (10 decimales): " << suma << endl;
    }
}

/**
 * FUNCIÓN AUXILIAR: Verificar si los puntos están equidistantes
 * Importante para determinar si se puede aplicar Simpson
 */
bool sonEquidistantes(double arreglo[FILAS][2], int filas){
    if(filas < 2) return true;
    
    double diferencia = arreglo[1][0] - arreglo[0][0];
    const double tolerancia = 1e-10;  // Tolerancia para errores de redondeo
    
    for(int i = 1; i < filas - 1; i++) {
        double diff_actual = arreglo[i + 1][0] - arreglo[i][0];
        if(fabs(diff_actual - diferencia) > tolerancia) {
            return false;
        }
    }
    return true;
}