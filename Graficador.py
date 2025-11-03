"""
🎯 GRAFICADOR AUTOMÁTICO PARA MÉTODOS NUMÉRICOS
===============================================
Graficador totalmente automático y configurable para comparar métodos numéricos.
Solo necesitas modificar la configuración al inicio del archivo.

Autor: CEGB03
"""

import numpy as np
import matplotlib.pyplot as plt
import os
from pathlib import Path

# ==========================================
# 📊 CONFIGURACIÓN PRINCIPAL
# ==========================================

# 🎯 ARCHIVOS A GRAFICAR (agregar/quitar según necesites)
ARCHIVOS_CONFIG = [
    {
        'archivo': 'data-Exacta.txt',
        'label': 'Solución Exacta', 
        'color': 'red',
        'marker': 'o',
        'estilo': '-'
    },
    {
        'archivo': 'data-RK4.txt',
        'label': 'Runge-Kutta 4',
        'color': 'blue', 
        'marker': '^',
        'estilo': '--'
    },
    {
        'archivo': 'data-Euler.txt',
        'label': 'Método de Euler',
        'color': 'green',
        'marker': 's',
        'estilo': '-.'
    },
    {
        'archivo': 'data-Heun.txt', 
        'label': 'Método de Heun',
        'color': 'orange',
        'marker': 'x',
        'estilo': ':'
    }
]

# 📁 DIRECTORIOS A BUSCAR (en orden de prioridad)
DIRECTORIOS_BUSQUEDA = [
    '/home/cegb03/Documentos/Metodos-Numericos-Cpp/',  # Directorio actual
    './data/',  # Subcarpeta data
    './',       # Directorio actual
]

# 🎨 CONFIGURACIÓN DEL GRÁFICO
CONFIGURACION_GRAFICO = {
    'titulo': 'Comparación de Métodos Numéricos para EDO',
    'xlabel': 'x',
    'ylabel': 'y(x)',
    'grid': True,
    'xlim': 'auto',  # 'auto' o (min, max)
    'ylim': 'auto',  # 'auto' o (min, max)
    'figsize': (10, 6),
    'dpi': 100,
    'estilo': 'seaborn-v0_8-darkgrid'  # Estilo del gráfico
}

# 💾 CONFIGURACIÓN DE GUARDADO
GUARDAR_CONFIG = {
    'guardar': True,
    'nombre_archivo': 'comparacion_metodos.png',
    'formato': 'png',  # png, pdf, svg, jpg
    'dpi': 300
}

# ==========================================
# 🛠️ FUNCIONES AUXILIARES
# ==========================================

def buscar_archivo(nombre_archivo):
    """Busca un archivo en los directorios configurados"""
    for directorio in DIRECTORIOS_BUSQUEDA:
        ruta_completa = Path(directorio) / nombre_archivo
        if ruta_completa.exists():
            print(f"✅ Encontrado: {ruta_completa}")
            return str(ruta_completa)
    
    print(f"❌ No encontrado: {nombre_archivo}")
    return None

def cargar_datos(ruta_archivo):
    """Carga datos desde archivo de texto"""
    try:
        data = np.loadtxt(ruta_archivo)
        if data.ndim == 1:
            # Si es un vector, asumir que x son índices
            x = np.arange(len(data))
            y = data
        else:
            # Si es matriz, tomar primeras dos columnas
            x = data[:, 0]
            y = data[:, 1]
        return x, y
    except Exception as e:
        print(f"❌ Error cargando {ruta_archivo}: {e}")
        return None, None

def aplicar_estilo_grafico():
    """Aplica el estilo configurado al gráfico"""
    try:
        plt.style.use(CONFIGURACION_GRAFICO['estilo'])
    except:
        print("⚠️ Estilo no disponible, usando estilo por defecto")
        plt.style.use('default')

def configurar_limites(x_data, y_data):
    """Configura los límites del gráfico"""
    # Límites X
    if CONFIGURACION_GRAFICO['xlim'] == 'auto':
        if x_data:
            x_min, x_max = min(min(x) for x in x_data), max(max(x) for x in x_data)
            margen_x = (x_max - x_min) * 0.05
            plt.xlim(x_min - margen_x, x_max + margen_x)
    else:
        plt.xlim(CONFIGURACION_GRAFICO['xlim'])
    
    # Límites Y
    if CONFIGURACION_GRAFICO['ylim'] == 'auto':
        if y_data:
            y_min, y_max = min(min(y) for y in y_data), max(max(y) for y in y_data)
            margen_y = (y_max - y_min) * 0.05
            plt.ylim(y_min - margen_y, y_max + margen_y)
    else:
        plt.ylim(CONFIGURACION_GRAFICO['ylim'])

# ==========================================
# 🚀 FUNCIÓN PRINCIPAL
# ==========================================

def graficar_automatico():
    """Función principal que ejecuta el graficador automático"""
    
    print("🎯 GRAFICADOR AUTOMÁTICO INICIADO")
    print("=" * 50)
    
    # Aplicar estilo
    aplicar_estilo_grafico()
    
    # Crear figura
    plt.figure(figsize=CONFIGURACION_GRAFICO['figsize'], dpi=CONFIGURACION_GRAFICO['dpi'])
    
    # Variables para almacenar datos
    x_data_list = []
    y_data_list = []
    archivos_graficados = 0
    
    # Procesar cada archivo configurado
    for config in ARCHIVOS_CONFIG:
        archivo = config['archivo']
        
        # Buscar archivo
        ruta = buscar_archivo(archivo)
        if ruta is None:
            continue
            
        # Cargar datos
        x, y = cargar_datos(ruta)
        if x is None or y is None:
            continue
            
        # Graficar
        plt.plot(x, y, 
                marker=config['marker'],
                color=config['color'],
                linestyle=config['estilo'],
                label=config['label'],
                linewidth=2,
                markersize=6,
                alpha=0.8)
        
        # Almacenar para configurar límites
        x_data_list.append(x)
        y_data_list.append(y)
        archivos_graficados += 1
        
        print(f"📈 Graficado: {config['label']} ({len(x)} puntos)")
    
    # Verificar si se graficó algo
    if archivos_graficados == 0:
        print("❌ No se encontraron archivos válidos para graficar")
        return
    
    # Configurar gráfico
    plt.title(CONFIGURACION_GRAFICO['titulo'], fontsize=14, fontweight='bold')
    plt.xlabel(CONFIGURACION_GRAFICO['xlabel'], fontsize=12)
    plt.ylabel(CONFIGURACION_GRAFICO['ylabel'], fontsize=12)
    
    if CONFIGURACION_GRAFICO['grid']:
        plt.grid(True, alpha=0.3)
    
    # Configurar límites
    configurar_limites(x_data_list, y_data_list)
    
    # Leyenda
    plt.legend(loc='best', framealpha=0.9)
    
    # Ajustar layout
    plt.tight_layout()
    
    # Guardar si está configurado
    if GUARDAR_CONFIG['guardar']:
        nombre_archivo = GUARDAR_CONFIG['nombre_archivo']
        formato = GUARDAR_CONFIG['formato']
        dpi = GUARDAR_CONFIG['dpi']
        
        plt.savefig(nombre_archivo, format=formato, dpi=dpi, bbox_inches='tight')
        print(f"💾 Gráfico guardado como: {nombre_archivo}")
    
    # Mostrar
    print("🎨 Mostrando gráfico...")
    plt.show()
    
    print(f"✅ Proceso completado. Archivos graficados: {archivos_graficados}")

# ==========================================
# 📝 CONFIGURACIONES PREDEFINIDAS
# ==========================================

def config_edo_basicos():
    """Configuración para métodos básicos de EDO"""
    global ARCHIVOS_CONFIG, CONFIGURACION_GRAFICO
    
    ARCHIVOS_CONFIG = [
        {'archivo': 'exacta.txt', 'label': 'Exacta', 'color': 'black', 'marker': '-', 'estilo': '-'},
        {'archivo': 'euler.txt', 'label': 'Euler', 'color': 'red', 'marker': 'o', 'estilo': '--'},
        {'archivo': 'heun.txt', 'label': 'Heun', 'color': 'blue', 'marker': '^', 'estilo': '-.'},
        {'archivo': 'rk4.txt', 'label': 'RK4', 'color': 'green', 'marker': 's', 'estilo': ':'}
    ]
    
    CONFIGURACION_GRAFICO.update({
        'titulo': 'Comparación Métodos EDO Básicos',
        'xlabel': 't',
        'ylabel': 'y(t)'
    })

def config_integracion():
    """Configuración para métodos de integración"""
    global ARCHIVOS_CONFIG, CONFIGURACION_GRAFICO
    
    ARCHIVOS_CONFIG = [
        {'archivo': 'trapecio.txt', 'label': 'Trapecio', 'color': 'blue', 'marker': 'o', 'estilo': '-'},
        {'archivo': 'simpson.txt', 'label': 'Simpson', 'color': 'red', 'marker': '^', 'estilo': '--'},
        {'archivo': 'gauss.txt', 'label': 'Gauss-Legendre', 'color': 'green', 'marker': 's', 'estilo': '-.'}
    ]
    
    CONFIGURACION_GRAFICO.update({
        'titulo': 'Comparación Métodos de Integración',
        'xlabel': 'Número de intervalos',
        'ylabel': 'Valor integral'
    })

def config_interpolacion():
    """Configuración para métodos de interpolación"""
    global ARCHIVOS_CONFIG, CONFIGURACION_GRAFICO
    
    ARCHIVOS_CONFIG = [
        {'archivo': 'datos_originales.txt', 'label': 'Datos', 'color': 'black', 'marker': 'o', 'estilo': 'none'},
        {'archivo': 'lagrange.txt', 'label': 'Lagrange', 'color': 'red', 'marker': '', 'estilo': '-'},
        {'archivo': 'spline.txt', 'label': 'Spline', 'color': 'blue', 'marker': '', 'estilo': '--'}
    ]
    
    CONFIGURACION_GRAFICO.update({
        'titulo': 'Comparación Métodos de Interpolación',
        'xlabel': 'x',
        'ylabel': 'y'
    })

# ==========================================
# 🎮 MENÚ INTERACTIVO
# ==========================================

def menu_interactivo():
    """Menú para seleccionar configuración predefinida"""
    
    print("\n🎯 GRAFICADOR AUTOMÁTICO - MENÚ DE CONFIGURACIÓN")
    print("=" * 55)
    print("1. 📊 Configuración actual")
    print("2. 🔧 EDO Básicos (Euler, Heun, RK4)")
    print("3. 🧮 Integración Numérica") 
    print("4. 📈 Interpolación")
    print("5. 🚀 Ejecutar con configuración actual")
    print("6. ❌ Salir")
    print("=" * 55)
    
    while True:
        try:
            opcion = input("Seleccione opción (1-6): ").strip()
            
            if opcion == '1':
                mostrar_configuracion_actual()
            elif opcion == '2':
                config_edo_basicos()
                print("✅ Configuración cambiada a: EDO Básicos")
            elif opcion == '3':
                config_integracion()
                print("✅ Configuración cambiada a: Integración")
            elif opcion == '4':
                config_interpolacion()
                print("✅ Configuración cambiada a: Interpolación")
            elif opcion == '5':
                graficar_automatico()
                break
            elif opcion == '6':
                print("👋 ¡Hasta luego!")
                break
            else:
                print("❌ Opción inválida. Intente de nuevo.")
                
        except KeyboardInterrupt:
            print("\n👋 ¡Hasta luego!")
            break

def mostrar_configuracion_actual():
    """Muestra la configuración actual"""
    print(f"\n📊 CONFIGURACIÓN ACTUAL:")
    print(f"Título: {CONFIGURACION_GRAFICO['titulo']}")
    print(f"Archivos a graficar:")
    for i, config in enumerate(ARCHIVOS_CONFIG, 1):
        print(f"  {i}. {config['archivo']} -> {config['label']}")

# ==========================================
# 🎯 EJECUCIÓN PRINCIPAL
# ==========================================

if __name__ == "__main__":
    # Detectar si se está ejecutando interactivamente
    import sys
    
    if len(sys.argv) > 1:
        # Ejecución con argumentos
        if sys.argv[1] == 'edo':
            config_edo_basicos()
        elif sys.argv[1] == 'int':
            config_integracion()
        elif sys.argv[1] == 'interp':
            config_interpolacion()
        
        graficar_automatico()
    else:
        # Ejecución interactiva
        menu_interactivo()