//
// Created by Sophia Diaz de Leon Gleason on 25/10/26.
//
#include "AVL.h"

AVL::AVL() : raiz(nullptr) {}

AVL::~AVL() {
    destruirRec(raiz);
}

void AVL::destruirRec(NodoAVL* n) {
    if (n) {
        destruirRec(n->izq);
        destruirRec(n->der);
        delete n;
    }
}

NodoAVL* AVL::rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->izq;
    NodoAVL* T2 = x->der;
    x->der = y;
    y->izq = T2;
    actualizarAltura(y);
    actualizarAltura(x);
    return x;
}

NodoAVL* AVL::rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->der;
    NodoAVL* T2 = y->izq;
    y->izq = x;
    x->der = T2;
    actualizarAltura(x);
    actualizarAltura(y);
    return y;
}

NodoAVL* AVL::rebalancear(NodoAVL* n) {
    actualizarAltura(n);
    int bf = factorBalance(n); // izq - der

    // Caso Izquierda-Izquierda o Izquierda-Derecha
    if (bf == 2) {
        if (factorBalance(n->izq) < 0) {
            n->izq = rotacionIzquierda(n->izq);
        }
        return rotacionDerecha(n);
    }
    // Caso Derecha-Derecha o Derecha-Izquierda
    if (bf == -2) {
        if (factorBalance(n->der) > 0) {
            n->der = rotacionDerecha(n->der);
        }
        return rotacionIzquierda(n);
    }
    return n;
}

NodoAVL* AVL::insertarRec(NodoAVL* n, int val, int id, const Registro& r) {
    if (!n) return new NodoAVL(val, id, r);

    ClaveAVL c{val, id};
    if (c < n->clave) {
        n->izq = insertarRec(n->izq, val, id, r);
    } else {
        n->der = insertarRec(n->der, val, id, r);
    }
    return rebalancear(n);
}

void AVL::insertar(int valor, int id, const Registro& r) {
    raiz = insertarRec(raiz, valor, id, r);
}

NodoAVL* AVL::minNodo(NodoAVL* n) {
    NodoAVL* act = n;
    while (act->izq) act = act->izq;
    return act;
}

NodoAVL* AVL::eliminarRec(NodoAVL* n, ClaveAVL c) {
    if (!n) return nullptr;

    if (c < n->clave) {
        n->izq = eliminarRec(n->izq, c);
    } else if (c > n->clave) {
        n->der = eliminarRec(n->der, c);
    } else {
        if (!n->izq || !n->der) {
            NodoAVL* temp = n->izq ? n->izq : n->der;
            delete n;
            return temp;
        } else {
            NodoAVL* suc = minNodo(n->der);
            n->clave = suc->clave;
            n->reg = suc->reg;
            n->der = eliminarRec(n->der, suc->clave);
        }
    }
    return rebalancear(n);
}

void AVL::eliminar(int valor, int id) {
    raiz = eliminarRec(raiz, ClaveAVL{valor, id});
}

void AVL::rangoRec(NodoAVL* n, int a, int b, int limite, ResultadoRango& salida, int& contador) const {
    if (!n) return;

    if (n->clave.valor >= a) {
        rangoRec(n->izq, a, b, limite, salida, contador);
    }

    if (n->clave.valor >= a && n->clave.valor <= b) {
        salida.n++;
        long long mult = (long long)(contador + 1) * n->clave.id;
        salida.firma = (salida.firma + mult) % 1000000007LL;

        if (salida.nFilas < limite && salida.nFilas < ResultadoRango::MAX_FILAS) {
            salida.filas[salida.nFilas++] = n->reg;
        }
        contador++;
    }

    if (n->clave.valor <= b) {
        rangoRec(n->der, a, b, limite, salida, contador);
    }
}

void AVL::rango(int a, int b, int limite, ResultadoRango& salida) const {
    salida.n = 0;
    salida.firma = 0;
    salida.nFilas = 0;
    if (a > b) return;
    int contador = 0;
    rangoRec(raiz, a, b, limite, salida, contador);
}