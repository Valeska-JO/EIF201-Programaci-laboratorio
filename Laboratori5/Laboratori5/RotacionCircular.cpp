#include "RotacionCircular.h"

namespace EIF201 {

    RotacionCircular::RotacionCircular()
        : cola(nullptr), cantidad(0) {
    }
    NodoLocutor* RotacionCircular::getCabeza() const {
        return (cola != nullptr) ? cola->siguiente : nullptr;
    }
    RotacionCircular::~RotacionCircular() {
        if (cola == nullptr) {
            return;
        }
        NodoLocutor* cabeza = cola->siguiente;
        cola->siguiente = nullptr;
        NodoLocutor* actual = cabeza;
        while (actual != nullptr) {
            NodoLocutor* temp = actual->siguiente;
            delete actual;
            actual = temp;
        }
        cola = nullptr;
        cout << "[RotacionCircular destruida]" << endl;
    }
    void RotacionCircular::insertarAlFinal(const string& nombre) {
        NodoLocutor* nuevo = new NodoLocutor(nombre);
        if (cola == nullptr) {
            nuevo->siguiente = nuevo;
            cola = nuevo;
        }
        else {
            nuevo->siguiente = cola->siguiente;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
        cantidad++;
    }
    void RotacionCircular::insertarAlInicio(const string& nombre) {
        NodoLocutor* nuevo = new NodoLocutor(nombre);
        if (cola == nullptr) {
            nuevo->siguiente = nuevo;
            cola = nuevo;
        }
        else {
            nuevo->siguiente = cola->siguiente;
            cola->siguiente = nuevo;
        }
        cantidad++;
    }

    bool RotacionCircular::insertarDespuesDe(const string& referencia, const string& nuevo_nombre) {
        if (cola == nullptr) {
            return false;
        }
        NodoLocutor* cabeza = getCabeza();
        NodoLocutor* actual = cabeza;
        do {
            if (actual->nombre == referencia) {
                NodoLocutor* nuevo = new NodoLocutor(nuevo_nombre);
                nuevo->siguiente = actual->siguiente;
                actual->siguiente = nuevo;
                if (actual == cola) cola = nuevo;
                cantidad++;
                return true;
            }
            actual = actual->siguiente;
        } while (actual != cabeza);
        return false;
    }

    bool RotacionCircular::existeLocutor(const string& nombre) const {

        if (cola == nullptr) {
            return false;
        }

        NodoLocutor* cabeza = getCabeza();
        NodoLocutor* actual = cabeza;

        do {

            if (actual->nombre == nombre) {
                return true;
            }

            actual = actual->siguiente;

        } while (actual != cabeza);

        return false;
    }
    int RotacionCircular::obtenerPosicion(const string& nombre) const {
        if (cola == nullptr) {
            return -1;
        }
        NodoLocutor* cabeza = getCabeza();
        NodoLocutor* actual = cabeza;
        int pos = 0;
        do {
            if (actual->nombre == nombre) {
                return pos;
            }
            actual = actual->siguiente;
            pos++;
        } while (actual != cabeza);
        return -1;
    }
    string RotacionCircular::turnoActual() const {
        if (cola == nullptr) {
            return "";
        }
        return getCabeza()->nombre;
    }
    bool RotacionCircular::eliminarLocutor(const string& nombre) {
        if (cola == nullptr) {
            return false;
        }
        NodoLocutor* cabeza = getCabeza();
        NodoLocutor* actual = cabeza;
        NodoLocutor* previo = cola;
        do {
            if (actual->nombre == nombre) {
                if (actual == cabeza && actual == cola) {
                    delete actual;
                    cola = nullptr;
                }
                else {
                    previo->siguiente = actual->siguiente;
                    if (actual == cola) {
                        cola = previo;
                    }
                    delete actual;
                }
                cantidad--;
                return true;
            }
            previo = actual;
            actual = actual->siguiente;
        } while (actual != cabeza);
        return false;
    }
        bool RotacionCircular::eliminarTurnoActual() {
            if (cola == nullptr) {
                return false;
            }
            return eliminarLocutor(getCabeza()->nombre);
        }

        string RotacionCircular::siguiente() {
            if (cola == nullptr) {
                return "";
            }
            cola = cola->siguiente;
            NodoLocutor* actual = getCabeza();
            actual->turnosAsignados++;

            return actual->nombre;
        }

        void RotacionCircular::simularTurnos(int n) {
            if (cola == nullptr) { cout << "Sin locutores en rotacion. " << endl; return; }
            for (int i = 0; i < n; i++) {
                cout << "Turno " << i << ":" << siguiente() << endl;
            }
        }
        void RotacionCircular::imprimirRotacion() const {
            if (cola == nullptr) {
                cout << "Rotación vacía." << endl;
                return;
            }
            NodoLocutor* cabeza = getCabeza();
            NodoLocutor* actual = cabeza;
            cout << "Rotación: ";
            do {
                cout << actual->nombre;
                actual = actual->siguiente;
                if (actual != cabeza) {
                    cout << " -> ";
                }
            } while (actual != cabeza);
            cout << " ->(inicio)" << endl;
        }
        void RotacionCircular::imprimirEstadistica() const {
            if (cola == nullptr) {
                cout << "No hay Locutores!!" << endl;
                return;
            }
            NodoLocutor* cabeza = getCabeza();
            NodoLocutor* actual = cabeza;
            cout << "\n--Estadísticas--" << endl;
            do {
                cout << actual->nombre << ": " << actual->turnosAsignados << " turnos" << endl;
                actual = actual->siguiente;
            } while (actual != cabeza);
        }

        int RotacionCircular::getCantidad() const {
            return cantidad;
        }
        bool RotacionCircular::estaVacia() const {
            return cola == nullptr;
        }

        string RotacionCircular::locutorMasActivo() const {
            if (cola == nullptr) {
                return "";
            }
            NodoLocutor* cabeza = getCabeza();
            NodoLocutor* actual = cabeza;
            NodoLocutor* masActivo = cabeza;
            do {
                if (actual->turnosAsignados > masActivo->turnosAsignados) {
                    masActivo = actual;
                }
                actual = actual->siguiente;
            } while (actual != cabeza);
            return masActivo->nombre;
        }
    }