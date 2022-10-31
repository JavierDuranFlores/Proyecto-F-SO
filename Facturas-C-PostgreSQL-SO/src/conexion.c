#include "../include/conexion.h"

/*
    Descripcion:
    Se encarga de hacer la conexion con la base de datos
*/
PGconn * conexion_db(PGconn * conexion) {

    // pregunta si la conexion no existe
    if (conexion == NULL) {
        // sino existe la conexion, se crea.
        conexion = PQconnectdb("host=127.0.0.1 port=5432 dbname=prestamos user=postgres password=1234");
    }

    // verificamos si todo a salido correctamente
    comprobar_estadodb(conexion);


    // si existe retorna la conexion nuevamente
    return conexion;
}

/*
    Descripcion:
    Se encarga de comprobar la conexion con la base de datos   
*/
void comprobar_estadodb(PGconn * conexion) {

    // Pregunta si la conexion tiene algun error
    if (PQstatus (conexion) == CONNECTION_BAD) {
        //si tiene erro manda un mensaje de error
        fprintf (stderr, "Falló la conexión a la base de datos:%s \n", PQerrorMessage (conexion));
    }

}