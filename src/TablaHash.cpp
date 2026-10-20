#include "TablaHash.h"

TablaHash::TablaHash() : capacidad(17), elementos(0) { // constructor hash con la clase hassh que proporciona el profe
    cubetas = new NodoHash*[capacidad];
    for (int i = 0; i < capacidad; ++i) {
        cubetas[i] = nullptr;
    }
}

TablaHash::~TablaHash() { // destructor hash con la clase hassh que proporciona el profe
    for (int i = 0; i < capacidad; ++i) {
        NodoHash* actual = cubetas[i];
        while (actual != nullptr) {
            NodoHash* aBorrar = actual;
            actual = actual->siguiente;
            delete aBorrar;
        }
    }
    delete[] cubetas;
}

int TablaHash::funcionHash(int id) const { // esta es la funcion hash, donde determinamos la posiicion de lo que ingresamos
    int idx = id % capacidad;
    if (idx < 0) idx += capacidad;
    return idx;
}

bool TablaHash::insertar(const Registro& r) { // funcion encargada de agregar elementos a la tablla
    int idx = funcionHash(r.id);
    NodoHash* actual = cubetas[idx];

    while (actual != nullptr) {
        if (actual->id == r.id) {
            return false;
        }
        actual = actual->siguiente;
    }

    NodoHash* nuevo = new NodoHash(r.id, r);
    nuevo->siguiente = cubetas[idx];
    cubetas[idx] = nuevo;
    elementos++;

    return true;
}

bool TablaHash::obtener(int id, Registro& salida) const { // funcion encargada de obtener elementos a la tablla
    int idx = funcionHash(id);
    NodoHash* actual = cubetas[idx];

    while (actual != nullptr) {
        if (actual->id == id) {
            salida = actual->reg;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

bool TablaHash::eliminar(int id) { // funcion encargada de eliminar elementos
    int idx = funcionHash(id);
    NodoHash* actual = cubetas[idx];
    NodoHash* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->id == id) {
            if (anterior == nullptr) {
                cubetas[idx] = actual->siguiente;
            }
            else {
                anterior->siguiente = actual->siguiente;
            }

            delete actual;
            elementos--;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }

    return false;
}

Registro* TablaHash::buscar(int id) const {
    int idx = funcionHash(id);
    NodoHash* actual = cubetas[idx];

    while (actual != nullptr) {
        if (actual->id == id) {
            return &(actual->reg);
        }
        actual = actual->siguiente;
    }
    return nullptr;
}