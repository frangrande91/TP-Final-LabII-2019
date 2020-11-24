#include "ADL.h"

/// IMPRIME UN TITULO
void imprimirCabecera(char cabecera[]){
    int i;
    gotoxy(30,0);printf("%c", 201);
    for(i=0; i<50; i++)
    {
        printf("%c",205);
    }
    printf("%c\n", 187);
    gotoxy(30,1);printf("%c%32s%19c\n", 186,cabecera,186);
    gotoxy(30,2);printf("%c", 200);
    for(i=0; i<50; i++)
    {
        printf("%c",205);
    }
    printf("%c", 188);
}

///FUNCIONES PARA PASAR DE ARCHIVO AL ADL
void archivosToADL(stCelda ADL[],int validos, nodoArbolCancion * arbol){

    usuariosToADL(ADL);
    //detallesPlaylistToADL(ADL,validos,arbol);
    playlistToADL(ADL, validos);
    detallesToADL(ADL, validos, arbol);
}

void usuariosToADL(stCelda ADL[]){
    FILE * archivo = fopen(archivoUsuarios,"rb");
    if(archivo){
        stUsuario aux;
        int i = 0;
        while(fread(&aux,sizeof(stUsuario),1,archivo)){
            ADL[i].usr = aux;
            ADL[i].listaPlaylist = inicListaPlaylist(); //inicializo la lista de playlist de cada usuario
            i++;
        }
        fclose(archivo);
    }
}

void playlistToADL(stCelda ADL[],int validos){
    FILE * archi = fopen(archivoPlaylist, "rb");
    if(archi){
        playlist aux;
        while(fread(&aux, sizeof(playlist), 1, archi)){
            int pos = buscarUsrEnADL(ADL,validos,aux.idUsr);
            nodoPlaylist * nuevo = crearNodoPlaylist(aux);
            ADL[pos].listaPlaylist = agregarFinalPlaylist(ADL[pos].listaPlaylist,nuevo);
        }
        fclose(archi);
    }
}

void detallesToADL(stCelda ADL[],int validos,nodoArbolCancion * arbol){
    int pos = 0, flag = 0;
    FILE * archi = fopen(archivoDetalle, "rb");
    if(archi){
        detallePlaylist auxDetalle;
        while(fread(&auxDetalle,sizeof(detallePlaylist),1,archi) && pos<validos){ // Leo en auxDetalle el registro del archivo
            nodoPlaylist * aux;
            while(flag == 0){
                aux = buscarPlaylist(ADL[pos].listaPlaylist, auxDetalle.idPlaylist); //Busco la playlist a partir del ID playlist del registro
                ///printf("%d", aux->play.idPlaylist); ///SI MUESTRO SE ROMPE ?¿?¿??¿?¿?¿?¿?¿
                if(aux) // Si la encuentro salgo del while
                    flag = 1;
                else    //Si no la encuentro, avanzo a la lista de playlist del segundo usuario
                    pos++;
            }
            nodoArbolCancion * auxArbol = buscarCancion(arbol,auxDetalle.idCancion); //Busco en el arbol la cancion a agregar
            nodoListaCancion * NuevaC = crearNodo(auxArbol->c);      // Creo el nodo con los datos de esa cancion
            aux->listaCanciones = agregarFinal(aux->listaCanciones, NuevaC); //Agrego la cancion en la lista de canciones de la playlist encontrada
            pos = 0; //Vuelvo a inicializar pos en 0 para que en la 2da vuelta empiece a buscar la playlist desde el primer usuario nuevamente.
        }
    fclose(archi);
    }
}
/*
void detallesPlaylistToADL(stCelda ADL[],int validos,nodoArbolCancion * arbol){
    FILE * archivoP = fopen(archivoPlaylist,"rb");
    FILE * archivoD = fopen(archivoDetalle,"rb");
    if(archivoP && archivoD){
        int i = 0;
        while(i<validos){
            playlist auxPlaylist;
            while(fread(&auxPlaylist,sizeof(playlist),1,archivoP)){
                if(ADL[i].usr.idUsuario == auxPlaylist.idUsr){
                    nodoPlaylist * Nuevo = crearNodoPlaylist(auxPlaylist);
                    ADL[i].listaPlaylist = agregarFinalPlaylist(ADL[i].listaPlaylist, Nuevo);

                    detallePlaylist auxDetalle;
                    while(fread(&auxDetalle,sizeof(detallePlaylist),1,archivoD)){
                        if(auxPlaylist.idPlaylist == auxDetalle.idPlaylist){
                            nodoArbolCancion * auxArbol = buscarCancion(arbol,auxDetalle.idCancion);
                            nodoListaCancion * NuevaC = crearNodo(auxArbol->c);
                            nodoPlaylist * auxSeg = ADL[i].listaPlaylist;
                            auxSeg->listaCanciones = agregarFinal(auxSeg->listaCanciones, NuevaC);
                        }
                    }
                }
            }
            fseek(archivoD,0,SEEK_SET);
            fseek(archivoP,0,SEEK_SET);

            i++;

        }
        fclose(archivoD);
        fclose(archivoP);
    }
}
*/

/// MANEJAR IMPRESIONES EN LA CONSOLA
void gotoxy(int X,int Y){
    HANDLE hand;
    COORD cordenada;
    hand = GetStdHandle(STD_OUTPUT_HANDLE);
    cordenada.X = X;
    cordenada.Y = Y;
    SetConsoleCursorPosition(hand,cordenada);
}

void ingresarContrasenia(char C[]){ //Funcion para esconder la contraseña con asteriscos
    int flag = 0,j = 0,dim = 30;
    char carac;
    while(!flag){
        carac = getch();
        if(carac == 13){
            C[j] = '\0';
            flag = !flag;
        }else if(carac == 8){
            if(j>0){
                j--;
                printf("\b \b");
            }
        }else if(j<dim){
            printf("*");
            C[j] = carac;
            j++;
        }
    }
}

void agregarUsuario(stCelda ADL[], int **validos){ //Recibe el adl y los validos
    system("cls");
    imprimirCabecera("REGISTRARSE");
    ADL[**validos].usr = cargarUsuario(ADL,**validos);//modularizo cargar un usuario
    **validos = ** validos + 1;
    system("cls");
    imprimirCabecera("USUARIO REGISTRADO CORRECTAMENTE");
    mostrarUsr(ADL[**validos-1].usr, 4); //muestro el usuario registrado
    getch();
}

stUsuario cargarUsuario(stCelda ADL[],int validos){
    int flag, flag2 = 0;
    char pass[30];
    stUsuario New;
    New.eliminado = 0;

    New.idUsuario = validos + 1;
    gotoxy(35,4);printf("NOMBRE USUARIO: ");
    gotoxy(35,5);printf("CONTRASE%cA: ",165);
    gotoxy(35,6);printf("INGRESE NUEVAMENTE LA CONTRASE%cA: ",165);
    gotoxy(35,7);printf("PAIS DE RESIDENCIA: ");
    gotoxy(35,8);puts("GENERO: ");
    gotoxy(35,9);puts("(m: masculino;   f: femenino;   o: otro)");
    gotoxy(35,10);printf("A%cO DE NACIMIENTO: ",165);

    do{
        fflush(stdin);
        gotoxy(51,4);gets(New.nombreUsuario);
        flag = validarExistenciaUsuario(ADL,New.nombreUsuario,validos);
        if(flag){
            gotoxy(35,15);printf("El nombre con ese usuario ya existe..");
            gotoxy(35,16);printf("Ingrese nuevamente");
            Sleep(2500);
        }
    }while(flag);

   do{
        fflush(stdin);
        gotoxy(47,5);ingresarContrasenia(New.pass);

        fflush(stdin);
        gotoxy(69,6);ingresarContrasenia(pass);
        if(strcmp(New.pass,pass) == 0)
            flag2 = 1;
        else
            printf("\t\nLAS CONTRASE%cAS NO COINCIDEN.. INGRESE NUEVAMENTE\n",165);
    } while(flag2 == 0);

    fflush(stdin);
    gotoxy(55,7);gets(New.pais);

    do{
        fflush(stdin);
        gotoxy(43,8);scanf("%c", &New.genero);
    }while((New.genero!='m') && (New.genero!='f') && (New.genero!='o'));

    do{
        gotoxy(54,10);scanf("%d",&New.anioNacimiento);
    }while(New.anioNacimiento<1910 || New.anioNacimiento>2016);

    return New;
}

int validarExistenciaUsuario(stCelda Celda[],char NombreUsuario[],int V){ //valida que el nombre de usuario elegido no exista,
                                              //si ya existe vuelve a preguntar hasta que se elija uno que no exista
    int i = 0, flag = 0;
    while((i < V) && (!flag)){
        if(!strcmp(Celda[i].usr.nombreUsuario,NombreUsuario))
            flag = !flag;
        i++;
    }
    return flag;
}


int validarAnioIngresado(){
    int anio;
    printf("A%cO DE NACIMIENTO: ",165);
    scanf("%d",&anio);
    while(anio<1910 || anio>2016){
        printf("\tEL A%cO INGRESADO ES INCORRECTO.. INGRESE NUEVAMENTE\n", 165);
        printf("A%cO DE NACIMIENTO: ",165);
        scanf("%d",&anio);
    }
    return anio;
}

/// MOSTRAR USUARIOS
void recorrerYmostrarUsrADL(stCelda A[],int validos, int gotox){
    char opc = 13;
    int i = 0;
    while(i<validos && opc == 13){
        system("cls");
        imprimirCabecera("LISTADO USUARIOS");
        mostrarUsr(A[i].usr, 4);
        gotoxy(35, 12); printf("%d usuario vistos de %d", i+1, validos);
        gotoxy(35, 13); printf("presione ENTER para ver otro usuario");
        i++;
        opc = getch();
    }
}

void mostrarUsr(stUsuario U, int gotox){
    gotoxy(35, gotox);printf("-------------------------------------");
    gotoxy(35, gotox+1);printf("ID             : %d\n",U.idUsuario);
    gotoxy(35, gotox+2);printf("NOMBRE USER    : %s\n",U.nombreUsuario);
    gotoxy(35, gotox+3);printf("A%cO NACIMIENTO : %d\n",165,U.anioNacimiento);
    gotoxy(35, gotox+4);printf("GENERO         : %c\n",U.genero);
    gotoxy(35, gotox+5);printf("PAIS RESIDENCIA: %s\n",U.pais);
    gotoxy(35, gotox+6);printf("ELIMINADO      : %d\n",U.eliminado);
    gotoxy(35, gotox+7);puts("-------------------------------------");

}

void eliminarUsr(stCelda ADL[], int validos){
    imprimirCabecera("ELIMINAR USUARIO");
    int id, pos;
    char control;
    gotoxy(35, 5);puts("INGRESE LA ID DEL USUARIO QUE DESEA ELIMINAR");
    gotoxy(35, 6);scanf("%d", &id);
    pos = buscarUsrEnADL(ADL, validos, id); //LLamo a la funcion que busca un usuario en el ADL a través de su id y me retorna la posicion
    mostrarUsr(ADL[pos].usr, 7);
    gotoxy(35, 16);puts("Presione ENTER si desea eliminar el usuario");
    fflush(stdin);
    gotoxy(35, 17);control = getch();
    if(control == 13){
        if(ADL[pos].usr.eliminado == 0){ //Pregunto que el usuario ya no esté dado de baja
            ADL[pos].usr.eliminado = 1; //Doy de baja el usuario
            mostrarUsr(ADL[pos].usr, 7);
            gotoxy(35, 18);puts("EL USUARIO HA SIDO ELIMINADO CORRECTAMENTE");
            getch();
        }
        else
            gotoxy(35, 7);puts("EL USUARIO QUE DESEA ELIMINAR YA HA SIDO ELIMINADO ANTES");
    }
}

int buscarUsrEnADL(stCelda ADL[], int validos, int id){
   int i = 0, pos = -1;
   while(i < validos && pos < 0){
        if(ADL[i].usr.idUsuario == id)
            pos = i;
        i++;
   }
   return pos; //retorno la pos del usuario en el ADL o -1 si no
}


/// MODIFICAR USUARIO
void modificarNombreUsuario(int pos, stCelda ADL[],int validos){
    system("cls");
    imprimirCabecera("MODIFICAR NOMBRE");
    if(!ADL[pos].usr.eliminado){
        gotoxy(35, 5);printf("NOMBRE USUARIO ACTUAL          : %s",ADL[pos].usr.nombreUsuario);
        gotoxy(35, 6);printf("INGRESE NUEVO NOMBRE DE USUARIO: ");
        fflush(stdin);
        gets(ADL[pos].usr.nombreUsuario);
    }else{
        gotoxy(35, 16);printf("EL USUARIO NO SE ENCUENTRA ACTIVO, NO SE PUEDE MOFDIFICAR");
    }
    mostrarUsr(ADL[pos].usr, 7);
    getch();
}

void modificarPassUsuario(int pos,stCelda ADL[],int validos){
    if(!ADL[pos].usr.eliminado){
        char pass[30];
        int flag = 0;
        do{
            system("cls");
            imprimirCabecera("MODIFICAR PASSWORD");
            gotoxy(35, 4);printf("CONTRASE%cA NUEVA: ",165);
            fflush(stdin);
            ingresarContrasenia(ADL[pos].usr.pass);
            gotoxy(35, 5);printf("INGRESE NUEVAMENTE LA CONTRASE%cA: ",165);
            fflush(stdin);
            ingresarContrasenia(pass);
            if(!strcmp(ADL[pos].usr.pass, pass)){
                flag = 1;
                gotoxy(35, 7); printf("CONTRASE%cA MODIFICADA",165);
            }
            else{
                gotoxy(35, 7);printf("LAS CONTRASE%cAS NO COINCIDEN.. INGRESE NUEVAMENTE\n",165);
            }
            Sleep(2500);
        } while(!flag);
    }else{
        printf("EL USUARIO NO SE ENCUENTRA ACTIVO");
        getch();
    }
}

int buscarUsrPorNombre(stCelda ADL[], int validos, char nombreUsr[]){
   int i = 0, pos = -1;
   while(i < validos && pos < 0){
        if(strcmp(ADL[i].usr.nombreUsuario, nombreUsr) == 0)
            pos = i;
        i++;
   }
   return pos; //retorno la pos del usuario en el ADL o -1 si no existe
}


/// VALIDAR INGRESO DEL USUARIO AL SISTEMA
int validarIngresoUsuario(stCelda ADL[], int validos){
    int flag = 0;
    int pos;
    char nombreUsr[30], pass[30];
    while(flag == 0){ //lo hago en un while usando un flag para poder retornar la posicion del usuario en el ADL
        system("cls");
        imprimirCabecera("INGRESANDO AL SISTEMA");
        gotoxy(35,5);puts("NOMBRE DE USUARIO: ");
        gotoxy(35,6);puts("PASSWORD         : ");
        fflush(stdin);
        gotoxy(54,5);gets(nombreUsr);

        pos = buscarUsrPorNombre(ADL, validos, nombreUsr); //busco la posicion del usuario
        if(pos == -1){
        gotoxy(35,8);printf("El usuario no existe");
        Sleep(1500);
        }
        else{
            gotoxy(54,6);ingresarContrasenia(pass);
            if(strcmp(ADL[pos].usr.pass, pass) == 0){
                gotoxy(35,8);printf("INGRESANDO AL SISTEMA");
                printf(".");Sleep(500);
                printf(".");Sleep(1000);
                printf(".");Sleep(1500);
                flag = 1;
            }
            else{
                gotoxy(35,8);printf("Password incorrecto");
                Sleep(1500);
            }
        }
    }
    return pos; //retorno la posicion del usuario en el ADL;
}

void usuariosToArchivo(stCelda ADL[], int validos){
    FILE * archivo = fopen(archivoUsuarios,"wb");
    if(archivo){
        int i = 0;
        while(i < validos){
            fwrite(&ADL[i].usr,sizeof(stUsuario),1,archivo);
            i++;
        }
        fclose(archivo);
    }
}

void playlistToArchivo(stCelda ADL[], int validos){
    FILE * archivoP = fopen(archivoPlaylist,"wb");
    FILE * archivoD = fopen(archivoDetalle,"wb");
    if(archivoP && archivoD){
        int i = 0;
        while(i < validos){
            if(ADL[i].listaPlaylist)
                usrPlaylistToarchivo(ADL[i].listaPlaylist,archivoP,archivoD);
            i++;
        }
        fclose(archivoD);
        fclose(archivoP);
    }
}

void usrPlaylistToarchivo(nodoPlaylist * Lista,FILE * archivoP,FILE * archivoD){
    playlist P;
    nodoPlaylist * seg = Lista;
    while(seg){
        P = seg->play;
        fwrite(&P,sizeof(playlist),1,archivoP);
        if(seg->listaCanciones)
            usrDetalleCancionPlaylistToArchivo(seg,archivoD);
        seg = seg->sig;
    }
}

void usrDetalleCancionPlaylistToArchivo(nodoPlaylist * Lista,FILE * archivoD){
    detallePlaylist D;
    nodoListaCancion * seg = Lista->listaCanciones;
    while(seg){
        D.idPlaylist = Lista->play.idPlaylist;
        D.idCancion = seg->c.idCancion;
        fwrite(&D,sizeof(detallePlaylist),1,archivoD);
        seg = seg->sig;
    }
}

