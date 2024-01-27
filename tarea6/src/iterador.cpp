/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/iterador.h"
#include "../include/info.h"

struct nodo
{
  nat elem;
  nodo *sig;
};

struct _rep_iterador
{
  nodo *inicio;
  nodo *actual;
  nodo *final;
};

TIterador crearIterador()
{
  TIterador vacio = new _rep_iterador;
  vacio->inicio = NULL;
  vacio->actual = NULL;
  vacio->final = NULL;
  return vacio;
}

void liberarIterador(TIterador iter)
{
  if (iter != NULL)
  {
    while (iter->inicio != iter->final)
    {
      nodo *borrar = iter->inicio;
      iter->inicio = iter->inicio->sig;
      delete borrar;
    }
    delete iter->inicio;
    delete iter;
  }
}

bool estaDefinidaActual(TIterador iter)
{
  return iter->actual != NULL;
}

void agregarAIterador(nat elem, TIterador const iter)
{
  if (iter->inicio == NULL)
  {
    nodo *agregar = new nodo;
    agregar->elem = elem;
    agregar->sig = NULL;
    iter->inicio = agregar;
    iter->final = iter->inicio;
  }
  else
  {
    nodo *agregar = new nodo;
    agregar->elem = elem;
    agregar->sig = NULL;
    iter->final->sig = agregar;
    iter->final = iter->final->sig;
  }
}

void reiniciarIterador(TIterador const iter)
{
  if (iter->inicio != NULL)
    iter->actual = iter->inicio;
}

void avanzarIterador(TIterador const iter)
{
  if (estaDefinidaActual(iter))
    iter->actual = iter->actual->sig;
}

nat actualEnIterador(TIterador iter)
{
  return iter->actual->elem;
}
