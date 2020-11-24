#include "arbol.h"

nodoArbolCancion * inicArbol(){
    return NULL;
}

nodoArbolCancion * crearNodoArbol(stCancion dato){
    nodoArbolCancion * nuevo = (nodoArbolCancion*)malloc(sizeof(nodoArbolCancion));
    nuevo->c = dato;
    nuevo->izq = NULL;
    nuevo->der = NULL;
    return nuevo;
}

nodoArbolCancion * buscarCancion(nodoArbolCancion * arbol, int id){
    nodoArbolCancion * rta = NULL;
    if(arbol)
        if(arbol->c.idCancion == id)
            rta = arbol;
        else{
            if(arbol->c.idCancion > id)
                rta = buscarCancion(arbol->izq, id);
            else
                rta = buscarCancion(arbol->der, id);
        }
    return rta;
}

void mostrarCancion(stCancion C){
    printf("\n\t\t\t\t--------------------------------------------\n");
    printf("\t\t\t\t\tID              : %d\n",C.idCancion);
    printf("\t\t\t\t\tTitulo          : %s\n",C.titulo);
    printf("\t\t\t\t\tArtista         : %s\n",C.artista);
    printf("\t\t\t\t\tA%co Lanzamiento : %d\n",164,C.anio);
    printf("\t\t\t\t\tAlbum           : %s\n",C.album);
    printf("\t\t\t\t\tGenero          : %s\n",C.genero);
    printf("\t\t\t\t\tDuracion        : %d\n",C.duracion);
    printf("\t\t\t\t\tEliminado       : %d\n",C.eliminado);
    printf("\t\t\t\t\tComentarios     : %s\n",C.comentario);
    puts("\t\t\t\t--------------------------------------------");
}

void inOrder(nodoArbolCancion * arbol){
    if(arbol){
        inOrder(arbol->izq);
        mostrarCancion(arbol->c);
        inOrder(arbol->der);
    }
}

int contarNodosArbol(nodoArbolCancion * Ar){
    int cont = 0;
    if(Ar){
        cont = contarNodosArbol(Ar->izq) + contarNodosArbol(Ar->der) + 1;
    }
    return cont;
}

int alturaArbol(nodoArbolCancion * A){
    int alt = 0,altIzq, altDer;
    if(A){
        altIzq = contarNodosArbol(A->izq);
        altDer = contarNodosArbol(A->der);
        if(altIzq>altDer)
            alt = altIzq +1;
        else
            alt = altDer +1;

    }
    return alt;
}

int factorEquilibrio(nodoArbolCancion * A){
    int fE = 0, altIzq, altDer;
    if(A){
        altIzq = alturaArbol(A->izq);
        altDer = alturaArbol(A->der);
        fE = altDer - altIzq;
    }
    return fE;
}
///ROTA EL ARBOL A LA IZQUIERDA.
nodoArbolCancion * rotacionIzquierda(nodoArbolCancion * A){
    nodoArbolCancion * raiz = A;
    nodoArbolCancion * nDer = A->der;

    raiz->der = nDer->izq;
    nDer->izq = raiz;
    raiz = nDer;

    return raiz;
}
///ROTA EL ARBOL A LA DERECHA.
nodoArbolCancion * rotacionDerecha(nodoArbolCancion * A){
    nodoArbolCancion * raiz = A;
    nodoArbolCancion * nIzq = A->izq;

    raiz->izq = nIzq->der;
    nIzq->der = raiz;
    raiz = nIzq;

    return raiz;
}

nodoArbolCancion * insertBalanced(nodoArbolCancion * arbol, stCancion C){
    if(!arbol)
        arbol = crearNodoArbol(C);
    else{
        if(C.idCancion > arbol->c.idCancion)
            arbol->der = insertBalanced(arbol->der, C);
        else
            arbol->izq = insertBalanced(arbol->izq, C);
    }
    int Fe = factorEquilibrio(arbol);

    if(Fe > 1 && C.idCancion > arbol->c.idCancion)
        arbol = rotacionIzquierda(arbol);
    else if(Fe > 1 && C.idCancion < arbol->c.idCancion){
        arbol->der = rotacionDerecha(arbol->der);
        arbol = rotacionIzquierda(arbol);
    }else if(Fe < -1 && C.idCancion > arbol->c.idCancion)
        arbol = rotacionDerecha(arbol);
    else if(Fe < -1 && C.idCancion < arbol->c.idCancion){
        arbol->izq = rotacionIzquierda(arbol->izq);
        arbol = rotacionDerecha(arbol);
    }

    return arbol;
}

nodoArbolCancion * archivoToArbol(nodoArbolCancion * Arbol){

    FILE * archivo = fopen(archivoCanciones, "rb");
    if(archivo){
        stCancion C;
        while(fread(&C, sizeof(stCancion), 1, archivo))
            Arbol = insertBalanced(Arbol, C);
        fclose(archivo);
    }
    return Arbol;
}

nodoArbolCancion * borrarNodoArbol(nodoArbolCancion * arbol, int id){
    if(arbol){
        if(id == arbol->c.idCancion){
            if(arbol->izq){
                nodoArbolCancion * masDer = nodoMasD(arbol->izq);
                arbol->c = masDer->c;
                arbol->izq = borrarNodoArbol(arbol->izq, masDer->c.idCancion);
            }else if(arbol->der){
                nodoArbolCancion * masIzq = nodoMasI(arbol->der);
                arbol->c = masIzq->c;
                arbol->der = borrarNodoArbol(arbol->der,masIzq->c.idCancion);
            }else{
                free(arbol);
                arbol = NULL;
            }
        }else if(id > arbol->c.idCancion)
            arbol->der = borrarNodoArbol(arbol->der,id);
        else if(id < arbol->c.idCancion)
            arbol->izq = borrarNodoArbol(arbol->izq,id);
    }
    return arbol;
}

nodoArbolCancion * nodoMasD(nodoArbolCancion * A){
    nodoArbolCancion * aux;
    if(A->der)
        A->der = nodoMasD(A->der);
    else
        aux = A;

    return aux;
}

nodoArbolCancion * nodoMasI(nodoArbolCancion * A){
    nodoArbolCancion * aux;
    if(A->izq)
        A->izq = nodoMasI(A->izq);
    else
        aux = A;
    return aux;
}

nodoArbolCancion * altaCancionArbol(nodoArbolCancion * arbol){
    stCancion C;
    int opc;
    system("cls");
    imprimirCabecera("INGRESANDO NUEVA CANCION");
    gotoxy(35,4);printf("Titulo:                       : ");
    gotoxy(35,5);printf("Artista                       : ");
    gotoxy(35,6);printf("A%co lanzamiento del album     :",164);
    gotoxy(35,7);printf("Album                         : ");
    gotoxy(35,8);printf("Duracion de la cancion        : ");
    gotoxy(35,9);printf("Genero                        : ");
    gotoxy(35,10);printf("Comentario(100 caracteres MAX): ");

    C.idCancion = contarRegistrosCanciones() + 1;
    C.eliminado = 0;



    fflush(stdin);
    ///44
    gotoxy(67,4);gets(C.titulo);


    fflush(stdin);
    ///42
    gotoxy(67,5);gets(C.artista);

    ///62
    gotoxy(67,6);scanf("%d",&C.anio);


    fflush(stdin);
    ///44
    gotoxy(67,7);gets(C.album);



    ///59
    gotoxy(67,8);scanf("%d",&C.duracion);

    fflush(stdin);
    gotoxy(67,9);gets(C.genero);


    fflush(stdin);
    ///36
    gotoxy(36,11);gets(C.comentario);

    arbol = insertBalanced(arbol,C);

    system("cls");
    imprimirCabecera("NUEVA CANCION");
    mostrarCancion(C);
    getch();

    return arbol;
}


void guardarCancionesArchivo(nodoArbolCancion * arbol){ ///TIENE QUE ESTAR EN ARCHIVO
    FILE * archivo = fopen(archivoCanciones,"wb");
    if(archivo){
        fseek(archivo,0,SEEK_SET);
        guardarCancion(archivo,arbol);
        fclose(archivo);
    }
}

void guardarCancion(FILE * archivo,nodoArbolCancion * arbol){ ///TIENE QUE ESTAR EN ARCHIVO
    if(arbol){
        guardarCancion(archivo,arbol->izq);
        fwrite(&arbol->c,sizeof(stCancion),1,archivo);
        guardarCancion(archivo,arbol->der);
    }
}

/// Eliminar un usuario
void eliminarCancion(nodoArbolCancion * arbol){
    if(arbol){
        int id;
        char control;
        nodoArbolCancion * aux;
        system("cls");
        imprimirCabecera("ELIMINAR CANCION");
        printf("\n\n\n");
        mostrarCancionCorta(arbol);
        gotoxy(35,4);puts("ID CANCION A ELIMINAR: ");
        gotoxy(58,4);scanf("%d", &id);
        aux = buscarCancion(arbol,id); //LLamo a la funcion que busca una cancion en el arbol a través de su id y la retorna
        if(aux){
            system("cls");
            imprimirCabecera("ELIMINAR CANCION");
            mostrarCancion(aux->c);
            gotoxy(35,18);puts("Si desea eliminar la cancion presione ENTER");
            fflush(stdin);
            control = getch();

            if(control == 13){
                gotoxy(35,7);
                    if(aux->c.eliminado == 0){ //Pregunto la cancion ya no esté dada de baja
                        aux->c.eliminado = 1; //Doy de baja la cancion
                        gotoxy(35, 20);puts("LA CANCION HA SIDO ELIMINADA CORRECTAMENTE");
                    }
            }
            else{
                gotoxy(35, 20);puts("LA CANCION QUE DESEA ELIMINAR YA HA SIDO ELIMINADO ANTES");
            }
        }
        else{
            gotoxy(35, 5);printf("La cancion no existe");
        }
        getch();
    }
}

nodoArbolCancion * eliminarArbol(nodoArbolCancion * arbol){
    int contador = contarRegistrosCanciones();
    while(arbol){
        arbol = borrarNodoArbol(arbol,contador);
        contador--;
    }
    return arbol;
}

void mostrarCancionCorta(nodoArbolCancion * arbol){

    if(arbol){
        mostrarCancionCorta(arbol->izq);
        printf("\t\t\t\t\t%d -    %s \n", arbol->c.idCancion, arbol->c.titulo);
        mostrarCancionCorta(arbol->der);
    }
}
/*
void recomendarCanciones(nodoArbolCancion * arbol, nodoPlaylist * listaPlaylist, char genero[]){
    int i = 0, flag;
    while(i == 0){
        nodoArbolCancion * recomendada = buscarCancionPorGenero(arbol, genero); //busco una cancion de ese genero en el arbol
        if(recomendada){
            if(listaPlaylist){ //Si el usuario no tiene ninguna playlist, muestro la cancion recomendada directamente
                mostrarCancion(recomendada->c);
                i++;
            }
            else{ //si tiene playlist ...
                flag = buscarCancionEnUsr(listaPlaylist, recomendada); // Verifico que el usuario ya no tenga esa cancion en sus playlists
                if(flag != -1){
                    mostrarCancion(recomendada->c);
                    i++;
                }
                else{

                }
            }
        }
        else
            gotoxy(35, 8); printf("NO EXISTEN CANCIONES CON ESE GENERO");
    }
*/
