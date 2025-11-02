//spline cubica

#include <iostream>
#include <math.h> 
#define FILAS 20
#define COLUMNAS 20

using namespace std;


void buildMatrix (double m[FILAS][2] , double a[FILAS][FILAS] , double b[FILAS] , int filas, int grado);

void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int grado);


void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int grado);


void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i);

double determinante(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas);	

void interpolacion (double m[FILAS][2], double x[FILAS], int filas, int grado);

void escribeSplineGeneral(double m[FILAS][2], double coef[FILAS], int filas, int grado);
	
void escribePolinomioGenerico(int filas, int grado);

void escribePolinomiosNumericos(double m[FILAS][2], double coef[FILAS], int filas, int grado);

void escribePolinomioGeneralNumerico(double m[FILAS][2], double coef[FILAS], int filas, int grado);

void mostrarSplineDetallado(double m[FILAS][2], double coef[FILAS], int filas, int grado);

/*
 *  Spline cúbico natural – salida: POLINOMIO GENERAL
 *  Compilar:  g++ spline_general.cpp -o spline_general
 */
int main(int argc, char *argv[]) {
    double m[5][2] = {
        {1  , 800},
        {3.5, 2310},
        {5  , 3090},
        {7  , 3940},
        {13 , 4755}
    };
    int filas = sizeof(m) / sizeof(m[0]);
    int grado = 3; // Grado del spline (3 = cúbico, 2 = cuadrático, etc.)
    cout << "\n--> Spline de grado " << grado << "\n";
    
    // Agregar validación del grado
    if (grado < 1 || grado > filas - 1) {
        cout << "Error: El grado debe estar entre 1 y " << (filas-1) << endl;
        return -1;
    }
    
    int coefPorTramo = grado + 1;
    int totalCoef = coefPorTramo * (filas - 1);
    
    double a[FILAS][FILAS] = {{0}}; 
    double b[FILAS] = {0};
    //aca ingresa m
    cout << "(X\t;\tY)\n";
    for(int i = 0 ; i < filas ; i++){
        cout << "(" << m[i][0] << "\t;\t" << m[i][1] << ")";
        cout << "\n";
    }
    
    buildMatrix(m, a, b, filas, grado);
    double* x = (double*)malloc(totalCoef * sizeof(double));
    triangulacion(a, b, x, totalCoef, grado);
    interpolacion(m, x, filas, grado);
    
    // Llamadas a las funciones de visualización
    mostrarSplineDetallado(m, x, filas, grado);
    
    free(x);
    return 0;
}

void buildMatrix (double m[FILAS][2] , double a[FILAS][FILAS] , double b[FILAS] , int filas, int grado){
	int n = filas - 1; // número de intervalos
	int coefPorTramo = grado + 1;
	int totalCoef = coefPorTramo * n;
	
	// Construcción de las primeras 2n filas (condiciones de paso por puntos)
	for (int k = 0; k < n ; k++){
		for(int j = 0; j < coefPorTramo; j++){
			a[2*k][coefPorTramo*k + j] = pow(m[k][0] , grado - j);
			a[2*k + 1][coefPorTramo*k + j] = pow(m[k+1][0] , grado - j);
		}
		
		b[2*k] = m[k][1];
		b[2*k + 1] = m[k + 1][1];
	}
	
	// Construcción de las condiciones de continuidad de derivadas
	int filaActual = 2 * n;
	for(int derivada = 1; derivada < grado; derivada++){
		for(int k = 0; k < n - 1; k++){
			for(int j = 0; j < coefPorTramo - derivada; j++){
				double factorial = 1;
				for(int f = 0; f < derivada; f++){
					factorial *= (grado - j - f);
				}
				a[filaActual][coefPorTramo*k + j] = factorial * pow(m[k+1][0], grado - j - derivada);
				a[filaActual][coefPorTramo*(k+1) + j] = -factorial * pow(m[k+1][0], grado - j - derivada);
			}
			b[filaActual] = 0;
			filaActual++;
		}
	}
	
	// Condiciones de frontera naturales (derivadas de orden alto = 0 en extremos)
	for(int derivada = 2; derivada <= grado; derivada++){
		// En el primer punto
		for(int j = 0; j < coefPorTramo - derivada + 1; j++){
			double factorial = 1;
			for(int f = 0; f < derivada; f++){
				factorial *= (grado - j - f);
			}
			a[filaActual][j] = factorial * pow(m[0][0], grado - j - derivada);
		}
		b[filaActual] = 0;
		filaActual++;
		
		// En el último punto
		for(int j = 0; j < coefPorTramo - derivada + 1; j++){
			double factorial = 1;
			for(int f = 0; f < derivada; f++){
				factorial *= (grado - j - f);
			}
			a[filaActual][coefPorTramo*(n-1) + j] = factorial * pow(m[n][0], grado - j - derivada);
		}
		b[filaActual] = 0;
		filaActual++;
	}
	
	cout << endl;
	for(int i = 0 ; i < totalCoef ; i++){ // Usar totalCoef en lugar de 4*n
		for(int j = 0 ; j < totalCoef ; j++){
			cout << "\t" << a[i][j];
		}
		cout << "\t" << b[i] << "\n";
	}
	
}
void triangulacion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int grado){
	for (int i = 0 ; i < (filas - 1) ; i++){
		pivot(a, b, filas , i);
		for (int j = i + 1; j < filas; j++) {
			double factor = -a[j][i] / a[i][i];
			for (int k = 0; k < filas; ++k) {
				a[j][k] = a[i][k] * factor + a[j][k];
			}
			b[j] = b[i] * factor + b[j];
		}
	}
	
	double norma = determinante(a,b,x,filas);
	if(norma == 0.0){
		cout << "\n\nmatriz singular" << endl;
	}else{
		retrostutitucion(a, b, x, filas, grado); // Corregir nombre aquí
	}
}
void retrostutitucion(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas, int grado){
    double value = 0;
    value = b[filas - 1] / a[filas - 1][filas - 1];
    x[filas - 1] = value;
    for (int i = filas - 2; i >= 0; --i) {
        double sum = 0;
        for (int j = i + 1; j < filas; ++j) {
            sum = sum + a[i][j] * x[j];
        }
        value = (b[i] - sum) / a[i][i];
        x[i] = value;
    }
    
    cout << "\nConjunto solucion: " << endl;
    cout << "Polinomios por tramo:" << endl << endl;
    
    int coefPorTramo = grado + 1;
    int numTramos = filas / coefPorTramo;
    
    for (int i = 0; i < numTramos; ++i) {
        cout << "Tramo " << (i+1) << ":" << endl;
        for(int j = 0; j < coefPorTramo; j++){
            printf("coef%d_%d = %8.6f\n", i, j, x[coefPorTramo*i + j]);
        }
        
        cout << "P" << i << "(x) = ";
        bool primero = true;
        for(int j = 0; j < coefPorTramo; j++){
            double coeficiente = x[coefPorTramo*i + j]; // Cambiar nombre aquí también
            
            // Saltar coeficientes muy pequeños
            if(fabs(coeficiente) < 1e-10) continue;
            
            // Manejar signos
            if(!primero) {
                if(coeficiente >= 0) cout << " + ";
                else cout << " - ";
                printf("%.6f", fabs(coeficiente));
            } else {
                printf("%.6f", coeficiente);
                primero = false;
            }
            
            // Agregar la parte de la variable
            if(grado - j > 1) cout << "*x^" << (grado - j);
            else if(grado - j == 1) cout << "*x";
        }
        cout << endl << endl;
    }
}
void pivot(double a[FILAS][COLUMNAS], double b[FILAS], int filas, int i){
	if (fabs(a[i][i]) < 0.0001) {
		for (int j = i + 1; j < filas; j++) {
			if (fabs(a[j][i]) > fabs(a[i][i])) {
				for (int k = i; k < filas; ++k) {
					double swap = a[i][k];
					a[i][k] = a[j][k];
					a[j][k] = swap;
				}
				double swap = b[i];
				b[i] = b[j];
				b[j] = swap;
			}
		}
	}
}
double determinante(double a[FILAS][COLUMNAS], double b[FILAS], double x[FILAS], int filas){
	double norma = 1;
	for(int i = 0; i < filas ; i++){
		norma = norma * a[i][i];
	}
	return norma;
}
	
void interpolacion (double m[FILAS][2], double z[FILAS] ,int fila, int grado){
	double x;//Coeficiente a interpolar
	cout << "Ingrese el valor a interpolar\n";
	cin >> x;
	int intervalo;
	double resultado = 0;
	int coefPorTramo = grado + 1;
	
	if (x >= m[0][0] && x <= m[fila - 1][0]){
		
		for (int i = 0; i < fila - 1; i++) {
			
			if(x >= m[i][0] && x < m[i+1][0]){
				for(int j = 0; j < coefPorTramo; j++){
					resultado += z[coefPorTramo*i + j] * pow(x, grado - j);
				}
				intervalo = i;
				break;
			}
		}
		cout << "\nEl valor a interpolar se encuentra en el intervalo " << intervalo << endl;
		cout << "\nEl valor interpolado para " << x << " es: " << resultado << endl;

	}else{
		cout << "\nEl valor a interpolar no se encuentra en el rango de datos\n";
	}
}

void mostrarSplineDetallado(double m[FILAS][2], double coef[FILAS], int filas, int grado) {
    string tipoSpline;
    switch(grado){
        case 1: tipoSpline = "LINEAL"; break;
        case 2: tipoSpline = "CUADRÁTICO"; break;
        case 3: tipoSpline = "CÚBICO"; break;
        default: tipoSpline = "DE GRADO " + to_string(grado); break;
    }
    
    int n = filas - 1;
    int coefPorTramo = grado + 1;
    
    // ===================================================================
    // SECCIÓN 1: SPLINE EN FORMA DE TRAMOS (como Lagrange expandido)
    // ===================================================================
    cout << "\n=== SPLINE " << tipoSpline << " EN FORMA DETALLADA ===" << endl;
    cout << "S(x) = ";
    
    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << "      ";
        }
        
        cout << "{ ";
        
        // Mostrar cada coeficiente del tramo actual
        bool primero = true;
        for(int j = 0; j < coefPorTramo; j++){
            double coeficiente = coef[coefPorTramo*i + j];
            
            // Manejar signos
            if(!primero) {
                if(coeficiente >= 0) cout << " + ";
                else cout << " - ";
                printf("%.6f", fabs(coeficiente));
            } else {
                if(coeficiente < 0) cout << "-";
                printf("%.6f", fabs(coeficiente));
                primero = false;
            }
            
            // Agregar la parte de la variable
            if(grado - j > 1) cout << "*x^" << (grado - j);
            else if(grado - j == 1) cout << "*x";
        }
        
        printf(" }  si %.3f ≤ x ≤ %.3f", m[i][0], m[i+1][0]);
        
        if (i < n - 1) {
            cout << endl << "      ";
        }
    }
    cout << endl << endl;
    
    // ===================================================================
    // SECCIÓN 2: FORMA SIMPLIFICADA POR TRAMOS
    // ===================================================================
    cout << "=== FORMA SIMPLIFICADA POR TRAMOS ===" << endl;
    cout << "El spline está compuesto por " << n << " polinomios de grado " << grado << ":" << endl;
    
    for (int i = 0; i < n; i++) {
        printf("S%d(x) = ", i+1);
        
        bool primero = true;
        for(int j = 0; j < coefPorTramo; j++){
            double coeficiente = coef[coefPorTramo*i + j];
            
            // Saltar coeficientes muy pequeños
            if(fabs(coeficiente) < 1e-10) continue;
            
            // Manejar signos
            if(!primero) {
                if(coeficiente >= 0) cout << " + ";
                else cout << " - ";
                printf("%.6e", fabs(coeficiente));
            } else {
                printf("%.6e", coeficiente);
                primero = false;
            }
            
            // Agregar la parte de la variable
            if(grado - j > 1) cout << " * x^" << (grado - j);
            else if(grado - j == 1) cout << " * x";
        }
        
        printf("   [%.3f ≤ x ≤ %.3f]", m[i][0], m[i+1][0]);
        cout << endl;
    }
    cout << endl;
    
    // ===================================================================
    // SECCIÓN 3: SPLINE EXPANDIDO COMO POLINOMIO GLOBAL (APROXIMACIÓN)
    // ===================================================================
    cout << "=== REPRESENTACIÓN COMO FUNCIÓN GLOBAL ===" << endl;
    cout << "Cada tramo puede expresarse como función indicadora:" << endl;
    cout << "S(x) = ";
    
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << " + ";
        
        cout << "[";
        
        // Mostrar el polinomio del tramo
        bool primero = true;
        for(int j = 0; j < coefPorTramo; j++){
            double coeficiente = coef[coefPorTramo*i + j];
            
            if(fabs(coeficiente) < 1e-10) continue;
            
            if(!primero) {
                if(coeficiente >= 0) cout << " + ";
                else cout << " - ";
                printf("%.6f", fabs(coeficiente));
            } else {
                if(coeficiente < 0) cout << "-";
                printf("%.6f", fabs(coeficiente));
                primero = false;
            }
            
            if(grado - j > 1) cout << "*x^" << (grado - j);
            else if(grado - j == 1) cout << "*x";
        }
        
        printf("] * I[%.3f,%.3f](x)", m[i][0], m[i+1][0]);
        
        if (i < n - 1) {
            cout << endl << "     ";
        }
    }
    cout << endl;
    cout << "donde I[a,b](x) = 1 si a ≤ x ≤ b, 0 en otro caso" << endl << endl;
    
    // ===================================================================
    // SECCIÓN 4: COEFICIENTES ORGANIZADOS
    // ===================================================================
    cout << "=== COEFICIENTES DEL SPLINE ===" << endl;
    cout << "Organización por tramos y potencias:" << endl;
    
    for (int i = 0; i < n; i++) {
        printf("Tramo %d [%.3f, %.3f]:\n", i+1, m[i][0], m[i+1][0]);
        for(int j = 0; j < coefPorTramo; j++){
            printf("  a%d,%d (coef. de x^%d) = %.10f\n", i, j, grado-j, coef[coefPorTramo*i + j]);
        }
        cout << endl;
    }
    
    // ===================================================================
    // SECCIÓN 5: MATRIZ DE COEFICIENTES
    // ===================================================================
    cout << "=== MATRIZ DE COEFICIENTES ===" << endl;
    cout << "Cada fila representa un tramo, cada columna una potencia de x:" << endl;
    cout << "Tramo\\Potencia  ";
    for(int j = grado; j >= 0; j--) {
        printf("   x^%d    ", j);
    }
    cout << "   Intervalo" << endl;
    cout << string(80, '-') << endl;
    
    for (int i = 0; i < n; i++) {
        printf("Tramo %d:      ", i+1);
        for(int j = 0; j < coefPorTramo; j++){
            printf("%9.4f ", coef[coefPorTramo*i + j]);
        }
        printf("   [%.1f, %.1f]", m[i][0], m[i+1][0]);
        cout << endl;
    }
    cout << endl;
    
    // ===================================================================
    // SECCIÓN 6: PROPIEDADES DEL SPLINE
    // ===================================================================
    cout << "=== PROPIEDADES DEL SPLINE " << tipoSpline << " ===" << endl;
    cout << "• Grado: " << grado << endl;
    cout << "• Número de puntos: " << filas << endl;
    cout << "• Número de tramos: " << n << endl;
    cout << "• Coeficientes por tramo: " << coefPorTramo << endl;
    cout << "• Total de coeficientes: " << (coefPorTramo * n) << endl;
    cout << "• Continuidad: C^" << (grado-1) << " (continuo hasta derivada " << (grado-1) << ")" << endl;
    cout << "• Condiciones de frontera: Naturales (derivadas de orden ≥ 2 nulas en extremos)" << endl;
    
    // Verificar continuidad en los puntos de unión
    cout << "\n=== VERIFICACIÓN DE CONTINUIDAD ===" << endl;
    for (int i = 1; i < n; i++) {
        double x_union = m[i][0];
        
        // Evaluar tramo izquierdo en x_union
        double valor_izq = 0;
        for(int j = 0; j < coefPorTramo; j++){
            valor_izq += coef[coefPorTramo*(i-1) + j] * pow(x_union, grado - j);
        }
        
        // Evaluar tramo derecho en x_union
        double valor_der = 0;
        for(int j = 0; j < coefPorTramo; j++){
            valor_der += coef[coefPorTramo*i + j] * pow(x_union, grado - j);
        }
        
        printf("En x = %.3f: S%d(%.3f) = %.6f, S%d(%.3f) = %.6f, |diferencia| = %.2e\n", 
                x_union, i, x_union, valor_izq, i+1, x_union, valor_der, fabs(valor_izq - valor_der));
    }
    
    cout << endl;
}
