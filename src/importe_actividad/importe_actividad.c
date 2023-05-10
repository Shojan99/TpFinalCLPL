#include "../../includes/includelib.h"
#include "../tipo_actividad/tipo_actividad.h"

#include "importe_actividad.h"

THIS(obj_ImporteActividad)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
static void toString_ImporteActividadImpl(void *self)
{
     obj_ImporteActividad *obj=this(self);     
     
     // version con algunos datos, ver como gestionar la posibilidad de listar mas informacion.
     printf("\n"); 
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getCodigoImporteActividad_Impl(void *self)
{ return *((int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static int getCodTipoActImporteActividad_Impl(void *self)
{ return *((int *) getValue(self,POS_CODTIPOACT_IMPACT)); }
//----------------------------------------------------
static int getAnioImporteActividad_Impl(void *self)
{ return *((int *) getValue(self,POS_ANIO_IMPACT)); }
//----------------------------------------------------
static int getMesImporteActividad_Impl(void *self)
{ return *((int *) getValue(self,POS_MES_IMPACT)); }
//----------------------------------------------------
static float getImporteImporteActividad_Impl(void *self)
{ return *((float *) getValue(self,POS_IMPORTE_IMPACT)); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setCodigoImporteActividad_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setCodTipoActImporteActividad_Impl(void *self,int val)
{ setValue(self,POS_CODTIPOACT_IMPACT,&val); }
//----------------------------------------------------
static void setAnioImporteActividad_Impl(void *self,int val)
{ setValue(self,POS_ANIO_IMPACT,&val); }
//----------------------------------------------------
static void setMesImporteActividad_Impl(void *self,int val)
{ setValue(self,POS_MES_IMPACT,&val); }
//----------------------------------------------------
static void setImporteImporteActividad_Impl(void *self,float val)
{ setValue(self,POS_IMPORTE_IMPACT,&val); }
//----------------------------------------------------
static void destroyInternalAct_Impl(void *self)
{
	obj_ImporteActividad *obj = this(self);	
	// finalizar cada referencia inicializada - no NULL
	//obj->tipo_actividad

}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
/// ....
obj_TipoActividad *getTipoActividad_ImporteActividadObj_Impl(void *self)
{
	obj_ImporteActividad *obj = this(self);	
	//acceso a la informacion relacionada
	return NULL;
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_ImporteActividad(void *self)
{
  obj_ImporteActividad *obj      = this(self);
  obj->ds  			    = &table_ImporteActividad;
  obj->constructor 	    = ImporteActividad_new;
  obj->sizeObj 		    = sizeof(obj_ImporteActividad*);
  // inicializar cada puntero a una referencia relacionada, para ver cuando se busca por el id..
  obj->tipo_actividad   = NULL;
  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_ImporteActividadImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getCodigo 		= getCodigoImporteActividad_Impl;
  obj->getCodTipoAct	= getCodTipoActImporteActividad_Impl;
  obj->getAnio			= getAnioImporteActividad_Impl;
  obj->getMes 			= getMesImporteActividad_Impl;
  obj->getImporte 		= getImporteImporteActividad_Impl;
  /// setters  
  obj->setCodigo 		= setCodigoImporteActividad_Impl;
  obj->setCodTipoAct	= setCodTipoActImporteActividad_Impl;    
  obj->setAnio			= setAnioImporteActividad_Impl;
  obj->setMes 			= setMesImporteActividad_Impl;
  
  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalAct_Impl;
  //---- acceso a relaciones  
  obj->getTipoActividadObj 	= getTipoActividad_ImporteActividadObj_Impl;  
  return obj;
}
//----------------------------------------------------
//constructor de ImporteActividad
obj_ImporteActividad *ImporteActividad_new()
{
  return (obj_ImporteActividad *)init_obj(sizeof(obj_ImporteActividad), init_ImporteActividad);
}
//----------------------------------------------------

