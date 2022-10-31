
#include "../../include/modelos/empleado.h"

Empleado * empleado_constructor (char * nombre, char * apellidoP, char * apellidoM,
				char * edad) {

    Empleado * empleado = (Empleado *) malloc (sizeof(Empleado));

    empleado->nombre = nombre;
    empleado->apellidoP = apellidoP;
    empleado->apellidoM = apellidoM;
    empleado->edad = edad;

    return empleado;

} 

Empleado * recolectar_datos_empleado() {

    vacia_buffer();

    printf("Digite su nombre: ");
    char * nombre = nextLine();

    printf("Digite su apellido Paterno: ");
    char * apellidoP = nextLine();

    printf("Digite su apellido Materno: ");
    char * apellidoM = nextLine();

    printf("Digite su edad: ");
    char * edad = nextLine();

    return empleado_constructor(nombre, apellidoP, apellidoM, edad);
}