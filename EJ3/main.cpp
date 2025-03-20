#include <iostream>
#include <memory>
using namespace std;

struct Nodo {
    int valor;
    unique_ptr<Nodo> siguiente;
};

struct ListaEnlazada {
    unique_ptr<Nodo> cabeza;
    int size = 0;
};

// Usamos make_unique para trabajar siempre con unique_ptr.
unique_ptr<Nodo> create_node(int valor) {
    return make_unique<Nodo>(Nodo{valor, nullptr});
}

// Inserta un nodo al inicio de la lista.
// Movemos la cabeza actual al siguiente del nuevo nodo.
void push_front(ListaEnlazada& lista, int valor) {
    unique_ptr<Nodo> nuevo = create_node(valor);
    nuevo->siguiente = move(lista.cabeza);
    lista.cabeza = move(nuevo);
    lista.size++;
}

// Inserta un nodo al final de la lista.
// Recorremos hasta el último nodo para enlazar el nuevo.
void push_back(ListaEnlazada& lista, int valor) {
    unique_ptr<Nodo> nuevo = create_node(valor);

    if (!lista.cabeza) {
        lista.cabeza = move(nuevo);
    } else {
        Nodo* temp = lista.cabeza.get();
        while (temp->siguiente) {
            temp = temp->siguiente.get();
        }
        temp->siguiente = move(nuevo);
    }
    lista.size++;
}

// Inserta un nodo en la posición dada.
// Si la posición es inválida, se coloca al final de la lista.
void insert(ListaEnlazada& lista, int valor, int posicion) {
    if (posicion <= 0) {
        push_front(lista, valor);
        return;
    }

    unique_ptr<Nodo> nuevo = create_node(valor);

    Nodo* temp = lista.cabeza.get();
    int i = 0;

    while (temp->siguiente && i < posicion - 1) {
        temp = temp->siguiente.get();
        i++;
    }

    nuevo->siguiente = move(temp->siguiente);
    temp->siguiente = move(nuevo);
    lista.size++;
}

// Elimina un nodo en la posición indicada.
// Si la posición es inválida, no se hace nada.
void erase(ListaEnlazada& lista, int posicion) {
    if (!lista.cabeza || posicion < 0) return;

    if (posicion == 0) {
        lista.cabeza = move(lista.cabeza->siguiente);
        lista.size--;
        return;
    }

    Nodo* temp = lista.cabeza.get();
    int i = 0;

    while (temp->siguiente->siguiente && i < posicion - 1) {
        temp = temp->siguiente.get();
        i++;
    }

    if (temp->siguiente) {
        temp->siguiente = move(temp->siguiente->siguiente);
        lista.size--;
    }
}

// Recorre e imprime la lista enlazada, mostrando el tamaño al final.
void print_list(const ListaEnlazada& lista) {
    Nodo* temp = lista.cabeza.get();
    while (temp) {
        cout << temp->valor;
        if (temp->siguiente) cout << " -> ";
        temp = temp->siguiente.get();
    }
    cout << " (Size: " << lista.size << ")" << endl;
}

int main() {
    auto lista = make_unique<ListaEnlazada>();
    //Agregar couts con pasos
    push_front(*lista, 3);
    push_front(*lista, 2);
    push_front(*lista, 1);
    print_list(*lista);  // 1 -> 2 -> 3 (Size: 3)

    push_back(*lista, 4);
    push_back(*lista, 5);
    print_list(*lista);  // 1 -> 2 -> 3 -> 4 -> 5 (Size: 5)

    insert(*lista, 0, 0);
    insert(*lista, 6, 10);  // posición mayor al largo (se agrega al final)
    print_list(*lista);  // 0 -> 1 -> 2 -> 3 -> 4 -> 5 -> 6 (Size: 7)

    erase(*lista, 2);
    erase(*lista, 10);  // posición inválida (borra el ultimo)
    print_list(*lista);  // 0 -> 1 -> 3 -> 4 -> 5 -> 6 (Size: 6)

    return 0;
}

