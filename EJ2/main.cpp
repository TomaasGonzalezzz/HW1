#include <iostream>
#include <fstream>

using namespace std;

// Uso enum para representar los niveles de severidad
enum NivelSeveridad {
    DEBUG = 1,
    INFO,
    WARNING,
    ERROR,
    CRITICAL,
    SECURITY
};

// Función para convertir el enum en una cadena de texto
string obtenerEtiqueta(NivelSeveridad nivel) {
    switch (nivel) {
        case DEBUG: return "DEBUG";
        case INFO: return "INFO";
        case WARNING: return "WARNING";
        case ERROR: return "ERROR";
        case CRITICAL: return "CRITICAL";
        case SECURITY: return "SECURITY";
        default: return "UNKNOWN";
    }
}

// Función que escribe un mensaje en el archivo de log
void logMessage(string mensaje, NivelSeveridad nivel) {
    ofstream logFile("log.txt", ios::app); // Abre archivo en modo append 
    
    if (!logFile) {
        cout << "Error al abrir el archivo de log." << endl;
        return;
    }

    logFile << "[" << obtenerEtiqueta(nivel) << "] " << mensaje << endl;
    logFile.close();
}

// Función para errores con archivo y línea
void logMessage(string mensaje, string archivo, int linea) {
    ofstream logFile("log.txt", ios::app);
    
    if (!logFile) {
        cout << "Error al abrir el archivo de log. No hay registro." << endl;
        return;
    }

    logFile << "[" << obtenerEtiqueta(ERROR) << "] " << mensaje << " (Archivo: " << archivo << ", Línea: " << linea << ")" << endl;
    logFile.close();
}

// Función para mensajes de seguridad
void logMessage(string mensaje, string usuario) {
    ofstream logFile("log.txt", ios::app);
    
    if (!logFile) {
        cout << "Error al abrir el archivo de log." << endl;
        return;
    }

    logFile << "[" << obtenerEtiqueta(SECURITY) << "] " << mensaje << " (Usuario: " << usuario << ")" << endl;
    logFile.close();
}

int main() {
    try {
        logMessage("Aviso para los que laburan de verdad", DEBUG);
        logMessage("La computadora prende... depende la hora", INFO);
        logMessage("Borraste el system32", WARNING);
        logMessage("Error al intentar conectar al wifi ajeno", ERROR);
        logMessage("2 de VRAM no corren el ARK", CRITICAL);
        logMessage("Intento de acceder con contraseña errónea", "totocrack456");

        // Genero error intencionalmente para capturarlo en runtime
        throw runtime_error("Se intentó dividir por cero");
    } catch (const exception& e) {
        logMessage(e.what(), __FILE__, __LINE__);
        cout << "Error detectado, cerrando el programa." << endl;
        return 1;
    }

    return 0;
}