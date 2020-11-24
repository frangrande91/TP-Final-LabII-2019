#include "archivo.h"

///FUNCIONES PARA CONTAR LOS REGISTROS DE LOS ARCHIVOS
int contarRegistrosUsuarios(){
    FILE * archivo = fopen("usuarios.dat","rb");
    int total = 0;
    if(archivo){
        fseek(archivo,0,SEEK_END);
        total = ftell(archivo) / sizeof(stUsuario);
        fclose(archivo);
    }
    return total;
}

int contarRegistrosCanciones(){
    FILE * archivo = fopen(archivoCanciones,"rb");
    int total = 0;
    if(archivo){
        fseek(archivo,0,SEEK_END);
        total = ftell(archivo) / sizeof(stCancion);
    }
    return total;
}

int contarRegistrosPlaylist(){
    FILE * archivo = fopen(archivoPlaylist,"rb");
    int total = 0;
    if(archivo){
        fseek(archivo,0,SEEK_END);
        total = ftell(archivo) / sizeof(playlist);
    }
    return total;
}

///FUNCIONES PARA PROBAR LAS CARGAS EN LOS ARCHIVOS
void recorrerArchivoUsuarios(){
    FILE * archivo = fopen(archivoUsuarios,"rb");
    if(archivo){
        stUsuario U;
        while(fread(&U,sizeof(stUsuario),1,archivo))
            mostrarUsr(U,5);
        fclose(archivo);
    }
}

void recorrerArchivoPlaylist(){
    FILE * archivo = fopen(archivoPlaylist,"rb");
    if(archivo){
        playlist P;
        while(fread(&P,sizeof(playlist),1,archivo)){
            printf("IDP   : %d\n",P.idPlaylist);
            printf("IDUSR : %d\n",P.idUsr);
            printf("NOMBRE: %s\n",P.nombrePlaylist);
        }
        fclose(archivo);
    }
}

void recorrerArchivoCanciones(){
    FILE * archivo = fopen(archivoCanciones,"rb");
    if(archivo){
        stCancion C;
        while(fread(&C,sizeof(stCancion),1,archivo))
            mostrarCancion(C);
        fclose(archivo);
    }
}

void recorrerArchivoDetallesPlaylist(){
    FILE * archivo = fopen(archivoDetalle,"rb");
    if(archivo){
        detallePlaylist dp;
        while(fread(&dp,sizeof(detallePlaylist),1,archivo)){
            printf("IDP        : %d\n",dp.idPlaylist);
            printf("IDUCANCION : %d\n",dp.idCancion);
        }
        fclose(archivo);
    }
}
