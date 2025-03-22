#include <iostream>
#include <vector>

using namespace std;

// Esta función crea una matriz de tamaño n x n y la llena con números consecutivos
vector<vector<int>> crearMatriz(int n) {
    vector<vector<int>> matriz(n, vector<int>(n));
    int valor = 1;
    
    // Rellena la matriz con numeros consecutivos
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = valor++;
        }
    }
    
    return matriz;
}

// Función que imprime los elementos de la matriz en orden descendente 
void imprimirMatriz(const vector<vector<int>>& matriz, int n) {
    int totalElementos = n * n;
    
    for (int k = totalElementos - 1; k >= 0; k--) {
        int i = k / n;  // Fila 
        int j = k % n;  // Columna 
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
