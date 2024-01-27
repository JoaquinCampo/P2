  /* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/aplicaciones.h"
#include <string.h>

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