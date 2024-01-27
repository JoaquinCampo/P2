/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colaDePrioridad.h"
#include "../include/info.h"

struct _rep_colaDePrioridad
{
  TInfo *heap;
  nat *posicion;
  nat max;
  nat cant;
};

TColaDePrioridad crearCP(nat N)
{
  TColaDePrioridad devolver = new _rep_colaDePrioridad;
  devolver->heap = new TInfo[N + 1];
  devolver->posicion = new nat[N + 1];
  for (nat i = 0; i < N + 1; i++)
    devolver->posicion[i] = 0;
  devolver->max = N;
  devolver->cant = 0;
  return devolver;
}

TColaDePrioridad invertirPrioridad(TColaDePrioridad cp)
{
  return NULL;
}

void liberarCP(TColaDePrioridad cp)
{
  for (nat i = 1; i < cp->cant + 1; i++)
    liberarInfo(cp->heap[i]);
  delete[] cp->posicion;
  delete[] cp->heap;
  delete cp;
}

void filtradoAscendenteMin(TColaDePrioridad &cp, nat pos)
{
  TInfo subir = cp->heap[pos];
  while (pos > 1 && realInfo(cp->heap[pos / 2]) > realInfo(subir))
  {
    cp->heap[pos] = cp->heap[pos / 2];
    cp->posicion[natInfo(cp->heap[pos / 2])] = pos;
    pos = pos / 2;
  }
  cp->heap[pos] = swap;
  cp->posicion[natInfo(subir)] = pos;
}

void filtradoDescendenteMin(TColaDePrioridad &cp, nat pos)
{
  TInfo bajar = cp->heap[pos];
  if (2 * pos < cp->cant + 1)
  {
    do
    {
      nat hijo = 2 * pos;
      if (hijo < cp->cant && realInfo(cp->heap[hijo]) > realInfo(cp->heap[hijo + 1]))
        hijo++;
      if (realInfo(bajar) < realInfo(cp->heap[hijo]))
      {
        cp->heap[pos] = cp->heap[hijo];
        cp->posicion[natInfo(cp->heap[hijo])] = pos;
        pos = hijo;
      }
    } while (2 * pos < cp->cant + 1 && realInfo(swap) > realInfo(cp->heap[2 * pos]));
    cp->heap[pos] = swap;
    cp->posicion[natInfo(subir)] = pos;
  }
}

void insertarEnCP(nat elem, double valor, TColaDePrioridad cp)
{
  if (0 < elem && elem < cp->max + 1)
  {
    if (estaEnCP(elem, cp))
    {
      liberarInfo(cp->heap[cp->posicion[elem]]);
      cp->heap[cp->posicion[elem]] = crearInfo(elem, valor);
      if (cp->cant > 1)
        filtradoAscendente(cp, cp->cant);
      filtradoDescendente(cp, cp->cant);
    }
    else
    {
      cp->cant++;
      iberarInfo(cp->heap[cp->posicion[elem]]);
      cp->heap[cp->posicion[elem]] = crearInfo(elem, valor);
      cp->posicion[elem] = cp->cant;
      if (cp->cant > 1)
        filtradoAscendente(cp, cp->cant);
    }
  }
  return cp;
}

bool estaVaciaCP(TColaDePrioridad cp)
{
  return cp->cant == 0;
}

nat prioritario(TColaDePrioridad cp)
{
  return cp->heap[1];
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp)
{
  if (!estaVaciaCP(cp))
  {
    liberarInfo(cp->heap[1]);
    cp->heap[1] = copiaInfo(cp->heap[cp->cant]);
    cp->posicion[natInfo(cp->heap[cp->cant])] = 0;
    liberarInfo(cp->heap[cp->cant]);
    cp->cant--;
    filtradoDescendente(cp, 1);
  }
}

bool estaEnCP(nat elem, TColaDePrioridad cp)
{
  return cp->posicion[elem] != 0;
}

double prioridad(nat elem, TColaDePrioridad cp)
{
  return realInfo(cp->heap[cp->posicion[elem]]);
}