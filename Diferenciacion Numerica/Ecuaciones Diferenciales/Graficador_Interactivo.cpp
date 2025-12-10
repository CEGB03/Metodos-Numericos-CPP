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

// ==========================================
// 🛠️ FUNCIONES AUXILIARES
// ==========================================

bool extraer_metodo_y_h(const string& filename, string& metodo, double& h, string& label) {
    size_t dot_pos = filename.find_last_of('.');
    if (dot_pos == string::npos) return false;
    
    string stem = filename.substr(0, dot_pos);
    size_t underscore_pos = stem.find_last_of('_');
    if (underscore_pos == string::npos) return false;
    
    metodo = stem.substr(0, underscore_pos);
    string h_str = stem.substr(underscore_pos + 1);
    
    try {
        h = stod(h_str);
        
        string metodo_cap = metodo;
        metodo_cap[0] = toupper(metodo_cap[0]);
        
        char buf[100];
        snprintf(buf, sizeof(buf), "%s (h=%.4g)", metodo_cap.c_str(), h);
        label = buf;
        
        return true;
    } catch (...) {
        return false;
    }
}

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
        
        if (linea.empty() || linea[0] == '#') continue;
        
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

vector<Archivo> encontrar_archivos(const string& filtro = "") {
    vector<Archivo> resultado;
    
    try {
        for (const auto& entry : fs::directory_iterator(".")) {
            if (!entry.is_regular_file()) continue;
            
            string filename = entry.path().filename().string();
            
            if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt") {
                continue;
            }
            
            string metodo;
            double h;
            string label;
            
            if (!extraer_metodo_y_h(filename, metodo, h, label)) {
                continue;
            }
            
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
    
    sort(resultado.begin(), resultado.end(), [](const Archivo& a, const Archivo& b) {
        if (a.metodo != b.metodo) return a.metodo < b.metodo;
        return a.h < b.h;
    });
    
    return resultado;
}

// =========================================================================
// 🛠️ CONSTRUIR NOMBRE DESCRIPTIVO
// =========================================================================
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

// =========================================================================
// 🖥️ GENERA SCRIPT DE GNUPLOT INTERACTIVO (con zoom, pan, exportación)
// =========================================================================
bool generar_gnuplot_script_interactivo(const vector<Archivo>& archivos, const string& output_file) {
    ofstream script("temp_plot.gp");
    if (!script.is_open()) {
        cerr << "Error: No se pudo crear script de gnuplot" << endl;
        return false;
    }
    
    // Terminal interactivo (wxt o qt con soporte completo)
    script << "set terminal wxt size 1200,700 title 'Comparación de Métodos Numéricos'\n";
    script << "# Alternativa si wxt no funciona: set terminal qt\n\n";
    
    script << "set title 'Comparación de Métodos Numéricos'\n";
    script << "set xlabel 'x'\n";
    script << "set ylabel 'y'\n";
    script << "set grid\n";
    script << "set style data linespoints\n";
    script << "set key top right\n";
    script << "set datafile separator ','\n\n";
    
    // Comandos interactivos
    script << "# Controles:\n";
    script << "#   Rueda del ratón: Zoom\n";
    script << "#   Click + Arrastrar: Pan (mover vista)\n";
    script << "#   Click derecho + menú: Exportar a PNG\n";
    script << "#   'q': Salir\n\n";
    
    // Construcción del plot
    script << "plot ";
    
    for (size_t i = 0; i < archivos.size(); i++) {
        const Archivo& arch = archivos[i];
        
        if (i > 0) script << ", ";
        
        script << "'" << arch.ruta << "' using 1:2 ";
        script << "title '" << arch.label << "' ";
        script << "with linespoints ";
        script << "linewidth 2 pointsize 0.8";
    }
    
    script << "\n\n";
    
    // Comando para exportar a PNG
    script << "# Para exportar a PNG después de hacer zoom/pan:\n";
    script << "# set terminal png size 1200,700\n";
    script << "# set output 'comparacion_export.png'\n";
    script << "# replot\n";
    
    script.close();
    return true;
}

// =========================================================================
// 🎯 GRAFICA CON INTERFAZ INTERACTIVA
// =========================================================================
bool graficar_interactivo(const string& filtro = "") {
    cout << "🎯 GRAFICADOR INTERACTIVO DE MÉTODOS NUMÉRICOS\n";
    cout << "=" << string(58, '=') << "\n\n";
    
    vector<Archivo> archivos = encontrar_archivos(filtro);
    
    if (archivos.empty()) {
        cout << "❌ No se encontraron archivos .txt\n";
        if (!filtro.empty()) {
            cout << "   (Filtro usado: '" << filtro << "')\n";
        }
        return false;
    }
    
    // Mostrar información
    cout << "📊 Archivos encontrados:\n\n";
    string metodo_actual = "";
    for (const Archivo& arch : archivos) {
        if (arch.metodo != metodo_actual) {
            metodo_actual = arch.metodo;
            cout << "   " << metodo_actual << ":\n";
        }
        cout << "      ✓ " << fs::path(arch.ruta).filename().string() << endl;
    }
    cout << "\n";
    
    cout << "📈 Cargando datos...\n\n";
    
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
    
    cout << "\n🎨 Generando gráfico interactivo...\n";
    cout << "   (Se abrirá una ventana. Usa el ratón para zoom/pan)\n\n";
    
    // Construir nombre descriptivo
    string output_file = construir_nombre_comparacion(archivos);
    
    // Generar script
    if (!generar_gnuplot_script_interactivo(archivos, output_file)) {
        return false;
    }
    
    // Crear script para PNG con mejor resolución
    ofstream script_png("temp_plot_png.gp");
    script_png << "set terminal png size 1400,800 enhanced\n";
    script_png << "set output '" << output_file << "'\n";
    script_png << "set title 'Comparación de Métodos Numéricos'\n";
    script_png << "set xlabel 'x'\n";
    script_png << "set ylabel 'y'\n";
    script_png << "set grid\n";
    script_png << "set style data linespoints\n";
    script_png << "set key top right\n";
    script_png << "set datafile separator ','\n\n";
    script_png << "plot ";
    
    for (size_t i = 0; i < archivos.size(); i++) {
        const Archivo& arch = archivos[i];
        if (i > 0) script_png << ", ";
        // Convertir a ruta absoluta
        string ruta_absoluta = fs::absolute(arch.ruta).string();
        script_png << "'" << ruta_absoluta << "' using 1:2 title '" << arch.label 
                   << "' with linespoints linewidth 2 pointsize 0.8";
    }
    script_png << "\n";
    script_png.close();
    
    // Generar PNG
    cout << "📊 Generando PNG...\n";
    int result = system("gnuplot temp_plot_png.gp 2>/dev/null");
    
    if (result == 0) {
        cout << "   ✅ PNG generado: " << output_file << "\n";
        
        // Intentar abrir con visor de imágenes (SÍNCRONO - sin background)
        cout << "\n🖼️  Abriendo visor de imágenes...\n";
        
        vector<string> visores = {"feh", "eog", "display", "gpicview", "xdg-open"};
        bool abierto = false;
        
        for (const auto& visor : visores) {
            cout << "   Intentando: " << visor << "...\n";
            string cmd = visor + " " + output_file + " 2>/dev/null";
            int res = system(cmd.c_str());  // SIN el & para esperar
            
            if (res == 0) {
                cout << "   ✅ Visor usado: " << visor << "\n";
                abierto = true;
                break;
            }
        }
        
        if (!abierto) {
            cout << "   ⚠️  No se pudo abrir automáticamente\n";
            cout << "   Opción manual:\n";
            cout << "     feh " << output_file << "\n";
            cout << "     o abre el archivo directamente\n";
        }
        
        cout << "\n✅ Gráfico listo\n";
        cout << "   Archivo: " << output_file << "\n";
        cout << "   En el visor puedes:\n";
        cout << "   • Zoom: Rueda del ratón o +/-\n";
        cout << "   • Pan: Click + Arrastrar\n";
        cout << "   • Guardar: Botón derecho\n\n";
        
        return true;
    } else {
        cout << "❌ Error generando PNG\n";
        return false;
    }
}

// ==========================================
// 🎮 MENÚ INTERACTIVO
// ==========================================

void menu_interactivo() {
    while (true) {
        cout << "\n🎯 GRAFICADOR INTERACTIVO - MENÚ\n";
        cout << "=" << string(58, '=') << "\n";
        cout << "Opciones:\n";
        cout << "  1) Graficar TODOS los archivos .txt (interactivo)\n";
        cout << "  2) Graficar solo RK4 (interactivo)\n";
        cout << "  3) Graficar solo EULER (interactivo)\n";
        cout << "  4) Graficar solo HEUN (interactivo)\n";
        cout << "  5) Graficar h específico (interactivo)\n";
        cout << "  6) Exportar a PNG estático (sin interfaz)\n";
        cout << "  7) Usar Python Graficador.py\n";
        cout << "  8) Salir\n";
        cout << "=" << string(58, '=') << "\n";
        cout << "Seleccione opción (1-8): ";
        
        string opcion;
        getline(cin, opcion);
        
        if (opcion == "1") {
            graficar_interactivo();
        } else if (opcion == "2") {
            graficar_interactivo("rk4");
        } else if (opcion == "3") {
            graficar_interactivo("euler");
        } else if (opcion == "4") {
            graficar_interactivo("heun");
        } else if (opcion == "5") {
            cout << "Ingrese h (ej: 0.01): ";
            string h;
            getline(cin, h);
            graficar_interactivo(h);
        } else if (opcion == "6") {
            cout << "Exportando a PNG (sin interfaz)...\n";
            system("gnuplot < temp_plot.gp");
            cout << "✅ Guardado como comparacion.png\n";
        } else if (opcion == "7") {
            cout << "Abriendo Graficador.py...\n";
            system("python3 Graficador.py &");
        } else if (opcion == "8") {
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
        string filtro = argv[1];
        cout << "Usando filtro: " << filtro << "\n";
        graficar_interactivo(filtro);
    } else {
        menu_interactivo();
    }
    
    return 0;
}
