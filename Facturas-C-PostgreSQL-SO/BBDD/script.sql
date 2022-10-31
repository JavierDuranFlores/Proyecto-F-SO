CREATE DATABASE prestamos;

CREATE TABLE empleados (

    id_empleados SMALLSERIAL,
    nombre CHARACTER VARYING (30) NOT NULL,
    apellidoP CHARACTER VARYING (30) NOT NULL,
    apellidoM CHARACTER VARYING (30) NOT NULL,
    edad INT NOT NULL,

    CONSTRAINT pk_id_empleados PRIMARY KEY(id_empleados)
);

CREATE TABLE nominas (

  id_nominas SMALLSERIAL,
  cantidad NUMERIC(12, 2) NOT NULL,
  fecha DATE NOT NULL,BIGINT

  CONSTRAINT pk_id_nominas PRIMARY KEY (id_nominas)
);

CREATE TABLE empleados_nominas (
  id_empleado_nomina SMALLSERIAL,
  id_empleado SMALLINT NOT NULL,
  id_nomina SMALLINT NOT NULL,

  CONSTRAINT pk_empleados_nominas PRIMARY KEY (id_empleado_nomina),

  CONSTRAINT fk_id_empleado_empleados_nominas FOREIGN KEY (id_empleado)
    REFERENCES empleados (id_empleado),

  CONSTRAINT fk_id_nomina_empleados_nominas FOREIGN KEY(id_nomina)
    REFERENCES nominas (id_nominas) 
);

CREATE TABLE tipos_prestamos(

  id_tipo_prestamo SMALLSERIAL,
  tipo CHARACTER VARYING (30) NOT NULL,

  CONSTRAINT pk_tipos_prestamos PRIMARY KEY (id_tipo_prestamos)

);


CREATE TABLE prestamos (

  id_prestamo SMALLSERIAL,
  cantidad NUMERIC(12, 2) NOT NULL,
  fecha DATE NOT NULL,
  id_empleado SMALLINT NOT NULL,
  id_tienda SMALLINT NOT NULL,
  id_tipo_prestamo SMALLINT NOT NULL,

  CONSTRAINT pk_id_prestamo PRIMARY KEY(id_prestamo)

  CONSTRAINT fk_id_empleado_prestamos FOREIGN KEY(id_empleado)
    REFERENCES empleados(id_empleado) ON UPDATE CASCADE ON DELETE CASCADE,

  CONSTRAINT fk_id_tienda_prestamos FOREIGN KEY(id_tienda)
    REFERENCES tiendas (id_tienda) ON UPDATE CASCADE ON DELETE CASCADE,

  CONSTRAINT fk_id_tipo_prestamo FOREIGN KEY(id_tipo_prestamo)
    REFERENCES tipos_prestamos(id_tipo_prestamo) ON UPDATE CASCADE ON DELETE CASCADE

  
);

CREATE TABLE tiendas (
  id_tiendas SMALLSERIAL,
  nombre CHARACTER VARYING (30) NOT NULL,
  colonia CHARACTER VARYING(30) NOT NULL,
  calle CHARACTER VARYING(30) NOT NULL,
  ciudad CHARACTER VARYING (30) NOT NULL,


);

CREATE TABLE tipos_abonos(

  id_tipo_abono SMALLSERIAL,
  tipo CHARACTER VARYING NOT NULL,

  CONSTRAINT pk_id_tipo_abono PRIMARY KEY(id_tipo_abono)

);

CREATE TABLE abonos (

  id_abono SMALLSERIAL,
  cantidad NUMERIC(12, 2) NOT NULL,
  fecha DATE NOT NULL,
  id_tipo_abono SMALLINT NOT NULL,

  CONSTRAINT pk_id_abono PRIMARY KEY(id_abono),

  CONSTRAINT fk_id_tipo_abono_abonos FOREIGN KEY(id_tipo_abono)
    REFERENCES tipos_abonos(id_tipo_abono) ON UPDATE CASCADE ON DELETE CASCADE

);

CREATE TABLE exhibiciones(
  id_exhibicion SMALLSERIAL,
  n_quincenas CHARACTER VARYING(30) NOT NULL,
  id_prestamo SMALLINT NOT NULL,

  CONSTRAINT pk_id_exhibicion PRIMARY KEY (id_exhibicion),
  
  CONSTRAINT fk_id_prestamo FOREIGN KEY (id_prestamo)
    REFERENCES prestamos(id_prestamo) ON UPDATE CASCADE ON DELETE CASCADE
);
-- PL para recuperar los empleados
CREATE OR REPLACE FUNCTION mostrar_empleados ()
RETURNS SETOF empleados
AS
$BODY$

  BEGIN

  RETURN QUERY SELECT * FROM empleados;

  END;

$BODY$

LANGUAGE plpgsql;

-- PL para agregar empleados;

CREATE OR REPLACE FUNCTION insertar_empleado(CHARACTER VARYING, CHARACTER VARYING, CHARACTER VARYING, CHARACTER VARYING) RETURNS VOID
AS
$BODY$

  BEGIN

    INSERT INTO empleados VALUES (DEFAULT, $1, $2, $3, $4::INT);

  END;

$BODY$
LANGUAGE plpgsql;

--FUNCION PARA ACTUALIZAR
CREATE OR REPLACE FUNCTION actualizar (_columna CHARACTER VARYING, _nuevo CHARACTER VARYING, 
        _id CHARACTER VARYING, _tabla CHARACTER VARYING)
RETURNS VOID AS
$BODY$  
	BEGIN
    IF _tabla = 'empleados' THEN
      IF _columna = 'nombre' THEN
        UPDATE empleados SET nombre  = _nuevo WHERE id_empleados = _id::INT;
      ELSIF _columna = 'apellidoP' THEN
        UPDATE empleados SET apellidoP = _nuevo WHERE id_empleados = _id::INT;
      ELSIF _columna = 'apellidoM' THEN
        UPDATE empleados SET apellidoM = _nuevo WHERE id_empleados = _id::INT;
      ELSIF _columna = 'edad' THEN
        UPDATE empleados SET edad = _nuevo::INT WHERE id_empleados = _id::INT;
      END IF;
    END IF;
	END;
$BODY$
LANGUAGE plpgsql;

SELECT actualizar('edad', '43', '5', 'empleados');

-- FUNCION para eliminar empleados
CREATE OR REPLACE FUNCTION eliminar_empleado(CHARACTER VARYING)
RETURNS VOID AS
$BODY$
  BEGIN
    DELETE FROM empleados WHERE id_empleados = $1::SMALLINT;
  END;
$BODY$
LANGUAGE plpgsql;