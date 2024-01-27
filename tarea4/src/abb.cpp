/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"

struct _rep_abb {
    TInfo elemInfo;
    TAbb izq, der;
};

TAbb crearAbb() { return NULL; }

void liberarAbb(TAbb abb) {
    if (abb == NULL)
        delete abb;
    else {
        TAbb borrar = abb;
        liberarAbb(abb-> izq);
        liberarAbb(abb-> der);
        liberarInfo(borrar-> elemInfo);
        delete borrar;
    }
}

bool esVacioAbb(TAbb abb) { return abb == NULL; }

TAbb buscarSubarbol(nat clave, TAbb abb) {
    if ( abb == NULL || natInfo(abb-> elemInfo) == clave)
        return abb;
    else {
        if (natInfo(abb->elemInfo) < clave) 
            return buscarSubarbol(clave, abb-> der);
        else return buscarSubarbol(clave, abb-> izq);
    }
}

TInfo raiz(TAbb abb) { return abb-> elemInfo; }

TAbb izquierdo(TAbb abb) { return abb-> izq; }

TAbb derecho(TAbb abb) { return abb-> der; }

TInfo menorEnAbb(TAbb abb) { 
    if (abb -> izq != NULL)
        return menorEnAbb(abb-> izq);
    else return abb-> elemInfo;
}

TInfo mayorEnAbb(TAbb abb) { 
    if (abb -> der != NULL)
        return mayorEnAbb(abb-> der);
    else return abb-> elemInfo;
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der) {  
    TAbb nuevo = new _rep_abb;
    nuevo-> elemInfo = dato;
    nuevo-> izq = izq;
    nuevo-> der = der;
    return nuevo;
}

void agregarEnAbb(TInfo dato, TAbb &abb){
    if (abb == NULL){
        abb = new _rep_abb;
        abb-> elemInfo = dato;
        abb-> izq = NULL;
        abb-> der = NULL;
    }
    else {
        if (natInfo(abb-> elemInfo) < natInfo(dato))
            agregarEnAbb(dato, abb-> der);
        else agregarEnAbb(dato, abb-> izq);
    }
}

TAbb insertarEnAbb(TInfo dato, TAbb abb) {
    agregarEnAbb(dato, abb);
    return abb;
}


void eliminarTAbb(nat clave, TAbb &abb) {
    TAbb borrar ;
    if (natInfo(abb-> elemInfo) == clave){
        if (abb-> izq == NULL){
            borrar = abb;
            abb = abb-> der;
            liberarInfo(borrar-> elemInfo);
            delete borrar;
        }
        else if (abb-> der == NULL ){   
            borrar = abb;
            abb = abb-> izq;
            liberarInfo(borrar-> elemInfo);
            delete borrar;
        }
        else {
            liberarInfo(abb-> elemInfo);
            abb-> elemInfo = copiaInfo(mayorEnAbb(abb-> izq));
            eliminarTAbb(natInfo(abb-> elemInfo), abb-> izq);
            }
    }
    else if (clave > natInfo(abb-> elemInfo))
            eliminarTAbb(clave , abb-> der);
        else
        eliminarTAbb(clave, abb-> izq);
}

TAbb removerDeAbb(nat clave, TAbb abb) {
    eliminarTAbb(clave, abb);
    return abb;
}

TAbb copiaAbb(TAbb abb) {
    if (abb == NULL)
        return NULL;
    else {
        TAbb nuevo = new _rep_abb;
        nuevo-> elemInfo = copiaInfo(abb-> elemInfo);
        nuevo-> izq = copiaAbb(abb-> izq);
        nuevo-> der = copiaAbb(abb-> der);
    return nuevo;
    }
}