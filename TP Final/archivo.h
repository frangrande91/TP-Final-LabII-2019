#ifndef ARCHIVO_H_INCLUDED
#define ARCHIVO_H_INCLUDED
#include <stdio.h>

#define archivoCanciones "canciones.dat"
#define archivoUsuarios "usuarios.dat"
#define archivoPlaylist "playlist.dat"
#define archivoDetalle "detallesPlaylist.dat"


///ESTRUCTURAS PARA EL MANEJO DE ARCHIVOS
//"usuarios.dat"
typedef struct{
    int idUsuario;
    char nombreUsuario[30];
    char pass[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    int eliminado;   // indica 1 o 0 si el usuario fue eliminado
} stUsuario;

//"canciones.dat"
typedef struct{
   int idCancion;
   char titulo[30];
   char artista[20];
   int duracion;
   char album[20];
   int anio;
   char genero[20];
   char comentario[100];
   int eliminado;  // indica 1 o 0 si la canción fue eliminada
} stCancion;

//"playlist.dat"
typedef struct{
    int idPlaylist;
    char nombrePlaylist[30];
    int idUsr;
}playlist;

//detallesPlaylist.dat"
typedef struct{
    int idPlaylist;
    int idCancion;
}detallePlaylist;

int contarRegistrosUsuarios();

///PARA PROBAR CONTENIDOS DE LOS ARCHIVOS
void recorrerArchivoUsuarios();
void recorrerArchivoCanciones();
void recorrerArchivoPlaylist();


int contarRegistrosPlaylist();



#endif // ARCHIVO_H_INCLUDED
