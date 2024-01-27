/* 5280080 */ // sustituiir con los 7 dígitos de lubua cédula

#include "../include/aplicaciones.h"
#include "../include/cadena.h"
#include "../include/iterador.h"

TCadena insertarAlFinal(nat natural, double real, TCadena cad) {
  cad = insertarAlInicio(natural, real, cad);
  return cadenaSiguiente(cad);
}

TCadena removerPrimero(TCadena cad) {
  cad = removerDeCadena(natInfo(primeroEnCadena(cad)), cad);
  return cad;
}

TCadena copiaCadena(TCadena cad) {
  if( cantidadEnCadena(cad) > 0){
    TCadena copia = crearCadena();
    nat j = cantidadEnCadena(cad);
    for (nat i = 0; i < j; i++){
       copia = insertarAlFinal(natInfo(primeroEnCadena(cad)), realInfo(primeroEnCadena(cad)), copia);
       cad = cadenaSiguiente(cad);
    }
    return copia;
  }
  else return NULL;
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