/* 5280080 */ // sustituiir con los 7 dígitos de la cédula

#include "../include/mapping.h"
#include "../include/colCadenas.h"

struct _rep_mapping {
    TColCadenas mapeo;
    nat cant_relaciones;
};

TMapping crearMap(nat M) {
    TMapping map = new _rep_mapping;
    map-> mapeo = crearColCadenas(M);
    map-> cant_relaciones = 0;
    return map;    
}

void liberarMap(TMapping map) {
    liberarColCadenas(map-> mapeo);
    delete map;
}

TMapping asociarEnMap(nat clave, double valor, TMapping map) {
    map-> mapeo = insertarEnColCadenas(clave, valor, clave % tamanioColCadenas(map-> mapeo), map-> mapeo);
    map-> cant_relaciones++;
    return map;
}

TMapping desasociarEnMap(nat clave, TMapping map) { 
    map-> mapeo = removerDeColCadenas(clave, clave % tamanioColCadenas(map-> mapeo), map-> mapeo);
    map-> cant_relaciones--;
    return map;
 }

bool esClaveEnMap(nat clave, TMapping map) { 
    return estaEnColCadenas(clave, clave % tamanioColCadenas(map-> mapeo), map-> mapeo);
}

double valorEnMap(nat clave, TMapping map) { return realInfo(infoEnColCadenas(clave, clave % tamanioColCadenas( map-> mapeo), map-> mapeo)); }

bool estaLlenoMap(TMapping map) { return map-> cant_relaciones == tamanioColCadenas(map-> mapeo); }


