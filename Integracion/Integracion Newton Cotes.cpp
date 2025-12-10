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
void trapecioFuncion();    
void trapecioTabla();
void simpsonCompuestoFuncion();
void simpsonCompuestoTabla();
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
        cout << "0. Ver documentación de métodos" << endl;
        cout << "1. Trapecio - Función conocida" << endl;
        cout << "2. Trapecio - Tabla de datos" << endl;
        cout << "3. Simpson Compuesto - Función conocida" << endl;
        cout << "4. Simpson Compuesto - Tabla de datos" << endl;
        cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        switch(opcion){
            case 0: mostrarDocumentacion(); break;
            case 1: trapecioFuncion(); break;
            case 2: trapecioTabla(); break;
            case 3: simpsonCompuestoFuncion(); break;
            case 4: simpsonCompuestoTabla(); break;
            case 5: cout << "¡Hasta luego!" << endl; salir = true; break;
            default: cout << "❌ Opción inválida" << endl; break;
        }
    }
}

void leerDatos(double m[FILAS][2], int* filas){
    cout << "\nIngrese número de puntos: ";
    cin >> *filas;
    
    if(*filas <= 0) {
        cout << "❌ Error: Número de puntos debe ser positivo" << endl;
        *filas = 0;
        return;
    }
    
    if(*filas > FILAS) {
        cout << "⚠️ Advertencia: Máximo " << FILAS << " puntos permitidos. Se limitará a " << FILAS << endl;
        *filas = FILAS;
    }
    
    cout << "\nIngrese los datos (x, f(x)):" << endl;
    for(int i = 0; i < *filas; i++){
        cout << "Punto " << (i+1) << " - x: ";
        cin >> m[i][0];
        cout << "Punto " << (i+1) << " - f(x): ";
        cin >> m[i][1];
    }
    
    // Ordenar datos por x en forma ascendente (burbuja simple)
    for(int i = 0; i < *filas - 1; i++) {
        for(int j = 0; j < *filas - 1 - i; j++) {
            if(m[j][0] > m[j+1][0]) {
                double temp_x = m[j][0], temp_y = m[j][1];
                m[j][0] = m[j+1][0];
                m[j][1] = m[j+1][1];
                m[j+1][0] = temp_x;
                m[j+1][1] = temp_y;
            }
        }
    }
    cout << "\n✅ Datos ordenados por x" << endl;
}

/**
 * MÉTODO DEL TRAPECIO CON FUNCIÓN CONOCIDA
 * Integra numéricamente f(x) = x² + 1 usando la regla del trapecio
 * Divide [a,b] en n subintervalos y aproxima con trapecios
 */
void trapecioFuncion(){
    double a, b;
    int n; 
    cout << "\n🔧 REGLA DEL TRAPECIO - FUNCIÓN CONOCIDA" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "Función: f(x) = x² + 1" << endl;
    cout << "Límite inferior (a): ";
    cin >> a;
    cout << "Límite superior (b): ";
    cin >> b;
    cout << "Número de subintervalos (n): ";
    cin >> n;
    
    if(n <= 0) {
        cout << "❌ Error: El número de subintervalos debe ser positivo" << endl;
        return;
    }
    
    if(a >= b) {
        cout << "❌ Error: El límite inferior (a) debe ser menor que el superior (b)" << endl;
        return;
    }
    
    double h = (b-a)/n;
    double suma = funcion(a) + funcion(b);
    
    cout << "\n📊 Cálculo paso a paso:" << endl;
    cout << "h = (b-a)/n = (" << b << "-" << a << ")/" << n << " = " << h << endl;
    cout << "f(a) = f(" << a << ") = " << funcion(a) << endl;
    cout << "f(b) = f(" << b << ") = " << funcion(b) << endl;
    
    for(int i = 1; i < n; i++){
        double xi = a + i*h;
        double fi = funcion(xi);
        suma += 2 * fi;
        cout << "2·f(" << xi << ") = 2·" << fi << " = " << (2*fi) << endl;
    }
    
    double integral = (h/2) * suma;
    
    cout << fixed << setprecision(6);
    cout << "\n✅ RESULTADOS:" << endl;
    cout << "────────────────────────────────────────" << endl;
    cout << "Paso (h): " << h << endl;
    cout << "Suma total: " << suma << endl;
    cout << "∫[" << a << "," << b << "] f(x)dx ≈ " << integral << endl;
    
    // Calcular valor exacto para comparación
    double exacto = (pow(b,3)/3 + b) - (pow(a,3)/3 + a);
    cout << "Valor exacto: " << exacto << endl;
    cout << "Error absoluto: " << fabs(integral - exacto) << endl;
    cout << "Error relativo: " << (fabs(integral - exacto)/fabs(exacto))*100 << "%" << endl;
}

/**
 * MÉTODO DEL TRAPECIO CON TABLA DE DATOS
 * Integra usando puntos discretos (x,y)
 * Maneja tanto datos equidistantes como no equidistantes
 */
void trapecioTabla(){
    double m[FILAS][2];
    int filas;
    
    cout << "\n🔧 REGLA DEL TRAPECIO - TABLA DE DATOS" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    leerDatos(m, &filas);
    
    if(filas <= 0){
        cout << "❌ Error: No se pudieron leer los datos" << endl;
        return;
    }
    
    if(filas < 2){
        cout << "❌ Error: Se necesitan al menos 2 puntos" << endl;
        return;
    }
    
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
        
        cout << "h = " << h << endl;
        cout << "f(x₀) + f(xₙ) = " << m[0][1] << " + " << m[filas-1][1] << " = " << suma << endl;
        
        for(int i = 1; i < filas-1; i++){
            suma += 2 * m[i][1];
            cout << "2·f(x" << i << ") = 2·" << m[i][1] << " = " << (2*m[i][1]) << endl;
        }
        
        double integral = (h/2) * suma;
        cout << "\n📊 Integral ≈ (h/2) × suma = (" << h << "/2) × " << suma << " = " << integral << endl;
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
    }
}

/**
 * MÉTODO DE SIMPSON COMPUESTO CON FUNCIÓN CONOCIDA
 * Integra usando parábolas para mayor precisión
 * Requiere número PAR de subintervalos
 */
void simpsonCompuestoFuncion(){
    double a, b;
    int n; 
    
    cout << "\n🔧 REGLA DE SIMPSON COMPUESTO - FUNCIÓN CONOCIDA" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    cout << "Función: f(x) = x² + 1" << endl;
    cout << "Límite inferior (a): ";
    cin >> a;
    cout << "Límite superior (b): ";
    cin >> b;
    cout << "Número de subintervalos (n): ";
    cin >> n;
    
    if(n <= 0) {
        cout << "❌ Error: El número de subintervalos debe ser positivo" << endl;
        return;
    }
    
    if(a >= b) {
        cout << "❌ Error: El límite inferior (a) debe ser menor que el superior (b)" << endl;
        return;
    }
    
    if(n % 2 != 0) {
        cout << "❌ Error: El número de intervalos debe ser PAR para Simpson" << endl;
        cout << "💡 Sugerencia: Use " << (n+1) << " o " << (n-1) << " intervalos" << endl;
        return;
    }
    
    double h = (b-a)/n;
    double suma = funcion(a) + funcion(b);
    
    cout << "\n📊 Cálculo paso a paso:" << endl;
    cout << "h = (b-a)/n = (" << b << "-" << a << ")/" << n << " = " << h << endl;
    cout << "f(a) + f(b) = f(" << a << ") + f(" << b << ") = " << funcion(a) << " + " << funcion(b) << " = " << suma << endl;
    cout << "Patrón de coeficientes: 1-4-2-4-2-...-4-1" << endl;
    
    for(int i = 1; i <= n-1; i++){
        double x = a + i * h;
        double fx = funcion(x);
        if(i % 2 == 1){
            suma += 4 * fx;
            cout << "4·f(" << x << ") = 4·" << fx << " = " << (4*fx) << " (índice impar)" << endl;
        } else {
            suma += 2 * fx;
            cout << "2·f(" << x << ") = 2·" << fx << " = " << (2*fx) << " (índice par)" << endl;
        }
    }
    
    double integral = (h/3) * suma;
    
    cout << fixed << setprecision(6);
    cout << "\n✅ RESULTADOS:" << endl;
    cout << "────────────────────────────────────────" << endl;
    cout << "Paso (h): " << h << endl;
    cout << "Suma total: " << suma << endl;
    cout << "∫[" << a << "," << b << "] f(x)dx ≈ " << integral << endl;
    
    // Valor exacto
    double exacto = (pow(b,3)/3 + b) - (pow(a,3)/3 + a);
    cout << "Valor exacto: " << exacto << endl;
    cout << "Error absoluto: " << fabs(integral - exacto) << endl;
    cout << "Error relativo: " << (fabs(integral - exacto)/fabs(exacto))*100 << "%" << endl;
    cout << "⭐ Nota: Simpson es exacto para polinomios de grado ≤ 3" << endl;
}

/**
 * MÉTODO DE SIMPSON COMPUESTO CON TABLA DE DATOS
 * Requiere puntos equidistantes y número par de intervalos
 * Mayor precisión que trapecio para datos suaves
 */
void simpsonCompuestoTabla(){
    double m[FILAS][2];
    int filas;
    
    cout << "\n🔧 REGLA DE SIMPSON COMPUESTO - TABLA DE DATOS" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    leerDatos(m, &filas);
    
    if(filas <= 0){
        cout << "❌ Error: No se pudieron leer los datos" << endl;
        return;
    }
    
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

/**
 * DOCUMENTACIÓN DE MÉTODOS DE INTEGRACIÓN NUMÉRICA
 * Explica qué hace cada método, cuándo usarlo y sus características
 */
void mostrarDocumentacion(){
    cout << "\n╔════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║              DOCUMENTACIÓN DE MÉTODOS DE INTEGRACIÓN           ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════╝" << endl;
    
    cout << "\n🔧 MÉTODO DEL TRAPECIO - FUNCIÓN CONOCIDA" << endl;
    cout << "─────────────────────────────────────────────────────────────────" << endl;
    cout << "📋 QUÉ HACE:" << endl;
    cout << "   • Aproxima la integral dividiendo el área bajo la curva en trapecios" << endl;
    cout << "   • Conecta puntos consecutivos con líneas rectas" << endl;
    cout << "   • Fórmula: ∫[a,b] f(x)dx ≈ (h/2)[f(a) + 2∑f(xi) + f(b)]" << endl;
    cout << "📊 CUÁNDO USAR:" << endl;
    cout << "   • Cuando tienes la función f(x) definida" << endl;
    cout << "   • Método simple y confiable" << endl;
    cout << "   • Bueno para funciones suaves" << endl;
    cout << "⚡ CARACTERÍSTICAS:" << endl;
    cout << "   • Precisión: O(h²) - Error proporcional al cuadrado del paso" << endl;
    cout << "   • Requiere: Límites [a,b] y número de subintervalos" << endl;
    cout << "   • Funciona con cualquier número de puntos" << endl;
    
    cout << "\n🔧 MÉTODO DEL TRAPECIO - TABLA DE DATOS" << endl;
    cout << "─────────────────────────────────────────────────────────────────" << endl;
    cout << "📋 QUÉ HACE:" << endl;
    cout << "   • Aplica trapecios cuando solo tienes puntos (x,y) discretos" << endl;
    cout << "   • Maneja datos equidistantes y no equidistantes" << endl;
    cout << "   • Para no equidistantes: suma trapecios individuales" << endl;
    cout << "📊 CUÁNDO USAR:" << endl;
    cout << "   • Datos experimentales o mediciones" << endl;
    cout << "   • No conoces la función f(x)" << endl;
    cout << "   • Puntos pueden no estar uniformemente espaciados" << endl;
    cout << "⚡ CARACTERÍSTICAS:" << endl;
    cout << "   • Flexible: acepta cualquier espaciado de puntos" << endl;
    cout << "   • Robusto para datos reales con ruido" << endl;
    cout << "   • Mínimo 2 puntos requeridos" << endl;
    
    cout << "\n🔧 MÉTODO DE SIMPSON COMPUESTO - FUNCIÓN CONOCIDA" << endl;
    cout << "─────────────────────────────────────────────────────────────────" << endl;
    cout << "📋 QUÉ HACE:" << endl;
    cout << "   • Aproxima usando parábolas en lugar de líneas rectas" << endl;
    cout << "   • Usa patrón de coeficientes: 1-4-2-4-2-...-4-1" << endl;
    cout << "   • Fórmula: ∫[a,b] f(x)dx ≈ (h/3)[f(a) + 4∑f(x_impar) + 2∑f(x_par) + f(b)]" << endl;
    cout << "📊 CUÁNDO USAR:" << endl;
    cout << "   • Funciones suaves y bien comportadas" << endl;
    cout << "   • Cuando necesitas mayor precisión que trapecio" << endl;
    cout << "   • Funciones polinómicas de grado ≤ 3 (resultado exacto)" << endl;
    cout << "⚡ CARACTERÍSTICAS:" << endl;
    cout << "   • Precisión: O(h⁴) - Mucho más preciso que trapecio" << endl;
    cout << "   • REQUISITO: Número PAR de subintervalos" << endl;
    cout << "   • Mejor para funciones curvas" << endl;
    
    cout << "\n🔧 MÉTODO DE SIMPSON COMPUESTO - TABLA DE DATOS" << endl;
    cout << "─────────────────────────────────────────────────────────────────" << endl;
    cout << "📋 QUÉ HACE:" << endl;
    cout << "   • Aplica Simpson cuando solo tienes puntos discretos" << endl;
    cout << "   • Verifica que los puntos sean equidistantes" << endl;
    cout << "   • Aplica patrón 1-4-2-4-2-...-4-1 a los datos" << endl;
    cout << "📊 CUÁNDO USAR:" << endl;
    cout << "   • Datos experimentales uniformemente espaciados" << endl;
    cout << "   • Mayor precisión requerida que trapecio" << endl;
    cout << "   • Datos representan función suave" << endl;
    cout << "⚡ CARACTERÍSTICAS:" << endl;
    cout << "   • REQUISITO: Puntos EQUIDISTANTES" << endl;
    cout << "   • REQUISITO: Número PAR de intervalos (impar de puntos)" << endl;
    cout << "   • Mínimo 3 puntos requeridos" << endl;
    
    cout << "\n🎯 GUÍA DE SELECCIÓN DE MÉTODO" << endl;
    cout << "═════════════════════════════════════════════════════════════════" << endl;
    cout << "┌─────────────────────────┬─────────────────┬─────────────────────┐" << endl;
    cout << "│ SITUACIÓN               │ MÉTODO          │ RAZÓN               │" << endl;
    cout << "├─────────────────────────┼─────────────────┼─────────────────────┤" << endl;
    cout << "│ Función conocida        │ Simpson/Trapecio│ Mayor control       │" << endl;
    cout << "│ Datos experimentales    │ Tabla           │ No hay función      │" << endl;
    cout << "│ Datos equidistantes     │ Simpson Tabla   │ Mayor precisión     │" << endl;
    cout << "│ Datos NO equidistantes  │ Trapecio Tabla  │ Simpson no aplica   │" << endl;
    cout << "│ Pocos puntos disponibles│ Trapecio        │ Menos restrictivo   │" << endl;
    cout << "│ Alta precisión requerida│ Simpson         │ Error O(h⁴)         │" << endl;
    cout << "└─────────────────────────┴─────────────────┴─────────────────────┘" << endl;
    
    cout << "\n📐 FÓRMULAS MATEMÁTICAS" << endl;
    cout << "═════════════════════════════════════════════════════════════════" << endl;
    cout << "TRAPECIO:  ∫[a,b] f(x)dx ≈ (h/2)[f(x₀) + 2f(x₁) + 2f(x₂) + ... + 2f(xₙ₋₁) + f(xₙ)]" << endl;
    cout << "SIMPSON:   ∫[a,b] f(x)dx ≈ (h/3)[f(x₀) + 4f(x₁) + 2f(x₂) + 4f(x₃) + ... + f(xₙ)]" << endl;
    cout << "donde h = (b-a)/n  y  xᵢ = a + i·h" << endl;
    
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
}
