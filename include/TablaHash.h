#ifndef MINIDB_TABLAHASH_H
#define MINIDB_TABLAHASH_H

#include "Registro.h"

struct NodoHash {
    int id;
    Registro reg;
    NodoHash* siguiente;

    NodoHash(int _id, const Registro& _reg)
        : id(_id), reg(_reg), siguiente(nullptr) {}
};

class TablaHash {
private:
    NodoHash** cubetas;
    int capacidad;
    int elementos;
    int funcionHash(int id) const;

public:
    TablaHash();
    ~TablaHash();

    TablaHash(const TablaHash&) = delete;
    TablaHash& operator=(const TablaHash&) = delete;

    bool insertar(const Registro& r);
    bool obtener(int id, Registro& salida) const;
};

#endif