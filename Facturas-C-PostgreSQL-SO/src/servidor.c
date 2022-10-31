#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/conexion.h"
#include "../include/leer.h"


#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

/* 
   variable que servira para hacer la conexion
   con la base de datos.
*/
PGconn * conexion;

int fdWR, fdRD;
char txt[5];

// PROTOTIPOS
void menu_inicial();
void insertar();
void leer();
void actualizar();
void eliminar();

void empleado();

int main()
{
    // variable donde se guardara lo que retorne la funcion conexion_db
	conexion = conexion_db(conexion);

    conexion = conexion_db();
    mkfifo("consulta", 0666);
    mkfifo("menus", 0666);

    // se llama a la funcion menu_inicial
	int opcion = 0; // variable para guardara la opcion que se elija
    while(1) {

        fdWR = open("menus", O_RDONLY);
        read(fdWR, txt, sizeof(txt));
        opcion = atoi(txt);
        close(fdWR);

        printf("\n|-----------------------------|");
        printf("\n|          * Incio *		    |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Insertar	| 3. Eliminar	|");
        printf("\n| 2. Leer 	| 4. Actualizar |");
        printf("\n| 		 5. Salir	        |");
        printf("\n|-----------------------------|");
        printf("->%i\n", opcion);

        switch(opcion) {
            case 1:
                insertar();
				break;
            case 2:
                leer();                        
				break;
			case 3:
                eliminar();                        
				break;
			case 4:
                actualizar();                        
				break;
			case 5:
                printf("\nPrograma finalizado\n");
				break;
            default:
                printf("\nOpcion no disponible\n");    
                 break;
        }
    }
	return (0);
}



/*
    FUNCION menu_inicial()  :
    esta funcion se encarga de mostarr el primer
    menu, en donde las opciones a escoger son
    insertar, leer, eliminar y actualizar
*/
/*void menu_inicial() {

    int opcion = 0; // variable para guardara la opcion que se elija
    do {

        printf("\n|-----------------------------|");
        printf("\n|          * Incio *		    |");
        printf("\n|-----------------------------|");
        printf("\n| 1. Insertar	| 3. Eliminar	|");
        printf("\n| 2. Leer 	| 4. Actualizar |");
        printf("\n| 		 5. Salir	        |");
        printf("\n|-----------------------------|");
        printf("\n\n Escoja una opcion: ");
        scanf("%d", &opcion);1


        fdWR=open("servicios/menus",O_WRONLY);
        sprintf(txt,"%i",opcion);
        write(fdWR,txt,sizeof(txt));
        printf("%s", txt);
        close(fdWR);

        switch(opcion) {
            case 1:
                insertar();
                //Menu para ingresar
				break;
            case 2:
                leer();
                //Menu para Leer                        
				break;
			case 3:
                eliminar();
                //Menu para Eliminar                        
				break;
			case 4:
                actualizar();
                //Menu para Actualizar                        
				break;
			case 5:
                printf("\nPrograma finalizado\n");
				break;
            default:
                printf("\nOpcion no disponible\n");    
                 break;
        }
    }while (opcion != 5);

} // FIN de funcion
*/

/*
    Descripcion:
    Se encargara de mostrar los menus para poder
    insertar en las diferentes tablas

*/
void insertar() {

    int opcion = 0;

    char instruccion[999] = " ";

    fdWR = open("menus", O_RDONLY);
    read(fdWR, txt, sizeof(txt));
    opcion = atoi(txt);
    close(fdWR);

    printf("\n|-----------------------------|");
    printf("\n|          * Insertar *       |");
    printf("\n|-----------------------------|");
    printf("\n| 1. Empleado	| 3. Abono    |");
    printf("\n| 2. Prestamo	| 4. Salir    |");
    printf("\n|---------------------------|");
    printf("->%i\n", opcion);

    switch (opcion)
    {
    case 1:
        fdRD = open("consulta", O_RDONLY);
        read(fdRD, instruccion, sizeof(instruccion));
        printf("Con: %s\n", instruccion);
        close(fdRD);
        PQexec(conexion, instruccion);
        break;
    case 2:
        printf("\nOpcion aun no disponible\n");
        break;
    case 3:
        printf("\nOpcion aun no disponible\n");
        break;
    default:
        break;
    }

}


/*
    Descripcion:
    Se encargara de mostrar los menus para poder
    leer en las diferentes tablas

*/
void leer() {

    int opcion = 0;
    char instruccion[999] = " ";

    fdWR = open("menus", O_RDONLY);
    read(fdWR, txt, sizeof(txt));
    opcion = atoi(txt);
    close(fdWR);

    printf("\n|-----------------------------|");
    printf("\n|          * Leer *		    |");
    printf("\n|-----------------------------|");
    printf("\n| 1. Empleado	| 3. Abono  	|");
    printf("\n| 2. Prestamo	| 4. Salir      |");
    printf("\n|-----------------------------|");
    printf("->%i\n", opcion);

    switch (opcion)
    {
    case 1:
        printf("Leer al empleado");
        fdWR = open("consulta", O_WRONLY);
        strcat(instruccion, leer_todos_enviar(conexion, "mostrar_empleados", 'f'));
        printf("Tabla: %s", instruccion);
        write(fdWR, instruccion, sizeof(instruccion));
        close(fdWR);
        break;
    case 2:
        printf("\nOpcion aun no disponible\n");
        break;
    case 3:
        printf("\nOpcion aun no disponible\n");
        break;
    default:
        printf("\nOpcion no disponible\n");
        break;
    }

}

/*
    Descripcion:
    Se encargara de mostrar los menus para poder
    actualizar en las diferentes tablas

*/
void actualizar() {

    int opcion = 0;

    fdWR = open("menus", O_RDONLY);
    read(fdWR, txt, sizeof(txt));
    opcion = atoi(txt);
    close(fdWR);

    printf("\n|-----------------------------|");
    printf("\n|       * Actualizar *	    |");
    printf("\n|-----------------------------|");
    printf("\n| 1. Empleado	| 3. Abono  	|");
    printf("\n| 2. Prestamo	| 4. Salir      |");
    printf("\n|-----------------------------|");
    printf("->%i\n", opcion);

    switch (opcion)
    {
    case 1:
        empleado();
        break;
    case 2:
        printf("\nOpcion aun no disponible\n");
        break;
    case 3:
        printf("\nOpcion aun no disponible\n");
        break;
    default:
        printf("\nOpcion no disponible\n");
        break;
    }

}

/*
    Descripcion:
    Se encargara de mostrar los menus para poder
    eliminar en las diferentes tablas

*/
void eliminar() {

    int opcion = 0;
    char txt[5];
    char id[5] = " ";
    char instruccion[100];
    fdRD=open("menus",O_RDONLY);
    read(fdRD, txt, sizeof(txt));
    close(fdRD);
    do
    {

    printf("\n|-----------------------------|");
    printf("\n|         * Eliminar * 	    |");
    printf("\n|-----------------------------|");
    printf("\n| 1. Empleado	 | 3. Abono  	|");
    printf("\n| 2. Prestamo	 | 4. Salir     |");
    printf("\n|-----------------------------|");
    opcion = atoi(txt);
    printf("->%i\n", opcion);

    fdRD = open("consulta", O_RDONLY);

    read(fdRD, instruccion, sizeof(instruccion));
    printf("Con: %s\n", instruccion);
    close(fdRD);

    switch (opcion)
    {
    case 1:
        PQexec(conexion, instruccion);
    break;
    case 2:
        printf("\nOpcion aun no disponible\n");
    break;
    case 3:
        printf("\nOpcion aun no disponible\n");
    break;
    default:
        printf("\nOpcion no disponible\n");
        break;
    }

    } while (opcion != 4);

}

void empleado() {

    int opcion = 0;
    char txt[5];
    char instruccion[100] = " ";
    fdRD = open("menus", O_RDONLY);
    read(fdRD, txt, sizeof(txt));
    close(fdRD);
    do
    {

        printf("\n|---------------------|");
        printf("\n|       * Menu *      |");
        printf("\n|---------------------|");
        printf("\n| 1. nombre           |");
        printf("\n| 2. apellido paterno |");
        printf("\n| 3. apellido materno |");
        printf("\n| 4. edad             |");
        printf("\n| 5. regresar         |");
        printf("\n|---------------------|");
        printf("\n\n Escoja una opcion: ");
        opcion = atoi(txt);
        printf("->%i\n", opcion);

        fdRD = open("consulta", O_RDONLY);
        read(fdRD, instruccion, sizeof(instruccion));
        printf("Con: %s\n", instruccion);
        close(fdRD);
        switch (opcion)
        {
            case 1:
            PQexec(conexion, instruccion);
            break;
        case 2:
            PQexec(conexion, instruccion);
            break;
        case 3:
            PQexec(conexion, instruccion);
            break;
        case 4:
            PQexec(conexion, instruccion);
            break;
        default:
            printf("\nOpcion no dispobible");
            break;
        }
    }while(opcion != 5);
}