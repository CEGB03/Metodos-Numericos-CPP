#include <iostream>
#include <math.h>
#include <iomanip>
#define FILAS 20

using namespace std;

void printMatrizA(double a[FILAS][FILAS], int filas){
	cout << "\nMatriz A:\n";
	for(int i = 0 ; i < filas ; i++){
		for(int j = 0 ; j < 2 ; j++){
			cout << "\t" << a[i][j];
		}
		cout << endl;
	}
}

/**
 * FUNCIÓN DE PRUEBA
 * Función matemática f(x) = x² + 1 utilizada para demostrar los métodos
 * Su integral exacta es: ∫(x² + 1)dx = x³/3 + x + C
 */
double funcion(double x){
    return 1.481841*pow(x, 1.57181);
}

// Declaraciones de funciones
void simpsonCompuestoFuncion();
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
    bool salir = false;
    
    while(!salir) {
        cout << "\n╔══════════════════════════════════════════════════╗" << endl;
        cout << "║        INTEGRACIÓN NUMÉRICA (NEWTON-COTES)       ║" << endl;
        cout << "╚══════════════════════════════════════════════════╝" << endl;
        cout << "3. Simpson Compuesto - Función conocida" << endl;
        cout << "4. Simpson Compuesto - Tabla de datos" << endl;
        /* cout << "5. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion; */
    
        //simpsonCompuestoFuncion();
        simpsonCompuestoTabla();
        cout << "¡Hasta luego!" << endl; salir = true;
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
 * MÉTODO DE SIMPSON COMPUESTO CON FUNCIÓN CONOCIDA
 * Integra usando parábolas para mayor precisión
 * Requiere número PAR de subintervalos
 */
void simpsonCompuestoFuncion(){
    double a=1, b=5;
    int n=4; 
    
    cout << "\n🔧 REGLA DE SIMPSON COMPUESTO - FUNCIÓN CONOCIDA" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    /* cout << "Función: f(x) = x² + 1" << endl; */
    /* cout << "Límite inferior (a): ";
    cin >> a;
    cout << "Límite superior (b): ";
    cin >> b;
    cout << "Número de subintervalos (n): ";
    cin >> n; */
    
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
	int filas = 5;
	double m[filas][2];
	// Tabla de datos original
	//   N		         M(MB)
	m[0][0] = 1;	m[0][1] = 4.5;
	m[1][0] = 2;	m[1][1] = 12.7;
	m[2][0] = 3;	m[2][1] = 24.3;
	m[3][0] = 4;	m[3][1] = 39.0;
	m[4][0] = 5;	m[4][1] = 56.5;
	//printMatrizA(m, filas);

	//tabla de datos modificada por despejes
	//   N		         M(MB)
	m[0][0] = log(m[0][0]);	m[0][1] = log(m[0][1]);
	m[1][0] = log(m[1][0]);	m[1][1] = log(m[1][1]);
	m[2][0] = log(m[2][0]);	m[2][1] = log(m[2][1]);
	m[3][0] = log(m[3][0]);	m[3][1] = log(m[3][1]);
	m[4][0] = log(m[4][0]);	m[4][1] = log(m[4][1]); 
    
    cout << "\n🔧 REGLA DE SIMPSON COMPUESTO - TABLA DE DATOS" << endl;
    cout << "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━" << endl;
    //leerDatos(m, &filas);
    
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
        
        // EQUIDISTANCIADOR: generar puntos equidistantes por interpolación lineal
        cout << "\n🔧 EQUIDISTANCIADOR: Generando puntos equidistantes..." << endl;
        
        // Calcular paso equidistante para n-1 intervalos (n puntos)
        double x_min = m[0][0];
        double x_max = m[filas-1][0];
        int n_intervalos = filas - 1;
        double h_equi = (x_max - x_min) / n_intervalos;
        
        cout << "Rango: [" << x_min << ", " << x_max << "]" << endl;
        cout << "Paso equidistante: h = " << h_equi << endl;
        
        double m_equi[FILAS][2];
        
        // Generar puntos equidistantes interpolando linealmente
        for(int k = 0; k < filas; k++){
            double x_nuevo = x_min + k * h_equi;
            
            // Buscar intervalo [m[i], m[i+1]] que contiene x_nuevo
            int i = 0;
            while(i < filas-1 && m[i+1][0] < x_nuevo) i++;
            
            // Interpolación lineal: y = y0 + (y1-y0)/(x1-x0) * (x-x0)
            double x0 = m[i][0], y0 = m[i][1];
            double x1 = (i+1 < filas) ? m[i+1][0] : m[i][0];
            double y1 = (i+1 < filas) ? m[i+1][1] : m[i][1];
            
            double y_nuevo = y0 + (y1 - y0) / (x1 - x0) * (x_nuevo - x0);
            
            m_equi[k][0] = x_nuevo;
            m_equi[k][1] = y_nuevo;
        }
        
        // Mostrar puntos equidistantes
        cout << "\n📋 Puntos equidistantes generados:" << endl;
        for(int k = 0; k < filas; k++){
            cout << "(" << m_equi[k][0] << ", " << m_equi[k][1] << ")" << endl;
        }
        
        // Aplicar Simpson con los puntos equidistantes
        cout << "\n✅ Aplicando Simpson compuesto con puntos equidistantes" << endl;
        
        double suma = m_equi[0][1] + m_equi[filas-1][1];
        
        cout << "h = " << h_equi << endl;
        cout << "f(x₀) + f(xₙ) = " << m_equi[0][1] << " + " << m_equi[filas-1][1] << " = " << suma << endl;
        cout << "Patrón de coeficientes: 1-4-2-4-2-...-4-1" << endl;
        
        for(int i = 1; i <= filas-2; i++){
            if(i % 2 == 1){
                suma += 4 * m_equi[i][1];
                cout << "4·f(x" << i << ") = 4·" << m_equi[i][1] << " = " << (4*m_equi[i][1]) << " (índice impar)" << endl;
            } else {
                suma += 2 * m_equi[i][1];
                cout << "2·f(x" << i << ") = 2·" << m_equi[i][1] << " = " << (2*m_equi[i][1]) << " (índice par)" << endl;
            }
        }
        
        double integral = (h_equi/3) * suma;
        
        cout << "\n✅ RESULTADOS CON EQUIDISTANCIAMIENTO:" << endl;
        cout << "────────────────────────────────────────" << endl;
        cout << "Paso (h): " << h_equi << endl;
        cout << "Suma total: " << suma << endl;
        cout << "Integral ≈ (h/3) × suma = (" << h_equi << "/3) × " << suma << " = " << integral << endl;
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
