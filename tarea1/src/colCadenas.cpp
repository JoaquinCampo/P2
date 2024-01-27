/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/colCadenas.h"
#include "../include/cadena.h"

struct _rep_colCadenas {
    TCadena arr_TCadena[CANT_CADS];
};

TColCadenas crearColCadenas() {
    TColCadenas colCadenasVacias = new _rep_colCadenas;
    for (int i = 0; i < CANT_CADS; i++)
      colCadenasVacias ->arr_TCadena[i] = crearCadena();
  return colCadenasVacias;
}

/* en siguientes tareas
void liberarColCadenas(TColCadenas col) {
}
*/
nat cantidadColCadenas(nat pos, TColCadenas col) {
  return cantidadEnCadena(col->arr_TCadena[pos]);
}

bool estaEnColCadenas(nat natural, nat pos, TColCadenas col) {
  return estaEnCadena(natural, col -> arr_TCadena[pos]);
}

TColCadenas insertarEnColCadenas(nat natural, double real, nat pos, TColCadenas col) {
  insertarAlInicio(natural,real,col -> arr_TCadena[pos]);
  return col;
}

TInfo infoEnColCadenas(nat natural, nat pos, TColCadenas col) {
  return infoCadena(natural, col -> arr_TCadena[pos]);
}

TColCadenas removerDeColCadenas(nat natural, nat pos, TColCadenas col) {
  removerDeCadena(natural, col -> arr_TCadena[pos]);
  return col;
}