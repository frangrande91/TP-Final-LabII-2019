#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "ADL.h"



void gotoxy(int X,int Y);
int ingresarOpcion();

void iniciarMenu();

void menuPrincipal();
void imprimirMenuPrincipal();
void switchMenuPrincipal(int opc, stCelda ADL[], int *validos, nodoArbolCancion * arbol);

///*********************************************** MENU DE ADMINISTRADOR *******************************************************
// validar ingreso del administrador al sistema.
int validarIngresoAdministrador();


// menu principal del administrador
void menuAdministrador();
void imprimirOpcAdministrador();
nodoArbolCancion * switchMenuAdministrador(int opc, stCelda ADL[], int validos, nodoArbolCancion * arbol);

// menu para administrar usuarios
void menuAdministrarUsuarios();
void imprimirMenuAdministrarUsuarios();
void switchMenuAdministrarUsuarios(int opc, int * validos, stCelda ADL[], nodoArbolCancion * arbol);

void menuModificarPlaylist(nodoPlaylist * play, nodoArbolCancion * arbol);

// menu para administrar canciones

nodoArbolCancion * menuAdministrarCanciones(nodoArbolCancion * arbol);
void imprimirAdministrarCanciones();
nodoArbolCancion * switchMenuAdministrarCanciones(int opc,nodoArbolCancion * arbol);

///Menu para modificar una cancion
void menuModificarCancion(nodoArbolCancion * arbol);
void imprimirOpcModificarCancion();
void switchMenuModificarCancion(int opc,nodoArbolCancion * nodoMfcar);

///******************************************** MENU USUARIO *********************************************************

void menuUsuario();
void imprimirOpcUsuario();
void switchMenuUsuario(int opc, stCelda ADL[], int validos, int posUsr, nodoArbolCancion * arbol);

#endif // MENU_H_INCLUDED
