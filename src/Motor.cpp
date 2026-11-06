// =============================================================================
//  Motor.cpp — ESTE ES TU PROYECTO. Todo lo de aquí es un esqueleto.
// =============================================================================
#include "Motor.h"

#include <cstring>

Motor::Motor() {} // llamamos el constructor
Motor::~Motor() {} // llamamos el destructor

// Donde mandamos a llamar a todas las funciones

bool Motor::insertar(const Registro& r) {
    if (!tablaPrincipal.insertar(r)) {
        return false;
    }
    indiceOrdenado.insertar(r.valor, r.id, r);
    return true; // OK
}

bool Motor::obtener(int id, Registro& salida) {
    return tablaPrincipal.obtener(id, salida);
}

bool Motor::eliminar(int id) {
    Registro r;
    if (!tablaPrincipal.obtener(id, r)) {
        return false;
    }
    tablaPrincipal.eliminar(id);
    indiceOrdenado.eliminar(r.valor, id);
    return true;
}

bool Motor::actualizar(int id, int nuevoValor) {
    Registro* reg = tablaPrincipal.buscar(id);
    if (!reg) {
        return false;
    }

    int viejoValor = reg->valor;
    if (viejoValor == nuevoValor) {
        return true;

        indiceOrdenado.eliminar(viejoValor, id);
        reg->valor = nuevoValor;
        indiceOrdenado.insertar(nuevoValor, id, *reg);

        return true; // OK
    }
}

void Motor::rango(int a, int b, int limite, ResultadoRango& salida) {
    indiceOrdenado.rango(a, b, limite, salida);
}

int Motor::contar(int a, int b) {
    return indiceOrdenado.contar(a, b);
}

bool Motor::kesimo(int k, Registro& salida) {}
int  Motor::top(int k, int categoria, Registro* salida) { (void)k; (void)categoria; (void)salida; return 0; }

void Motor::iniciarTransaccion() {}
bool Motor::confirmar() { return false; }
bool Motor::revertir() { return false; }

int Motor::altura() const{
    return indiceOrdenado.altura();
}
void Motor::configurarCache(int capacidad) { (void)capacidad; }

EstadisticasCache Motor::estadisticasCache() const {
    EstadisticasCache e;
    std::memset(&e, 0, sizeof(e));
    return e;
}

bool Motor::verificar(char* mensaje, int capacidad) {
    if (capacidad > 0) mensaje[0] = '\0';
    return true;
}

void Motor::imprimirStats(std::ostream& os) { os << "(sin estadisticas)\n"; }
