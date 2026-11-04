//
// Created by Sophia Diaz de Leon Gleason on 25/10/26.
//

#ifndef MINIDB_AVL_H
#define MINIDB_AVL_H

#include "Registro.h"

struct ClaveAVL {
    int valor;
    int id;

    bool operator<(const ClaveAVL& o) const {
        if (valor != o.valor) return valor < o.valor;
        return id < o.id;
    }
    bool operator>(const ClaveAVL& o) const { return o < *this; }
    bool operator==(const ClaveAVL& o) const { return valor == o.valor && id == o.id; }
    bool operator<=(const ClaveAVL& o) const { return !(o < *this); }
};

struct NodoAVL {
    ClaveAVL clave;
    Registro reg;
    int altura;
    NodoAVL* izq;
    NodoAVL* der;

    NodoAVL(int val, int _id, const Registro& r)
        : clave{val, _id}, reg(r), altura(0), izq(nullptr), der(nullptr) {}
};

class AVL {
private:
    NodoAVL* raiz;

    int alt(NodoAVL* n) const { return n ? n->altura : -1; }
    int maximo(int a, int b) const { return (a > b) ? a : b; }
    int factorBalance(NodoAVL* n) const { return n ? alt(n->izq) - alt(n->der) : 0; }

    void actualizarAltura(NodoAVL* n) {
        if (n) n->altura = 1 + maximo(alt(n->izq), alt(n->der));
    }

    NodoAVL* rotacionDerecha(NodoAVL* y);
    NodoAVL* rotacionIzquierda(NodoAVL* x);
    NodoAVL* rebalancear(NodoAVL* n);
    NodoAVL* insertarRec(NodoAVL* n, int val, int id, const Registro& r);
    NodoAVL* minNodo(NodoAVL* n);
    NodoAVL* eliminarRec(NodoAVL* n, ClaveAVL c);
    void destruirRec(NodoAVL* n);

    void rangoRec(NodoAVL* n, int a, int b, int limite, ResultadoRango& salida, int& contador) const;

public:
    AVL();
    ~AVL();

    AVL(const AVL&) = delete;
    AVL& operator=(const AVL&) = delete;

    void insertar(int valor, int id, const Registro& r);
    void eliminar(int valor, int id);
    void rango(int a, int b, int limite, ResultadoRango& salida) const;
    int altura() const { return alt(raiz); }
};

#endif //MINIDB_AVL_H
