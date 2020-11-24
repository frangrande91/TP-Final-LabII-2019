#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include "archivo.h"
#include "arbol.h"


typedef struct _nodoListaCancion{
    stCancion c;
    struct _nodoListaCancion * sig;
}nodoListaCancion;

typedef struct _nodoPlaylist{
    playlist play;
    struct nodoListaCancion * listaCanciones;
    struct _nodoPlaylist * sig;
}nodoPlaylist;

/*******************************FUNCIONES DE LA LISTA DE CANCIONES***************************************/
nodoListaCancion * inicLista();
nodoListaCancion * crearNodo(stCancion dato);
nodoListaCancion * agregarPPio(nodoListaCancion * Lista, nodoListaCancion * Nuevo);
nodoListaCancion * buscarUltimo(nodoListaCancion * Lista);
nodoListaCancion * agregarFinal(nodoListaCancion * Lista, nodoListaCancion * Nuevo);
//DEPENDIENDO EL TIPO DE DATO
nodoListaCancion * agregarEnOrden(nodoListaCancion * Lista, nodoListaCancion * Nuevo);// POR NOMBRE
nodoListaCancion * borrarUnNodo(nodoListaCancion * Lista, int id);
void recorrerYmostrarListaCanciones(nodoListaCancion * lista, int gotox);

///MODIFICAR PLAYLIST
nodoListaCancion * agregarCancionAplaylist(nodoArbolCancion * arbol, nodoListaCancion * Lista);
nodoListaCancion * borrarCancionEnPlaylist(nodoListaCancion * Lista);
nodoListaCancion * borrarTodaLaLista(nodoListaCancion * lista);

nodoListaCancion * buscarCancionEnPlaylist(nodoListaCancion * lista, int idCancion);

/*******************************FUNCIONES DE LA LISTA DE PLAYLIST***************************************/
nodoPlaylist * inicListaPlaylist();
nodoPlaylist * crearNodoPlaylist(playlist dato);
nodoPlaylist * agregarFinalPlaylist(nodoPlaylist * Lista, nodoPlaylist * Nuevo);
nodoPlaylist * buscarUltimoPlaylist(nodoPlaylist * Lista);
void recorrerYmostrarListasPlaylist(nodoPlaylist * Lista);
void mostrarPlay(playlist Play, int i);

///BUSCAR UNA PLAYLIST X ID
nodoPlaylist * buscarPlaylist(nodoPlaylist * listaPlay,int id);

/// MODIFICAR PLAYLIST
nodoPlaylist * modificarNombrePlaylist(nodoPlaylist * play);
nodoPlaylist * borrarPlaylist(nodoPlaylist * listaPlaylist, int idPlaylist);

///CREAR PLAYLIST
nodoPlaylist * crearPlaylist(nodoPlaylist * Lista,stUsuario Usr);

///LISTAS A ARCHIVOS
void listaPlaylistToArchivo(nodoPlaylist * Lista);
void cancionesToArchivoDetalles(nodoPlaylist * Lista);






///RECOMENDAR CANCION
void recomendarCancion(nodoArbolCancion * arbol, nodoListaCancion * Lista);
#endif // LISTA_H_INCLUDED
