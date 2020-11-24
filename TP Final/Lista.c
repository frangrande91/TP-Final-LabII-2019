#include "Lista.h"

/*********************************** FUNCIONES DE LA LISTA DE CANCIONES ***************************************/
nodoListaCancion * inicLista(){
    return NULL;
}

nodoListaCancion * crearNodo(stCancion dato){
    nodoListaCancion * nuevo = (nodoListaCancion*)malloc(sizeof(nodoListaCancion));
    nuevo->c = dato;
    nuevo->sig = NULL;
    return nuevo;
}

nodoListaCancion * agregarPPio(nodoListaCancion * Lista, nodoListaCancion * Nuevo){
   Nuevo->sig = Lista;
   Lista = Nuevo;
   return Lista;
}

nodoListaCancion * buscarUltimo(nodoListaCancion * Lista){
    nodoListaCancion * seg = Lista;
    while(seg->sig)
         seg = seg->sig;
    return seg;
}

nodoListaCancion * agregarFinal(nodoListaCancion * Lista, nodoListaCancion * Nuevo){
    if(!Lista)
        Lista = Nuevo;
    else{
        nodoListaCancion * seg = buscarUltimo(Lista);
        seg->sig = Nuevo;
    }
    return Lista;
}

nodoListaCancion * agregarEnOrden(nodoListaCancion * Lista, nodoListaCancion * Nuevo){
    if(!Lista)
        Lista = Nuevo;
    else{
        if(Nuevo->c.idCancion>Lista->c.idCancion)
            Lista = agregarPPio(Lista,Nuevo);
        else{
            nodoListaCancion * ante;
            nodoListaCancion * seg;
            ante = Lista;
            seg = Lista->sig;
            while(seg && strcmp(Nuevo->c.titulo,seg->c.titulo)){
                ante=seg;
                seg = seg->sig;
            }
            ante->sig = Nuevo;
            Nuevo->sig = seg;
        }
    }
    return Lista;
}


nodoListaCancion * borrarUnNodo(nodoListaCancion * Lista, int ID){
    nodoListaCancion * seg;
    nodoListaCancion * ante;
    if(Lista && Lista->c.idCancion==ID){
        nodoListaCancion * aBorrar = Lista;
        Lista = Lista->sig;
        free(aBorrar);
    }else{
        seg = Lista;
        while(seg && seg->c.idCancion!=ID){
            ante = seg;
            seg = seg->sig;
        }
        if(seg){
            ante->sig = seg->sig;
            free(seg);
        }
    }
    return Lista;
}



nodoListaCancion * agregarCancionAplaylist(nodoArbolCancion * arbol, nodoListaCancion * Lista){
    int id;
    system("cls");
    imprimirCabecera("AGREGAR CANCIONES");
    printf("\n\n\n\n");
    mostrarCancionCorta(arbol);
    gotoxy(35, 4);printf("INGRESE ID DE LA CANCION QUE DESEA AGREGAR: ");
    gotoxy(80, 4);scanf("%d",&id);
    nodoArbolCancion * aux = buscarCancion(arbol, id); // si no lo encuentra retorna NULL, por lo contrario retorna datos.
    if(aux){
        Lista = agregarFinal(Lista, aux); //si la cancion ya se enceuntra en la playlist la agregar igual por si quiere agregar la misma cancion varias veces
        gotoxy(35, 5);printf("CANCION CARGADA CORRECTAMENTE");
    }
    else{
        gotoxy(35, 6);puts("LA CANCION BUSCADA NO SE ENCUENTRA EN EL PROGRAMA.");
    }
    getch();
    return Lista;
}

nodoListaCancion * borrarCancionEnPlaylist(nodoListaCancion * Lista){
    int id;
    system("cls");
    imprimirCabecera("BORRAR CANCION DE PLAYLIST");
    if(Lista){
        recorrerYmostrarListaCanciones(Lista, 4);
        printf("INGRESE EL ID DE LA CANCION QUE DESEA BORRAR DE LA PLAYLIST: ");
        scanf("%d",&id);
        nodoListaCancion * aux = buscarCancionEnPlaylist(Lista, id);
        if(aux){ // si la cancion se encuentra en la playlist..
            Lista = borrarUnNodo(Lista, id); //la borro
            puts("CANCION BORRADA");
        }
        else
            printf("LA CANCION NO SE ENCUENTRA EN LA PLAYLIST");
    }
    else{
        gotoxy(35, 5);printf("LA PLAYLIST NO TIENE CANCIONES");
    }
    getch();

    return Lista;
}

nodoListaCancion * borrarTodaLaLista(nodoListaCancion * lista){
    nodoListaCancion * proximo;
    nodoListaCancion * seg = lista;
    while(seg){
            proximo = seg->sig;
            free(seg);
            seg = proximo;
    }
    return seg;
}

void recorrerYmostrarListaCanciones(nodoListaCancion * lista, int gotox){
    while(lista){
        mostrarCancion(lista->c);
        lista = lista->sig;
        gotox += 11;
    }
}

/*********************************** FUNCIONES DE LA LISTA DE PLAYLIST ***************************************/
nodoPlaylist * inicListaPlaylist(){
    return NULL;
}


nodoPlaylist * crearNodoPlaylist(playlist dato){
    nodoPlaylist * nuevo = (nodoPlaylist*)malloc(sizeof(nodoPlaylist));
    nuevo->play = dato;
    nuevo->listaCanciones = inicLista();
    nuevo->sig = NULL;
    return nuevo;
}

nodoPlaylist * agregarFinalPlaylist(nodoPlaylist * Lista, nodoPlaylist * Nuevo){
    if(!Lista)
        Lista = Nuevo;
    else{
        nodoPlaylist * seg = buscarUltimoPlaylist(Lista);
        seg->sig = Nuevo;
    }
    return Lista;
}

nodoPlaylist * buscarUltimoPlaylist(nodoPlaylist * Lista){
    nodoPlaylist * seg = Lista;
    while(seg->sig)
         seg = seg->sig;
    return seg;
}

nodoPlaylist * buscarPlaylist(nodoPlaylist * listaPlay, int id){
    nodoPlaylist * seg = listaPlay;
    nodoPlaylist * rta = NULL;
    while(seg && !rta){
        if(seg->play.idPlaylist == id)
            rta = seg;
        seg = seg->sig;
    }
    return rta;
}

nodoPlaylist * modificarNombrePlaylist(nodoPlaylist * play){
    system("cls");
    imprimirCabecera("MODIFICAR NOMBRE PLAYLIST");
    gotoxy(35, 5);printf("Nombre actual: %s", play->play.nombrePlaylist);
    gotoxy(35, 6);printf("Ingrese el nuevo nombre de la playlist: ");
    fflush(stdin);
    scanf("%s", &play->play.nombrePlaylist);
    gotoxy(35, 8);printf("NOMBRE MODIFICADO CORRECTAMENTE");
    getch();
    return play;
}

void recorrerYmostrarListasPlaylist(nodoPlaylist * Lista){
    int i = 8;
    system("cls");
    imprimirCabecera("LISTA DE PLAYLIST");
    gotoxy(35,6);printf("ID    NOMBRE PLAYLIST");
    while(Lista){
        mostrarPlay(Lista->play, i);
        i++;
        Lista = Lista->sig;
    }
}

void mostrarPlay(playlist Play, int i){

    gotoxy(35, i);printf("%d     %s",Play.idPlaylist,Play.nombrePlaylist);
}


nodoPlaylist * crearPlaylist(nodoPlaylist * Lista,stUsuario Usr){
    playlist P;
    system("cls");
    imprimirCabecera("CREAR PLAYLIST");
    P.idUsr = Usr.idUsuario;
    P.idPlaylist = 1 + contarRegistrosPlaylist();
    gotoxy(35,4);printf("Nombre playlist: ");
    fflush(stdin);
    gotoxy(52,4);gets(P.nombrePlaylist);
    nodoPlaylist * Nuevo = crearNodoPlaylist(P);
    Lista = agregarFinalPlaylist(Lista,Nuevo);
    gotoxy(35, 6);printf("PLAYLIS CREADA CORRECTAMENTE");
    getch();
    return Lista;
}

void listaPlaylistToArchivo(nodoPlaylist * Lista){
    FILE * archivo = fopen(archivoPlaylist,"wb");
    if(archivo){
        playlist P;
        nodoPlaylist * seg = Lista;
        while(seg){
            P = seg->play;
            fwrite(&P,sizeof(playlist),1,archivo);
            seg = seg->sig;
        }
        fclose(archivo);
    }
}

void cancionesToArchivoDetalles(nodoPlaylist * Lista){
    FILE * archivo = fopen(archivoDetalle,"wb");
    if(archivo){
        detallePlaylist D;
        nodoListaCancion * seg = Lista->listaCanciones;
        while(seg){
            D.idPlaylist = Lista->play.idPlaylist;
            D.idCancion = seg->c.idCancion;
            fwrite(&D,sizeof(detallePlaylist),1,archivo);
            seg = seg->sig;
        }
        fclose(archivo);
    }
}

nodoPlaylist * elegirPlaylist(nodoPlaylist * Lista){
    nodoPlaylist * aux;
    int idPlay;
    imprimirCabecera("PLAYLISTS DEL USUARIO");
    recorrerYmostrarListasPlaylist(Lista);
    gotoxy(35, 4);printf("Ingrese ID de la playlist: ");
    scanf("%d",&idPlay);
    aux = buscarPlaylist(Lista, idPlay);
    return aux;
}

nodoPlaylist * borrarPlaylist(nodoPlaylist * listaPlaylist, int idPlaylist){
    nodoPlaylist * seg;
    nodoPlaylist * ante;
    if(listaPlaylist && listaPlaylist->play.idPlaylist == idPlaylist){
        nodoPlaylist * aBorrar = listaPlaylist;
        free(aBorrar);
        listaPlaylist = listaPlaylist->sig;
    }
    else{
        seg = listaPlaylist;
        while(seg && seg->play.idPlaylist != idPlaylist){
                ante = seg;
                seg = seg->sig;
        }
    }
        if(seg){
            ante->sig = seg->sig;
            free(seg);
        }
    return listaPlaylist;
}

void recomendarCancion(nodoArbolCancion * arbol, nodoListaCancion * Lista){
    nodoListaCancion * seg;
    srand(time(NULL));
    int random,cont = 1;
    while(cont < 4){
        seg = Lista;
        while(seg){
            random = 1+rand()%contarRegistrosCanciones();
            nodoArbolCancion * aux = arbol;
            aux = buscarCancion(arbol,random);
            if(random != Lista->c.idCancion && !strcmpi(aux->c.genero,Lista->c.genero)){
                mostrarCancionCorta(aux);
                cont++;
            }
            seg = seg->sig;
        }
    }
    getch();
}

nodoListaCancion * buscarCancionEnPlaylist(nodoListaCancion * lista, int idCancion)
{
    nodoListaCancion *rta = NULL;
    nodoListaCancion * seg = lista;

    while ((seg) && (seg->c.idCancion != idCancion))
        seg = seg->sig;

    return seg; //Si no lo encuentra retorna NULL
}
