#include <stdio.h>
#include "../include/conexion.h"

/* 
   variable que servira para hacer la conexion
   con la base de datos.
*/
PGconn * conexion;

// PROTOTIPOS
void menu_inicial() ;

int main()
{
    // variable donde se guardara lo que retorne la funcion conexion_db
	conexion = conexion_db(conexion);

    // se llama a la funcion menu_inicial
	menu_inicial();

	return (0);
}


/*
    FUNCION menu_inicial()  :
    esta funcion se encarga de mostarr el primer
    menu, en donde las opciones a escoger son
    insertar, leer, eliminar y actualizar
*/
void menu_inicial() {

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
        scanf("%d", &opcion);

        switch(opcion) {
            case 1:
                //Menu para ingresar
				break;
            case 2:
                //Menu para Leer                        
				break;
			case 3:
                //Menu para Eliminar                        
				break;
			case 4:
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