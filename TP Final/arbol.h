#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include "archivo.h"

typedef struct{
    stCancion c;
    struct nodoArbolCancion * izq;
    struct nodoArbolCancion * der;
} nodoArbolCancion;


nodoArbolCancion * inicArbol();
nodoArbolCancion * crearNodoArbol(stCancion dato);
nodoArbolCancion * insertarNodoArbol(nodoArbolCancion * arbol, stCancion dato);/// POR ID BALANCEAR
nodoArbolCancion * buscarCancion(nodoArbolCancion * arbol, int id); ///POR ID

/// Mostrar arbol
void inOrder(nodoArbolCancion * arbol);
void mostrarCancion(stCancion C);
void mostrarCancionCorta(nodoArbolCancion * arbol);


/// Ingresar balanceado
int contarNodosArbol(nodoArbolCancion * Ar);
int alturaArbol(nodoArbolCancion * A);
int factorEquilibrio(nodoArbolCancion * A);
nodoArbolCancion * rotacionIzquierda(nodoArbolCancion * A);
nodoArbolCancion * rotacionDerecha(nodoArbolCancion * A);
nodoArbolCancion * insertBalanced(nodoArbolCancion * A, stCancion C);
nodoArbolCancion * borrarNodoArbol(nodoArbolCancion * A,int id);
nodoArbolCancion * eliminarArbol(nodoArbolCancion * arbol);
nodoArbolCancion * nodoMasD(nodoArbolCancion * A);
nodoArbolCancion * nodoMasI(nodoArbolCancion * A);
nodoArbolCancion * archivoToArbol(nodoArbolCancion * Arbol);

/// CANCIONES
nodoArbolCancion * altaCancionArbol(nodoArbolCancion * arbol);
void guardarCancionesArchivo(nodoArbolCancion * arbol);
void guardarCancion(FILE * archivo,nodoArbolCancion * arbol);
void eliminarCancion(nodoArbolCancion * arbol);

//void recomendarCanciones(nodoArbolCancion * arbol, nodoPlaylist * listaPlaylist, char genero[]);

#endif // ARBOL_H_INCLUDED
