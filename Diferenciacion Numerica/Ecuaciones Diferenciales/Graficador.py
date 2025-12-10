#!/usr/bin/env python3
"""
🎯 GRAFICADOR AUTOMÁTICO PARA MÉTODOS NUMÉRICOS
================================================
Graficador simplificado que lee automáticamente archivos con formato:
    metodo_h.txt  (ej: rk4_0.01.txt, euler_0.10.txt, heun_0.01.txt)

Uso:
    python3 Graficador.py              # Grafica todos los .txt del directorio actual
    python3 Graficador.py rk4          # Filtra solo rk4_*.txt
    python3 Graficador.py rk4_0.01.txt # Grafica archivo específico

Autor: CEGB03
"""

import numpy as np
import matplotlib
# Usar backend que no requiere interfaz gráfica
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from pathlib import Path
import sys
import os

# ==========================================
# 🎨 CONFIGURACIÓN DE ESTILOS
# ==========================================

# Colores por método
COLORES_METODOS = {
    'rk4': ['#0066cc', '#0099ff', '#33ccff'],      # Azul (varios tonos)
    'euler': ['#cc6600', '#ff9933', '#ffcc66'],    # Naranja (varios tonos)
    'heun': ['#006600', '#00cc00', '#66ff66'],     # Verde (varios tonos)
    'exacta': ['#cc0000', '#ff3333', '#ff9999'],   # Rojo (varios tonos)
}

# Marcadores diferentes para cada h
MARCADORES_POR_H = ['^', 'o', 's', 'D', 'v', '*', 'p', 'H', '+', 'x']

ESTILOS_LINEA = {
    'rk4': '-',
    'euler': '--',
    'heun': '-.',
    'exacta': '-',
}

# ==========================================
# 🛠️ FUNCIONES AUXILIARES
# ==========================================

def extraer_metodo_y_h(filename):
    """Extrae el método y valor de h del nombre del archivo
    
    Ejemplos:
        rk4_0.01.txt -> ('rk4', 0.01, 'RK4 (h=0.01)')
        euler_0.10.txt -> ('euler', 0.10, 'Euler (h=0.10)')
    """
    stem = Path(filename).stem  # Sin extensión
    partes = stem.split('_')
    
    if len(partes) < 2:
        return None, None, stem
    
    metodo = partes[0].lower()
    try:
        h = float('_'.join(partes[1:]))
        label = f"{metodo.capitalize()} (h={h:.4g})"
        return metodo, h, label
    except ValueError:
        return None, None, stem

def cargar_datos(filepath):
    """Carga datos desde archivo CSV x,y o x,y1,y2"""
    try:
        data = np.genfromtxt(filepath, delimiter=',', skip_header=1)
        
        if data.ndim == 1:
            # Archivo con una sola línea de datos
            x = np.array([0])
            y = data
        else:
            x = data[:, 0]
            y = data[:, 1]  # Tomar solo la primera columna y (ignorar y2 si existe)
        
        return x, y
    except Exception as e:
        print(f"⚠️  Error leyendo {filepath}: {e}")
        return None, None

def encontrar_archivos_datos(filtro=None):
    """Encuentra todos los archivos .txt con formato metodo_h.txt
    
    Args:
        filtro: None (todos), o string para filtrar por método/h (ej: 'rk4', '0.01')
    
    Returns:
        Dict con estructura: {metodo: [(filepath, h, label), ...]}
    """
    archivos = {}
    
    for txt_file in Path('.').glob('*.txt'):
        metodo, h, label = extraer_metodo_y_h(txt_file.name)
        
        if metodo is None:
            continue
        
        # Aplicar filtro si existe
        if filtro:
            filtro_lower = filtro.lower()
            if filtro_lower not in txt_file.name.lower():
                continue
        
        if metodo not in archivos:
            archivos[metodo] = []
        
        archivos[metodo].append((str(txt_file), h, label))
    
    # Ordenar por h dentro de cada método
    for metodo in archivos:
        archivos[metodo].sort(key=lambda x: x[1])
    
    return archivos

def graficar_automatico(filtro=None):
    """Función principal que ejecuta el graficador automático"""
    
    print("🎯 GRAFICADOR AUTOMÁTICO DE MÉTODOS NUMÉRICOS")
    print("=" * 60)
    
    # Encontrar archivos
    archivos = encontrar_archivos_datos(filtro)
    
    if not archivos:
        print(f"❌ No se encontraron archivos .txt")
        if filtro:
            print(f"   (Filtro usado: '{filtro}')")
        return
    
    print(f"📊 Archivos encontrados:")
    for metodo in sorted(archivos.keys()):
        print(f"   {metodo}:")
        for filepath, h, label in archivos[metodo]:
            print(f"      ✓ {Path(filepath).name}")
    
    # Crear figura
    fig, ax = plt.subplots(figsize=(12, 7), dpi=100)
    
    # Graficar datos
    total_lineas = 0
    
    for metodo in sorted(archivos.keys()):
        for idx, (filepath, h, label) in enumerate(archivos[metodo]):
            x, y = cargar_datos(filepath)
            
            if x is None or y is None:
                continue
            
            # Obtener colores para este método
            colores_disponibles = COLORES_METODOS.get(metodo, ['#000000'])
            color_idx = idx % len(colores_disponibles)
            color = colores_disponibles[color_idx]
            
            # Obtener marcador diferente para cada h
            marker_idx = idx % len(MARCADORES_POR_H)
            marker = MARCADORES_POR_H[marker_idx]
            
            linestyle = ESTILOS_LINEA.get(metodo, '-')
            
            # Graficar
            if len(x) > 1:
                ax.plot(x, y,
                       color=color,
                       marker=marker,
                       linestyle=linestyle,
                       label=label,
                       linewidth=2,
                       markersize=4,
                       alpha=0.8)
            else:
                ax.plot(x, y, marker, color=color, label=label, markersize=8)
            
            total_lineas += 1
            print(f"   📈 Graficado: {label}")
    
    if total_lineas == 0:
        print("❌ No se pudieron graficar datos válidos")
        return
    
    # Configurar gráfico
    ax.set_xlabel('x', fontsize=12, fontweight='bold')
    ax.set_ylabel('y', fontsize=12, fontweight='bold')
    ax.set_title('Comparación de Métodos Numéricos', fontsize=14, fontweight='bold')
    ax.grid(True, alpha=0.3, linestyle='--')
    ax.legend(loc='best', framealpha=0.95, fontsize=10)
    
    # Ajustar layout
    plt.tight_layout()
    
    # Guardar
    output_file = 'comparacion.png'
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    print(f"\n💾 Gráfico guardado como: {output_file}")
    
    # Abrir la imagen con el visor disponible
    import subprocess
    visores = ['feh', 'eog', 'display', 'gpicview', 'xdg-open']
    abierto = False
    
    for visor in visores:
        try:
            print(f"🖼️  Abriendo con {visor}...")
            subprocess.Popen([visor, output_file])
            abierto = True
            break
        except FileNotFoundError:
            continue
    
    if not abierto:
        print(f"ℹ️  No se pudo abrir automáticamente.")
        print(f"   Abre manualmente: {output_file}")
    
    print(f"✅ Proceso completado. {total_lineas} línea(s) graficada(s).\n")

# ==========================================
# 🎮 INTERFAZ DE USUARIO
# ==========================================

def mostrar_menu():
    """Menú interactivo del graficador"""
    
    print("\n🎯 GRAFICADOR AUTOMÁTICO - MENÚ")
    print("=" * 60)
    print("Opciones:")
    print("  1) Graficar TODOS los archivos .txt del directorio")
    print("  2) Graficar solo archivos RK4")
    print("  3) Graficar solo archivos EULER")
    print("  4) Graficar solo archivos HEUN")
    print("  5) Graficar un h específico (ej: 0.01)")
    print("  6) Salir")
    print("=" * 60)

def menu_interactivo():
    """Bucle interactivo del menú"""
    
    while True:
        mostrar_menu()
        
        try:
            opcion = input("Seleccione opción (1-6): ").strip()
            
            if opcion == '1':
                graficar_automatico()
            elif opcion == '2':
                graficar_automatico('rk4')
            elif opcion == '3':
                graficar_automatico('euler')
            elif opcion == '4':
                graficar_automatico('heun')
            elif opcion == '5':
                h = input("Ingrese h (ej: 0.01): ").strip()
                graficar_automatico(h)
            elif opcion == '6':
                print("👋 ¡Hasta luego!")
                break
            else:
                print("❌ Opción no válida. Intente de nuevo.\n")
                
        except KeyboardInterrupt:
            print("\n👋 ¡Hasta luego!")
            break

# ==========================================
# 🎯 EJECUCIÓN PRINCIPAL
# ==========================================

if __name__ == "__main__":
    
    if len(sys.argv) > 1:
        # Ejecución con argumentos: Graficador.py rk4_0.01.txt
        filtro = sys.argv[1]
        print(f"Usando filtro: {filtro}")
        graficar_automatico(filtro)
    else:
        # Ejecución interactiva
        menu_interactivo()