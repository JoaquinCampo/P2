/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/abb.h"

struct _rep_abb
{
    TInfo elemInfo;
    TAbb izq, der;
};

TAbb crearAbb() { return NULL; }

void liberarAbb(TAbb abb)
{
    if (abb == NULL)
        delete abb;
    else
    {
        TAbb borrar = abb;
        liberarAbb(abb->izq);
        liberarAbb(abb->der);
        liberarInfo(borrar->elemInfo);
        delete borrar;
    }
}

bool esVacioAbb(TAbb abb) { return abb == NULL; }

TAbb buscarSubarbol(nat clave, TAbb abb)
{
    if (abb == NULL || natInfo(abb->elemInfo) == clave)
        return abb;
    else
    {
        if (natInfo(abb->elemInfo) < clave)
            return buscarSubarbol(clave, abb->der);
        else
            return buscarSubarbol(clave, abb->izq);
    }
}

TInfo raiz(TAbb abb) { return abb->elemInfo; }

TAbb izquierdo(TAbb abb) { return abb->izq; }

TAbb derecho(TAbb abb) { return abb->der; }

TInfo menorEnAbb(TAbb abb)
{
    if (abb->izq != NULL)
        return menorEnAbb(abb->izq);
    else
        return abb->elemInfo;
}

TInfo mayorEnAbb(TAbb abb)
{
    if (abb->der != NULL)
        return mayorEnAbb(abb->der);
    else
        return abb->elemInfo;
}

TAbb consAbb(TInfo dato, TAbb izq, TAbb der)
{
    TAbb nuevo = new _rep_abb;
    nuevo->elemInfo = dato;
    nuevo->izq = izq;
    nuevo->der = der;
    return nuevo;
}

void agregarEnAbb(TInfo dato, TAbb &abb)
{
    if (abb == NULL)
    {
        abb = new _rep_abb;
        abb->elemInfo = dato;
        abb->izq = NULL;
        abb->der = NULL;
    }
    else
    {
        if (natInfo(abb->elemInfo) < natInfo(dato))
            agregarEnAbb(dato, abb->der);
        else
            agregarEnAbb(dato, abb->izq);
    }
}

TAbb insertarEnAbb(TInfo dato, TAbb abb)
{
    agregarEnAbb(dato, abb);
    return abb;
}

void eliminarTAbb(nat clave, TAbb &abb)
{
    TAbb borrar;
    if (natInfo(abb->elemInfo) == clave)
    {
        if (abb->izq == NULL)
        {
            borrar = abb;
            abb = abb->der;
            liberarInfo(borrar->elemInfo);
            delete borrar;
        }
        else if (abb->der == NULL)
        {
            borrar = abb;
            abb = abb->izq;
            liberarInfo(borrar->elemInfo);
            delete borrar;
        }
        else
        {
            liberarInfo(abb->elemInfo);
            abb->elemInfo = copiaInfo(mayorEnAbb(abb->izq));
            eliminarTAbb(natInfo(abb->elemInfo), abb->izq);
        }
    }
    else if (clave > natInfo(abb->elemInfo))
        eliminarTAbb(clave, abb->der);
    else
        eliminarTAbb(clave, abb->izq);
}

TAbb removerDeAbb(nat clave, TAbb abb)
{
    eliminarTAbb(clave, abb);
    return abb;
}

TAbb copiaAbb(TAbb abb)
{
    if (abb == NULL)
        return NULL;
    else
    {
        TAbb nuevo = new _rep_abb;
        nuevo->elemInfo = copiaInfo(abb->elemInfo);
        nuevo->izq = copiaAbb(abb->izq);
        nuevo->der = copiaAbb(abb->der);
        return nuevo;
    }
}

TAbb RR(TAbb abb)
{
    TAbb devolver = abb->der;
    abb->der = devolver->izq;
    devolver->izq = abb;
    return devolver;
}

TAbb LL(TAbb abb)
{
    TAbb devolver = abb->izq;
    abb->izq = devolver->der;
    devolver->der = abb;
    return devolver;
}

TAbb LR(TAbb abb)
{
    TAbb subir = abb->izq->der;
    TAbb medio = abb->izq;
    abb->izq = subir->der;
    medio->der = subir->izq;
    subir->izq = medio;
    subir->der = abb;
    return subir;
}

TAbb RL(TAbb abb)
{
    TAbb subir = abb->der->izq;
    TAbb medio = abb->der;
    abb->der = subir->izq;
    medio->izq = subir->der;
    subir->der = medio;
    subir->izq = abb;
    return subir;
}

TAbb rotar(nat clave, char tipo[2], TAbb abb)
{
    if (abb == NULL)
        return abb;
    else if (natInfo(abb->elemInfo) == clave)
    {
        if (tipo[0] == 'R' && tipo[1] == 'R')
        {
            if (abb->der != NULL)
                return RR(abb);
            else
                return abb;
        }
        else if (tipo[0] == 'L' && tipo[1] == 'L')
        {
            if (abb->izq != NULL)
                return LL(abb);
            else
                return abb;
        }
        else if (tipo[0] == 'L' && tipo[1] == 'R')
        {
            if (abb->izq != NULL && abb->izq->der != NULL)
                return LR(abb);
            else
                return abb;
        }
        else
        {
            if (abb->der != NULL && abb->der->izq != NULL)
                return RL(abb);
            else
                return abb;
        }
    }
    else
    {
        if (natInfo(abb->elemInfo) < clave)
            abb->der = rotar(clave, tipo, abb->der);
        else
            abb->izq = rotar(clave, tipo, abb->izq);
        return abb;
    }
}