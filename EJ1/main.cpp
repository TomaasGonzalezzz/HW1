#include <iostream>
#include <vector>

using namespace std;

// Función para crear la matriz de tamaño n x n
vector<vector<int>> crearMatriz(int n) {
    vector<vector<int>> matriz(n, vector<int>(n));
    int valor = 1;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = valor++;
        }
    }
    
    return matriz;
}

// Función para imprimir los elementos de la matriz en orden descendente con un solo for
void imprimirMatriz(const vector<vector<int>>& matriz, int n) {
    int totalElementos = n * n;
    
    for (int k = totalElementos - 1; k >= 0; k--) {
        int i = k / n;  // Fila calculada
        int j = k % n;  // Columna calculada
        cout << "M" << "[" << i << "][" << j << "] = " << matriz[i][j] << endl;
    }
}

int main() {
    int n;
    
    cout << "Ingrese el tamaño de la matriz: ";
    cin >> n;
    
    if (n <= 1) {
        cout << "El valor de n debe ser mayor que 1." << endl;
        return 1;
    }

    vector<vector<int>> matriz = crearMatriz(n);
    imprimirMatriz(matriz, n);

    return 0;
}
