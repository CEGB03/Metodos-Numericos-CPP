#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <filesystem>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <map>

using namespace std;
namespace fs = filesystem;

// ==========================================
// 🎨 ESTRUCTURA Y CONFIGURACIÓN
// ==========================================

struct Archivo {
    string ruta;
    string metodo;
    double h;
    string label;
};

struct Punto {
    double x;
    double y;
};

// Colores para gnuplot (RGB en hexadecimal)
map<string, string> COLORES = {
    {"rk4", "#1f77b4"},      // Azul
    {"euler", "#ff7f0e"},    // Naranja
    {"heun", "#2ca02c"},     // Verde
    {"exacta", "#d62728"},   // Rojo
};

map<string, string> MARCADORES = {
    {"rk4", "^"},
    {"euler", "o"},
    {"heun", "s"},
    {"exacta", "-"},
};

map<string, string> ESTILOS_LINEA = {
    {"rk4", "solid"},
    {"euler", "dashed"},
    {"heun", "dashdot"},
    {"exacta", "solid"},
};

// ==========================================
// 🛠️ FUNCIONES AUXILIARES
// ==========================================

// Extrae el método y h del nombre del archivo
bool extraer_metodo_y_h(const string& filename, string& metodo, double& h, string& label) {
    // Esperado: "rk4_0.01.txt"
    size_t dot_pos = filename.find_last_of('.');
    if (dot_pos == string::npos) return false;
    
    string stem = filename.substr(0, dot_pos);
    size_t underscore_pos = stem.find_last_of('_');
    if (underscore_pos == string::npos) return false;
    
    metodo = stem.substr(0, underscore_pos);
    string h_str = stem.substr(underscore_pos + 1);
    
    try {
        h = stod(h_str);
        
        // Convertir primera letra a mayúscula
        string metodo_cap = metodo;
        metodo_cap[0] = toupper(metodo_cap[0]);
        
        // Crear label
        char buf[100];
        snprintf(buf, sizeof(buf), "%s (h=%.4g)", metodo_cap.c_str(), h);
        label = buf;
        
        return true;
    } catch (...) {
        return false;
    }
}

// Carga datos desde archivo CSV
bool cargar_datos(const string& filepath, vector<Punto>& datos) {
    ifstream file(filepath);
    if (!file.is_open()) {
        cerr << "Error: No se pudo abrir " << filepath << endl;
        return false;
    }
    
    string linea;
    int linea_num = 0;
    
    // Saltar encabezado
    getline(file, linea);
    
    while (getline(file, linea)) {
        linea_num++;
        
        // Ignorar líneas vacías
        if (linea.empty() || linea[0] == '#') continue;
        
        // Buscar primera coma
        size_t comma1 = linea.find(',');
        if (comma1 == string::npos) continue;
        
        try {
            double x = stod(linea.substr(0, comma1));
            double y = stod(linea.substr(comma1 + 1));
            datos.push_back({x, y});
        } catch (...) {
            cerr << "Advertencia: Error parsiendo línea " << linea_num << " de " << filepath << endl;
        }
    }
    
    file.close();
    return !datos.empty();
}

// Encuentra archivos con formato metodo_h.txt
vector<Archivo> encontrar_archivos(const string& filtro = "") {
    vector<Archivo> resultado;
    
    try {
        for (const auto& entry : fs::directory_iterator(".")) {
            if (!entry.is_regular_file()) continue;
            
            string filename = entry.path().filename().string();
            
            // Solo procesar archivos .txt
            if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt") {
                continue;
            }
            
            string metodo;
            double h;
            string label;
            
            if (!extraer_metodo_y_h(filename, metodo, h, label)) {
                continue;
            }
            
            // Aplicar filtro
            if (!filtro.empty()) {
                string filtro_lower = filtro;
                string filename_lower = filename;
                transform(filtro_lower.begin(), filtro_lower.end(), filtro_lower.begin(), ::tolower);
                transform(filename_lower.begin(), filename_lower.end(), filename_lower.begin(), ::tolower);
                
                if (filename_lower.find(filtro_lower) == string::npos) {
                    continue;
                }
            }
            
            resultado.push_back({entry.path().string(), metodo, h, label});
        }
    } catch (const exception& e) {
        cerr << "Error al buscar archivos: " << e.what() << endl;
    }
    
    // Ordenar por método y luego por h
    sort(resultado.begin(), resultado.end(), [](const Archivo& a, const Archivo& b) {
        if (a.metodo != b.metodo) return a.metodo < b.metodo;
        return a.h < b.h;
    });
    
    return resultado;
}

// Genera script de gnuplot
bool generar_gnuplot_script(const vector<Archivo>& archivos, const string& output_file) {
    ofstream script("temp_plot.gp");
    if (!script.is_open()) {
        cerr << "Error: No se pudo crear script de gnuplot" << endl;
        return false;
    }
    
    // Encabezado - sintaxis compatible con gnuplot 6.0
    script << "set terminal png size 1200,700\n";
    script << "set output '" << output_file << "'\n";
    script << "set title 'Comparación de Métodos Numéricos'\n";
    script << "set xlabel 'x'\n";
    script << "set ylabel 'y'\n";
    script << "set grid\n";
    script << "set style data linespoints\n";
    script << "set key top right\n";
    script << "set datafile separator ','\n\n";
    
    // Construir comando plot
    script << "plot ";
    
    for (size_t i = 0; i < archivos.size(); i++) {
        const Archivo& arch = archivos[i];
        
        if (i > 0) script << ", ";
        
        // Convertir a ruta absoluta
        string ruta_absoluta = fs::absolute(arch.ruta).string();
        script << "'" << ruta_absoluta << "' using 1:2 ";
        script << "title '" << arch.label << "' ";
        script << "with linespoints ";
        script << "linewidth 2 pointsize 0.5";
    }
    
    script << "\n";
    
    // Cerrar script
    script.close();
    return true;
}

// Ejecuta gnuplot o usa alternativa
bool ejecutar_gnuplot() {
    // Intentar múltiples rutas de gnuplot
    vector<string> rutas_gnuplot = {
        "gnuplot",
        "/usr/bin/gnuplot",
        "/usr/local/bin/gnuplot",
        "/opt/local/bin/gnuplot"
    };
    
    int result = -1;
    
    for (const auto& ruta : rutas_gnuplot) {
        string comando = ruta + " temp_plot.gp 2>/dev/null";
        result = system(comando.c_str());
        
        if (result == 0) {
            remove("temp_plot.gp");
            return true;
        }
    }
    
    // Si gnuplot no está disponible, mostrar instrucciones
    cout << "\n⚠️  gnuplot no encontrado en el sistema\n";
    cout << "Opciones:\n";
    cout << "  1. Instalarlo: sudo apt install gnuplot\n";
    cout << "  2. Ejecutar manualmente: gnuplot < temp_plot.gp\n";
    cout << "  3. Usar Graficador.py: python3 Graficador.py\n\n";
    cout << "Script guardado en: temp_plot.gp\n";
    
    return false;
}

// Muestra información de archivos encontrados
void mostrar_info_archivos(const vector<Archivo>& archivos) {
    cout << "\n📊 Archivos encontrados:\n";
    
    string metodo_actual = "";
    for (const Archivo& arch : archivos) {
        if (arch.metodo != metodo_actual) {
            metodo_actual = arch.metodo;
            cout << "\n   " << metodo_actual << ":\n";
        }
        cout << "      ✓ " << fs::path(arch.ruta).filename().string() << endl;
    }
    cout << "\n";
}

// Construir nombre descriptivo del archivo PNG
string construir_nombre_comparacion(const vector<Archivo>& archivos) {
    if (archivos.empty()) return "comparacion.png";
    
    string nombre = "comparacion";
    string metodo_anterior = "";
    int contador = 0;
    
    for (const Archivo& arch : archivos) {
        if (arch.metodo != metodo_anterior) {
            if (contador > 0) nombre += "-";
            nombre += arch.metodo;
            
            char buf[50];
            snprintf(buf, sizeof(buf), "_h");
            nombre += buf;
            
            int h_count = 0;
            for (const Archivo& a : archivos) {
                if (a.metodo == arch.metodo) {
                    if (h_count > 0) nombre += "_";
                    snprintf(buf, sizeof(buf), "%.4g", a.h);
                    nombre += buf;
                    h_count++;
                }
            }
            
            metodo_anterior = arch.metodo;
            contador++;
        }
    }
    
    return nombre + ".png";
}

// Grafica automáticamente
bool graficar_automatico(const string& filtro = "") {
    cout << "🎯 GRAFICADOR AUTOMÁTICO DE MÉTODOS NUMÉRICOS\n";
    cout << "=" << string(58, '=') << "\n\n";
    
    // Encontrar archivos
    vector<Archivo> archivos = encontrar_archivos(filtro);
    
    if (archivos.empty()) {
        cout << "❌ No se encontraron archivos .txt\n";
        if (!filtro.empty()) {
            cout << "   (Filtro usado: '" << filtro << "')\n";
        }
        return false;
    }
    
    // Mostrar información
    mostrar_info_archivos(archivos);
    
    cout << "📈 Cargando datos...\n\n";
    
    // Cargar todos los datos para validación
    int archivos_validos = 0;
    for (Archivo& arch : archivos) {
        vector<Punto> datos;
        if (cargar_datos(arch.ruta, datos)) {
            cout << "   ✓ " << arch.label << " (" << datos.size() << " puntos)\n";
            archivos_validos++;
        } else {
            cout << "   ✗ " << arch.label << " (error al cargar)\n";
        }
    }
    
    if (archivos_validos == 0) {
        cout << "\n❌ No se pudieron cargar datos válidos\n";
        return false;
    }
    
    cout << "\n🎨 Generando gráfico...\n";
    
    // Construir nombre descriptivo
    string output_file = construir_nombre_comparacion(archivos);
    
    // Generar script
    if (!generar_gnuplot_script(archivos, output_file)) {
        return false;
    }
    
    // Ejecutar gnuplot
    bool gnuplot_ok = ejecutar_gnuplot();
    
    if (gnuplot_ok) {
        cout << "💾 Gráfico guardado como: " << output_file << "\n";
    } else {
        cout << "⚠️  No se pudo generar el gráfico PNG automáticamente\n";
        cout << "   Pero puedes ejecutar manualmente:\n";
        cout << "   $ gnuplot temp_plot.gp\n";
        cout << "   O usar la alternativa Python:\n";
        cout << "   $ python3 Graficador.py\n";
    }
    
    cout << "✅ Proceso completado. " << archivos_validos << " línea(s) procesada(s).\n\n";
    
    return true;
}

// Menú interactivo
void menu_interactivo() {
    while (true) {
        cout << "\n🎯 GRAFICADOR AUTOMÁTICO - MENÚ\n";
        cout << "=" << string(58, '=') << "\n";
        cout << "Opciones:\n";
        cout << "  1) Graficar TODOS los archivos .txt del directorio\n";
        cout << "  2) Graficar solo archivos RK4\n";
        cout << "  3) Graficar solo archivos EULER\n";
        cout << "  4) Graficar solo archivos HEUN\n";
        cout << "  5) Graficar un h específico (ej: 0.01)\n";
        cout << "  6) Salir\n";
        cout << "=" << string(58, '=') << "\n";
        cout << "Seleccione opción (1-6): ";
        
        string opcion;
        getline(cin, opcion);
        
        if (opcion == "1") {
            graficar_automatico();
        } else if (opcion == "2") {
            graficar_automatico("rk4");
        } else if (opcion == "3") {
            graficar_automatico("euler");
        } else if (opcion == "4") {
            graficar_automatico("heun");
        } else if (opcion == "5") {
            cout << "Ingrese h (ej: 0.01): ";
            string h;
            getline(cin, h);
            graficar_automatico(h);
        } else if (opcion == "6") {
            cout << "👋 ¡Hasta luego!\n";
            break;
        } else {
            cout << "❌ Opción no válida. Intente de nuevo.\n";
        }
    }
}

// ==========================================
// 🎯 FUNCIÓN PRINCIPAL
// ==========================================

int main(int argc, char* argv[]) {
    if (argc > 1) {
        // Ejecución con argumentos
        string filtro = argv[1];
        cout << "Usando filtro: " << filtro << "\n";
        graficar_automatico(filtro);
    } else {
        // Ejecución interactiva
        menu_interactivo();
    }
    
    return 0;
}
