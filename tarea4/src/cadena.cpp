/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"

struct _rep_cadena {
  TInfo elemInfo;
  TCadena sig;
  TCadena ant;
};

TCadena crearCadena() {
  return NULL;
}

void liberarCadena(TCadena cad) {
if (cad != NULL){
  if (cad == cad-> sig){
    liberarInfo(cad-> elemInfo);
    delete(cad);
  }
  else {
    TCadena primero = cad;
    cad = cad-> sig;
    while(cad != primero){
      TCadena borrar = cad;
      cad = cad-> sig;
      liberarInfo(borrar-> elemInfo);
      delete(borrar);
    }
    liberarInfo(primero-> elemInfo);
    delete(primero);
  }
}
}

nat cantidadEnCadena(TCadena cad) {
  nat contador = 0;
  if (cad == NULL)
    return 0;
  if (cad == cad-> sig)
    return 1;
  else{
    TCadena primero = cad;
    cad = cad-> sig;
    contador++;
    while (cad != primero){
      cad = cad-> sig;
      contador++;
    }
    return contador;
  }
}

bool estaEnCadena(nat natural, TCadena cad) {
    if (cad == NULL)
        return false;
    if (cad == cad-> sig){
        if (natInfo(cad-> elemInfo) == natural)
            return true;
        else return false;
    }
    else {
        bool estado = false;
        if(natInfo(cad-> elemInfo) == natural)
            return true;
        TCadena primero = cad;
        cad = cad-> sig;
        while (natInfo(cad-> elemInfo) != natural && cad != primero)
            cad = cad-> sig;
        if (cad == primero)
          estado = false;
        else estado = true;
        return estado;
    }
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad) {
  TCadena aux = new _rep_cadena;
  aux-> elemInfo = crearInfo(natural, real);
  if (cad == NULL){
    cad = aux;
    cad-> sig = cad;
    cad-> ant = cad;
    return cad;
  }
  else{
    aux-> sig = cad;
    aux-> ant = cad-> ant;
    cad-> ant -> sig = aux;
    cad-> ant = aux;
    cad = aux;
  return cad;
  }
}

TInfo infoCadena(nat natural, TCadena cad) {
  if (natInfo(cad->elemInfo) == natural)
    return cad-> elemInfo;
  else {
    TCadena primero = cad;
    cad = cad-> sig;
    while (natInfo(cad-> elemInfo) != natural && cad != primero)
      cad = cad-> sig;
  return cad -> elemInfo;
  }
}

TInfo primeroEnCadena(TCadena cad) {
  return cad->elemInfo;
}

TCadena cadenaSiguiente(TCadena cad) {
  if (cad == NULL || cad == cad-> sig)
    return cad;
  else return cad-> sig;
}

TCadena removerDeCadena(nat natural, TCadena cad) {
  if (cad == cad-> sig){
    liberarInfo(cad-> elemInfo);
    delete(cad);
    return NULL;
  }
  else {
    if(natInfo(cad->elemInfo) == natural){
      cad-> ant-> sig = cad -> sig;
      cad-> sig-> ant = cad-> ant;
      TCadena devolver = cad-> sig;
      liberarInfo(cad-> elemInfo);
      delete(cad);
      return devolver;
    }
    else {
      TCadena primero = cad;
      cad = cad-> sig;
      while(natInfo(cad-> elemInfo) != natural)
        cad = cad-> sig;
      cad-> ant-> sig = cad -> sig;
      cad-> sig-> ant = cad-> ant;
      liberarInfo(cad->elemInfo);
      delete(cad);
      return primero;
    }
  }
}

void imprimirCadena(TCadena cad){
  if (cad != NULL){
    nat j = cantidadEnCadena(cad);
    for(nat i = 0; i < j; i++){
      imprimirInfo(cad-> elemInfo);
      cad = cad-> sig;
    }
  }
  printf("\n");
}

TCadena insertarAlFinal(nat natural, double real, TCadena cad) {
  cad = insertarAlInicio(natural, real, cad);
  return cadenaSiguiente(cad);
}

TCadena removerPrimero(TCadena cad) {
  cad = removerDeCadena(natInfo(primeroEnCadena(cad)), cad);
  return cad;
}

TCadena copiaCadena(TCadena cad) {
  nat j = cantidadEnCadena(cad);
  if( j > 0){
    TCadena copia = crearCadena();
    for (nat i = 0; i < j; i++){
       copia = insertarAlFinal(natInfo(primeroEnCadena(cad)), realInfo(primeroEnCadena(cad)), copia);
       cad = cadenaSiguiente(cad);
    }
    return copia;
  }
  else return NULL;
}