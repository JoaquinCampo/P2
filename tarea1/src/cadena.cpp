/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/cadena.h"

// los elementos se mantienen entre 0 y cantidad - 1, incluidos
struct _rep_cadena {
    int longitud;
    TInfo arr_TInf[L];
};

TCadena crearCadena() {
    TCadena CadenaVacia = new _rep_cadena;
    CadenaVacia -> longitud = 0;
  return CadenaVacia;
}

/* en siguientes tareas
void liberarCadena(TCadena cad) {
}
*/

nat cantidadEnCadena(TCadena cad) {
  return cad -> longitud;
}

bool estaEnCadena(nat natural, TCadena cad) {
    int i = 0;
    while(i < cad -> longitud && natInfo(cad-> arr_TInf[i]) != natural)
        i++;
    if (i < cad -> longitud)
        return true;
    else return false;
}

TCadena insertarAlInicio(nat natural, double real, TCadena cad) {
    for(int i = cad -> longitud; i > 0; i--)
        cad -> arr_TInf[i] = cad -> arr_TInf[i-1];
    cad -> arr_TInf[0] = crearInfo(natural, real);
    cad ->longitud++;
    return cad;
}

TInfo infoCadena(nat natural, TCadena cad) {
  int i = 0;
  while( i < cad -> longitud && natInfo(cad -> arr_TInf[i]) != natural)
  i++;
  return cad -> arr_TInf[i];
}

TCadena removerDeCadena(nat natural, TCadena cad) {
    int i = 0;
    while( i < cad -> longitud && natInfo(cad -> arr_TInf[i]) != natural)
        i++;
    liberarInfo(cad-> arr_TInf[i]);
    for (int j = i; j < cad -> longitud - 1; j++) 
        cad -> arr_TInf[j] = cad -> arr_TInf[j+1];
    cad -> longitud--;
    return cad;
}

void imprimirCadena(TCadena cad) {
    if( cantidadEnCadena(cad) != 0){
        for (int i = 0; i < cad -> longitud; i++)
            printf("%s", infoATexto(cad -> arr_TInf[i]));
    }
printf("\n");
}