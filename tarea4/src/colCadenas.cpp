/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"

struct _rep_colCadenas {
  TCadena *arr_TCadena;
  nat cant_Cadenas;
};

TColCadenas crearColCadenas(nat tamanio) {
  TColCadenas colCadenasVacias = new _rep_colCadenas;
  colCadenasVacias-> arr_TCadena = new TCadena [tamanio];
  colCadenasVacias-> cant_Cadenas = tamanio;
  for (nat i = 0; i < tamanio; i++)
    colCadenasVacias-> arr_TCadena[i] = crearCadena();
  return colCadenasVacias;
}

void liberarColCadenas(TColCadenas col) {
  for(nat i = 0; i < col-> cant_Cadenas; i++)
    liberarCadena(col->arr_TCadena[i]);
  delete [] col-> arr_TCadena;
  delete col;
}

nat tamanioColCadenas(TColCadenas col){return col-> cant_Cadenas;}

TCadena cadenaDeColCadenas(nat pos, TColCadenas col) {
  return col-> arr_TCadena[pos];
}

nat cantidadColCadenas(nat pos, TColCadenas col) {
  return cantidadEnCadena(col-> arr_TCadena[pos]);
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col) {
  return estaEnCadena(natural, col-> arr_TCadena[pos]);
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos,
                                 TColCadenas col) {
  col-> arr_TCadena[pos] = insertarAlInicio(natural, real, col-> arr_TCadena[pos]);
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col) {
  return infoCadena(natural, col-> arr_TCadena[pos]);
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col) {
  col-> arr_TCadena[pos] = removerDeCadena(natural, col-> arr_TCadena[pos]);
  return col;
}