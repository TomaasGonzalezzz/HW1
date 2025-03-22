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

// Uso make_unique para usar unique_ptr.
unique_ptr<Nodo> create_node(int valor) {
    return make_unique<Nodo>(Nodo{valor, nullptr});
}

// Inserta un nodo al inicio de la lista.

void push_front(ListaEnlazada& lista, int valor) {
    unique_ptr<Nodo> nuevo = create_node(valor);
    // Mueve la cabeza actual al siguiente del nuevo nodo.
    nuevo->siguiente = move(lista.cabeza);
    lista.cabeza = move(nuevo);
    lista.size++;
}

// Inserta un nodo al final de la lista.
void push_back(ListaEnlazada& lista, int valor) {
    unique_ptr<Nodo> nuevo = create_node(valor);

    if (!lista.cabeza) {
        lista.cabeza = move(nuevo);
    } else {
        Nodo* temp = lista.cabeza.get();
        // Recorro hasta el último nodo para enlazar el nuevo.
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

// Recorre e imprime la lista enlazada, muestra el tamaño al final.
void print_list(const ListaEnlazada& lista) {
    Nodo* temp = lista.cabeza.get();
    while (temp) {
        cout << temp->valor;
        if (temp->siguiente) cout << " -> ";
        temp = temp->siguiente.get();
    }
    cout << " (Tamaño: " << lista.size << ")" << endl;
}

int main() {
    auto lista = make_unique<ListaEnlazada>();
    
    push_front(*lista, 4);
    push_front(*lista, 3);
    push_front(*lista, 2);
    push_front(*lista, 1);
    print_list(*lista);  

    push_back(*lista, 5);
    push_back(*lista, 6);
    push_back(*lista, 7);
    push_back(*lista, 8);
    print_list(*lista);  

    insert(*lista, 0, 0);
    insert(*lista, 9, 15);  // posición inválida (inserta al final)
    print_list(*lista);  

    erase(*lista, 2);
    erase(*lista, 12);  // posición inválida (borra el ultimo)
    print_list(*lista);  

    return 0;
}

