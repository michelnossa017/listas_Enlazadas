#include <iostream>
using namespace std;

const int CAPACIDAD = 10;     // Tamaño fijo de los arreglos (memoria simulada)
const int NULO = -1;          // Representa "puntero nulo" usando -1

class ListaCursores {
private:
    int data[CAPACIDAD];      // Arreglo paralelo: valores
    int next[CAPACIDAD];      // Arreglo paralelo: cursor al siguiente
    int head;                 // Cursor al primer nodo de la lista
    int free_;                // Cursor al primer espacio libre

public:
    // Constructor: inicializa todos los espacios como libres,
    // enlazados entre sí (0 -> 1 -> 2 -> ... -> CAPACIDAD-1 -> NULO)
    ListaCursores() {
        for (int i = 0; i < CAPACIDAD - 1; i++) {
            next[i] = i + 1;
        }

        next[CAPACIDAD - 1] = NULO;
        free_ = 0;             // El primer libre es la posición 0
        head = NULO;           // La lista empieza vacía
    }

    // Toma un espacio libre del arreglo (equivalente a "new" / "malloc")
    int asignarNodo() {
        if (free_ == NULO) {
            cout << "¡Sin espacio disponible! (arreglo lleno)\n";
            return NULO;
        }

        int nodo = free_;      // Tomamos el primer libre
        free_ = next[free_];   // Avanzamos el cursor de libres
        return nodo;
    }

    // Devuelve un espacio al "montón" de libres (equivalente a "delete" / "free")
    void liberarNodo(int idx) {
        next[idx] = free_;     // El nodo liberado apunta al antiguo libre
        free_ = idx;           // Ahora el primer libre es este nodo
    }

    // Inserta un valor al INICIO de la lista
    void insertarInicio(int valor) {
        int nuevo = asignarNodo();

        if (nuevo == NULO) return;

        data[nuevo] = valor;
        next[nuevo] = head;     // El nuevo nodo apunta al antiguo head
        head = nuevo;           // El head ahora es el nuevo nodo
    }

    // Elimina la PRIMERA ocurrencia de un valor en la lista
    void eliminarValor(int valor) {
        int actual = head;
        int anterior = NULO;

        while (actual != NULO && data[actual] != valor) {
            anterior = actual;
            actual = next[actual];
        }

        if (actual == NULO) {
            cout << "Valor " << valor << " no encontrado en la lista.\n";
            return;
        }

        // Desconectar el nodo "actual" de la lista
        if (anterior == NULO) {
            head = next[actual];  // Eliminando el primer nodo
        } else {
            next[anterior] = next[actual];  // Saltar el nodo actual
        }

        liberarNodo(actual);  //Regresar el espacio a la lista de libres
    }

    //Recorre e imprime la lista siguiendo los cursores desde head
    void imprimir() {
        int actual = head;
        cout << "Lista: ";
        if (actual == NULO) cout << "(vacía)";
        while (actual != NULO) {
            cout << data[actual];
            if (next[actual] != NULO) cout << " -> ";
            actual = next[actual];
        }
        cout << "\n";
    }

    //Muestra el estado interno de los arreglos paralelos (para depurar
    // y comparar con la traza hecha a mano / con la IA)
    void mostrarEstadoInterno(){
        cout << "\n idx : ";
        for (int i = 0; i < CAPACIDAD; i++) cout << i << " ";
        cout << "\n data : ";
        for (int i = 0; i < CAPACIDAD; i++) cout << data[i] << " ";
        cout << "\n next : ";
        for (int i = 0; i < CAPACIDAD; i++) cout << next[i] << " ";
        cout << "\n head = " << head << " | free = " << free_ << "\n\n";

    }
};

int main() {
    ListaCursores lista;

    cout << "== Insertando 30, 20, 10 al inicio ==\n";
    lista.insertarInicio(30);
    lista.insertarInicio(20);
    lista.insertarInicio(10);
    lista.imprimir();
    lista.mostrarEstadoInterno();

    cout << "== Eliminando el valor 20 ==\n";
    lista.eliminarValor(20);
    lista.imprimir();
    lista.mostrarEstadoInterno();

    cout << "== Insertando 40 al inicio (reutiliza el espacio liberado) ==\n";
    lista.insertarInicio(40);
    lista.imprimir();
    lista.mostrarEstadoInterno();

    return 0;
}