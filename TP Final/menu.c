#include "menu.h"


///Variables constantes pora ingresar como administrador
const char nombreAdministrador[] = {"CachaMate"};
const char passAdministrador[] = {"123"};


/// TOMA ELECCION ELEGIDA POR EL USUARIO
int ingresarOpcion(){
    int opcion;
    gotoxy(33,13);printf("Ingrese opcion: ");
    fflush(stdin);
    gotoxy(49,13);scanf("%d",&opcion);
    return opcion;
}

/// MENU DE MENUS
void iniciarMenu(){
    int opc, validos;

    do{
        nodoArbolCancion * arbol = inicArbol();
        arbol = archivoToArbol(arbol);
        validos = contarRegistrosUsuarios();
        stCelda * ADL = (stCelda*)malloc(sizeof(stCelda)*(validos+1));
        archivosToADL(ADL, validos, arbol);
        system("cls");
        imprimirMenuPrincipal();
        opc = ingresarOpcion();
        switchMenuPrincipal(opc, ADL, &validos, arbol);
    }while(opc);
}

void imprimirMenuPrincipal(){
    imprimirCabecera("SPOTIFY UTN");
    gotoxy(35,4);puts("1. Ingresar como administrador.");
    gotoxy(35,5);puts("2. Ingresar como usuario");
    gotoxy(35,6);puts("3. Registrarse");
    gotoxy(35,7);puts("0. Salir");
}

void switchMenuPrincipal(int opc, stCelda ADL[], int *validos, nodoArbolCancion * arbol){
    int flag, posUsr;
    switch(opc){
        case 0:
            system("cls");
            imprimirCabecera("SALIR DEL SISTEMA");
            gotoxy(35,6);printf("SALIENDO DEL SISTEMA");
            printf(".");Sleep(500);
            printf(".");Sleep(1000);
            printf(".");Sleep(1500);
            break;
        case 1:
            flag = validarIngresoAdministrador();
            if(flag)
                menuAdministrador(ADL,*validos,arbol);
            break;
        case 2:
            posUsr = validarIngresoUsuario(ADL, *validos);
            if(posUsr != -1)
                menuUsuario(ADL, *validos, posUsr, arbol);
            break;
        case 3:
            agregarUsuario(ADL, &validos);
            gotoxy(35, 15); printf("BIENVENIDO A SPOTIFY UTN");
            getch();
            usuariosToArchivo(ADL, *validos);
            break;
        case 4:
            ///PARA PROBAR
            /*system("cls");
            recorrerArchivoUsuarios();

            printf("termino archivo usuarioos");
            getch();
            system("cls");
            recorrerArchivoCanciones();
            printf("termino archivo Cancions");
            getch();*/
            system("cls");
            recorrerArchivoPlaylist();
            printf("termino archivo play");
            getch();
            system("cls");
            recorrerArchivoDetallesPlaylist();
            printf("termino archivo Detalles");
            getch();
            break;
        default:
            gotoxy(35, 14);puts("La opcion ingresada es incorrecta.");
            getch();
        }
}
/********************************** ENTRANDO COMO ADMINISTRADOR **************************************/

/// VALIDAR INGRESO DEL ADMINISTRADOR AL SISTEMA
int validarIngresoAdministrador(){
    int flag = 0;
    char nombreUsr[30],pass[30];
    system("cls");
    imprimirCabecera("INGRESANDO AL SISTEMA");
    gotoxy(35,5);puts("NOMBRE DE USUARIO: ");
    gotoxy(35,6);puts("PASSWORD         : ");
    fflush(stdin);
    gotoxy(54,5);gets(nombreUsr);
    gotoxy(54,6);ingresarContrasenia(pass);

    if(!strcmp(nombreUsr,nombreAdministrador) && !strcmp(pass,passAdministrador)){
        flag = !flag;
        gotoxy(35,8);printf("INGRESANDO AL SISTEMA");
        printf(".");Sleep(500);
        printf(".");Sleep(1000);
        printf(".");Sleep(1500);
    }else{
        gotoxy(35,7);printf("Nombre y/o contrase%ca incorrectos.",164);
        Sleep(1500);
    }

    return flag;
}

/// INGRESAMOS AL MENU DE ADMINISTRADOR
void menuAdministrador(stCelda ADL[],int validos,nodoArbolCancion * arbol){
    int opc;

    do{
        system("cls");
        imprimirOpcAdministrador();
        opc = ingresarOpcion();
        arbol = switchMenuAdministrador(opc, ADL, validos, arbol);
    }while(opc);
}

/// IMPRIME OPCIONES DEL MENU ADMINISTRADOR.
void imprimirOpcAdministrador(){
    imprimirCabecera("MENU ADMINISTRADOR");
    gotoxy(35,4);puts("1. Administrar usuarios");
    gotoxy(35,5);puts("2. Administrar canciones");
    gotoxy(35,6);puts("0. Salir del modo administrador");
}

/// SWITCH DEL MENU DE ADMINISTRADOR
nodoArbolCancion * switchMenuAdministrador(int opc, stCelda ADL[], int validos, nodoArbolCancion * arbol){
        switch(opc){
            case 0:
                system("cls");
                imprimirCabecera("CERRAR SESION ADMINISTRADOR");
                gotoxy(35,6);printf("SALIENDO DEL MODO ADMINISTRADOR");
                printf(".");Sleep(500);
                printf(".");Sleep(1000);
                printf(".");Sleep(1500);
                break;
            case 1:
                menuAdministrarUsuarios(ADL,validos,arbol);
                break;
            case 2:
                arbol = menuAdministrarCanciones(arbol);
                break;
            default:
            gotoxy(35, 14);puts("La opcion ingresada es incorrecta.");
            getch();
        }
        return arbol;
}

void menuAdministrarUsuarios(stCelda ADL[],int validos,nodoArbolCancion * arbol){
    int opc ;
    do{
        system("cls");
        imprimirMenuAdministrarUsuarios();
        opc = ingresarOpcion();
        switchMenuAdministrarUsuarios(opc, &validos, ADL, arbol);
    }while(opc);
}

void imprimirMenuAdministrarUsuarios(){
    imprimirCabecera("ADMINISTRAR USUARIOS");
    gotoxy(35,4);puts("1. Alta");
    gotoxy(35,5);puts("2. Baja");
    gotoxy(35,6);puts("3. Modificacion");
    gotoxy(35,7);puts("4. Consulta");
    gotoxy(35,8);puts("5. Listados");
    gotoxy(35,9);puts("0. Volver al menu anterior");
}

void switchMenuAdministrarUsuarios(int opc, int * validos, stCelda ADL[],nodoArbolCancion * arbol){
    int id, pos;
    switch(opc){
        case 0:
            break;
        case 1:
            agregarUsuario(ADL,&validos);
            break;
        case 2:
            system("cls");
            eliminarUsr(ADL, *validos);
            break;
        case 3:
            system("cls");
            imprimirCabecera("MODIFICAR USUARIO");
            gotoxy(35, 5);printf("Ingrese el ID del usuario que desea modificar: ");
            scanf("%d", &id);
            pos = buscarUsrEnADL(ADL, *validos, id);
            if(pos!=-1)
                menuModificarUsuario(pos, ADL, *validos, arbol);
            else{
                gotoxy(35, 7);printf("EL USUARIO NO EXISTE");
                getch();
            }

            break;
        case 4:
            system("cls");
            imprimirCabecera("USUARIO");
            gotoxy(35, 4);printf("Ingrese el ID del usuario que desea ver: ");
            scanf("%d", &id);
            pos = buscarUsrEnADL(ADL,*validos,id);
            if(pos != -1){
                mostrarUsr(ADL[pos].usr, 5);
                getch();
            }
            else{
                gotoxy(35, 6);printf("EL USUARIO NO EXISTE");
                Sleep(2000);
            }
            break;
        case 5:
            system("cls");
            imprimirCabecera("USUARIOS REGISTRADOS");
            if(!(*validos)){
                gotoxy(35, 5);printf("NO HAY USUARIOS");
                getch();
            }
            else
                recorrerYmostrarUsrADL(ADL, *validos, 5);
            break;
        default:
            gotoxy(35, 14);puts("La opcion seleccionada es incorrecta.");
            Sleep(1500);
    }
    usuariosToArchivo(ADL,*validos);
}

void menuModificarUsuario(int pos,stCelda ADL[],int validos,nodoArbolCancion * arbol){
    int opc;
    do{
        system("cls");
        imprimirMenuModificarUsuario();
        opc = ingresarOpcion();
        switchModificarUsuario(opc,pos,ADL,validos,arbol);
    }while(opc);
}

void imprimirMenuModificarUsuario(){
    system("cls");
    imprimirCabecera("MODIFICAR USUARIO");
    gotoxy(35, 4);printf("1. Modificar nombre ");
    gotoxy(35, 5);printf("2. Modificar contrase%ca ", 164);
    gotoxy(35, 6);printf("3. Modificacion playlist");
    gotoxy(35, 7);printf("0. Volver al menu anterior");
}

void switchModificarUsuario(int opc, int pos, stCelda ADL[], int validos, nodoArbolCancion * arbol){
    int idPlay;
    switch(opc){
        case 0:
            break;
        case 1:
            modificarNombreUsuario(pos, ADL, validos);
            break;
        case 2:
            modificarPassUsuario(pos, ADL, validos);
            break;
        case 3:
            if(ADL[pos].listaPlaylist)
                menuModificarPlaylist(ADL[pos].listaPlaylist, arbol);
            else{
                gotoxy(35, 16);printf("No tiene playlists para modificar");
                getch();
            }
            break;
        default:
            gotoxy(35, 14);printf("La opcion elegida es incorrecta.");
            Sleep(1500);
    }
    usuariosToArchivo(ADL, validos);
    playlistToArchivo(ADL,validos);
}

void menuModificarPlaylist(nodoPlaylist * play, nodoArbolCancion * arbol){
    int opc;
    do{
        system("cls");
        imprimirMenuModificarPlaylist();
        opc = ingresarOpcion();
        switchModificarPlaylist(opc,arbol,play);
    }while(opc);
}

void imprimirMenuModificarPlaylist(){
    system("cls");
    imprimirCabecera("MODIFICAR PLAYLIST");
    gotoxy(35, 4);puts("1. Modificar nombre playlist.");
    gotoxy(35, 5);puts("2. Agregar canciones.");
    gotoxy(35, 6);puts("3. Borrar canciones.");
    gotoxy(35, 7);puts("4. Borrar Playlist.");
    gotoxy(35, 8);puts("0. Volver al menu anterior\n");
}

void switchModificarPlaylist(int opc, nodoArbolCancion * arbol, nodoPlaylist * play){
    int idPlay;
    nodoPlaylist * aux;
    switch(opc){
        case 0:
            break;
        case 1:
            aux = elegirPlaylist(play);
            if(aux)
                aux = modificarNombrePlaylist(aux);//NO MODIFICA LA LISTA DE PLAYLIST, SOLO EL NOMBRE
            else{
                gotoxy(35, 5);printf("La playlist no existe");
                getch();
            }
            break;
        case 2:
            aux = elegirPlaylist(play);
            if(aux)
                aux->listaCanciones = agregarCancionAplaylist(arbol, aux->listaCanciones);
            else{
                gotoxy(35, 5);printf("La playlist no existe");
                getch();
            }
            break;
        case 3:
            aux = elegirPlaylist(play);
            if(aux)
                aux->listaCanciones = borrarCancionEnPlaylist(aux->listaCanciones);
            else{
                gotoxy(35, 5);printf("La playlist no existe");
                getch();
            }
            break;
        case 4:
            ///SE ROMPEEEE
            aux = elegirPlaylist(play);
            if(aux)
                play = borrarPlaylist(play, aux->play.idPlaylist);
            else{
                gotoxy(35, 5);printf("La playlist no existe");
                getch();
            }
            break;
        default:
            gotoxy(35, 14);puts("La opcion elegida es incorrecta.");
            getch();
    }
}

nodoArbolCancion * menuAdministrarCanciones(nodoArbolCancion * arbol){
    int opc;
    do{
        imprimirAdministrarCanciones();
        opc = ingresarOpcion();
        arbol = switchMenuAdministrarCanciones(opc,arbol);
    }while(opc);
    return arbol;
}

void imprimirAdministrarCanciones(){
    system("cls");
    imprimirCabecera("MENU CANCIONES");
    gotoxy(35,4);puts("1.Alta cancion.");
    gotoxy(35,5);puts("2.Baja cancion.");
    gotoxy(35,6);puts("3.Modificar cancion.");
    gotoxy(35,7);puts("4.Consulta cancion.");
    gotoxy(35,8);puts("5.Lista de canciones.");
    gotoxy(35,9);puts("6.Eliminar cancion definitivamente.");
    gotoxy(35,10);puts("0.Volver al menu anterior.");
}

nodoArbolCancion * switchMenuAdministrarCanciones(int opc,nodoArbolCancion * arbol){
    int id;
    nodoArbolCancion * rta;
    switch(opc){
        case 0:
            break;
        case 1:
            arbol = altaCancionArbol(arbol);
            break;
        case 2:
            eliminarCancion(arbol);
            break;
        case 3:
            system("cls");
            imprimirCabecera("MENU MODIFICAR CANCION");
            printf("\n\n\n\n");
            mostrarCancionCorta(arbol);
            gotoxy(35, 5);printf("Ingresa id de cancion a modificar: ");
            gotoxy(70, 5);scanf("%d",&id);
            rta = buscarCancion(arbol,id);
            if(rta)
                menuModificarCancion(rta);
            else{
                gotoxy(35, 7);puts("La cancion buscada no existe.");
            }
            getch();
            break;
        case 4:
            system("cls");
            imprimirCabecera("CANCIONES");
            printf("\n\nID     NOMBRE\n\n");

            mostrarCancionCorta(arbol);
            gotoxy(35,4);printf("Ingrese ID de la cancion que desea ver: ");
            scanf("%d", &id);
            nodoArbolCancion * buscada = buscarCancion(arbol, id);
            if(buscada){
                system("cls");
                imprimirCabecera("CANCION");
                mostrarCancion(buscada->c);
            }
            else{
                gotoxy(35 , 5);printf("La cancion no existe");
            }
            getch();
            break;
        case 5:
            system("cls");
            imprimirCabecera("CANCIONES");
            inOrder(arbol);
            getch();
            break;
        case 6:
            system("cls");
            imprimirCabecera("BORRAR NODO ARBOL");
            nodoArbolCancion * aux = arbol;
            printf("\n\n");
            gotoxy(35,4);printf("Ingrese id cancion a borrar: ");
            mostrarCancionCorta(aux);

            gotoxy(64,4);scanf("%d",&id);
            borrarNodoArbol(aux,id);
            mostrarCancionCorta(aux);
            getch();
            break;
        default:
            gotoxy(35, 14);puts("La opcion elegida es incorrecta.");
            getch();
    }
    guardarCancionesArchivo(arbol);
    return arbol;
}

void menuModificarCancion(nodoArbolCancion * arbol){
    int opc;
    do{
        imprimirOpcModificarCancion();
        opc = ingresarOpcion();
        switchMenuModificarCancion(opc,arbol);

    }while(opc);
}

void imprimirOpcModificarCancion(){
    system("cls");
    imprimirCabecera("MENU MODIFICAR CANCION");
    gotoxy(35,4);puts("1.Album.");
    gotoxy(35,5);printf("2.A%co Lanzamiento.",164);
    gotoxy(35,6);puts("3.Artista.");
    gotoxy(35,7);puts("4.Duracion.");
    gotoxy(35,8);puts("5.Genero.");
    gotoxy(35,9);puts("6.Titulo.");
    gotoxy(35,10);puts("7.Comentario.");
    gotoxy(35,11);puts("8.Dar de alta");
    gotoxy(35,12);puts("0.Volver al menu anterior.");
}

void switchMenuModificarCancion(int opc, nodoArbolCancion * nodoMfcar){
    system("cls");
    imprimirCabecera("MODIFICAR CANCION");
    gotoxy(35,4);
    switch(opc){
        case 0:
            break;
        case 1:
            printf("\n");
            mostrarCancion(nodoMfcar->c);
            gotoxy(35, 16);printf("Ingrese el nuevo nombre del album: ");
            fflush(stdin);
            gets(nodoMfcar->c.album);
            system("cls");
            imprimirCabecera("CANCION MODIFICADA");
            mostrarCancion(nodoMfcar->c);
            getch();
            break;
        case 2:
            printf("\n");
            mostrarCancion(nodoMfcar->c);
            gotoxy(35, 16);printf("Ingrese el nuevo a%co lanzamiento: ", 164);
            fflush(stdin);
            scanf("%d",&nodoMfcar->c.anio);
            system("cls");
            imprimirCabecera("CANCION MODIFICADA");
            mostrarCancion(nodoMfcar->c);
            getch();
            break;
        case 3:
            printf("\n");
            mostrarCancion(nodoMfcar->c);
            gotoxy(35, 16);printf("Ingrese el nuevo nombre del artista: ");
            fflush(stdin);
            gets(nodoMfcar->c.artista);
            system("cls");
            imprimirCabecera("CANCION MODIFICADA");
            mostrarCancion(nodoMfcar->c);
            getch();
            break;
        case 4:
            printf("\n");
            mostrarCancion(nodoMfcar->c);
            gotoxy(35, 16);printf("Ingrese la nueva duracion de la cancion: ");
            scanf("%d",&nodoMfcar->c.duracion);
            system("cls");
            imprimirCabecera("CANCION MODIFICADA");
            mostrarCancion(nodoMfcar->c);
            getch();
            break;
        case 5:
            printf("\n");
            mostrarCancion(nodoMfcar->c);
            gotoxy(35, 16);printf("Ingrese el nuevo genero de la cancion: ");
            fflush(stdin);
            gets(nodoMfcar->c.genero);
            system("cls");
            imprimirCabecera("CANCION MODIFICADA");
            mostrarCancion(nodoMfcar->c);
            getch();
            break;
        case 6:
            printf("\n");
            mostrarCancion(nodoMfcar->c);
            gotoxy(35, 16);printf("Ingrese el nuevo nombre de la cancion: ");
            fflush(stdin);
            gets(nodoMfcar->c.titulo);
            system("cls");
            imprimirCabecera("CANCION MODIFICADA");
            mostrarCancion(nodoMfcar->c);
            getch();
            break;
        case 7:
            printf("\n");
            mostrarCancion(nodoMfcar->c);
            gotoxy(35, 16);printf("Ingrese un nuevo comentario a la cancion: ");
            fflush(stdin);
            gets(nodoMfcar->c.comentario);
            system("cls");
            imprimirCabecera("CANCION MODIFICADA");
            mostrarCancion(nodoMfcar->c);
            getch();
            break;
        case 8:
            if(nodoMfcar->c.eliminado){
                nodoMfcar->c.eliminado = 0;
                system("cls");
                imprimirCabecera("CANCION MODIFICADA");
                mostrarCancion(nodoMfcar->c);
            }
            else{
                gotoxy(35, 7);printf("La cancion ya se encuentra activa");
            }
            getch();
        break;
        default:
            gotoxy(35, 14);puts("La opcion ingresada es incorrecta.");
            //getch();
    }
}

/********************************** ENTRANDO COMO USUARIO **************************************/

void menuUsuario(stCelda ADL[],int validos, int posUsr, nodoArbolCancion * arbol){
    int opc;

    do{
        system("cls");
        imprimirOpcUsuario();
        opc = ingresarOpcion();
        switchMenuUsuario(opc, ADL, validos, posUsr, arbol);
        usuariosToArchivo(ADL,validos);
    }while(opc);
}

void imprimirOpcUsuario(){
    imprimirCabecera("MENU USUARIO");
    gotoxy(35,4);puts("1.Ver perfil.");
    gotoxy(35,5);puts("2.Mostrar playlist.");
    gotoxy(35,6);puts("3.Escuchar Cancion.");
    gotoxy(35,7);puts("4.Canciones recomendadas.");
    gotoxy(35,8);puts("5.Crear Playlist.");
    gotoxy(35,9);puts("0.Cerrar sesion.");

}

void switchMenuUsuario(int opc, stCelda ADL[], int validos, int posUsr, nodoArbolCancion * arbol){
    int idPlaylist, idCancion;
    char rta, genero[20];
    nodoPlaylist * aux;
    switch(opc){
        case 0:
            system("cls");
            imprimirCabecera("CERRAR SESION");
            gotoxy(35,6);printf("CERRANDO SESION");
            printf(".");Sleep(500);
            printf(".");Sleep(1000);
            printf(".");Sleep(1500);
            break;
        case 1:
            system("cls");
            imprimirCabecera("USUARIO");
            mostrarUsr(ADL[posUsr].usr, 5); //muestro el perfil del usuario que ingreso al programa
            getch();
            break;
        case 2:
            if(ADL[posUsr].listaPlaylist){ //verifico que el usuario tenga playlists
                recorrerYmostrarListasPlaylist(ADL[posUsr].listaPlaylist); //muestro todas las playlist al usuario
                gotoxy(35,4);printf("Elija una playlist para ver: ");
                scanf("%d", &idPlaylist); //Elige una para ver
                nodoPlaylist * aux;

                aux = buscarPlaylist(ADL[posUsr].listaPlaylist, idPlaylist); //Busco la playlist elegida en el ADL
                if(aux){
                    if(aux->listaCanciones){ //Si la playlist tiene canciones las muestro
                        system("cls");
                        imprimirCabecera("PLAYLIST ELEGIDA");
                        recorrerYmostrarListaCanciones(aux->listaCanciones, 5);
                    }
                    else{
                        gotoxy(35, 12);printf("La playlist no tiene canciones");
                    }
                }else{
                    gotoxy(35,5);printf("La playlist no existe.");
                }
            }
            else{
                system("cls");
                imprimirCabecera("PLAYLISTS");
                gotoxy(35, 5);printf("No tiene ninguna playlist");
            }
            getch();
            break;
        case 3:
            system("cls");
            imprimirCabecera("ESCUCHAR CANCION");
            gotoxy(35,4); printf("Ingrese id de la cancion a escuchar: ");
            printf("\n\t\t\t\t\tID-    TITULO");
            printf("\n\n");
            mostrarCancionCorta(arbol);
            gotoxy(72,4);scanf("%d", &idCancion);
            nodoArbolCancion * cancion = buscarCancion(arbol, idCancion);
            if(cancion){
                system("cls");
                imprimirCabecera("ESCUCHAR CANCION");
                mostrarCancion(cancion->c);
                gotoxy(35,20);printf("ESCUCHANDO CANCION");
                printf(".");Sleep(500);
                printf(".");Sleep(1000);
                printf(".");Sleep(1500);
                printf(".");Sleep(2000);
                printf(".");Sleep(2500);
                system("cls");
                imprimirCabecera("AGREGAR CANCION");
                gotoxy(35,7);printf("Si desea agregar la cancion a una playlist presione ENTER");
                rta = getch();
                if(rta == 13){
                    system("cls");
                    imprimirCabecera("PLAYLISTS");
                    recorrerYmostrarListasPlaylist(ADL[posUsr].listaPlaylist); //muestro las playlists del usuario
                    gotoxy(35, 4);printf("Elija una playlist.. Ingrese el id de la misma: ");
                    scanf("%d", &idPlaylist);
                    nodoPlaylist * aux = buscarPlaylist(ADL[posUsr].listaPlaylist, idPlaylist);//busco la playlist elegida
                    if(aux){
                        nodoListaCancion * nuevo = crearNodo(cancion->c); //creo el nodo de la cancion escuchada
                        aux->listaCanciones = agregarFinal(aux->listaCanciones, nuevo); //agrego la cancion a la playlist
                        cancionesToArchivoDetalles(ADL[posUsr].listaPlaylist); //La agrego en el archivo tambien
                    }else{
                        gotoxy(35,10);printf("La playlist no existe.");
                        getch();
                    }
                }
            }
            else{
                gotoxy(35,5);printf("La cancion no existe");
                getch();
            }
            break;
        case 4:
            system("cls");
            imprimirCabecera("CANCIONES RECOMENDADAS");
            gotoxy(35, 4);printf("ELIJA UN GENERO PARA VER CANCIONES RECOMENDADAS: ");
            gotoxy(80, 4);gets(genero);
            //recomendarCanciones(arbol, ADL[posUsr].listaPlaylist, genero)
            getch();
            break;



            /*
            gotoxy(35,4);printf("ELIJA LA PLAYLIST PARA VER SUS CANCIONES RECOMENDADAS");
            getch();
            aux = elegirPlaylist(ADL[posUsr].listaPlaylist);
            system("cls");
            imprimirCabecera("CANCIONES RECOMENDADAS");
            recomendarCancion(arbol,aux->listaCanciones);
            break;
            */
        case 5:
            ADL[posUsr].listaPlaylist = crearPlaylist(ADL[posUsr].listaPlaylist,ADL[posUsr].usr);
            break;
        default:
            gotoxy(35, 14);puts("La opcion elegida es incorrecta.");
            getch();
    }
    playlistToArchivo(ADL,validos);
}
