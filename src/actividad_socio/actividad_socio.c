#include "../../includes/includelib.h"
#include "../tipo_actividad/tipo_actividad.h"
#include "../profesor/profesor.h"
#include "../actividad/actividad.h"
#include "../localidad/localidad.h"
#include "../socio/socio.h"
#include "actividad_socio.h"

THIS(obj_ActividadSocio)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
//----------------------------------------------------
static void toString_ActividadSocioImpl(void *self)
{
    obj_ActividadSocio *obj=this(self);     
    // version con algunos datos, ver como gestionar la posibilidad de listar mas informacion.
    printf("Codigo Actividad-Socio: %d\n - Codigo Socio: %d\n - Codigo actividad: %d\n - Fecha Inicio: %s\n - Fecha Fin: %s\n",
	obj->getCodigo(obj),
	obj->getNroSocio(obj),
	obj->getCodAct(obj), 
	obj->getFechaInicio(obj),
	obj->getFechaFin(obj));
    // version con algunos datos, ver como gestionar la posibilidad de listar mas informacion.
    //printf("\n"); 
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getCodigoActividadSocio_Impl(void *self)
{ return *((int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static int getNroSocioActividadSocio_Impl(void *self)
{ return *((int *) getValue(self,POS_NROSOCIO_ACTSOCIO)); }
//----------------------------------------------------
static int getCodActActividadSocio_Impl(void *self)
{ return *((int *) getValue(self,POS_COD_ACT_ACTSOCIO)); }
//----------------------------------------------------
static char *getFechaInicioActividadSocio_Impl(void *self)
{ return  (char *) getValue(self,POS_FECHA_INICIO_ACTSOCIO); }
//----------------------------------------------------
static char *getFechaFinActividadSocio_Impl(void *self)
{ return  (char *) getValue(self,POS_FECHA_FIN_ACTSOCIO); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setCodigoActividadSocio_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setNroSocioActividadSocio_Impl(void *self,int val)
{ setValue(self,POS_NROSOCIO_ACTSOCIO,&val); }
//----------------------------------------------------
static void setCodActActividadSocio_Impl(void *self,int val)
{ setValue(self,POS_COD_ACT_ACTSOCIO,&val); }
//----------------------------------------------------
static void setFechaInicioActividadSocio_Impl(void *self,char *fdesde)
{ setValue(self,POS_FECHA_INICIO_ACTSOCIO,fdesde); }
//----------------------------------------------------
static void setFechaFinActividadSocio_Impl(void *self,char *ffin)
{ setValue(self,POS_FECHA_FIN_ACTSOCIO,ffin); }
//----------------------------------------------------
static void destroyInternalAct_Impl(void *self)
{
	obj_ActividadSocio *obj = this(self);	
	// finalizar cada referencia inicializada - no NULL
	//obj->actividad
	//obj->socio
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------

//----------------------------------------------------
//implementacion ingresos
//----------------------------------------------------
void ingresarActividadSocio() //consultar el static void!!!
{
    obj_ActividadSocio *actSoc;
    actSoc = ActividadSocio_new();
    int nro_soc, cod_act;
    char fechaInicio[12], fechaFin[12];
    
    printf("ingrese el numero de socio\n");
    scanf("%d",&nro_soc);
    actSoc->setNroSocio(actSoc,nro_soc);
    
    printf("ingrese el numero de actividad\n");
    scanf("%d",&cod_act);
    actSoc->setCodAct(actSoc,cod_act);
    
    printf("ingrese la fecha de inicio\n");
    fflush(stdin);
    fgets(fechaInicio,12,stdin);
    actSoc->setFechaInicio(actSoc,fechaInicio);

    printf("ingrese la fecha de fin\n");
    fflush(stdin);
    fgets(fechaFin,12,stdin);
    actSoc->setFechaFin(actSoc,fechaFin);

    if(!actSoc->saveObj(actSoc))
    {
        printf("Ocurrio un error al agregar la actividad de un socio:\n%s\n",getLastError());
    }
    destroyObj(actSoc);
}
obj_Actividad *getActividad_ActividadSocioObj_Impl(void *self)
{
	obj_ActividadSocio *obj = this(self);	
	//acceso a la informacion relacionada
	return NULL;
}
//----------------------------------------------------
//implementacion listados
//----------------------------------------------------
void listarActividadesSocio(){
    printf("[ Listado de actividades de socio ]\n");
    int i;
    void *list;
    char cod[20],filtro[] = "nro_socio=";
    printf("Ingrese el nro de socio que desea buscar sus actividades\n");
    fflush(stdin);
	fgets(cod,20,stdin);
	strcat(filtro, cod);
    obj_ActividadSocio *actSoc;    
    obj_ActividadSocio *itm;
    actSoc = ActividadSocio_new();
    int size = actSoc->findAll(actSoc,&list,filtro);
    for(i=0;i<size;++i)
    {
        itm = ((Object **)list)[i];    
        ((Object *)itm)->toString(itm);
    }
    destroyObjList(list,size);
    destroyObj(actSoc);
}
//----------------------------------------------------
obj_Socio *getSocio_ActividadSocioObj_Impl(void *self)
{
	obj_ActividadSocio *obj = this(self);	
	//acceso a la informacion relacionada
	return NULL;
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_ActividadSocio(void *self)
{
  obj_ActividadSocio *obj      = this(self);
  obj->ds  			    = &table_ActividadSocio;
  obj->constructor 	    = ActividadSocio_new;
  obj->sizeObj 		    = sizeof(obj_ActividadSocio*);
  // inicializar cada puntero a una referencia relacionada, para ver cuando se busca por el id..
  obj->actividad   		= NULL;
  obj->socio			= NULL;
  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_ActividadSocioImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getCodigo 		= getCodigoActividadSocio_Impl;
  obj->getNroSocio		= getNroSocioActividadSocio_Impl;
  obj->getCodAct		= getCodActActividadSocio_Impl;
  obj->getFechaInicio 	= getFechaInicioActividadSocio_Impl;
  obj->getFechaFin 		= getFechaFinActividadSocio_Impl;
  /// setters  
  obj->setCodigo 		= setCodigoActividadSocio_Impl;
  obj->setNroSocio		= setNroSocioActividadSocio_Impl;
  obj->setCodAct		= setCodActActividadSocio_Impl;    
  obj->setFechaInicio	= setFechaInicioActividadSocio_Impl;
  obj->setFechaFin 		= setFechaFinActividadSocio_Impl;
  
  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalAct_Impl;
  //---- acceso a relaciones  
  obj->getActividadObj 	= getActividad_ActividadSocioObj_Impl;
  obj->getSocioObj		= getSocio_ActividadSocioObj_Impl;
  return obj;
}
//----------------------------------------------------
//constructor de ActividadSocio
obj_ActividadSocio *ActividadSocio_new()
{
  return (obj_ActividadSocio *)init_obj(sizeof(obj_ActividadSocio), init_ActividadSocio);
}
//----------------------------------------------------

