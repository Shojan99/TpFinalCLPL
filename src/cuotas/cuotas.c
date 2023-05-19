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
int compararImportes(const void *a, const void *b) {
    obj_ImporteActividad *impA = *(obj_ImporteActividad **)a;
    obj_ImporteActividad *impB = *(obj_ImporteActividad **)b;
    
    int anioA = impA->getAnio(impA);
    int anioB = impB->getAnio(impB);
    
    if (anioA != anioB) {
        return anioB - anioA;
    }
    
    int mesA = impA->getMes(impA);
    int mesB = impB->getMes(impB);
    
    return mesB - mesA;
}

void anularCuota() {
    int codigoSocio, i;
    printf("Ingrese el codigo de socio: ");
    scanf("%d", &codigoSocio);
    
    obj_ActividadSocio *actSoc;
    actSoc = ActividadSocio_new();
    
    char filtro[100];
    sprintf(filtro, "nro_socio=%d", codigoSocio);
    
    void *list;
    int size = actSoc->findAll(actSoc, &list, filtro);
    
    if (size == 0) {
        printf("El socio no tiene actividades asociadas.\n");
        destroyObj(actSoc);
        return;
    }
    
    printf("Codigos de actividad asociados al socio:\n");
    for (i = 0; i < size; i++) {
        obj_ActividadSocio *itmActSoc = ((obj_ActividadSocio **)list)[i];
        int codigoAct = itmActSoc->getCodAct(itmActSoc);
        printf("%d. Codigo de actividad: %d\n", i+1, codigoAct);
    }
    
    int opcionAct;
    printf("Seleccione una actividad (ingrese el número): ");
    scanf("%d", &opcionAct);
    
    if (opcionAct < 1 || opcionAct > size) {
        printf("Opcion de actividad invalida.\n");
        destroyObj(actSoc);
        return;
    }
    
    obj_ActividadSocio *itmActSoc = ((obj_ActividadSocio **)list)[opcionAct - 1];
    int codigoAct = itmActSoc->getCodAct(itmActSoc);
    destroyObj(actSoc);
    
    obj_Cuotas *cuota;
    cuota = Cuotas_new();
    
    sprintf(filtro, "estado='P' AND cod_act_socio=%d", codigoSocio, codigoAct);
    
    size = cuota->findAll(cuota, &list, filtro);
    
    if (size == 0) {
        printf("No hay cuotas pagadas para la actividad seleccionada.\n");
        destroyObj(cuota);
        return;
    }
    
    printf("Cuotas pagadas asociadas a la actividad:\n");
    for (i = 0; i < size; i++) {
        obj_Cuotas *itmCuota = ((obj_Cuotas **)list)[i];
        int codigoCuota = itmCuota->getCodigo(itmCuota);
        float importe = itmCuota->getImporte(itmCuota);
        char *fechaVencimiento = itmCuota->getFechaVenc(itmCuota);
        
        printf("%d. Codigo de cuota: %d\n", i+1, codigoCuota);
        printf("   Importe: %.2f\n", importe);
        printf("   Fecha de vencimiento: %s\n", fechaVencimiento);
    }
    
    int opcionCuota;
    printf("Seleccione una cuota para anular (ingrese el numero): ");
    scanf("%d", &opcionCuota);
    
    if (opcionCuota < 1 || opcionCuota > size) {
        printf("Opcion de cuota invalida.\n");
        destroyObj(cuota);
        return;
    }
    
    obj_Cuotas *itmCuota = ((obj_Cuotas **)list)[opcionCuota - 1];
    int codigoCuota = itmCuota->getCodigo(itmCuota);
    destroyObj(cuota);

    cuota = Cuotas_new();
    int cuotaSize = cuota->findbykey(cuota, codigoCuota);
    
    if (cuotaSize == 0) {
        printf("No se encontro la cuota correspondiente al codigo %d.\n", codigoCuota);
        destroyObj(cuota);
        return;
    }
    
    cuota->setEstado(cuota, "A");
    
    if (!cuota->saveObj(cuota)) {
        printf("Ocurrio un error al anular la cuota:\n%s\n", getLastError());
    } else {
        printf("Cuota anulada exitosamente.\n");
    }
    
    destroyObj(cuota);
}

void pagarCuota() {
    int codigoSocio, i;
    printf("Ingrese el codigo de socio: ");
    scanf("%d", &codigoSocio);
    
    obj_ActividadSocio *actSoc;
    actSoc = ActividadSocio_new();
    
    char filtro[100];
    sprintf(filtro, "nro_socio=%d", codigoSocio);
    
    void *list;
    int size = actSoc->findAll(actSoc, &list, filtro);
    
    if (size == 0) {
        printf("El socio no tiene actividades asociadas.\n");
        destroyObj(actSoc);
        return;
    }
    
    printf("Codigos de actividad asociados al socio:\n");
    for (i = 0; i < size; i++) {
        obj_ActividadSocio *itmActSoc = ((obj_ActividadSocio **)list)[i];
        int codigoAct = itmActSoc->getCodAct(itmActSoc);
        printf("%d. Codigo de actividad: %d\n", i+1, codigoAct);
    }
    
    int opcionAct;
    printf("Seleccione una actividad (ingrese el numero): ");
    scanf("%d", &opcionAct);
    
    if (opcionAct < 1 || opcionAct > size) {
        printf("Opcion de actividad invalida.\n");
        destroyObj(actSoc);
        return;
    }
    
    obj_ActividadSocio *itmActSoc = ((obj_ActividadSocio **)list)[opcionAct - 1];
    int codigoAct = itmActSoc->getCodAct(itmActSoc);
    destroyObj(actSoc);
    
    obj_Cuotas *cuota;
    cuota = Cuotas_new();
    
    sprintf(filtro, "estado='I' AND cod_act_socio=%d", codigoSocio, codigoAct);
    
    size = cuota->findAll(cuota, &list, filtro);
    
    if (size == 0) {
        printf("No hay cuotas impagas para la actividad seleccionada.\n");
        destroyObj(cuota);
        return;
    }
    
    printf("Cuotas impagas asociadas a la actividad:\n");
    for (i = 0; i < size; i++) {
        obj_Cuotas *itmCuota = ((obj_Cuotas **)list)[i];
        int codigoCuota = itmCuota->getCodigo(itmCuota);
        float importe = itmCuota->getImporte(itmCuota);
        char *fechaVencimiento = itmCuota->getFechaVenc(itmCuota);
        
        printf("%d. Codigo de cuota: %d\n", i+1, codigoCuota);
        printf("   Importe: %.2f\n", importe);
        printf("   Fecha de vencimiento: %s\n", fechaVencimiento);
    }
    
    int opcionCuota;
    printf("Seleccione una cuota para pagar (ingrese el numero): ");
    scanf("%d", &opcionCuota);
    
    if (opcionCuota < 1 || opcionCuota > size) {
        printf("Opcion de cuota invalida.\n");
        destroyObj(cuota);
        return;
    }
    
    obj_Cuotas *itmCuota = ((obj_Cuotas **)list)[opcionCuota - 1];
    int codigoCuota = itmCuota->getCodigo(itmCuota);
    destroyObj(cuota);

    cuota = Cuotas_new();
    int cuotaSize = cuota->findbykey(cuota, codigoCuota);
    
    if (cuotaSize == 0) {
        printf("No se encontro la cuota correspondiente al codigo %d.\n", codigoCuota);
        destroyObj(cuota);
        return;
    }
    
    cuota->setEstado(cuota, "P");
    
    time_t tiempoActual;
    struct tm *tiempoLocal;
    char fechaPago[11];
    
    tiempoActual = time(NULL);
    tiempoLocal = localtime(&tiempoActual);
    strftime(fechaPago, sizeof(fechaPago), "%Y-%m-%d", tiempoLocal);
    
    cuota->setFechaPago(cuota, fechaPago);
    
    if (!cuota->saveObj(cuota)) {
        printf("Ocurrio un error al pagar la cuota:\n%s\n", getLastError());
    } else {
        printf("Cuota pagada exitosamente.\n");
    }
    
    destroyObj(cuota);
}

void ingresarCuota() {
    obj_Cuotas *cuota;
    cuota = Cuotas_new();
    
    int cod_socio, anio, mes, i;
    float importe = 0;
    char filtro[100];
    char fechaVencimiento[12], estado[2];
    
    printf("Ingrese el codigo del socio: ");
    scanf("%d", &cod_socio);
    sprintf(filtro, "nro_socio=%d", cod_socio);
    
    printf("Ingrese el anio de pago: ");
    scanf("%d", &anio);
    cuota->setAnio(cuota, anio);
    
    printf("Ingrese el mes: ");
    scanf("%d", &mes);
    cuota->setMes(cuota, mes);
    
    obj_ActividadSocio *actSoc;
    actSoc = ActividadSocio_new();
    void *list;
    int size = actSoc->findAll(actSoc, &list, filtro);
    
    if (size == 0) {
        printf("El socio no tiene actividades asociadas.\n");
        destroyObj(actSoc);
        destroyObj(cuota);
        return;
    }
    
    printf("Actividades del socio:\n");
    for (i = 0; i < size; i++) {
        obj_ActividadSocio *itmActSoc = ((obj_ActividadSocio **)list)[i];
        int codigoAct = itmActSoc->getCodAct(itmActSoc);
        
        obj_Actividad *act;
        act = Actividad_new();
        int actSize = act->findbykey(act, codigoAct);
        
        if (actSize == 0) {
            printf("No se encontro la actividad correspondiente al codigo %d.\n", codigoAct);
            destroyObj(act);
            destroyObj(actSoc);
            destroyObj(cuota);
            return;
        }
        
        char *fechaFin = act->getFechaFin(act);
        
        if (fechaFin == NULL) {
            printf("La actividad con codigo %d ya finalizo.\n", codigoAct);
            destroyObj(act);
            destroyObj(actSoc);
            destroyObj(cuota);
            return;
        }
        
        printf("%d. Codigo de actividad: %d\n", i+1, codigoAct);
        destroyObj(act);
    }
    
    int opcion;
    printf("Seleccione una actividad para crear la cuota (ingrese el numero): ");
    scanf("%d", &opcion);
    
    if (opcion < 1 || opcion > size) {
        printf("Opcion invalida.\n");
        destroyObj(actSoc);
        destroyObj(cuota);
        return;
    }
    
    obj_ActividadSocio *itmActSoc = ((obj_ActividadSocio **)list)[opcion - 1];
    int codigoAct = itmActSoc->getCodAct(itmActSoc);
    destroyObj(actSoc);
    
    obj_Actividad *act;
    act = Actividad_new();
    int actSize = act->findbykey(act, codigoAct);
    
    if (actSize == 0) {
        printf("No se encontro la actividad correspondiente al codigo %d.\n", codigoAct);
        destroyObj(act);
        destroyObj(cuota);
        return;
    }
    
    char *fechaFin = act->getFechaFin(act);
    
    if (fechaFin == NULL) {
        printf("La actividad con codigo %d no esta activa.\n", codigoAct);
        destroyObj(act);
        destroyObj(cuota);
        return;
    }
    
    int codigoTipoAct = act->getCodTipoAct(act);
    destroyObj(act);
    
    obj_ImporteActividad *impAct;
    impAct = ImporteActividad_new();
    int impActSize = impAct->findbykey(impAct, codigoTipoAct);
    
    if (impActSize == 0) {
        printf("No se encontro el importe para el tipo de actividad con codigo %d.\n", codigoTipoAct);
        destroyObj(impAct);
        destroyObj(cuota);
        return;
    }
    
    importe = impAct->getImporte(impAct);
    destroyObj(impAct);

    printf("Ingrese la fecha de vencimiento (formato: AAAA-MM-DD): ");
    scanf("%s", fechaVencimiento);
    cuota->setFechaVenc(cuota, fechaVencimiento);
    cuota->setCodActSocio(cuota, codigoAct);
    cuota->setImporte(cuota, importe);
    cuota->setEstado(cuota, "I");
    cuota->setFechaPago(cuota, "NULL");
    
    if (!cuota->saveObj(cuota)) {
        printf("Ocurrio un error al agregar la cuota:\n%s\n", getLastError());
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
