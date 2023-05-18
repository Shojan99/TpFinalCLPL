#include "../../includes/includelib.h"
#include "../tipo_actividad/tipo_actividad.h"
#include "../profesor/profesor.h"
#include "../actividad/actividad.h"
#include "../localidad/localidad.h"
#include "../socio/socio.h"
#include "../actividad_socio/actividad_socio.h"
#include "../importe_actividad/importe_actividad.h"
#include "cuotas.h"
#include <stdlib.h>

THIS(obj_Cuotas)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
static void toString_CuotasImpl(void *self)
{
    obj_Cuotas *obj=this(self);     
    printf("Codigo SocioActividad:%d\nEstado:%s\nImporte:%f\nAnio :%d Mes:%d\n",
	obj->getCodActSocio(obj),
	obj->getEstado(obj),
    obj->getImporte(obj),
    obj->getAnio(obj),
    obj->getMes(obj));
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
void ingresarCuota() {
    obj_Cuotas *cuota;
    cuota = Cuotas_new();
    
    int codActSocio, cod_socio, anio, mes;
    float importe = 0;
    char filtro[100];
    char fechaVencimiento[12], fechaPago[12], estado[2];
    
    printf("Ingrese el codigo del socio: ");
    scanf("%d", &cod_socio);
    sprintf(filtro, "nro_socio=%d", cod_socio);
    
    printf("Ingrese el anio de pago: ");
    scanf("%d", &anio);
    cuota->setAnio(cuota, anio);
    
    printf("Ingrese el mes: ");
    scanf("%d", &mes);
    cuota->setMes(cuota, mes);

    printf("Ingrese el estado (formato: I = impago | P = Pago | A = Anulado): ");
    fflush(stdin);
    fgets(estado, 2, stdin);
    cuota->setEstado(cuota, estado);
    
    printf("Ingrese la fecha de vencimiento (formato: AAAA/MM/DD): ");
    fflush(stdin);
    fgets(fechaVencimiento, 12, stdin);
    cuota->setFechaVenc(cuota, fechaVencimiento);
    
    printf("Ingrese la fecha de pago (formato: AAAA/MM/DD): ");
    fflush(stdin);
    fgets(fechaPago, 12, stdin);
    cuota->setFechaPago(cuota, fechaPago);
    
    obj_ActividadSocio *actSoc;
	actSoc = ActividadSocio_new();
	void *list;
	int size = actSoc->findAll(actSoc, &list, filtro);
	
	int i, k, j;
	for (i = 0; i < size; i++) {
	    obj_ActividadSocio *itmActSoc = ((obj_ActividadSocio **)list)[i];
	    int codigoAct = itmActSoc->getCodAct(itmActSoc);
	    obj_Actividad *act;
	    act = Actividad_new();
	    int actSize = act->findbykey(act, codigoAct);
	    if (actSize > 0) {
	    	obj_ImporteActividad *impAct;
	        impAct = ImporteActividad_new();
			int codigoTipoAct = act->getCodTipoAct(act);
	        int impActSize = impAct->findbykey(impAct, codigoTipoAct);
	        if (impActSize > 0) {
	            importe += impAct->getImporte(impAct);
	        }
	        cuota->setCodActSocio(cuota, itmActSoc->getCodAct(itmActSoc));
	        destroyObj(act);
	    }
	}
	cuota->setImporte(cuota, importe);
	destroyObjList(list, size);
	
	if (!cuota->saveObj(cuota)) {
	    printf("Ocurri� un error al agregar la cuota:\n%s\n", getLastError());
	}
	destroyObj(cuota);
}
void ListarCuotas() {
    printf("[ Listado de cuotas ]\n");
    
    char tipoEstado;
    printf("Ingrese el tipo de estado (I - Impagas, P - Pagas, A - Anuladas): ");
    scanf(" %c", &tipoEstado);
    
    char fechaDesde[11];
    char fechaHasta[11];
    
    printf("Ingrese la fecha de inicio (formato: AAAA-MM-DD): ");
    scanf(" %s", fechaDesde);
    
    printf("Ingrese la fecha de fin (formato: AAAA-MM-DD): ");
    scanf(" %s", fechaHasta);
    
    char filtro[100];
    sprintf(filtro, "estado='%c' AND fecha_venc BETWEEN '%s' AND '%s'",tipoEstado, fechaDesde, fechaHasta);
 	//		
    int i;
    void *list;
    obj_Cuotas *cuo;    
    obj_Cuotas *itm;
    cuo = Cuotas_new();
    int size = cuo->findAll(cuo,&list,filtro);
    printf("[ Listado de Cuotas ]\n");
    for(i=0;i<size;++i)
    {
    	itm = ((Object **)list)[i];
    	((Object *)itm)->toString(itm);
    }
    destroyObjList(list,size);
    destroyObj(cuo);
}
