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
obj_Actividad *getActividad_ActividadSocioObj_Impl(void *self)
{
	obj_ActividadSocio *obj = this(self);	
	//acceso a la informacion relacionada
	return NULL;
}

obj_Socio *getSocio_ActividadSocioObj_Impl(void *self)
{
	obj_ActividadSocio *obj = this(self);	
	//acceso a la informacion relacionada
	return NULL;
}
//----------------------------------------------------
//implementacion ingresos
//----------------------------------------------------
void ingresarActividadSocio()
{
    obj_Actividad *act;
    act = Actividad_new();
    obj_ActividadSocio *actSoc;
    actSoc = ActividadSocio_new();
    int nro_soc, cod_act;
    char fechaInicio[12];
    
    printf("Ingrese el numero de socio.\n");
    scanf("%d", &nro_soc);
    actSoc->setNroSocio(actSoc, nro_soc);
    obj_Socio *soc;
    soc = Socio_new();
    if (soc->findbykey(soc, nro_soc) == NOT_FOUND) {
        printf("No se encontro el socio correspondiente al numero: %d\n", nro_soc);
        destroyObj(act);
        destroyObj(actSoc);
        destroyObj(soc);
        return;
    }
    destroyObj(soc);
    
    printf("Ingrese el numero de actividad.\n");
    scanf("%d", &cod_act);
    
    actSoc->setCodAct(actSoc, cod_act);
    int actSize = act->findbykey(act, cod_act);
    if (actSize == 0) {
        printf("No se encontro la actividad correspondiente al codigo: %d\n", cod_act);
        destroyObj(act);
        destroyObj(actSoc);
        return;
    }
    
    char *fechaFin = act->getFechaFin(act);
    
    if (fechaFin != NULL && strcmp(fechaFin, "") != 0) {
        printf("La actividad %d finalizo.\n", cod_act);
        destroyObj(act);
        destroyObj(actSoc);
        return;
    }
    
    printf("Ingrese la fecha de inicio (formato AAAA-MM-DD).\n");
    scanf("%11s", fechaInicio);
    actSoc->setFechaInicio(actSoc, fechaInicio);
  
    actSoc->setFechaFin(actSoc, "NULL");

    if (!actSoc->saveObj(actSoc)) {
        printf("Ocurrio un error al agregar la actividad de un socio:\n%s\n", getLastError());
    }
    
    destroyObj(actSoc);
}


//----------------------------------------------------
//implementacion listados
//----------------------------------------------------
void listarActividadesSocio(){
    printf("[ Listado de actividades de socio ]\n");
    int i;
    void *list;
    char cod[20],filtro[] = "nro_socio=";
    printf("Ingrese el nro de socio que desea buscar sus actividades.\n");
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
void actualizarActividadSocio()
{
    obj_ActividadSocio *actS;
    actS = ActividadSocio_new();
    int nro_soc, cod_act, i, confirma, cod;
    char fechaInicio[12], fechaFin[12];
    
    printf("[ Actualizar Actividad Socio ]\nIngrese el codigo de la actividad socio a modificar.\n");
    scanf("%d", &cod);
    
    if (actS->findbykey(actS, cod) != NOT_FOUND) {
        
        do {
            system("cls");
            printf("Ingrese lo que desea modificar\n1 - numero de socio\n2 - codigo de actividad\n3 - fecha de inicio\n4 - fecha de fin\n");
            scanf("%d", &i);
            
            switch (i) {
                case 1:
                    printf("Ingrese el nuevo numero de socio.\n");
                    scanf("%d", &nro_soc);
                    actS->setNroSocio(actS, nro_soc);
                    
                    if (!actS->saveObj(actS)) {
                        printf("Ocurrio un error al actualizar el numero de socio:\n%s\n", getLastError());
                    } else {
                        printf("Se actualizo el numero de socio.\n");
                    }
                    break;
                    
                case 2:
                    printf("Ingrese el nuevo numero de actividad.\n");
                    scanf("%d", &cod_act);
                    actS->setCodAct(actS, cod_act);
                    
                    if (!actS->saveObj(actS)) {
                        printf("Ocurrio un error al actualizar el codigo de actividad:\n%s\n", getLastError());
                    } else {
                        printf("Se actualizo el nuevo codigo de actividad.\n");
                    }
                    break;
                    
                case 3:
                    printf("Ingrese la nueva fecha de inicio (formato AAAA-MM-DD).\n");
                    scanf("%11s", fechaInicio);
                    actS->setFechaInicio(actS, fechaInicio);
                    if (!actS->saveObj(actS)) {
                        printf("Ocurrio un error al actualizar la nueva fecha de inicio:\n%s\n", getLastError());
                    } else {
                        printf("Se actualizo la fecha de inicio.\n");
                    }
                    break;
                    
                case 4:
                    printf("Ingrese la fecha de fin (formato AAAA-MM-DD).\n");
                    scanf("%11s", fechaFin);
                    char *fechaInicioActual = actS->getFechaInicio(actS);
                    if (strcmp(fechaFin, "") != 0 && strcmp(fechaInicioActual, "") != 0) {
                        if (strcmp(fechaFin, fechaInicioActual) < 0) {
                            printf("La fecha de fin no puede ser menor a la fecha de inicio.\n");
                            break;
                        }
                    }
                    
                    actS->setFechaFin(actS, fechaFin);
                    
                    if (!actS->saveObj(actS)) {
                        printf("Ocurrio un error al actualizar la nueva fecha de fin:\n%s\n", getLastError());
                    } else {
                        printf("Se actualizo la fecha de fin.\n");
                    }
                    break;
                    
                default:
                    printf("Ingrese un valor valido.\n");
                    break;
            }
            
            printf("Desea seguir ingresando?\n - Presione cualquier tecla para si y 0 para no.\n");
            scanf("%d", &confirma);
            
        } while (confirma != 0);
        
    } else {
        system("cls");
        printf("No se encontro la actividad socio.\n");
    }
    
    destroyObj(actS);
}
