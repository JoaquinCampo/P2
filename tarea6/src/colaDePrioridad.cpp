/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colaDePrioridad.h"
#include "../include/info.h"

struct _rep_colaDePrioridad
{
  TInfo *heap;
  nat *posicion;
  nat max;
  nat cant;
  bool prioMin;
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
  devolver->prioMin = true;
  return devolver;
}

void swapPos(nat &a, nat &b)
{
  nat aux = a;
  a = b;
  b = aux;
}

void swapTInfo(TInfo &a, TInfo &b)
{
  TInfo aux = a;
  a = b;
  b = aux;
}

void filtradoDescendenteMin(TColaDePrioridad &cp, nat pos)
{
  TInfo bajar = cp->heap[pos];
  while (2 * pos < cp->cant + 1)
  {
    nat hijo = 2 * pos;
    if (2 * pos < cp->cant && realInfo(cp->heap[2 * pos + 1]) < realInfo(cp->heap[2 * pos]))
      hijo++;
    if (realInfo(bajar) > realInfo(cp->heap[hijo]))
    {
      swapTInfo(cp->heap[pos], cp->heap[hijo]);
      swapPos(cp->posicion[natInfo(cp->heap[hijo])], cp->posicion[natInfo(cp->heap[pos])]);
      pos = hijo;
    }
    else
      break;
  }
}

void filtradoDescendenteMax(TColaDePrioridad &cp, nat pos)
{
  TInfo bajar = cp->heap[pos];
  while (2 * pos < cp->cant + 1)
  {
    nat hijo = 2 * pos;
    if (2 * pos < cp->cant && realInfo(cp->heap[2 * pos + 1]) > realInfo(cp->heap[2 * pos]))
      hijo++;
    if (realInfo(bajar) < realInfo(cp->heap[hijo]))
    {
      swapTInfo(cp->heap[pos], cp->heap[hijo]);
      swapPos(cp->posicion[natInfo(cp->heap[hijo])], cp->posicion[natInfo(cp->heap[pos])]);
      pos = hijo;
    }
    else
      break;
  }
}

void filtradoAscendenteMin(TColaDePrioridad &cp, nat pos)
{
  TInfo subir = cp->heap[pos];
  while (pos > 1 && realInfo(cp->heap[pos / 2]) > realInfo(subir))
  {
    swapTInfo(cp->heap[pos], cp->heap[pos / 2]);
    swapPos(cp->posicion[natInfo(cp->heap[pos])], cp->posicion[natInfo(cp->heap[pos / 2])]);
    pos = pos / 2;
  }
}

void filtradoAscendenteMax(TColaDePrioridad &cp, nat pos)
{
  TInfo subir = cp->heap[pos];
  while (pos > 1 && realInfo(cp->heap[pos / 2]) < realInfo(subir))
  {
    swapTInfo(cp->heap[pos], cp->heap[pos / 2]);
    swapPos(cp->posicion[natInfo(cp->heap[pos])], cp->posicion[natInfo(cp->heap[pos / 2])]);
    pos = pos / 2;
  }
}

TColaDePrioridad invertirPrioridad(TColaDePrioridad cp)
{
  if (!estaVaciaCP(cp) && cp->cant != 1)
  {
    if (cp->prioMin)
    {
      for (nat i = 1; i <= cp->cant; i++)
        filtradoAscendenteMax(cp, i);
    }
    else
    {
      for (nat i = 1; i <= cp->cant; i++)
        filtradoAscendenteMin(cp, i);
    }
  }
  cp->prioMin = !cp->prioMin;
  return cp;
}

void liberarCP(TColaDePrioridad cp)
{
  for (nat i = 1; i < cp->cant + 1; i++)
    liberarInfo(cp->heap[i]);
  delete[] cp->posicion;
  delete[] cp->heap;
  delete cp;
}

TColaDePrioridad insertarEnCP(nat elem, double valor, TColaDePrioridad cp)
{
  if (0 < elem && elem < cp->max + 1)
  {
    if (estaEnCP(elem, cp))
    {
      liberarInfo(cp->heap[cp->posicion[elem]]);
      cp->heap[cp->posicion[elem]] = crearInfo(elem, valor);
      if (cp->cant > 1)
      {
        if (cp->prioMin)
        {
          filtradoAscendenteMin(cp, cp->posicion[elem]);
          filtradoDescendenteMin(cp, cp->posicion[elem]);
        }
        else
        {
          filtradoAscendenteMax(cp, cp->posicion[elem]);
          filtradoDescendenteMax(cp, cp->posicion[elem]);
        }
      }
      return cp;
    }
    else
    {
      cp->cant++;
      cp->heap[cp->cant] = crearInfo(elem, valor);
      cp->posicion[elem] = cp->cant;
      if (cp->cant > 1)
      {
        if (cp->prioMin)
          filtradoAscendenteMin(cp, cp->cant);
        else
          filtradoAscendenteMax(cp, cp->cant);
      }
      return cp;
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
  return natInfo(cp->heap[1]);
}

TColaDePrioridad eliminarPrioritario(TColaDePrioridad cp)
{
  if (!estaVaciaCP(cp))
  {
    if (cp->cant == 1)
    {
      cp->posicion[natInfo(cp->heap[1])] = 0;
      liberarInfo(cp->heap[1]);
      cp->cant--;
    }
    else
    {
      cp->posicion[natInfo(cp->heap[1])] = 0;
      liberarInfo(cp->heap[1]);
      cp->heap[1] = copiaInfo(cp->heap[cp->cant]);
      cp->posicion[natInfo(cp->heap[cp->cant])] = 1;
      liberarInfo(cp->heap[cp->cant]);
      cp->cant--;
      if (cp->prioMin)
        filtradoDescendenteMin(cp, 1);
      else
        filtradoDescendenteMax(cp, 1);
    }
  }
  return cp;
}

bool estaEnCP(nat elem, TColaDePrioridad cp)
{
  if (0 < elem && elem < cp->max + 1)
    return cp->posicion[elem] != 0;
  else
    return false;
}

double prioridad(nat elem, TColaDePrioridad cp)
{
  return realInfo(cp->heap[cp->posicion[elem]]);
}
