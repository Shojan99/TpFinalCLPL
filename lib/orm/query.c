#include "../../config/config.h"
#include "../utils/utils.h"
#include "query.h"
#include <string.h>
#include <malloc.h>

THIS(obj_Query)// crea definicion de funcion this para este modulo. .. Macro en config.h
// modulo en desarrollo - incompleto :-(

//al crear objeto de criterio, se debe tener una nombre de tabla del modelo, un alias
// addAnd 
// addOr 
// addJoin 
// list

static void addAndQuery_Impl(void *self,char *cr)
{ 
 obj_Query *obj = this(self); 
}
// crear funcion que destruya el objeto criterio
obj_Query *Query_new(char *tabla)
{
	// crear la instancia a devolver para generar la consulta SQL con metodos 
	obj_Query *obj = this(obj);
	obj->sql = (char *)malloc(sizeof(char)*MAX_SQL); // dar espacio para crear la sentencia SQL
	obj->addAnd = addAndQuery_Impl;
	CLEAR(obj->sql,MAX_SQL);
	obj->t = tabla;
	// crear los metodos que permita agregar condiciones y opciones de la consulta.
	return obj;
}

