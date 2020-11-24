#ifndef ADL_H_INCLUDED
#define ADL_H_INCLUDED
#include <windows.h>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include "archivo.h"
#include "arbol.h"
#include "Lista.h"
#include "time.h"


typedef struct{
    stUsuario usr;
    struct nodoPlaylist * listaPlaylist;
}stCelda;

///UTILIDADES
void imprimirCabecera(char cabecera[]);
void gotoxy(int X,int Y);
void ingresarContrasenia(char C[]);

/// ARCHIVOS TO ADL
void archivosToADL(stCelda ADL[],int validos, nodoArbolCancion * arbol);
void usuariosToADL(stCelda ADL[]);
void detallesPlaylistToADL(stCelda ADL[],int validos,nodoArbolCancion * arbol);

void agregarUsuario(stCelda ADL[],int ** validos);
stUsuario cargarUsuario(stCelda ADL[],int validos);
int validarExistenciaUsuario(stCelda Celda[],char NombreUsuario[],int V);
int validarAnioIngresado();

/// MOSTRAR USUARIO
void recorrerYmostrarUsrADL(stCelda A[],int validos, int gotox);
void mostrarUsr(stUsuario U, int gotox);

void eliminarUsr(stCelda ADL[], int validos);
int buscarUsrEnADL(stCelda ADL[], int validos, int id);
int buscarUsrPorNombre(stCelda ADL[], int validos, char nombreUsr[]); //busca usuario por nombre usuario

/// MODIFICAR USUARIO
void modificarNombreUsuario(int pos,stCelda ADL[],int validos);
void modificarPassUsuario(int pos,stCelda ADL[],int validos);
void modificarPlaylist(int id, stCelda ADL[], int validos);

/// MODIFICAR PLAYLIST
///void modificarNombrePlaylist(nodoPlaylist * play);

int validarIngresoUsuario(stCelda ADL[], int validos); ///LO PONGO ACA PORQUE TRABAJA CON EL ADL SOLAMENTE


/// NUEVOS DATOS A ARCHIVOS
void usuariosToArchivo(stCelda ADL[], int validos);
void usrPlaylistToarchivo(nodoPlaylist * Lista,FILE * archivoP,FILE * archivoD);
void usrDetalleCancionPlaylistToArchivo(nodoPlaylist * Lista,FILE * archivoD);


#endif // ADL_H_INCLUDED

