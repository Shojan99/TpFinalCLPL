#include "../../includes/includelib.h"
#include "../tipo_actividad/tipo_actividad.h"
#include "../profesor/profesor.h"
#include "actividad.h"
#include <stdbool.h> 
#include <string.h> 


THIS(obj_Actividad)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
static void toString_ActividadImpl(void *self)
{
     obj_Actividad *obj=this(self);     
     obj_TipoActividad *t_act = obj->getTipoActividadObj(obj);
     // version con algunos datos, ver como gestionar la posibilidad de listar mas informacion.
     printf("Codigo Actividad: %d - Codigo Tipo Actividad:%d - Fecha inicio: %s - Fecha fin: %s - Numero legajo profesor: %d \n",
	 obj->getCodigo(obj), 
	 obj->getCodTipoAct(obj),
	 obj->getFechaDesde(obj), 
	 obj->getFechaFin(obj),
	 obj->getLegajoProfe(obj)); 
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getCodigoActividad_Impl(void *self)
{ return *((int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static int getCodTipoActActividad_Impl(void *self)
{ return *((int *) getValue(self,POS_CODTIPO_ACT)); }
//----------------------------------------------------
static int getLegajoProfeActividad_Impl(void *self)
{ return *((int *) getValue(self,POS_LEGAJO_PROFE_ACT)); }
//----------------------------------------------------
static char *getFechaDesdeActividad_Impl(void *self)
{ return  (char *) getValue(self,POS_FECHA_DESDE_ACT); }
//----------------------------------------------------
static char *getFechaFinActividad_Impl(void *self)
{ return  (char *) getValue(self,POS_FECHA_FIN_ACT); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setCodigoActividad_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setCodTipoActActividad_Impl(void *self,int val)
{ setValue(self,POS_CODTIPO_ACT,&val); }
//----------------------------------------------------
static void setLegajoProfeActividad_Impl(void *self,int val)
{ setValue(self,POS_LEGAJO_PROFE_ACT,&val); }
//----------------------------------------------------
static void setFechaDesdeActividad_Impl(void *self,char *fdesde)
{ setValue(self,POS_FECHA_DESDE_ACT,fdesde); }
//----------------------------------------------------
static void setFechaFinActividad_Impl(void *self,char *ffin)
{ setValue(self,POS_FECHA_FIN_ACT,ffin); }
//----------------------------------------------------
static void destroyInternalAct_Impl(void *self)
{
	obj_Actividad *obj = this(self);	
	// finalizar cada referencia inicializada - no NULL
	//obj->tipo_actividad
	//obj->profesor
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
/// ....
obj_TipoActividad *getTipoActividad_ActividadObj_Impl(void *self)
{
	obj_Actividad *obj = this(self);	
	//acceso a la informacion relacionada
	return NULL;
}
//----------------------------------------------------
obj_Profesor *getProfesor_ActividadObj_Impl(void *self)
{
	obj_Actividad *obj = this(self);	
	//acceso a la informacion relacionada
	return NULL;
}
//----------------------------------------------------
//implementacion ingresar
//----------------------------------------------------
void ingresarActividad(){
    int codActividad,legajo, tipoActividad;
    char fechaInicio[12];
    
    obj_Actividad *act;
    act = Actividad_new();
    
    printf("ingrese el tipo de la actividad\n");
    scanf("%d",&tipoActividad);
    act->setCodTipoAct(act,tipoActividad);   
    
    printf("ingrese el legajo del profe que va a dar la actividad\n");
    scanf("%d",&legajo);
    act->setLegajoProfe(act,legajo);      
    
    printf("ingrese la fecha de inicio\n");
    fflush(stdin);
    fgets(fechaInicio,12,stdin);
    act->setFechaDesde(act,fechaInicio);
    act->setFechaFin(act,"NULL");
    if(!act->saveObj(act))
    {
              printf("Ocurrio un error al agregar actividad:\n%s\n",getLastError());
    }
    destroyObj(act);
}
 

void actualizarActividad()
{
    obj_Actividad *act;
    act = Actividad_new();
    
    int codActividad, codigo, legajo, i, confirma;
    int fechaInicioInt, fechaFinInt;
    char fechaInicio[12], fechaFin[12];
    
    printf("[ Actualizar actividad ]\nIngrese el codigo de la actividad a modificar\n");
    scanf("%d", &codigo);
    
    if (act->findbykey(act, codigo) != NOT_FOUND) {
        
        do {
            system("cls");
            printf("Ingrese lo que desea modificar:\n1 - Codigo del tipo de actividad\n2 - Legajo del profesor\n3 - Fecha de inicio\n4 - Fecha de fin\n");
            scanf("%d", &i);
            
            switch (i) {
                case 1:
                    printf("Ingrese el nuevo codigo del tipo de actividad\n");
                    scanf("%d", &codActividad);
                    act->setCodTipoAct(act, codActividad);
                    
                    if (!act->saveObj(act)) {
                        printf("Ocurrio un error al actualizar el codigo del tipo de actividad\n%s\n", getLastError());
                    } else {
                        printf("Se actualizo el codigo del tipo de actividad\n");
                    }
                    
                    break;
                    
                case 2:
                    printf("Ingrese el nuevo legajo del profesor\n");
                    scanf("%d", &legajo);
                    act->setLegajoProfe(act, legajo);
                    
                    if (!act->saveObj(act)) {
                        printf("Ocurrio un error al actualizar el nuevo legajo del profesor:\n%s\n", getLastError());
                    } else {
                        printf("Se actualizo el legajo del profesor\n");
                    }
                    
                    break;
                    
                case 3:
                    printf("Ingrese la nueva fecha de inicio (formato AAAA-MM-DD)\n");
                    scanf("%s", fechaInicio);

                    fechaInicioInt = atoi(fechaInicio);
                    if (strcmp(act->getFechaFin(act), "") != 0) {
                        strcpy(fechaFin, act->getFechaFin(act));
                        fechaFinInt = atoi(fechaFin);
                        
                        if (fechaInicioInt > fechaFinInt) {
                            printf("La fecha de inicio no puede ser mayor a la fecha de fin\n");
                            break;
                        }
                    }
                    
                    act->setFechaDesde(act, fechaInicio);
                    
                    if (!act->saveObj(act)) {
                        printf("Ocurrio un error al actualizar la fecha de inicio\n%s\n", getLastError());
                    } else {
                        printf("Se actualizo la fecha de inicio\n");
                    }
                    
                    break;
                    
                case 4:
                    printf("Ingrese la nueva fecha de fin (formato AAAA-MM-DD)\n");
                    scanf("%s", fechaFin);
                    fechaFinInt = atoi(fechaFin);
                    if (strcmp(act->getFechaDesde(act), "") != 0) {
                        strcpy(fechaInicio, act->getFechaDesde(act));
                        fechaInicioInt = atoi(fechaInicio);
                        
                        if (fechaFinInt < fechaInicioInt) {
                            printf("La fecha de fin no puede ser menor a la fecha de inicio\n");
                            break;
                        }
                    }
                    act->setFechaFin(act, fechaFin);
                    if (!act->saveObj(act)) {
                        printf("Ocurrio un error al actualizar la fecha de fin\n%s\n", getLastError());
                    } else {
                        printf("Se actualizo la fecha de fin\n");
                    }
                    
                    break;
                    
                default:
                    printf("Ingrese un valor valido\n");
                    break;
            }
            
            printf("Desea seguir ingresando?\n- Presione cualquier tecla para si, 0 para no\n");
            scanf("%d", &confirma);
            
        } while (confirma != 0);
        
    } else {
        system("cls");
        printf("No se encontró la actividad\n");
    }
    
    destroyObj(act);
}


/*
void listarActividades(){
    printf("[ Listado de Actividades ]\n");
    int i;
    void *list;
    obj_Actividad *loc;    
    obj_Actividad *itm;
    loc = Actividad_new();
    int size = loc->findAll(loc,&list,NULL);
    for(i=0;i<size;++i)
    {
    	itm = ((Object **)list)[i];
    	((Object *)itm)->toString(itm);
    }
    destroyObjList(list,size);
    destroyObj(loc);
    
}
*/
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Actividad(void *self)
{
  obj_Actividad *obj      = this(self);
  obj->ds  			    = &table_Actividad;
  obj->constructor 	    = Actividad_new;
  obj->sizeObj 		    = sizeof(obj_Actividad*);
  // inicializar cada puntero a una referencia relacionada, para ver cuando se busca por el id..
  obj->tipo_actividad   = NULL;
  obj->profesor   		= NULL;
  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_ActividadImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getCodigo 		= getCodigoActividad_Impl;
  obj->getCodTipoAct	= getCodTipoActActividad_Impl;
  obj->getLegajoProfe	= getLegajoProfeActividad_Impl;
  obj->getFechaDesde 	= getFechaDesdeActividad_Impl;
  obj->getFechaFin 		= getFechaFinActividad_Impl;
  /// setters  
  obj->setCodigo 		= setCodigoActividad_Impl;
  obj->setLegajoProfe	= setLegajoProfeActividad_Impl;    
  obj->setFechaDesde	= setFechaDesdeActividad_Impl;
  obj->setFechaFin 		= setFechaFinActividad_Impl;
  obj->setCodTipoAct 	= setCodTipoActActividad_Impl;
  
  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalAct_Impl;
  //---- acceso a relaciones  
  obj->getTipoActividadObj 	= getTipoActividad_ActividadObj_Impl;  
  obj->getProfesorObj		= getProfesor_ActividadObj_Impl;
  return obj;
}
//----------------------------------------------------
//constructor de Actividad
obj_Actividad *Actividad_new()
{
  return (obj_Actividad *)init_obj(sizeof(obj_Actividad), init_Actividad);
}
//----------------------------------------------------

