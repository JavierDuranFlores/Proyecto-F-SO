#ifndef CONEXION_H
#define CONEXION_H

#include <stdio.h>
#include <libpq-fe.h>

PGconn * conexion_db(PGconn * conexion;);
void comprobar_estadodb(PGconn * conexion;);

#endif
