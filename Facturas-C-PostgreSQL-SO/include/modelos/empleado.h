#ifndef EMPLEADO_H
#define EMPLEADO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../next_line.h"

typedef struct Empleado {

    char * idEmpleado;
    char * nombre;
    char * apellidoP;
    char * apellidoM;
    char * edad;

}Empleado;

Empleado * empleado_constructor (char * nombre, char * apellidoP, char * apellidoM,
				char * edad);

Empleado * recolectar_datos_empleado();


#endif