/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cola.h"

struct nodo {
    TInfo dato_Queue;
    nodo * sig;
    nodo * ant;
};

struct _rep_cola {
    nodo * reciente;
    nodo * antiguo;
    nat cant_Queue;
};

TCola crearCola() { 
    TCola Queue = new _rep_cola;
    Queue-> reciente = NULL;
    Queue-> antiguo = NULL;
    Queue-> cant_Queue = 0;
    return Queue;
}

void liberarCola(TCola c) {
    if (c != NULL){
        while (c-> reciente != NULL){
            nodo *borrar = c-> reciente;
            c-> reciente = c-> reciente-> sig;
            liberarInfo(borrar-> dato_Queue);
            delete borrar;
        }
        delete c;
    }
}

nat cantidadEnCola(TCola c) { return c-> cant_Queue; }

TCola encolar(TInfo info, TCola c) {
    nodo *agregar = new nodo;
    agregar-> dato_Queue = copiaInfo(info);
    if (c-> cant_Queue == 0){
        agregar-> sig = NULL;
        agregar-> ant = NULL;
        c-> antiguo = agregar;
        c-> reciente = agregar;
    }
    else {
        agregar-> sig = c-> reciente;
        agregar-> ant = NULL;
        c-> reciente-> ant = agregar;
        c-> reciente = agregar;
    }
    c-> cant_Queue ++;
    return c;
}

TInfo frente(TCola c) { return c-> antiguo-> dato_Queue; }

TCola desencolar(TCola c) { 
    if (c-> cant_Queue == 1){
        liberarInfo(c-> antiguo-> dato_Queue);
        delete c-> reciente;
        c-> reciente = NULL;
        c-> antiguo = NULL;
        c-> cant_Queue = 0;
        return c;
    }
    else {
        nodo * borrar = c-> antiguo;
        c-> antiguo = c-> antiguo-> ant;
        c-> antiguo-> sig = NULL;
        liberarInfo(borrar-> dato_Queue);
        delete borrar;
        c-> cant_Queue --;
        return c;
    }
}
