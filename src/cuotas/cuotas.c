#include "../../includes/includelib.h"
#include "../tipo_actividad/tipo_actividad.h"
#include "../profesor/profesor.h"
#include "../actividad/actividad.h"
#include "../localidad/localidad.h"
#include "../socio/socio.h"
#include "../actividad_socio/actividad_socio.h"
#include "cuotas.h"

THIS(obj_Cuotas)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
static void toString_CuotasImpl(void *self)
{
     obj_Cuotas *obj=this(self);     
     
     // version con algunos datos, ver como gestionar la posibilidad de listar mas informacion.
     printf("\n"); 
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getCodigoCuotas_Impl(void *self)
{ return *((int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static int getCodActSocioCuotas_Impl(void *self)
{ return *((int *) getValue(self,POS_COD_ACT_SOC_CUOT)); }
//----------------------------------------------------
static int getAnioCuotas_Impl(void *self)
{ return *((int *) getValue(self,POS_ANIO_CUOT)); }
//----------------------------------------------------
static int getMesCuotas_Impl(void *self)
{ return *((int *) getValue(self,POS_MES_CUOT)); }
//----------------------------------------------------
static char *getEstadoCuotas_Impl(void *self)
{ return  (char *) getValue(self,POS_EST_CUOT); }
//----------------------------------------------------
static float getImporteCuotas_Impl(void *self)
{ return *((float *) getValue(self,POS_IMPORTE_CUOT)); }
//----------------------------------------------------
static char *getFechaVencCuotas_Impl(void *self)
{ return  (char *) getValue(self,POS_FVENC_CUOT); }
//----------------------------------------------------
static char *getFechaPagoCuotas_Impl(void *self)
{ return  (char *) getValue(self,POS_FPAGO_CUOT); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setCodigoCuotas_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setCodActSocioCuotas_Impl(void *self,int val)
{ setValue(self,POS_COD_ACT_SOC_CUOT,&val); }
//----------------------------------------------------
static void setAnioCuotas_Impl(void *self,int val)
{ setValue(self,POS_ANIO_CUOT,&val); }
//----------------------------------------------------
static void setMesCuotas_Impl(void *self,int val)
{ setValue(self,POS_MES_CUOT,&val); }
//----------------------------------------------------
static void setEstadoCuotas_Impl(void *self,char *estado)
{ setValue(self,POS_EST_CUOT,estado); }
//----------------------------------------------------
static void setImporteCuotas_Impl(void *self,float val)
{ setValue(self,POS_IMPORTE_CUOT,&val); }
//----------------------------------------------------
static void setFechaVencCuotas_Impl(void *self,char *fvenc)
{ setValue(self,POS_FVENC_CUOT,fvenc); }
//----------------------------------------------------
static void setFechaPagoCuotas_Impl(void *self,char *fpago)
{ setValue(self,POS_FPAGO_CUOT,fpago); }
//----------------------------------------------------
static void destroyInternalAct_Impl(void *self)
{
	obj_Cuotas *obj = this(self);	
	// finalizar cada referencia inicializada - no NULL
	//obj->actividad_socio	
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
/// ....
obj_ActividadSocio *getActividadSocio_CuotasObj_Impl(void *self)
{
	obj_Cuotas *obj = this(self);	
	//acceso a la informacion relacionada
	return NULL;
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Cuotas(void *self)
{
  obj_Cuotas *obj      = this(self);
  obj->ds  			    = &table_Cuotas;
  obj->constructor 	    = Cuotas_new;
  obj->sizeObj 		    = sizeof(obj_Cuotas*);
  // inicializar cada puntero a una referencia relacionada, para ver cuando se busca por el id..
  obj->actividad_socio  = NULL;
  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_CuotasImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getCodigo 		= getCodigoCuotas_Impl;
  obj->getCodActSocio	= getCodActSocioCuotas_Impl;
  obj->getAnio			= getAnioCuotas_Impl;
  obj->getMes			= getMesCuotas_Impl;
  obj->getEstado		= getEstadoCuotas_Impl;
  obj->getImporte		= getImporteCuotas_Impl;
  obj->getFechaVenc		= getFechaVencCuotas_Impl;
  obj->getFechaPago		= getFechaPagoCuotas_Impl;
  /// setters  
  obj->setCodigo 		= setCodigoCuotas_Impl;
  obj->setCodActSocio	= setCodActSocioCuotas_Impl;    
  obj->setAnio 			= setAnioCuotas_Impl;
  obj->setMes 			= setMesCuotas_Impl;
  obj->setEstado		= setEstadoCuotas_Impl;
  obj->setImporte		= setImporteCuotas_Impl;
  obj->setFechaVenc		= setFechaVencCuotas_Impl;
  obj->setFechaPago		= setFechaPagoCuotas_Impl;
  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalAct_Impl;
  //---- acceso a relaciones  
  obj->getActividadSocioObj 	= getActividadSocio_CuotasObj_Impl;  
  return obj;
}
//----------------------------------------------------
//constructor de Cuotas
obj_Cuotas *Cuotas_new()
{
  return (obj_Cuotas *)init_obj(sizeof(obj_Cuotas), init_Cuotas);
}
//----------------------------------------------------

