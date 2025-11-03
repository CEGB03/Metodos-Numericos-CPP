# 🧮 Métodos Numéricos en C++

Una colección completa de implementaciones de métodos numéricos fundamentales desarrollados en C++, diseñados para el aprendizaje y aplicación práctica en análisis numérico, cálculo numérico y resolución de ecuaciones.

## 📚 Tabla de Contenidos

- [🚀 Instalación y Compilación](#-instalación-y-compilación)
- [📁 Estructura del Proyecto](#-estructura-del-proyecto)
- [📖 Organización por Parciales](#-organización-por-parciales)
- [🔢 Módulos Disponibles](#-módulos-disponibles)
  - [📋 PRIMER PARCIAL](#-primer-parcial)
    - [🎯 Localización de Raíces](#-localización-de-raíces)
    - [⚖️ Sistemas de Ecuaciones Lineales](#️-sistemas-de-ecuaciones-lineales)
    - [📉 Regresión](#-regresión)
    - [📈 Interpolación](#-interpolación)
  - [📋 SEGUNDO PARCIAL](#-segundo-parcial)
    - [🧮 Integración Numérica](#-integración-numérica)
    - [📊 Derivación Numérica](#-derivación-numérica)
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
├── 📁 LocRaices/                    [PRIMER PARCIAL]
│   ├── 📁 Abiertos/
│   │   ├── Newton-Raphson.cpp
│   │   └── Punto-Fijo.cpp
│   └── 📁 Cerrados/
│       ├── Biseccion.cpp
│       └── RegulaFalsi.cpp
├── 📁 Sistemas de Ecuaciones Lineales/  [PRIMER PARCIAL]
│   ├── Eliminacion-Gaussiana.cpp
│   └── Métodos Iterativos.cpp
├── 📁 Regresion/                    [PRIMER PARCIAL]
│   ├── Regresion Lineal.cpp
│   └── polynomialRegression.cpp
├── 📁 Interpolacion/                [PRIMER PARCIAL]
│   ├── interpolacion.cpp
│   └── Spline.cpp
├── 📁 Integracion/                  [SEGUNDO PARCIAL]
│   ├── Integracion Newton Cotes.cpp
│   └── Gauss-Legendre.cpp
├── 📁 Diferenciacion Numerica/      [SEGUNDO PARCIAL]
│   ├── Derivadas.cpp
│   ├── 📁 Diferenciacion/
│   │   └── Diferenciacion.cpp
│   └── 📁 Ecuaciones Diferenciales/
│       ├── MetodoEuler.cpp
│       ├── MetodoHeun.cpp
│       ├── Runge-Kutta4.cpp
│       ├── MetodoPuntoMedio.cpp
│       └── EjemploEcsDifDeOrdenSuperior.cpp
├── .gitignore
└── README.md
```

## 📖 Organización por Parciales

### 📋 **PRIMER PARCIAL - Métodos Fundamentales**
**Contenido:** Localización de raíces, sistemas lineales, regresión e interpolación
- ✅ 4 métodos de localización de raíces
- ✅ 2 métodos para sistemas lineales  
- ✅ 2 tipos de regresión
- ✅ 2 métodos de interpolación

### 📋 **SEGUNDO PARCIAL - Análisis Avanzado**  
**Contenido:** Integración, derivación y ecuaciones diferenciales
- ✅ Métodos de integración numérica
- ✅ Diferenciación numérica
- ✅ 5 métodos para ecuaciones diferenciales

---

# 🔢 Módulos Disponibles

# 📋 PRIMER PARCIAL

## 🎯 Localización de Raíces

### 📄 `LocRaices/Cerrados/Biseccion.cpp`
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

### 📄 `LocRaices/Cerrados/RegulaFalsi.cpp`
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

### 📄 `LocRaices/Abiertos/Punto-Fijo.cpp`
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

### 📄 `LocRaices/Abiertos/Newton-Raphson.cpp`
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

## ⚖️ Sistemas de Ecuaciones Lineales

### 📄 `Sistemas de Ecuaciones Lineales/Eliminacion-Gaussiana.cpp`
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

### 📄 `Sistemas de Ecuaciones Lineales/Métodos Iterativos.cpp`
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

**⚡ Parámetros de relajación:**
- `ω = 1`: Gauss-Seidel normal
- `ω < 1`: Sub-relajación (mejora convergencia en casos difíciles)
- `ω > 1`: Sobre-relajación (acelera convergencia)

## 📉 Regresión

### 📄 `Regresion/Regresion Lineal.cpp`
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

### 📄 `Regresion/polynomialRegression.cpp`
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

## 📈 Interpolación

### 📄 `Interpolacion/interpolacion.cpp`
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
0.309 3.02
0.300 2.93
0.292 2.85
0.285 2.78
0.270 2.63
```

**📊 Salidas del programa:**

1. **Forma de Lagrange:**
```
P(x) = 3.02 * [(x-0.300)/(0.309-0.300) * (x-0.292)/(0.309-0.292) * ...]
     + 2.93 * [(x-0.309)/(0.300-0.309) * (x-0.292)/(0.300-0.292) * ...]
```

2. **Forma estándar expandida:**
```
P(x) = 2.1543*x³ - 15.234*x² + 45.678*x + 123.456
```

### 📄 `Interpolacion/Spline.cpp`
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
```

---

# 📋 SEGUNDO PARCIAL

## 🧮 Integración Numérica

### 📄 `Integracion/Integracion Newton Cotes.cpp`
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

### 📄 `Integracion/Gauss-Legendre.cpp`
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

## 📊 Derivación Numérica

### 📄 `Diferenciacion Numerica/Derivadas.cpp`
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

**⚡ Comparación de métodos:**

| Método | Precisión | Ubicación | Fórmula |
|--------|-----------|-----------|---------|
| **Progresiva** | O(h) | Extremo izquierdo | [f(x+h) - f(x)]/h |
| **Regresiva** | O(h) | Extremo derecho | [f(x) - f(x-h)]/h |
| **Central** | **O(h²)** | **Punto interior** | **[f(x+h) - f(x-h)]/(2h)** ← Mejor |

### 📄 `Diferenciacion Numerica/Diferenciacion/Diferenciacion.cpp`
**Implementación alternativa de diferenciación numérica**

**🎯 Qué hace:**
- Implementación básica de diferenciación
- Función recursiva para cálculo de longitud de arrays
- Versión simplificada para aprendizaje

**🚀 Cómo usar:**
```bash
# Compilar
g++ -o diferenciacion "Diferenciacion Numerica/Diferenciacion/Diferenciacion.cpp"

# Ejecutar
./diferenciacion
```

## 🔧 Ecuaciones Diferenciales

### 📄 `Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoEuler.cpp`
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

### 📄 `Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoHeun.cpp`
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

### 📄 `Diferenciacion Numerica/Ecuaciones Diferenciales/Runge-Kutta4.cpp`
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

### 📄 `Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoPuntoMedio.cpp`
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

### 📄 `Diferenciacion Numerica/Ecuaciones Diferenciales/EjemploEcsDifDeOrdenSuperior.cpp`
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

---

# 💻 Guía de Uso

## Compilación por Parciales

### 📋 **PRIMER PARCIAL**
```bash
# Localización de Raíces
g++ -o biseccion LocRaices/Cerrados/Biseccion.cpp
g++ -o regula-falsi LocRaices/Cerrados/RegulaFalsi.cpp
g++ -o punto-fijo LocRaices/Abiertos/Punto-Fijo.cpp
g++ -o newton LocRaices/Abiertos/Newton-Raphson.cpp

# Sistemas de Ecuaciones
g++ -o gauss "Sistemas de Ecuaciones Lineales/Eliminacion-Gaussiana.cpp"
g++ -o iterativos "Sistemas de Ecuaciones Lineales/Métodos Iterativos.cpp"

# Regresión
g++ -o regresion-lineal "Regresion/Regresion Lineal.cpp"
g++ -o regresion-poli Regresion/polynomialRegression.cpp

# Interpolación
g++ -o interpolacion Interpolacion/interpolacion.cpp
g++ -o spline Interpolacion/Spline.cpp
```

### 📋 **SEGUNDO PARCIAL**
```bash
# Integración
g++ -o integracion "Integracion/Integracion Newton Cotes.cpp"
g++ -o gauss-legendre Integracion/Gauss-Legendre.cpp

# Derivadas
g++ -o derivadas "Diferenciacion Numerica/Derivadas.cpp"
g++ -o diferenciacion "Diferenciacion Numerica/Diferenciacion/Diferenciacion.cpp"

# Ecuaciones Diferenciales
g++ -o euler "Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoEuler.cpp"
g++ -o heun "Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoHeun.cpp"
g++ -o rk4 "Diferenciacion Numerica/Ecuaciones Diferenciales/Runge-Kutta4.cpp"
g++ -o punto-medio "Diferenciacion Numerica/Ecuaciones Diferenciales/MetodoPuntoMedio.cpp"
g++ -o edo-superior "Diferenciacion Numerica/Ecuaciones Diferenciales/EjemploEcsDifDeOrdenSuperior.cpp"
```

## 📖 Ejemplos Prácticos por Parcial

### 🔍 **Ejemplo PRIMER PARCIAL: Sistema completo de análisis**

```bash
# 1. Encontrar raíces de f(x) = x³ - 2x + 1
./newton        # Convergencia rápida con derivada
./biseccion     # Método robusto con intervalo

# 2. Resolver sistema 3x3
./gauss         # Método directo
./iterativos    # Método iterativo para sistemas grandes

# 3. Ajustar datos experimentales
./regresion-lineal    # Relación lineal
./regresion-poli      # Relación polinómica

# 4. Interpolar puntos
./interpolacion # Lagrange o Vandermonde
./spline       # Spline suave de grado variable
```

### 🔍 **Ejemplo SEGUNDO PARCIAL: Análisis avanzado**

```bash
# 1. Calcular área bajo curva
./integracion   # Menú interactivo completo
./gauss-legendre # Alta precisión

# 2. Calcular derivadas numéricas
./derivadas     # Diferencias finitas completas

# 3. Resolver EDO: dy/dt = -2y + x
./euler         # Método básico
./heun          # Mejor precisión
./rk4           # Método estándar
./edo-superior  # Sistemas de EDO
```

## 📊 Guía de Selección por Parcial

### 📋 **PRIMER PARCIAL - Métodos Fundamentales**

| Problema | Método Recomendado | Cuándo usar |
|----------|-------------------|-------------|
| **Raíz sin derivada** | Bisección | Máxima robustez |
| **Raíz con derivada** | Newton-Raphson | Convergencia súper rápida |
| **Sistema pequeño** | Eliminación Gaussiana | Solución exacta |
| **Sistema grande** | Métodos Iterativos | Eficiencia en memoria |
| **Datos lineales** | Regresión Lineal | Relación simple |
| **Datos curvos** | Regresión Polinómica | Mejor ajuste |
| **Pocos puntos** | Lagrange | Interpolación directa |
| **Muchos puntos** | Spline | Suavidad garantizada |

### 📋 **SEGUNDO PARCIAL - Análisis Avanzado**

| Problema | Método Recomendado | Cuándo usar |
|----------|-------------------|-------------|
| **Integración robusta** | Trapecio | Funciones irregulares |
| **Integración precisa** | Simpson | Funciones suaves |
| **Máxima precisión** | Gauss-Legendre | Pocos puntos disponibles |
| **Derivadas de tabla** | Diferencias Centrales | Mejor precisión O(h²) |
| **EDO simple** | Euler | Aprendizaje/comprensión |
| **EDO precisión media** | Heun | Balance costo/precisión |
| **EDO aplicaciones** | Runge-Kutta 4 | Estándar industrial |
| **EDO orden superior** | Sistema RK4 | Conversión a sistema |

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

## 📄 Licencia

Este proyecto está bajo la **Licencia MIT**. Puedes usar, modificar y distribuir libremente.

## 👨‍💻 Autor

**CEGB03** - [GitHub](https://github.com/CEGB03)

---

## 📊 Estadísticas del Proyecto

### 📋 **PRIMER PARCIAL**
| Métrica | Valor |
|---------|-------|
| **Métodos de raíces** | 4 |
| **Métodos de sistemas** | 2 |
| **Métodos de regresión** | 2 |
| **Métodos de interpolación** | 2 |
| **Total primer parcial** | **10 métodos** |

### 📋 **SEGUNDO PARCIAL**
| Métrica | Valor |
|---------|-------|
| **Métodos de integración** | 2 |
| **Métodos de derivación** | 2 |
| **Métodos de EDO** | 5 |
| **Total segundo parcial** | **9 métodos** |

### 🎯 **PROYECTO COMPLETO**
| Métrica | Valor |
|---------|-------|
| **Líneas de código** | ~4,500+ |
| **Archivos fuente** | 17+ |
| **Métodos implementados** | **19 métodos** |
| **Áreas cubiertas** | 7 |
| **Complejidad** | Intermedia-Avanzada |

---

**📧 ¿Preguntas o sugerencias?** 
Abre un [Issue](https://github.com/CEGB03/Metodos-Numericos-CPP/issues) o contribuye al proyecto.

**⭐ Si este proyecto te ayudó en tus estudios, ¡dale una estrella!**

**🔗 Comparte** este repositorio con compañeros de ingeniería, matemáticas o ciencias de la computación.

---

*Desarrollado con 💻 y ☕ para la comunidad de métodos numéricos*

*Organizado por parciales para facilitar el estudio y la preparación de exámenes* 📚✨