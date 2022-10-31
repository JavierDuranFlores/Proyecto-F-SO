#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../include/next_line.h"
#include "../include/concat_punteros.h"
#include "../include/modelos/empleado.h"
#include "../include/agregar.h"
#include "../include/actualizar.h"
#include "../include/eliminar.h"

#include <time.h>       // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h>     // for sleep()


// PROTOTIPOS
void menu_inicial();
void insertar();
void leer();
void actualizar();
void eliminar();

void mostrar_tabla(char * tabla);

//PARA ACTUALIZAR
void empleado();

int fdWR, fdRD;
char txt[5];

/*int main()
{

    // se llama a la funcion menu_inicial
    menu_inicial();

    return (0);
}*/

/*
    FUNCION menu_inicial()  :
    esta funcion se encarga de mostarr el primer
    menu, en donde las opciones a escoger son
    insertar, leer, eliminar y actualizar
*/
int main()
{

    time_t begin = time(NULL);

    int opcion = 0; // variable para guardara la opcion que se elija
    while (1)
    {

        printf("\n|------------------------------|");
        printf("\n|          * Incio *	       |");
        printf("\n|------------------------------|");
        printf("\n| 1. Insertar	| 3. Eliminar  |");
        printf("\n| 2. Leer 	| 4. Actualizar|");
        printf("\n| 	   5. Salir            |");
        printf("\n|------------------------------|");
        printf("\nopcion: ");
        scanf("%i", &opcion);

        fdWR = open("menus", O_WRONLY);
        sprintf(txt, "%i", opcion);
        write(fdWR, txt, sizeof(txt));
        printf("%s", txt);
        close(fdWR);

        switch (opcion)
        {
        case 1:
            insertar();
            // Menu para ingresar
            break;
        case 2:
            leer();
            // Menu para Leer
            break;
        case 3:
            eliminar();
            // Menu para Eliminar
            break;
        case 4:
            actualizar();
            // Menu para Actualizar
            break;
        case 5:
            printf("\nPrograma finalizado\n");

            time_t end = time(NULL);
 
            // calcular el tiempo transcurrido encontrando la diferencia (end - begin)
            printf("el tiempo es %d segundo\n", (end - begin));
            return 0;

            break;
        default:
            printf("\nOpcion no disponible\n");
            break;
        }
    }

    
} // FIN de funcion

/*
    Descripcion:
    Se encargara de mostrar los menus para poder
    insertar en las diferentes tablas

*/
void insertar()
{
    Empleado * empleadoN;

    int opcion = 0;
    char txt[5];
    char instruccion[100]=" ";
    fdWR=open("menus",O_WRONLY);

    printf("\n|------------------------------|");
    printf("\n|          * Insertar *        |");
    printf("\n|------------------------------|");
    printf("\n| 1. Empleado	| 3. Abono     |");
    printf("\n| 2. Prestamo   | 4. Salir     |");
    printf("\n|------------------------------|");
    printf("\nopcion: ");
    scanf("%i", &opcion);

    fdWR = open("menus", O_WRONLY);
    sprintf(txt, "%i", opcion);
    write(fdWR, txt, sizeof(txt));
    printf("%s", txt);
    close(fdWR);

    switch (opcion)
    {
    case 1:
        empleadoN = recolectar_datos_empleado();
        strcat(instruccion,agregar_todos("insertar_empleado", 4, empleadoN->nombre, empleadoN->apellidoP, empleadoN->apellidoM, empleadoN->edad));
        fdWR = open("consulta", O_WRONLY);
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
        break;
    }
}

/*
    Descripcion:
    Se encargara de mostrar los menus para poder
    leer en las diferentes tablas

*/
void leer()
{

    int opcion = 0;
    char txt[5];
    char datos[999] = " ";
    char *tabla = " ";

    fdWR = open("menus", O_WRONLY);
    printf("\n|------------------------------|");
    printf("\n|           * Leer *           |");
    printf("\n|------------------------------|");
    printf("\n| 1. Empleado	| 3. Abono     |");
    printf("\n| 2. Prestamo   | 4. Salir     |");
    printf("\n|------------------------------|");
    printf("\nopcion: ");
    scanf("%i", &opcion);

    
    sprintf(txt, "%i", opcion);
    write(fdWR, txt, sizeof(txt));
    printf("%s", txt);
    close(fdWR);

    switch (opcion)
    {
    case 1:
        fdRD = open("consulta", O_RDONLY);
        read(fdRD, datos, sizeof(datos));
        tabla = cat_puntero(tabla, datos);
        mostrar_tabla(tabla);
        close(fdRD);
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
    actualizar en las diferentes tablas

*/
void actualizar()
{

    int opcion = 0;
    char txt[5];

    printf("\n|-----------------------------|");
    printf("\n|       * Actualizar *	    |");
    printf("\n|-----------------------------|");
    printf("\n| 1. Empleado	| 3. Abono  	|");
    printf("\n| 2. Prestamo	| 4. Salir      |");
    printf("\n|-----------------------------|");
    printf("\nopcion: ");
    scanf("%i", &opcion);

    fdWR = open("menus", O_WRONLY);
    sprintf(txt, "%i", opcion);
    write(fdWR, txt, sizeof(txt));
    printf("%s", txt);
    close(fdWR);

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
        break;
    }
}

/*
    Descripcion:
    Se encargara de mostrar los menus para poder
    eliminar en las diferentes tablas

*/
void eliminar()
{

    int opcion = 0;
    char txt[5] = " "; 
    char * id = " ";
    char instruccion[100]=" ";
    char * idPun = " ";
    fdWR=open("menus",O_WRONLY);

    do {
        for (int i = 0; i < 100; i++)
            instruccion[i] = '\0';

    printf("\n|-----------------------------|");
    printf("\n|        * Eliminar * 	    |");
    printf("\n|-----------------------------|");
    printf("\n| 1. Empleado	| 3. Abono  	|");
    printf("\n| 2. Prestamo	| 4. Salir      |");
    printf("\n|-----------------------------|");
    printf("\nopcion: ");
    scanf("%i", &opcion);

    sprintf(txt,"%i",opcion);
    write(fdWR,txt,sizeof(txt));
    close(fdWR);        
    vacia_buffer();

    switch (opcion)
    {
    case 1:
        printf("Digite el id cliente: ");
        id = nextLine();

        strcat(instruccion, eliminar_todos("eliminar_empleado", 1, id));
        fdWR = open("consulta", O_WRONLY);
        write(fdWR, instruccion, sizeof(instruccion));
        close(fdWR);
        printf("\n");
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
    } while (opcion != 4);
}

void mostrar_tabla(char * tabla) {

    char * fila = "\n";
    fila = strtok(tabla, ";");
    if(fila != NULL){
        while(fila != NULL){
            // Sólo en la primera pasamos la cadena; en las siguientes pasamos NULL
            //printf("Token: %s\n", fila);
            printf("\n%s\n", fila);
            fila = strtok(NULL, ";");
            
        }
    }

}

void empleado() {

    int opcion = 0;
    char txt[5];
    char instruccion[100]=" ";
    fdWR=open("menus",O_WRONLY);
    char * nuevo = " ";
    char * columna;
    char * id = " ";
    char * tabla = "empleados";
    char * sql = "SELECT actualizar(";
    do
    {

        for (int i = 0; i < 100; i++)
            instruccion[i] = '\0';

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
        scanf("%d", &opcion);

        sprintf(txt,"%i",opcion);
        write(fdWR,txt,sizeof(txt));
        close(fdWR);
        vacia_buffer();
        if (opcion != 5) {
            printf("Digite el id empleado: ");
            id = nextLine();
        }
        
        switch (opcion)
        {
            case 1:
            columna="nombre";
            printf("Digite su nombre: ");
            nuevo = nextLine();
            strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
            fdWR = open("consulta", O_WRONLY);
            write(fdWR, instruccion, sizeof(instruccion));
            close(fdWR);
            break;
        case 2:
            columna="apellidop";
            printf("Digite su apellido paterno: ");
            nuevo = nextLine();
            strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
            fdWR = open("consulta", O_WRONLY);
            write(fdWR, instruccion, sizeof(instruccion));
            close(fdWR);
           // PQexec(conn, instruccion);
            // actualizar_cliente_servicio(conn, "rfc");
            break;
        case 3:
            columna="apellidoM";
            printf("Digite su apellido materno: ");
            nuevo = nextLine();
            strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
            fdWR = open("consulta", O_WRONLY);
            write(fdWR, instruccion, sizeof(instruccion));
            close(fdWR);
            //PQexec(conn, instruccion);
            // actualizar_cliente_servicio(conn, "edad");
            break;
        case 4:
            columna="edad";
            printf("Digite su edad: ");
            nuevo = nextLine();
            strcat(instruccion, actualizar_todos_("actualizar", 4, columna, nuevo, id, tabla));
            fdWR = open("consulta", O_WRONLY);
            write(fdWR, instruccion, sizeof(instruccion));
            close(fdWR);
            //PQexec(conn, instruccion);
            // actualizar_cliente_servicio(conn, "apellidos");
            break;
        default:
            printf("\nOpcion no dispobible");

        }
    } while(opcion != 5);
}