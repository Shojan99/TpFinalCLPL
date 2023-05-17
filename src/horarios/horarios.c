#include "../../includes/includelib.h"
#include "../tipo_actividad/tipo_actividad.h"
#include "../profesor/profesor.h"
#include "../actividad/actividad.h"
#include "../lugar/lugar.h"
#include "../horarios/horarios.h"
#include "../actividad_socio/actividad_socio.h"
#include <string.h>
#define MAXIMA_LONGITUD_CADENA 6
#define CANTIDADCARACTERES 5
THIS(obj_Horario)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
static void toString_HorarioImpl(void *self)
{

	 obj_Horario *obj=this(self);     
     obj_Lugar *lug = obj->getLugarObj(obj);
     obj_Actividad *act = obj->getActividadObj(obj);

     char horaAcotada[MAXIMA_LONGITUD_CADENA] = "";
     char horaAcotada2[MAXIMA_LONGITUD_CADENA] = "";
    // Extraer
    strncpy(horaAcotada, obj->getHoraDesde(obj), CANTIDADCARACTERES);
    strncpy(horaAcotada2, obj->getHoraHasta(obj), CANTIDADCARACTERES);
     //obj_TipoActividad *t_act = act->getTipoActividadObj(act);
     // version con algunos datos, ver como gestionar la posibilidad de listar mas informacion.
     printf("Actividad:%d\nDia:%d\nHora Desde:%s\nHora Hasta:%s\nLugar: %s\n",
     act->getCodigo(act),
	 //t_act->getNombre(obj), 
     obj->getDia(obj), 
     horaAcotada,
     horaAcotada2,
     //obj->getCodLugar(obj);
     lug->getNombre(lug));
     // version con algunos datos, ver como gestionar la posibilidad de listar mas informacion.
     printf("\n"); 
     //destroyObj(obj);
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getCodigoHorario_Impl(void *self)
{ return *((int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static int getDiaHorario_Impl(void *self)
{ return *((int *) getValue(self,POS_DIA_HOR)); }
//----------------------------------------------------
static int getCodActHorario_Impl(void *self)
{ return *((int *) getValue(self,POS_COD_ACT_HOR)); }
//----------------------------------------------------
static char *getHoraDesdeHorario_Impl(void *self)
{ return  (char *) getValue(self,POS_HORA_DESDE_HOR); }
//----------------------------------------------------
static char *getHoraHastaHorario_Impl(void *self)
{ return  (char *) getValue(self,POS_HORA_HASTA_HOR); }
//----------------------------------------------------
static char *getCodLugarHorario_Impl(void *self)
{ return  *((int*) getValue(self,POS_LUGAR_HOR)); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setCodigoHorario_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setDiaHorario_Impl(void *self,int val)
{ setValue(self,POS_DIA_HOR,&val); }
//----------------------------------------------------
static void setCodActHorario_Impl(void *self,int val)
{ setValue(self,POS_COD_ACT_HOR,&val); }
//----------------------------------------------------
static void setHoraDesdeHorario_Impl(void *self,char *hdesde)
{ setValue(self,POS_HORA_DESDE_HOR,hdesde); }
//----------------------------------------------------
static void setHoraHastaHorario_Impl(void *self,char *hhasta)
{ setValue(self,POS_HORA_HASTA_HOR,hhasta); }
//----------------------------------------------------
static void setCodLugarHorario_Impl(void *self,int val)
{ setValue(self,POS_LUGAR_HOR,&val); }
//----------------------------------------------------
static void destroyInternalAct_Impl(void *self)
{
	obj_Horario *obj = this(self);	
	// finalizar cada referencia inicializada - no NULL
	//obj->actividad
	
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
obj_Actividad *getActividad_HorarioObj_Impl(void *self)
{
	obj_Horario *obj = this(self);	
	//acceso a la informacion relacionada
	if(obj->actividad == NULL)
	{
		obj->actividad = Actividad_new();
		obj->actividad->findbykey(obj->actividad,obj->getCodAct(obj));
		return obj->actividad;
	}
	return NULL;
}

//----------------------------------------------------
/*obj_Lugar *getLugar_HorarioObj_Impl(void *self)  
{
	obj_Horario *obj = this(self);	
	//acceso a la informacion relacionada
	if(obj->lugar == NULL)
	{
		obj->lugar = Lugar_new();
		obj->lugar->findbykey(obj->lugar,obj->getCodLugar(obj));  //no se puede hacer findkey porque lugar es una cadrena (asi esta definido en la base)
		return obj->lugar;
	}
	return NULL;
}*/

obj_Lugar *getLugar_HorarioObj_Impl(void *self)
{
	obj_Horario *obj = this(self);	
	if(obj->lugar== NULL)
	{
		obj->lugar = Lugar_new();
		obj->lugar->findbykey(obj->lugar,obj->getCodLugar(obj));
		return obj->lugar;
	}
	//acceso a la informacion relacionada
	return NULL;
}
//----------------------------------------------------
//implementacion ingresos
//----------------------------------------------------
void ingresarHorario(){
    obj_Horario *horario; 
    horario = Horario_new(); 
    int dia,codAct, codLug;  
	char horaDesde[6],horaHasta[6]; //

    printf("Ingrese el codigo del lugar\n");
    //fgets(lugar,90,stdin);
    //horario->setCodLugar(horario,codLug);
    scanf("%d",&codLug);
    horario->setCodLugar(horario,codLug);
    
	printf("Ingrese el dia\n");
    scanf("%d",&dia);
    horario->setDia(horario,dia);

    printf("Ingrese el codigo de la actividad\n");
    scanf("%d",&codAct);
    horario->setCodAct(horario,codAct);

    printf("Ingrese el horario de comienzo\n");
    fflush(stdin);
    fgets(horaDesde,6,stdin);
    horario->setHoraDesde(horario,horaDesde);

    printf("Ingrese el horario de finalizacion\n");
    fflush(stdin);
    fgets(horaHasta,6,stdin);
    horario->setHoraHasta(horario,horaHasta);
    if(!horario->saveObj(horario))
    {
        printf("Ocurrio un error al agregar un horario:\n%s\n",getLastError());
    }
    destroyObj(horario);

}
//----------------------------------------------------
//implementacion listados
//----------------------------------------------------
// Función para listar los horarios de un profesor en la semana
void listarHorariosSemana() {
    printf("[ Listado de horarios de la semana ]\n");
    
    obj_Horario *hor;
    hor = Horario_new();
        
    void *list;
    int size = hor->findAll(hor, &list, NULL);
    
    int i;
    for (i = 0; i < size; i++) {
        obj_Horario *itm = ((obj_Horario **)list)[i];
        ((Object *)itm)->toString(itm);
    }
    
    destroyObjList(list, size);
    destroyObj(hor);
}

void listarHorariosProfesorSemana() {
    printf("[ Listado de horarios del profesor en la semana ]\n");
    
    int legajo_profe;
    printf("Ingrese el codigo del legajo del profesor a buscar:\n");
    scanf("%d", &legajo_profe);
    
    obj_Horario *hor;
    hor = Horario_new();    
    obj_Actividad *act;
    act = Actividad_new();    
    char filtro[100];
    sprintf(filtro, "legajo_profe=%d", legajo_profe);    
    void *list;
    int size = act->findAll(act, &list, filtro);    
    int i;
    for (i = 0; i < size; i++) {
        obj_Actividad *itmAct = ((obj_Actividad **)list)[i];
        int codigoAct = itmAct->getCodigo(itmAct);       
        sprintf(filtro, "cod_act=%d", codigoAct);       
        void *horarioList;
        int horarioSize = hor->findAll(hor, &horarioList, filtro);        
        int j;
        for (j = 0; j < horarioSize; j++) {
            obj_Horario *itm = ((obj_Horario **)horarioList)[j];
            ((Object *)itm)->toString(itm);    
        }
        destroyObjList(horarioList, horarioSize);
    }
    destroyObjList(list, size);
    destroyObj(hor);
    destroyObj(act);
}

void listarHorariosSocioSemana() {/*
    printf("[ Listado de horarios de un socio en la semana ]\n");
    
    int nro_socio;
    printf("Ingrese el codigo del socio a buscar:\n");
    scanf("%d", &nro_socio);
    
    obj_Horario *hor;
    hor = Horario_new();    
    
    obj_ActividadSocio *actSoc;
    actSoc = ActividadSocio_new();  
    
    char filtro[100];
    sprintf(filtro, "nro_socio=%d", nro_socio);    
    void *list;
    int size = actSoc->findAll(actSoc, &list, filtro);    
    int i;
    for (i = 0; i < size; i++) {
        obj_ActividadSocio *itmActSoc = ((obj_ActividadSocio **)list)[i];
        int codigoAct = itmActSoc->getCodAct(itmActSoc);       
        sprintf(filtro, "cod_act=%d", codigoAct);       
        void *horarioList;
        int horarioSize = hor->findAll(hor, &horarioList, filtro);        
        int j;
        for (j = 0; j < horarioSize; j++) {
            obj_Horario *itm = ((obj_Horario **)horarioList)[j];
            ((Object *)itm)->toString(itm);    
        }
        destroyObjList(horarioList, horarioSize);
    }
    destroyObjList(list, size);
    destroyObj(hor);
    destroyObj(actSoc);*/
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Horario(void *self)
{
  obj_Horario *obj      = this(self);
  obj->ds  			    = &table_Horario;
  obj->constructor 	    = Horario_new;
  obj->sizeObj 		    = sizeof(obj_Horario*);
  // inicializar cada puntero a una referencia relacionada, para ver cuando se busca por el id..
  obj->actividad        = NULL;
  obj->lugar       		= NULL;
  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_HorarioImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getCodigo 		= getCodigoHorario_Impl;
  obj->getDia			= getDiaHorario_Impl;
  obj->getCodAct		= getCodActHorario_Impl;
  obj->getHoraDesde		= getHoraDesdeHorario_Impl;
  obj->getHoraHasta		= getHoraHastaHorario_Impl;
  obj->getCodLugar		= getCodLugarHorario_Impl;
  /// setters  
  obj->setCodigo 		= setCodigoHorario_Impl;
  obj->setDia			= setDiaHorario_Impl;    
  obj->setCodAct 		= setCodActHorario_Impl;
  obj->setHoraDesde		= setHoraDesdeHorario_Impl;
  obj->setHoraHasta		= setHoraHastaHorario_Impl;
  obj->setCodLugar		= setCodLugarHorario_Impl;
  //obj->setLugar			= setLugarHorario_Impl;
  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalAct_Impl;
  //---- acceso a relaciones  
  obj->getActividadObj 	= getActividad_HorarioObj_Impl;  
  obj->getLugarObj 		= getLugar_HorarioObj_Impl;  
  
  return obj;
}
//----------------------------------------------------
//constructor de Horario
obj_Horario *Horario_new()
{
  return (obj_Horario *)init_obj(sizeof(obj_Horario), init_Horario);
}
//----------------------------------------------------
