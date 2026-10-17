#ifndef MINIDB_TABLAHASH_H
#define MINIDB_TABLAHASH_H
// Verificamos que este definida la .h
#include "Registro.h" // Libreria del profe

struct NodoHash { //  declaramos estructura
    int id; // nuestra id unica
    Registro reg; // los datos reales que se almacenan en la lista
    NodoHash* siguiente; // puntero que apunta al sig registro en caso de tener repetidos

    NodoHash(int _id, const Registro& _reg)
        : id(_id), reg(_reg), siguiente(nullptr) {} // constructor en donde inicializamos nuestras variablles
                                                    // y declaramos nuestro sig puntero como null
};

class TablaHash { // declaramos nuestra clase
private:
    NodoHash** cubetas; // arreglo dinamico de los punteros (esto ya que si se repite una se crea una lista de los rep)
    int capacidad; // tamanio del arreglo cubetas
    int elementos; // cantidad de elementos que tenemos actualmente
    int funcionHash(int id) const; // aqui pasa la magia de la funcion hash

public:
    TablaHash(); // constructor de nuestra tabla
    ~TablaHash(); // destructor de nuestra tabla

    TablaHash(const TablaHash&) = delete;
    TablaHash& operator=(const TablaHash&) = delete; // deshabilita el constructor y se evita liberacion de memoria

    bool insertar(const Registro& r); // llamamos nuestras funciones
    bool obtener(int id, Registro& salida) const;
    bool eliminar(int id);
};

#endif