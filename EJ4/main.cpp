#include <iostream>
#include <chrono>

// Función recursiva para comparar dos cadenas con char*
bool compararRecursivo(const char* str1, const char* str2) {
    if (*str1 == '\0' && *str2 == '\0') return true;  // Si ambos llegan al final, son iguales
    if (*str1 != *str2) return false;  // Si un carácter no coincide, son diferentes
    return compararRecursivo(str1 + 1, str2 + 1);  // Llamado recursivo
}

// Comparación en tiempo de compilación
constexpr bool compararConstexpr(const char* str1, const char* str2) {
    return (*str1 == '\0' && *str2 == '\0') ? true : (*str1 == *str2 && compararConstexpr(str1 + 1, str2 + 1));
}

int main() {
    const char* texto1 = "Este es un texto de prueba con más de 64 caracteres para el ejercicio";
    const char* texto2 = "Este es un texto de prueba con más de 64 caracteres para el ejercicio";

    // Medir tiempo de ejecución de la comparación
    auto startTime = std::chrono::high_resolution_clock::now();
    bool resultado = compararRecursivo(texto1, texto2);
    auto endTime = std::chrono::high_resolution_clock::now();

    auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

    std::cout << "Los textos son " << (resultado ? "iguales" : "diferentes") << "." << std::endl;
    std::cout << "Tiempo de ejecución: " << elapsedTime.count() << " nanosegundos." << std::endl;

    // Comparación en tiempo de compilación
    // Medir tiempo de ejecución de la comparación
    startTime = std::chrono::high_resolution_clock::now();
    constexpr bool resultadoCompilacion = compararConstexpr("Texto de prueba", "Texto de prueba");
    endTime = std::chrono::high_resolution_clock::now();

    elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    std::cout << "Comparación en tiempo de compilación: " << (resultadoCompilacion ? "iguales" : "diferentes") << "." << std::endl;
    std::cout << "Tiempo de compilacion: " << elapsedTime.count() << std::endl;

    return 0;
}
