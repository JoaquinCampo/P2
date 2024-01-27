/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/pila.h"

struct nodo {
    TInfo dato_Pila;
    nodo *sig;
};

struct _rep_pila {
    nodo * pila;
    int cant_Elems;
};

TPila crearPila() {
    TPila nuevo = new _rep_pila;
    nuevo-> pila = NULL;
    nuevo-> cant_Elems = 0;
    return nuevo;
}

void liberarPila(TPila p) {
    while (p-> pila != NULL){
        nodo* borrar = p-> pila;
        p-> pila = p-> pila-> sig;
        liberarInfo (borrar-> dato_Pila);
        delete borrar;
    }
    p-> cant_Elems = 0;
    delete p;
}   

nat cantidadEnPila(TPila p) { return p-> cant_Elems; }

TPila apilar(TInfo info, TPila p) {
    if (p-> pila == NULL) {
        p-> cant_Elems = 1;
        nodo* agregar = new nodo;
        agregar-> dato_Pila = copiaInfo(info);
        agregar-> sig = NULL;
        p-> pila = agregar;
        return p;
    } 
    else {
        p-> cant_Elems++;
        nodo* agregar = new nodo;
        agregar-> dato_Pila = copiaInfo(info);
        agregar-> sig = p-> pila;
        p-> pila = agregar;
        return p;
    }
}

TInfo cima(TPila p) { return p-> pila-> dato_Pila; }

TPila desapilar(TPila p) {
    p-> cant_Elems--;
    nodo* borrar = p-> pila;
    p-> pila = p-> pila-> sig;
    liberarInfo(borrar-> dato_Pila);
    delete borrar;
    return p;
}