#include "TablaHash.h"

TablaHash::TablaHash() : capacidad(17), elementos(0) {
    cubetas = new NodoHash*[capacidad];
    for (int i = 0; i < capacidad; ++i) {
        cubetas[i] = nullptr;
    }
}

TablaHash::~TablaHash() {
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

int TablaHash::funcionHash(int id) const {
    int idx = id % capacidad;
    if (idx < 0) idx += capacidad;
    return idx;
}

bool TablaHash::insertar(const Registro& r) {
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

bool TablaHash::obtener(int id, Registro& salida) const {
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