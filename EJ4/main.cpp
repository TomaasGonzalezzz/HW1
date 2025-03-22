#include <iostream>
#include <chrono>

// Función recursiva que compara dos cadenas con char*
bool compararRecursivo(const char* str1, const char* str2) {
    if (*str1 == '\0' && *str2 == '\0') return true;  // Si llegan al final, son iguales
    if (*str1 != *str2) return false;  // Si un carácter no coincide, son diferentes
    return compararRecursivo(str1 + 1, str2 + 1);  
}

// Comparación en tiempo de compilación
constexpr bool compararConstexpr(const char* str1, const char* str2) {
    return (*str1 == '\0' && *str2 == '\0') ? true : (*str1 == *str2 && compararConstexpr(str1 + 1, str2 + 1));
}

int main() {
    const char* texto1 = "Mi nombre es Tomas y soy estudiante de segundo año de Ingenieria en IA";
    const char* texto2 = "Mi nombre es Tomas y soy estudiante de segundo año de Ingenieria en IA";

    // Mide tiempo de ejecución de la comparación en tiempo de ejecucion
    auto startTime = std::chrono::high_resolution_clock::now();
    bool resultado = compararRecursivo(texto1, texto2);
    auto endTime = std::chrono::high_resolution_clock::now();

    auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

    std::cout << "Los textos son " << (resultado ? "iguales" : "distintos") << "." << std::endl;
    std::cout << "Tiempo de ejecución: " << elapsedTime.count() << " nanosegundos." << std::endl;

    // Medir tiempo de ejecución de la comparación en tiempo de compilacion
    startTime = std::chrono::high_resolution_clock::now();
    constexpr bool resultadoCompilacion = compararConstexpr("Argentina es mucho mas grande que Uruguay", "Argentina es mucho mas grande que Uruguay");
    endTime = std::chrono::high_resolution_clock::now();

    elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
    std::cout << "Comparación en tiempo de compilación: " << (resultadoCompilacion ? "iguales" : "distintos") << "." << std::endl;
    std::cout << "Tiempo de compilacion: " << elapsedTime.count() << std::endl;

    return 0;
}
