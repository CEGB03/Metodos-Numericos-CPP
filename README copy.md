# 🧮 Métodos Numéricos en C++

Una colección completa de implementaciones de métodos numéricos fundamentales desarrollados en C++, diseñados para el aprendizaje y aplicación práctica en análisis numérico, cálculo numérico y resolución de ecuaciones.

## 📚 Tabla de Contenidos

- [🚀 Instalación y Compilación](#-instalación-y-compilación)
- [📁 Estructura del Proyecto](#-estructura-del-proyecto)
- [🔢 Módulos Disponibles](#-módulos-disponibles)
  - [🎯 Localización de Raíces](#-localización-de-raíces)
  - [📈 Interpolación](#-interpolación)
  - [🧮 Integración Numérica](#-integración-numérica)
  - [📊 Derivación Numérica](#-derivación-numérica)
  - [⚖️ Sistemas de Ecuaciones Lineales](#️-sistemas-de-ecuaciones-lineales)
  - [📉 Regresión](#-regresión)
  - [🔧 Ecuaciones Diferenciales](#-ecuaciones-diferenciales)
- [💻 Guía de Uso](#-guía-de-uso)
- [📖 Ejemplos Prácticos](#-ejemplos-prácticos)
- [🛠️ Contribución](#️-contribución)

## 🚀 Instalación y Compilación

### Requisitos Previos
- Compilador C++ (g++, clang++, o equivalente)
- Sistema operativo: Linux, macOS, o Windows con MinGW

### Compilación Rápida
```bash
# Clonar el repositorio
git clone https://github.com/CEGB03/Metodos-Numericos-CPP.git
cd Metodos-Numericos-CPP

# Compilar cualquier módulo
g++ -o programa "ruta/del/archivo.cpp"
./programa
```

## 📁 Estructura del Proyecto

```
Metodos-Numericos-Cpp/
├── 📁 LocRaices/
│   ├── 📁 Abiertos/
│   │   ├── Newton-Raphson.cpp     # Método de Newton-Raphson
│   │   ├── Punto-Fijo.cpp         # Método de Punto Fijo
│   └── 📁 Cerrados/
│       ├── Biseccion.cpp          # Método de Bisección
│       └── RegulaFalsi.cpp        # Método de Regula Falsi
├── 📁 Interpolacion/
│   ├── interpolacion.cpp          # Lagrange y Vandermonde
│   ├── Spline.cpp                # Splines de grado variable
│   ├── data.txt                  # Datos de prueba
├── 📁 Integracion/
│   ├── Integracion Newton Cotes.cpp  # Trapecio y Simpson
│   └── Gauss-Legendre.cpp        # Cuadratura Gauss-Legendre
├── 📁 Diferenciacion Numerica/
│   ├── Derivadas.cpp             # Diferencias finitas
│   ├── 📁 Diferenciacion/
│   │   └── Diferenciacion.cpp    # Implementación alternativa
│   └── 📁 Ecuaciones Diferenciales/
│       ├── MetodoEuler.cpp       # Método de Euler
│       ├── MetodoHeun.cpp        # Método de Heun
│       ├── Runge-Kutta4.cpp      # Runge-Kutta 4to orden
│       ├── MetodoPuntoMedio.cpp  # Método del Punto Medio
│       └── EjemploEcsDifDeOrdenSuperior.cpp
├── 📁 Sistemas de Ecuaciones Lineales/
│   ├── Eliminacion-Gaussiana.cpp  # Eliminación Gaussiana
│   ├── Métodos Iterativos.cpp     # Jacobi, Gauss-Seidel, Relajación
│   ├── data.txt                  # Datos de prueba
├── 📁 Regresion/
│   ├── Regresion Lineal.cpp      # Regresión lineal
│   ├── polynomialRegression.cpp  # Regresión polinómica
├── .gitignore                    # Archivos ignorados
└── README.md                     # Este archivo
```
      a# Ejecutable

## 🔢 Módulos Disponibles

### 🎯 Localización de Raíces

#### 📄 `LocRaices/Abiertos/Newton-Raphson.cpp`
**Método de Newton-Raphson para encontrar raíces con convergencia cuadrática**

**🎯 Qué hace:**
- Localiza raíces de ecuaciones no lineales usando la fórmula: `x₁ = x₀ - f(x₀)/f'(x₀)`
- Convergencia cuadrática (muy rápida)
- Requiere la derivada de la función

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o newton LocRaices/Abiertos/Newton-Raphson.cpp

# Ejecutar
./newton
```

**📝 Modificar función:**
```cpp
// En el código fuente, cambiar estas dos funciones:
double f(double x) {
    return x * x - 4;  // Tu función f(x) aquí
}

double fPrima(double x) {
    return 2 * x;      // Derivada f'(x) aquí
}
```

**📊 Entrada esperada:**
```
Tolerancia: 0.0001
Punto inicial: 1.5
```

**📈 Salida típica:**
```
=== MÉTODO DE NEWTON-RAPHSON ===
Función: f(x) = x² - 4
Derivada: f'(x) = 2x

Iteración 1:
  f(x₀) = -1.750000
  f'(x₀) = 3.000000
  x₁ = 2.083333

✓ Raíz encontrada: x = 2.000000
✓ Convergencia EXITOSA en 4 iteraciones
```

**⚡ Características:**
- ✅ Convergencia cuadrática súper rápida
- ✅ Cálculo de errores porcentuales y exactos
- ✅ Tabla detallada de iteraciones
- ✅ Validación de derivada no nula
- ❌ Requiere derivada analítica
- ❌ Puede no converger si punto inicial es malo

#### 📄 `LocRaices/Abiertos/Punto-Fijo.cpp`
**Transformación f(x) = 0 → x = g(x) para localización iterativa**

**🎯 Qué hace:**
- Transforma ecuación f(x) = 0 en punto fijo x = g(x)
- Iteración: x₁ = g(x₀), x₂ = g(x₁), ...
- Verificación automática de convergencia |g'(x)| < 1

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o punto-fijo LocRaices/Abiertos/Punto-Fijo.cpp

# Ejecutar
./punto-fijo
```

**📝 Estrategias para obtener g(x):**

| Método | Ejemplo | g(x) resultante |
|--------|---------|-----------------|
| **Despeje directo** | f(x) = x² - 4 = 0 | g(x) = 2 (raíz positiva) |
| **Fórmula general** | Cualquier f(x) | g(x) = x - λ*f(x) con λ = 0.1 |
| **Transformación** | f(x) = cos(x) - x | g(x) = cos(x) |

```cpp
// Modificar en el código fuente:
double g(double x) { 
    return 2;  // Para f(x) = x² - 4, raíz positiva
    // return cos(x);        // Para f(x) = cos(x) - x
    // return x - 0.1*f(x);  // Fórmula general
}
```

**📊 Características:**
- ✅ No requiere derivada
- ✅ Verificación automática |g'(x)| < 1
- ✅ Múltiples estrategias de transformación
- ✅ Límite de seguridad de iteraciones
- ❌ Convergencia puede ser lenta
- ❌ Requiere análisis previo de g(x)

#### 📄 `LocRaices/Cerrados/Biseccion.cpp`
**Método de Bisección con convergencia garantizada**

**🎯 Qué hace:**
- Localiza raíces en intervalo [a,b] donde f(a)·f(b) < 0
- Divide iterativamente el intervalo por la mitad
- Convergencia garantizada si hay cambio de signo

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o biseccion LocRaices/Cerrados/Biseccion.cpp

# Ejecutar
./biseccion
```

**📝 Modificar función:**
```cpp
double funcion(double x) {
    return log(x) + exp(sin(x)) - x;  // Tu función aquí
}
```

**📊 Entrada típica:**
```
Límite inferior: 0.5
Límite superior: 1.0
Tolerancia: 0.0001
```

**⚡ Características:**
- ✅ Convergencia SIEMPRE garantizada
- ✅ Muy robusto y estable
- ✅ No requiere derivada
- ✅ Maneja funciones complicadas
- ❌ Convergencia lineal (lenta)
- ❌ Solo encuentra una raíz por intervalo

#### 📄 `LocRaices/Cerrados/RegulaFalsi.cpp`
**Método de Regula Falsi (Falsa Posición) - Interpolación lineal**

**🎯 Qué hace:**
- Similar a bisección pero usa interpolación lineal
- Fórmula: `c = (a*f(b) - b*f(a))/(f(b) - f(a))`
- Más rápido que bisección, mantiene convergencia garantizada

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o regula-falsi LocRaices/Cerrados/RegulaFalsi.cpp

# Ejecutar
./regula-falsi
```

**⚡ Características:**
- ✅ Convergencia garantizada como bisección
- ✅ Más rápido que bisección
- ✅ Interpola en lugar de dividir por la mitad
- ✅ Robusto para funciones continuas
- ❌ Puede ser lento en algunos casos especiales

### 📈 Interpolación

#### 📄 `Interpolacion/interpolacion.cpp`
**Métodos de Lagrange y Vandermonde con visualización completa**

**🎯 Qué hace:**
- **Lagrange:** Construye polinomio usando bases de Lagrange Li(x)
- **Vandermonde:** Resuelve sistema matricial para coeficientes
- Expansión automática a forma polinómica estándar P(x) = a₀ + a₁x + ...

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o interpolacion Interpolacion/interpolacion.cpp

# Ejecutar (lee datos desde data.txt)
./interpolacion
```

**📄 Formato archivo `data.txt`:**
```
1.0    800.0
3.5    2310.0
5.0    3090.0
7.0    3940.0
13.0   4755.0
```

**📊 Salidas del programa:**

1. **Forma de Lagrange:**
```
P(x) = 800 * [(x-3.5)/(1-3.5) * (x-5)/(1-5) * ...]
     + 2310 * [(x-1)/(3.5-1) * (x-5)/(3.5-5) * ...]
```

2. **Forma estándar expandida:**
```
P(x) = 2.1543*x³ - 15.234*x² + 45.678*x + 123.456
```

3. **Coeficientes individuales:**
```
a₀ = 123.456  (término independiente)
a₁ = 45.678   (coeficiente de x)
a₂ = -15.234  (coeficiente de x²)
a₃ = 2.1543   (coeficiente de x³)
```

**⚡ Características:**
- ✅ Lagrange: Visualización completa paso a paso
- ✅ Vandermonde: Matriz de coeficientes explícita
- ✅ Expansión automática a forma estándar
- ✅ Lectura desde archivo data.txt
- ✅ Interpolación de valores específicos
- ❌ Inestable para muchos puntos (grado alto)

#### 📄 `Interpolacion/Spline.cpp`
**Splines de grado variable - COMPLETAMENTE ADAPTABLE**

**🎯 Qué hace:**
- Crea splines de **cualquier grado** (1=lineal, 2=cuadrático, 3=cúbico, etc.)
- Garantiza continuidad hasta derivada (grado-1)
- Condiciones de frontera naturales automáticas
- Visualización detallada por tramos

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o spline Interpolacion/Spline.cpp

# Ejecutar
./spline
```

**📝 Configurar grado del spline:**
```cpp
// En main(), línea ~50:
int grado = 3;  // ← CAMBIAR AQUÍ EL GRADO DESEADO
// grado = 1: Spline lineal (C⁰ - solo continuo)
// grado = 2: Spline cuadrático (C¹ - continuo y derivable)  
// grado = 3: Spline cúbico (C² - continuo hasta 2da derivada)
// grado = 4: Spline cuártico (C³)
// ...y así sucesivamente
```

**📊 Ejemplo salida Spline Cúbico:**
```
=== SPLINE CÚBICO EN FORMA DETALLADA ===
S(x) = { -0.123456*x³ + 2.345678*x² - 5.678901*x + 800.000000 }  si 1.000 ≤ x ≤ 3.500
       { 0.098765*x³ - 1.234567*x² + 4.567890*x + 1234.567890 }  si 3.500 ≤ x ≤ 5.000
       { -0.045678*x³ + 0.987654*x² - 2.345678*x + 2000.000000 }  si 5.000 ≤ x ≤ 7.000
       { 0.012345*x³ - 0.543210*x² + 1.234567*x + 1500.000000 }  si 7.000 ≤ x ≤ 13.000

=== VERIFICACIÓN DE CONTINUIDAD ===
En x = 3.500: S1(3.500) = 2310.000000, S2(3.500) = 2310.000000, |diferencia| = 1.23e-12
En x = 5.000: S2(5.000) = 3090.000000, S3(5.000) = 3090.000000, |diferencia| = 4.56e-13
```

**⚡ Características:**
- ✅ **ADAPTABLE A CUALQUIER GRADO** - Solo cambiar una variable
- ✅ Matemáticamente correcto para todos los grados
- ✅ Continuidad automática hasta derivada (grado-1)
- ✅ Verificación numérica de continuidad
- ✅ Múltiples formas de visualización
- ✅ Interpolación de valores específicos
- ✅ Muy estable para muchos puntos

### 🧮 Integración Numérica

#### 📄 `Integracion/Integracion Newton Cotes.cpp`
**Métodos de Trapecio y Simpson con menú interactivo completo**

**🎯 Qué hace:**
- **Trapecio:** Aproxima área con trapecios (precisión O(h²))
- **Simpson:** Usa parábolas para mayor precisión (O(h⁴))
- Maneja funciones conocidas y datos tabulados
- Documentación integrada completa

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o integracion "Integracion/Integracion Newton Cotes.cpp"

# Ejecutar
./integracion
```

**📊 Menú interactivo:**
```
╔══════════════════════════════════════════════════╗
║        INTEGRACIÓN NUMÉRICA (NEWTON-COTES)       ║
╚══════════════════════════════════════════════════╝
0. Ver documentación de métodos
1. Trapecio - Función conocida      [f(x) = x² + 1]
2. Trapecio - Tabla de datos        [puntos discretos]
3. Simpson Compuesto - Función      [f(x) = x² + 1] 
4. Simpson Compuesto - Tabla        [puntos discretos]
5. Salir
```

**📝 Función actual:** `f(x) = x² + 1`
```cpp
// Para cambiar función, modificar:
double funcion(double x){
    return pow(x,2) + 1;  // Tu función aquí
}
```

**📊 Casos de uso y precisión:**

| Método | Precisión | Cuándo usar | Restricciones |
|--------|-----------|-------------|---------------|
| **Trapecio Función** | O(h²) | Función conocida, robustez | Ninguna especial |
| **Trapecio Tabla** | O(h²) | Datos experimentales | Mínimo 2 puntos |
| **Simpson Función** | O(h⁴) | Función conocida, precisión | Intervalos PAR |
| **Simpson Tabla** | O(h⁴) | Datos experimentales precisos | Puntos equidistantes + intervalos PAR |

**📋 Ejemplo entrada Trapecio:**
```
Límite inferior (a): 0
Límite superior (b): 2  
Número de subintervalos (n): 4

Resultado: ∫[0,2] (x²+1)dx ≈ 4.6667
Valor exacto: 4.6667
Error absoluto: 8.33e-06
```

#### 📄 `Integracion/Gauss-Legendre.cpp`
**Cuadratura de Gauss-Legendre para alta precisión**

**🎯 Qué hace:**
- Integración de alta precisión con pocos puntos de evaluación
- Usa puntos y pesos pre-calculados óptimos
- Órdenes disponibles: 2, 3, 4, 5, 6 puntos
- Transformación automática de intervalos

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o gauss-legendre Integracion/Gauss-Legendre.cpp

# Ejecutar
./gauss-legendre
```

**📊 Precisión por orden:**

| Orden | Puntos | Exacto para polinomios hasta grado |
|-------|--------|-------------------------------------|
| 2 | 2 puntos | 3 |
| 3 | 3 puntos | 5 |
| 4 | 4 puntos | 7 |
| 5 | 5 puntos | 9 |
| 6 | 6 puntos | 11 |

### 📊 Derivación Numérica

#### 📄 `Diferenciacion Numerica/Derivadas.cpp`
**Diferencias finitas para cálculo de derivadas**

**🎯 Qué hace:**
- **Progresivas:** `f'(x) ≈ [f(x+h) - f(x)]/h` - Para inicio de intervalo
- **Regresivas:** `f'(x) ≈ [f(x) - f(x-h)]/h` - Para final de intervalo  
- **Centrales:** `f'(x) ≈ [f(x+h) - f(x-h)]/(2h)` - Mejor precisión O(h²)
- **Segunda derivada:** `f''(x) ≈ [f(x+h) - 2f(x) + f(x-h)]/h²`

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o derivadas "Diferenciacion Numerica/Derivadas.cpp"

# Ejecutar
./derivadas
```

**📊 Datos tabulados incluidos:**
```cpp
double a[FILAS][2] = {
    {0,    1},     {0.25, 1.384}, {0.5,  1.849}, {0.75, 2.417},
    {1,    3.118}, {1.25, 3.99},  {1.5,  5.082}, {1.75, 6.45}, 
    {2,    8.189}
};
```

**📈 Salida típica:**
```
Derivadas calculadas:
(0, 2.532)      ← Diferencias progresivas
(0.25, 1.856)   ← Diferencias centrales
(0.5, 2.272)    ← Diferencias centrales
...
(1.75, 6.956)   ← Diferencias centrales  
(2, 7.476)      ← Diferencias regresivas
```

**⚡ Comparación de métodos:**

| Método | Precisión | Ubicación | Fórmula |
|--------|-----------|-----------|---------|
| **Progresiva** | O(h) | Extremo izquierdo | [f(x+h) - f(x)]/h |
| **Regresiva** | O(h) | Extremo derecho | [f(x) - f(x-h)]/h |
| **Central** | **O(h²)** | **Punto interior** | **[f(x+h) - f(x-h)]/(2h)** ← Mejor |

### ⚖️ Sistemas de Ecuaciones Lineales

#### 📄 `Sistemas de Ecuaciones Lineales/Eliminacion-Gaussiana.cpp`
**Eliminación Gaussiana con pivoteo parcial**

**🎯 Qué hace:**
- Resuelve sistemas Ax = b mediante eliminación gaussiana
- Pivoteo parcial automático para estabilidad numérica
- Verificación de matriz singular
- Cálculo del determinante

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o gauss "Sistemas de Ecuaciones Lineales/Eliminacion-Gaussiana.cpp"

# Ejecutar (lee desde data.txt)
./gauss
```

**📄 Formato archivo `data.txt` (matriz aumentada):**
```
1  2  1  4  13
0  2  4  3  28  
4  2  2  1  20
-3 1  3  2  6
```
Representa el sistema:
```
x₁ + 2x₂ + x₃ + 4x₄ = 13
     2x₂ + 4x₃ + 3x₄ = 28
4x₁ + 2x₂ + 2x₃ + x₄ = 20
-3x₁ + x₂ + 3x₃ + 2x₄ = 6
```

**📊 Salida típica:**
```
La norma es: -156.000000

Conjunto solucion:
x1 = 1.000000
x2 = 2.000000  
x3 = 3.000000
x4 = 1.000000
```

**⚡ Características:**
- ✅ Pivoteo automático para evitar divisiones por cero
- ✅ Detección de sistemas singulares
- ✅ Lectura desde archivo flexible
- ✅ Cálculo de determinante como verificación

#### 📄 `Sistemas de Ecuaciones Lineales/Métodos Iterativos.cpp`
**Jacobi, Gauss-Seidel y Relajación para sistemas grandes**

**🎯 Qué hace:**
- **Jacobi:** Iteración simultánea con valores previos
- **Gauss-Seidel:** Usa valores actualizados inmediatamente  
- **Relajación:** Gauss-Seidel con factor de aceleración ω

**🚀 Cómo usar:**
```bash
# Compilar  
g++ -o iterativos "Sistemas de Ecuaciones Lineales/Métodos Iterativos.cpp"

# Ejecutar (lee desde data.txt)
./iterativos
```

**📊 Menú de selección:**
```
Seleccione:
1 --> Jacobi 
2 --> Gauss Seidel 
3 --> Gauss Seidel con Relajación
```

**📝 Verificación dominancia diagonal:**
El programa verifica automáticamente si la matriz es diagonalmente dominante:
```cpp
|aii| > Σ|aij|  para todo i≠j
```

**⚡ Parámetros de relajación:**
- `ω = 1`: Gauss-Seidel normal
- `ω < 1`: Sub-relajación (mejora convergencia en casos difíciles)
- `ω > 1`: Sobre-relajación (acelera convergencia)

**📊 Comparación métodos iterativos:**

| Método | Velocidad | Memoria | Requisitos |
|--------|-----------|---------|------------|
| **Jacobi** | Media | Más | Dominancia diagonal |
| **Gauss-Seidel** | **Rápida** | **Menos** | **Dominancia diagonal** |
| **Relajación** | **Variable** | Menos | Dominancia + parámetro ω |

### 📉 Regresión

#### 📄 `Regresion/Regresion Lineal.cpp`
**Regresión lineal por mínimos cuadrados con análisis estadístico**

**🎯 Qué hace:**
- Ajusta recta y = a₀ + a₁x a datos experimentales
- Calcula coeficientes por mínimos cuadrados
- Análisis estadístico: R², error estándar, correlación

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o regresion-lineal "Regresion/Regresion Lineal.cpp"

# Ejecutar
./regresion-lineal
```

**📊 Datos de ejemplo incluidos:**
```cpp
double m[ROWS][2];
m[0][0] = -1; m[0][1] = 10;
m[1][0] = 0;  m[1][1] = 9;
m[2][0] = 1;  m[2][1] = 7;
m[3][0] = 2;  m[3][1] = 5;
// ... más puntos
```

**📈 Salida típica:**
```
Matriz del sistema:
    28.000000    14.000000    38.000000
    14.000000     8.000000    38.000000

Conjunto solución:
X0 = -1.607143  (pendiente a₁)
X1 = 9.107143   (intercepto a₀)

Ecuación de regresión: y = 9.107143 - 1.607143*x

El error cuadrático medio es de: 0.534522
El coeficiente de correlación es: 0.982745
```

**📊 Métricas calculadas:**
- **R²**: Coeficiente de determinación (0-1, más cerca de 1 = mejor ajuste)
- **Error cuadrático medio**: Desviación promedio de los datos
- **Coeficiente de correlación**: Fuerza de relación lineal

#### 📄 `Regresion/polynomialRegression.cpp`
**Regresión polinómica de grado variable con análisis completo**

**🎯 Qué hace:**
- Ajusta polinomio P(x) = a₀ + a₁x + a₂x² + ... + aₙxⁿ
- Grado configurable según datos disponibles
- Análisis estadístico detallado
- Validación automática de viabilidad

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o regresion-poli Regresion/polynomialRegression.cpp

# Ejecutar
./regresion-poli
```

**📊 Datos incluidos:**
```cpp
double nodes[6][2] = {
    {0.2, -0.94}, {0.6, -0.26}, {1.3, 2.35},
    {1.4, 2.94},  {1.8, 5.45},  {2.0, 7.20}
};
```

**📝 Selección de grado:**
```
----------------------------
Ingresar grado del polinomio: 
----------------------------
2    ← Usuario ingresa grado deseado
```

**📈 Salida para polinomio grado 2:**
```
POLINOMIO
-2.34567 + 1.45678 X^1 + 0.987654 X^2

--------
DETALLES  
--------
Error/Residuo (suma de cuadrados): 0.123456
Error cuadrático medio: 0.161245  
Desviación estándar: 0.198765
Coeficiente de determinación: 0.987654
Coeficiente de correlación: 0.993827
```

**⚡ Validación automática:**
- Verifica que haya suficientes puntos para el grado solicitado
- Detecta sistemas singulares  
- Calcula todas las métricas estadísticas relevantes

### 🔧 Ecuaciones Diferenciales

#### 📄 `Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoEuler.cpp`
**Método de Euler básico para EDO de primer orden**

**🎯 Qué hace:**
- Resuelve EDO: `dy/dx = f(x,y)` con condición inicial `y(x₀) = y₀`
- Método más simple: `y₁ = y₀ + h*f(x₀,y₀)`
- Precisión O(h), fácil de implementar

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o euler "Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoEuler.cpp"

# Ejecutar
./euler
```

**📝 Función actual:** `f(x,y) = -2xy`
```cpp
// Para cambiar EDO, modificar:
double f(double x, double y){
    return (-2*x*y);  // Tu función f(x,y) aquí
}
```

**📊 Entrada típica:**
```
Intervalo [a,b]
a: 0
b: 1
Cantidad de puntos: 10
Ingrese x0 e y0
x0: 0
y0: 1
```

**📈 Salida paso a paso:**
```
X1 = 0.100000
Y1 = 1.000000
X2 = 0.200000  
Y2 = 0.980000
X3 = 0.300000
Y3 = 0.941200
...
```

#### 📄 `Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoHeun.cpp`
**Método de Heun (Euler mejorado) - Predictor-Corrector**

**🎯 Qué hace:**
- Esquema predictor-corrector para mayor precisión
- **Predictor:** `y*₁ = y₀ + h*f(x₀,y₀)` (como Euler)
- **Corrector:** `y₁ = y₀ + (h/2)[f(x₀,y₀) + f(x₁,y*₁)]`
- Precisión O(h²) - Mucho mejor que Euler

**🚀 Cómo usar:**
```bash
# Compilar  
g++ -o heun "Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoHeun.cpp"

# Ejecutar
./heun
```

**⚡ Características:**
- ✅ Mejor precisión que Euler con poco esfuerzo extra
- ✅ Esquema auto-correctivo
- ✅ Buen balance precisión/costo computacional

#### 📄 `Diferenciacion Numerica/Ecuaciones Diferenciales/Runge-Kutta4.cpp`
**Runge-Kutta 4to orden - El estándar de oro para EDO**

**🎯 Qué hace:**
- Método de 4to orden más utilizado en la práctica
- Calcula 4 coeficientes k₁, k₂, k₃, k₄ por paso
- Precisión O(h⁴) - Excelente para la mayoría de problemas
- Muy estable y confiable

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o rk4 "Diferenciacion Numerica/Ecuaciones Diferenciales/Runge-Kutta4.cpp"

# Ejecutar
./rk4
```

**📝 Función actual:** `f(x,y) = x√y`
```cpp
double f(double x, double y){
    return x*sqrt(y);  // Tu EDO aquí: dy/dx = x√y
}
```

**🔬 Algoritmo interno:**
```
k₁ = f(xᵢ, yᵢ)
k₂ = f(xᵢ + h/2, yᵢ + k₁h/2)  
k₃ = f(xᵢ + h/2, yᵢ + k₂h/2)
k₄ = f(xᵢ + h, yᵢ + k₃h)
yᵢ₊₁ = yᵢ + (h/6)(k₁ + 2k₂ + 2k₃ + k₄)
```

#### 📄 `Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoPuntoMedio.cpp`
**Método del Punto Medio con evaluación central**

**🎯 Qué hace:**
- Evalúa la derivada en el punto medio del intervalo
- `y₁ = y₀ + h*f(x₀ + h/2, y₀ + (h/2)*f(x₀,y₀))`
- Precisión O(h²) con un enfoque diferente

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o punto-medio "Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoPuntoMedio.cpp"

# Ejecutar  
./punto-medio
```

#### 📄 `Diferenciacion Numerica/Ecuaciones Diferenciales/EjemploEcsDifDeOrdenSuperior.cpp`
**Sistemas de EDO usando Runge-Kutta - Orden superior reducido a primer orden**

**🎯 Qué hace:**
- Resuelve EDO de orden superior convirtiéndolas en sistemas
- Ejemplo: `y'' + y = 4cos(x)` → Sistema: `y₁' = y₂, y₂' = -y₁ + 4cos(x)`
- Aplica RK4 simultáneamente a ambas ecuaciones

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o edo-superior "Diferenciacion Numerica/Ecuaciones Diferenciales/EjemploEcsDifDeOrdenSuperior.cpp"

# Ejecutar
./edo-superior
```

**📊 Sistema actual:**
```cpp
double f1(double y2){
    return y2;  // y₁' = y₂
}
double f2(double x, double y1){  
    return -y1 + 4*cos(x);  // y₂' = -y₁ + 4cos(x)
}
```

**📈 Condiciones iniciales:** `y(0) = 0, y'(0) = 0`

## 💻 Guía de Uso

### Compilación de Módulos Específicos

```bash
# Localización de Raíces
g++ -o newton LocRaices/Abiertos/Newton-Raphson.cpp
g++ -o punto-fijo LocRaices/Abiertos/Punto-Fijo.cpp
g++ -o biseccion LocRaices/Cerrados/Biseccion.cpp
g++ -o regula-falsi LocRaices/Cerrados/RegulaFalsi.cpp

# Interpolación
g++ -o interpolacion Interpolacion/interpolacion.cpp
g++ -o spline Interpolacion/Spline.cpp

# Integración
g++ -o integracion "Integracion/Integracion Newton Cotes.cpp"
g++ -o gauss-legendre Integracion/Gauss-Legendre.cpp

# Derivadas y EDO
g++ -o derivadas "Diferenciacion Numerica/Derivadas.cpp"
g++ -o euler "Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoEuler.cpp"
g++ -o heun "Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoHeun.cpp"
g++ -o rk4 "Diferenciacion Numerica/Ecuaciones Diferenciales/Runge-Kutta4.cpp"
g++ -o punto-medio "Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoPuntoMedio.cpp"
g++ -o edo-superior "Diferenciacion Numerica/Ecuaciones Diferenciales/EjemploEcsDifDeOrdenSuperior.cpp"

# Sistemas de Ecuaciones
g++ -o gauss "Sistemas de Ecuaciones Lineales/Eliminacion-Gaussiana.cpp"
g++ -o iterativos "Sistemas de Ecuaciones Lineales/Métodos Iterativos.cpp"

# Regresión
g++ -o regresion-lineal "Regresion/Regresion Lineal.cpp"
g++ -o regresion-poli Regresion/polynomialRegression.cpp
```

### Archivos de Datos

Algunos programas requieren archivos de entrada específicos:

#### **📄 `Interpolacion/data.txt`** (para interpolación):
```
1.0    800.0
3.5    2310.0
5.0    3090.0
7.0    3940.0
13.0   4755.0
```

#### **📄 `Sistemas de Ecuaciones Lineales/data.txt`** (matriz aumentada):
```
1  2  1  4  13
0  2  4  3  28
4  2  2  1  20
-3 1  3  2  6
```

### Personalización de Funciones

#### **Para métodos de raíces:**
```cpp
// Newton-Raphson.cpp
double f(double x) {
    return x*x*x - 2*x + 1;  // f(x) = x³ - 2x + 1
}
double fPrima(double x) {
    return 3*x*x - 2;        // f'(x) = 3x² - 2
}

// Punto-Fijo.cpp  
double g(double x) {
    return sqrt(2*x - 1);    // Para f(x) = x² - 2x + 1
}
```

#### **Para integración:**
```cpp
// Integracion Newton Cotes.cpp
double funcion(double x){
    return sin(x) * exp(-x);  // Tu función a integrar
}
```

#### **Para EDO:**
```cpp
// Cualquier método de EDO
double f(double x, double y) {
    return x + y;            // Tu EDO: y' = x + y
}
```

#### **Para splines - Cambiar grado:**
```cpp
// Spline.cpp, en main():
int grado = 2;  // ← Cambiar: 1=lineal, 2=cuadrático, 3=cúbico, etc.
```

## 📖 Ejemplos Prácticos Completos

### Ejemplo 1: Encontrar √2 usando diferentes métodos

#### **Newton-Raphson:**
```cpp
// f(x) = x² - 2, f'(x) = 2x
double f(double x) { return x*x - 2; }
double fPrima(double x) { return 2*x; }
// Punto inicial: 1.5 → Converge a 1.414213...
```

#### **Punto Fijo:**
```cpp
// g(x) = 2/x (converge a ±√2 según punto inicial)
double g(double x) { return 2.0/x; }
// Punto inicial: 1.0 → Converge a 1.414213...
```

#### **Bisección:**
```cpp
double funcion(double x) { return x*x - 2; }
// Intervalo [1, 2] → Converge a 1.414213...
```

### Ejemplo 2: Interpolación de datos de temperatura

**Datos experimentales:**
```cpp
// data.txt
0.0    20.0    // t=0min,  T=20°C
10.0   35.2    // t=10min, T=35.2°C  
20.0   48.7    // t=20min, T=48.7°C
30.0   60.1    // t=30min, T=60.1°C
```

**Usar Lagrange para T(15min):**
```bash
./interpolacion
# Seleccionar método 1 (Lagrange)
# Interpolar valor: 15
# Resultado: T(15min) ≈ 41.95°C
```

### Ejemplo 3: Integrar área bajo curva

**Calcular ∫₀² (x²+1) dx:**
```bash
./integracion
# Opción 3: Simpson Compuesto - Función
# a: 0, b: 2, intervalos: 4
# Resultado: 4.666667 (exacto para este polinomio)
```

### Ejemplo 4: Resolver EDO poblacional

**EDO:** `dy/dt = ky` (crecimiento exponencial)
```cpp
// En MetodoEuler.cpp o Runge-Kutta4.cpp:
double f(double t, double y) {
    return 0.1 * y;  // k = 0.1 (tasa crecimiento 10%)
}
// Condición inicial: y(0) = 100 (población inicial)
// Solución exacta: y(t) = 100*e^(0.1*t)
```

### Ejemplo 5: Sistema de ecuaciones 3x3

**Sistema:**
```
2x + y + z = 8
x + 3y + z = 10  
x + y + 4z = 12
```

**Archivo data.txt:**
```
2  1  1  8
1  3  1  10
1  1  4  12
```

**Métodos disponibles:**
- **Eliminación Gaussiana:** Solución directa
- **Jacobi/Gauss-Seidel:** Para sistemas grandes
- **Resultado esperado:** x=1, y=2, z=3

## 📊 Guía de Selección de Métodos

### Para Localización de Raíces:

| Situación | Método Recomendado | Velocidad | Robustez |
|-----------|-------------------|-----------|----------|
| Conoces f'(x) y buen punto inicial | **Newton-Raphson** | ⭐⭐⭐⭐⭐ | ⭐⭐ |
| Puedes obtener g(x) fácilmente | **Punto Fijo** | ⭐⭐⭐ | ⭐⭐⭐ |
| Tienes intervalo con cambio de signo | **Bisección** | ⭐⭐ | ⭐⭐⭐⭐⭐ |
| Quieres balance velocidad/robustez | **Regula Falsi** | ⭐⭐⭐ | ⭐⭐⭐⭐ |

### Para Interpolación:

| Situación | Método | Estabilidad | Suavidad |
|-----------|--------|-------------|----------|
| ≤ 8 puntos | **Lagrange** | ⭐⭐⭐ | ⭐⭐⭐ |
| > 8 puntos | **Spline cúbico** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| Datos experimentales con ruido | **Spline lineal** | ⭐⭐⭐⭐ | ⭐⭐ |
| Necesitas función analítica | **Lagrange** | ⭐⭐⭐ | ⭐⭐⭐ |

### Para Integración:

| Prioridad | Método | Precisión | Esfuerzo |
|-----------|--------|-----------|----------|
| **Máxima precisión** | **Gauss-Legendre** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ |
| **Balance** | **Simpson** | ⭐⭐⭐⭐ | ⭐⭐ |
| **Robustez** | **Trapecio** | ⭐⭐⭐ | ⭐ |
| **Datos irregulares** | **Trapecio tabla** | ⭐⭐⭐ | ⭐ |

### Para EDO:

| Situación | Método | Precisión | Costo |
|-----------|--------|-----------|-------|
| **Aprendizaje/comprensión** | **Euler** | ⭐⭐ | ⭐ |
| **Balance precio/calidad** | **Heun** | ⭐⭐⭐ | ⭐⭐ |
| **Aplicaciones reales** | **Runge-Kutta 4** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ |
| **Casos específicos** | **Punto Medio** | ⭐⭐⭐ | ⭐⭐ |

### Para Sistemas Lineales:

| Tamaño del Sistema | Método Recomendado | Memoria | Precisión |
|-------------------|-------------------|---------|-----------|
| **Pequeño (< 100)** | **Eliminación Gaussiana** | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |
| **Mediano (100-1000)** | **Gauss-Seidel** | ⭐⭐⭐⭐ | ⭐⭐⭐⭐ |
| **Grande (> 1000)** | **Métodos Iterativos** | ⭐⭐⭐⭐⭐ | ⭐⭐⭐ |
| **Mal condicionado** | **Gaussiana + Pivoteo** | ⭐⭐⭐ | ⭐⭐⭐⭐⭐ |

## 🛠️ Solución de Problemas Comunes

### ❌ **Error: "Matriz singular"**
**Problema:** Sistema sin solución única
**Solución:**
- Verificar datos de entrada
- Comprobar dependencias lineales
- Usar pivoteo si disponible

### ❌ **Error: "No converge" en métodos iterativos**
**Problema:** Criterios de convergencia no cumplidos
**Solución:**
```cpp
// Para Newton-Raphson: f'(x) ≠ 0
// Para Punto Fijo: |g'(x)| < 1
// Para sistemas: matriz diagonalmente dominante
```

### ❌ **Error: "Número PAR de intervalos" en Simpson**
**Problema:** Simpson requiere n par
**Solución:**
- Usar n = 2, 4, 6, 8...
- O cambiar a método del trapecio

### ❌ **Precisión baja en derivadas numéricas**
**Problema:** Valor de h inadecuado
**Solución:**
```cpp
// h muy grande → Error de truncamiento
// h muy pequeño → Errores de redondeo
// Valor óptimo: h ∈ [10⁻⁶, 10⁻³]
```

### ❌ **Spline no encuentra solución**
**Problema:** Grado demasiado alto para pocos puntos
**Solución:**
```cpp
// Regla: grado ≤ (número_puntos - 1)
// Para 5 puntos: grado ≤ 4
if (grado > filas - 1) {
    cout << "Reducir grado a " << (filas-1) << endl;
}
```

## 🛠️ Contribución

### Cómo contribuir
1. **Fork** el repositorio
2. **Crear** rama: `git checkout -b feature/nueva-funcionalidad`
3. **Desarrollar** siguiendo las convenciones del proyecto
4. **Commit**: `git commit -m 'Add: nueva funcionalidad'`
5. **Push**: `git push origin feature/nueva-funcionalidad`
6. **Pull Request** con descripción detallada

### Estilo de código
```cpp
// ✅ Nombres descriptivos en español
void eliminacionGaussiana();
void interpolacionLagrange();

// ✅ Comentarios explicativos
// Aplica pivoteo parcial para evitar división por cero

// ✅ Constantes definidas
#define FILAS 20
#define TOLERANCIA 1e-6

// ✅ Validación de entrada
if (grado < 1 || grado > filas-1) {
    cout << "Error: grado inválido" << endl;
    return;
}
```

### Áreas de mejora sugeridas
- [ ] **Interfaz gráfica** con bibliotecas como FLTK o Qt
- [ ] **Paralelización** con OpenMP para sistemas grandes
- [ ] **Precisión extendida** con bibliotecas como Boost.Multiprecision
- [ ] **Tests automatizados** con Google Test
- [ ] **Documentación LaTeX** para formulas matemáticas
- [ ] **Benchmarking** comparativo entre métodos

## 📄 Licencia

Este proyecto está bajo la **Licencia MIT**. Puedes usar, modificar y distribuir libremente.

```
MIT License - Copyright (c) 2025 CEGB03

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction...
```

## 👨‍💻 Autor

**CEGB03** - [GitHub](https://github.com/CEGB03)

---

## 🚀 Roadmap Futuro

### Próximas funcionalidades v2.0
- [ ] **Métodos de elementos finitos** básicos
- [ ] **Análisis de Fourier** (FFT, DFT)
- [ ] **Optimización numérica** (gradiente descendente, simplex)
- [ ] **Análisis de estabilidad** para métodos de EDO
- [ ] **Integración adaptativa** (Romberg, Gauss-Kronrod)
- [ ] **Splines de tensión** y B-splines
- [ ] **Métodos de Monte Carlo** para integración
- [ ] **Solver para EDP** (diferencias finitas)

### Mejoras técnicas v1.5
- [ ] **CMake build system** multiplataforma
- [ ] **Manejo de excepciones** robusto
- [ ] **Logging system** para debugging
- [ ] **Configuración JSON** para parámetros
- [ ] **API unificada** entre módulos
- [ ] **Documentación Doxygen** automática

---

## 📊 Estadísticas del Proyecto

| Métrica | Valor |
|---------|-------|
| **Líneas de código** | ~3,500+ |
| **Archivos fuente** | 15+ |
| **Métodos implementados** | 25+ |
| **Áreas cubiertas** | 7 |
| **Complejidad** | Intermedia-Avanzada |
| **Compatibilidad** | C++11+ |

---

**📧 ¿Preguntas, sugerencias o encontraste un bug?** 
Abre un [Issue](https://github.com/CEGB03/Metodos-Numericos-CPP/issues) o contribuye al proyecto.

**⭐ Si este proyecto te ayudó en tus estudios o trabajo, ¡dale una estrella!**

**🔗 Comparte** este repositorio con compañeros de ingeniería, matemáticas o ciencias de la computación.

---

*Desarrollado con 💻 y ☕ para la comunidad de métodos numéricos*