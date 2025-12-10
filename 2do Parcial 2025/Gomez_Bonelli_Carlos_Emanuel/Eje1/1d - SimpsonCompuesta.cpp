#include <iostream>
#include <math.h>
#include <iomanip>
#define FILAS 20

using namespace std;

// Declaraciones de funciones
void simpsonCompuestoTabla();
bool sonEquidistantes(double arreglo[FILAS][2], int filas);
void leerDatos(double m[FILAS][2], int* filas);
void mostrarMenu();

int main(int argc, char *argv[]) {
    mostrarMenu();
    return 0;
}

void mostrarMenu(){
    int opcion;
    cout << "\n=== MENÚ: INTEGRACIÓN NUMÉRICA (NEWTON-COTES) ===" << endl;
    cout << "4. Simpson Compuesto - Tabla de datos" << endl;
    cout << "5. Salir" << endl;
    cout << "Seleccione una opción: ";
    /* if(!(cin >> opcion)){
        cout << "Entrada inválida. Saliendo." << endl;
        cin.clear(); // Limpiar el estado de error
        cin.ignore(10000, '\n'); // Ignorar el resto de la línea
        return;
    } */

    opcion = 4;
    switch(opcion){
        case 4:
            simpsonCompuestoTabla();
            break;
        case 5:
            cout << "¡Hasta luego!" << endl;
            return;
        default:
            cout << "Opción inválida" << endl;
            break;
    }
    
    // Pausa antes de mostrar el menú nuevamente
    cout << "\nPresione Enter para continuar...";
    /* cin.ignore(); // Limpiar el buffer de entrada
    cin.get();    // Esperar a que el usuario presione Enter */

}

void leerDatos(double m[FILAS][2], int* filas){
    cout << "\nIngrese número de puntos: ";
    cin >> *filas;
    cout << "\nIngrese los datos (x, f(x)):" << endl;
    for(int i = 0; i < *filas; i++){
        cout << "Punto " << (i+1) << " - x: ";
        cin >> m[i][0];
        cout << "Punto " << (i+1) << " - f(x): ";
        cin >> m[i][1];
    }
}

/**
 * MÉTODO DE SIMPSON COMPUESTO CON TABLA DE DATOS
 * Requiere puntos equidistantes y número par de intervalos
 * Mayor precisión que trapecio para datos suaves
 */
void simpsonCompuestoTabla(){
    double m[5][2] = {
        {0.00, 0.0000},
        {0.25, 0.3166},
        {0.50, 0.7905},
        {0.75, 1.4433},
        {1.00, 2.2873}
    };
    int filas = 5;
    
    cout << "\n🔧 REGLA DE SIMPSON COMPUESTO - TABLA DE DATOS" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    
    if(filas < 3){
        cout << "❌ Error: Se necesitan al menos 3 puntos para Simpson" << endl;
        return;
    }
    
    if((filas-1) % 2 != 0){
        cout << "❌ Error: El número de intervalos (n = " << (filas-1) 
             << ") debe ser PAR" << endl;
        cout << "💡 Sugerencia: Use " << (filas-1) << " o " << (filas+1) << " puntos" << endl;
        return;
    }
    
    // Mostrar datos
    cout << "\n📋 Datos ingresados:" << endl;
    for(int i = 0; i < filas; i++){
        cout << "(" << m[i][0] << ", " << m[i][1] << ")" << endl;
    }
    
    bool flag = sonEquidistantes(m, filas);
    
    if(flag){
        cout << "\n✅ Puntos equidistantes - Aplicando Simpson compuesto" << endl;
        
        double h = m[1][0] - m[0][0];
        double suma = m[0][1] + m[filas-1][1];
        
        cout << "h = " << h << endl;
        cout << "f(x₀) + f(xₙ) = " << m[0][1] << " + " << m[filas-1][1] << " = " << suma << endl;
        cout << "Patrón de coeficientes: 1-4-2-4-2-...-4-1" << endl;
        
        for(int i = 1; i <= filas-2; i++){
            if(i % 2 == 1){
                suma += 4 * m[i][1];
                cout << "4·f(x" << i << ") = 4·" << m[i][1] << " = " << (4*m[i][1]) << " (índice impar)" << endl;
            } else {
                suma += 2 * m[i][1];
                cout << "2·f(x" << i << ") = 2·" << m[i][1] << " = " << (2*m[i][1]) << " (índice par)" << endl;
            }
        }
        
        double integral = (h/3) * suma;
        
        cout << "\n✅ RESULTADOS:" << endl;
        cout << "────────────────────────────────────────" << endl;
        cout << "Paso (h): " << h << endl;
        cout << "Suma total: " << suma << endl;
        cout << "Integral ≈ (h/3) × suma = (" << h << "/3) × " << suma << " = " << integral << endl;
        
        // CÁLCULO DEL ERROR PARA EL PROBLEMA 1d
        double I_exacta = 0.9093306736;
        double error_absoluto = fabs(integral - I_exacta);
        
        cout << fixed << setprecision(10);
        cout << "\n📊 ANÁLISIS DE ERROR (Problema 1d):" << endl;
        cout << "Valor exacto: " << I_exacta << endl;
        cout << "Valor aproximado: " << integral << endl;
        cout << "Error absoluto: " << error_absoluto << endl;
        
    } else {
        cout << "❌ Error: Simpson compuesto requiere puntos EQUIDISTANTES" << endl;
        cout << "💡 Sugerencia: Use el método del trapecio para puntos no equidistantes" << endl;
        cout << "📊 Diferencias encontradas entre puntos:" << endl;
        for(int i = 1; i < filas; i++){
            cout << "   Δx" << i << " = " << (m[i][0] - m[i-1][0]) << endl;
        }
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