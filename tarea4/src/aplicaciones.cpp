/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include <string.h>
#include "../include/colCadenas.h"

bool estaOrdenada(TCadena cad) {
  if (cad == NULL || cad == cadenaSiguiente(cad))
    return true;
  else {
    for (TCadena aux = cad; cadenaSiguiente(aux) != cad; aux = cadenaSiguiente(aux))
      if (natInfo(primeroEnCadena(cadenaSiguiente(aux))) <= natInfo(primeroEnCadena(aux)))
        return false;
    return true;
  }
}

TCadena mezclaCadenas(TCadena cad1, TCadena cad2){
  if (cad2 == NULL)
    return copiaCadena(cad1);
  if (cad1 == NULL)
    return copiaCadena(cad2);
  else {
    nat i = 0, j = 0;
    nat cant1 = cantidadEnCadena(cad1), cant2 = cantidadEnCadena(cad2);
    TCadena resultado = crearCadena();
    while (i < cant1 && j < cant2) {
      if (natInfo(primeroEnCadena(cad1)) < natInfo(primeroEnCadena(cad2))){
        resultado = insertarAlFinal(natInfo(primeroEnCadena(cad1)), realInfo(primeroEnCadena(cad1)), resultado);
        cad1 = cadenaSiguiente(cad1);
        i++;
      }
      else if(natInfo(primeroEnCadena(cad1)) > natInfo(primeroEnCadena(cad2))){
        resultado = insertarAlFinal(natInfo(primeroEnCadena(cad2)), realInfo(primeroEnCadena(cad2)), resultado);
        cad2 = cadenaSiguiente(cad2);
        j++;
      }
      else {
          if (realInfo(primeroEnCadena(cad1)) >= realInfo(primeroEnCadena(cad2))){
            resultado = insertarAlFinal(natInfo(primeroEnCadena(cad1)), realInfo(primeroEnCadena(cad1)), resultado);
          }
          else {
            resultado = insertarAlFinal(natInfo(primeroEnCadena(cad2)), realInfo(primeroEnCadena(cad2)), resultado);
          }
          cad1 = cadenaSiguiente(cad1);
          cad2 = cadenaSiguiente(cad2);
          i++;
          j++;
        }
      } //while
    while (i < cant1){
      resultado = insertarAlFinal(natInfo(primeroEnCadena(cad1)), realInfo(primeroEnCadena(cad1)), resultado);
      cad1 = cadenaSiguiente(cad1);
      i++;
    }
    while (j < cant2){
      resultado = insertarAlFinal(natInfo(primeroEnCadena(cad2)), realInfo(primeroEnCadena(cad2)), resultado);
      cad2 = cadenaSiguiente(cad2);
      j++;
    }
  return resultado;
  }
}

TAbb balanced(TInfo *arreglo, int inicio, int final){
  if (inicio > final)
    return NULL;
  else {
    int mid = (inicio + final) / 2;
    return consAbb(copiaInfo(arreglo [mid]), balanced(arreglo,inicio, mid - 1), balanced(arreglo, mid + 1, final));
  }
}

TAbb crearBalanceado(TInfo *arreglo, nat n) { 
  if (n == 0)
    return NULL;
  else return balanced(arreglo, 0, --n);
}

TAbb unionAbbs(TAbb abb1, TAbb abb2) {
    TCadena cad1 = linealizacion (abb1);
    TCadena cad2 = linealizacion (abb2);
    TCadena doble = mezclaCadenas(cad1, cad2);
    nat cant = cantidadEnCadena(doble);
    TInfo *arr = new TInfo[cant];
    for(nat i = 0; i < cant; i++) {
      arr[i] = primeroEnCadena(doble);
      doble = cadenaSiguiente(doble);
    }
    TAbb resultado = crearBalanceado(arr, cant);
    liberarCadena(cad1);
    liberarCadena(cad2);
    liberarCadena(doble);
    delete [] arr;
    return resultado;
}

TCola encolarCad(TCadena cad, TCola cola, nat cant) {
  if (cant == 0){}
  else {
    TInfo info = primeroEnCadena(cad);
    cola = encolarCad(cadenaSiguiente(cad), cola, --cant);
    cola = encolar(info, cola);
  }
  return cola;
}

TCola ordenadaPorModulo(nat p, TCadena cad) {
  if (cad == NULL) {
    TCola cola = crearCola();
    return cola;
  }
  if (cad == cadenaSiguiente(cad)) {
    TCola devolver = crearCola();
    devolver = encolar(primeroEnCadena(cad), devolver); 
    return devolver;
  }
  else {
    TColCadenas col = crearColCadenas(p);
    nat cant = cantidadEnCadena(cad);
    for (nat i = 0; i < cant; i++) {
      col = insertarEnColCadenas(natInfo(primeroEnCadena(cad)), realInfo(primeroEnCadena(cad)), natInfo(primeroEnCadena(cad)) % p, col);
      cad = cadenaSiguiente(cad);
    }
    TCola devolver = crearCola();
    for (nat i = 0; i < p; i++){
      TCadena colCad = cadenaDeColCadenas(i, col);
      nat cant = cantidadColCadenas(i, col);
      devolver = encolarCad(colCad, devolver, cant);
    }
    liberarColCadenas(col);
    return devolver;
  }
}

TPila menoresQueElResto(TCadena cad, nat cantidad) {
  TPila p = crearPila();
  if (cad == NULL)
      return p;
  else {
    p = apilar(primeroEnCadena(cad), p);
    cad = cadenaSiguiente(cad);
    cantidad--;
    while (cantidad > 0) {
      if (cantidadEnPila(p) == 0) {
        p = apilar(primeroEnCadena(cad), p);
        cad = cadenaSiguiente(cad);
        cantidad--;
      }
      else {
        if (natInfo(cima(p)) < natInfo(primeroEnCadena(cad))) {
          p = apilar(primeroEnCadena(cad), p);
          cad = cadenaSiguiente(cad);
          cantidad--;
        }
        else p = desapilar(p);
      }
    }
    return p;
  }
}

void inOrder(TAbb abb, TCadena &cad){
  if (abb != NULL){
    inOrder(derecho(abb), cad);
    cad = insertarAlInicio(natInfo(raiz(abb)), realInfo(raiz(abb)), cad);
    inOrder(izquierdo(abb), cad);
  }
}

TCadena linealizacion(TAbb abb) { 
  TCadena cad = crearCadena();
  inOrder(abb, cad);
  return cad;
}

void imprimirAux (TAbb abb, int contador){
  if (abb != NULL){
    contador++;
    imprimirAux(derecho(abb), contador);
    for (int i = 0; i < contador; i++)
      printf("-");
    imprimirInfo(raiz(abb));
    printf("\n");
    imprimirAux(izquierdo(abb),contador);
  }
}

void imprimirAbb(TAbb abb) {
  int contador = -1;
  imprimirAux(abb, contador);
}

nat max (nat i, nat j){
    if ( i < j)
        return j;
    else return i;
}

nat altura (TAbb abb){
    if (abb == NULL)
        return 0;
    else return 1 + max(altura(izquierdo(abb)),altura(derecho(abb)));
}

bool esPerfecto(TAbb abb) {
  if (abb == NULL)
    return true;
  else if ((izquierdo(abb) == NULL && derecho(abb) != NULL) || (izquierdo(abb) != NULL && derecho(abb) == NULL))
    return false;
  else return esPerfecto(izquierdo(abb)) && esPerfecto(derecho(abb)) && altura(izquierdo(abb)) == altura(derecho(abb));
}

TAbb menores(double limite, TAbb abb) { 
  TAbb nuevo;
  if (abb == NULL)
    return NULL;
  else {
    TAbb diestro = menores(limite, derecho(abb));
    TAbb zurdo = menores(limite, izquierdo(abb));
    if (realInfo(raiz(abb)) < limite){
      nuevo = consAbb(copiaInfo(raiz(abb)), zurdo, diestro);
      return nuevo;
    }
    else if (diestro == NULL)
      nuevo = zurdo;
    else if(zurdo == NULL)
      nuevo = diestro;
    else {
      TInfo mayor = copiaInfo(mayorEnAbb(zurdo));
      nuevo = consAbb(mayor, removerDeAbb(natInfo(mayor), zurdo), diestro);
    }  
    return nuevo;
  }
}

void caminoRecursivo(nat clave, nat k, TAbb abb, TIterador &iter, nat &contador){
  if (natInfo(raiz(abb)) == clave){}
  else if(natInfo(raiz(abb)) < clave)
    caminoRecursivo(clave, k, derecho(abb), iter, contador);
  else if(natInfo(raiz(abb)) > clave)
    caminoRecursivo(clave, k, izquierdo(abb), iter, contador);
  if (contador < k){
    agregarAIterador(natInfo(raiz(abb)),iter);
    contador++;
  }
}

TIterador caminoAscendente(nat clave, nat k, TAbb abb) {
  nat contador = 0;
  TIterador iter = crearIterador();
  caminoRecursivo(clave, k, abb, iter, contador);
  return iter;
}

void imprimirPalabrasRecursivo (nat k, TPalabras palabras, nat contador, ArregloChars frase){
  if (palabras != NULL && letra(palabras) == '\0'){
    frase[contador] = '\0';
    printf("%s\n", frase);
    if (contador < k && siguientes(palabras) != NULL)
        imprimirPalabrasRecursivo(k, siguientes(palabras), contador, frase);
  }
    else if (contador < k){
      frase[contador] = letra(palabras);
      imprimirPalabrasRecursivo(k, subarboles(palabras), contador + 1, frase);
      if (siguientes(palabras) != NULL)
        imprimirPalabrasRecursivo(k, siguientes(palabras), contador, frase);
    }
}

void imprimirPalabrasCortas(nat k, TPalabras palabras) {
  nat contador = 0;
  char frase[k];
  imprimirPalabrasRecursivo(k, subarboles(palabras), contador, frase);
}

void finPrefijoRec(ArregloChars prefijo, TPalabras palabras, nat largoPrefijo, nat &contador, TPalabras &devolver){
  if (letra(palabras) != '\0' && letra(palabras) == prefijo[contador]){
    contador++;
    if (contador < largoPrefijo)
      finPrefijoRec(prefijo, subarboles(palabras), largoPrefijo, contador, devolver);
    else if(contador == largoPrefijo)
      devolver = palabras;
  }
    else if(siguientes(palabras) != NULL)
        finPrefijoRec(prefijo, siguientes(palabras), largoPrefijo, contador, devolver);
}

TPalabras buscarFinPrefijo(ArregloChars prefijo, TPalabras palabras) {
  nat largoPrefijo = strlen(prefijo); //checkear para el caso del que prefijo aparezca mas de una vez
  nat contador = 0;
  TPalabras devolver = NULL;
  if (palabras != NULL) finPrefijoRec(prefijo, subarboles(palabras), largoPrefijo, contador, devolver);
  return devolver;
}

TIterador reversoDeIteradorAux(TIterador &iter, TIterador &copia){
  if(!estaDefinidaActual(iter)){}
  else {
    nat info = actualEnIterador(iter);
    avanzarIterador(iter); 
    if (estaDefinidaActual(iter))
      reversoDeIteradorAux(iter, copia); 
    agregarAIterador(info, copia);
  }
  return copia;
}

TIterador reversoDeIterador(TIterador iter) {
  reiniciarIterador(iter);
  TIterador copia = crearIterador();
  copia = reversoDeIteradorAux(iter, copia); 
  return copia;
}