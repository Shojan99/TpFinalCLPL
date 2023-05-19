#include "../../includes/includelib.h"
#include "../tipo_actividad/tipo_actividad.h"

#include "importe_actividad.h"

THIS(obj_ImporteActividad)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
static void toString_ImporteActividadImpl(void *self)
{
     obj_ImporteActividad *obj=this(self);     

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
//implementacion de ingresos
//----------------------------------------------------
void ingresarImporteActividad(){
    int codTipoAct, anio, mes;
	double importe;

    obj_ImporteActividad *impAct;
    impAct = ImporteActividad_new();
    
    printf("ingrese el tipo de actividad del importe.\n");
    scanf("%d",&codTipoAct);
    impAct->setCodTipoAct(impAct,codTipoAct);   
    
    printf("ingrese el año del importe de la actividad.\n");
    scanf("%d",&anio);
    impAct->setAnio(impAct,anio);  
	
	printf("ingrese el mes del importe de la actividad.\n");
    scanf("%d",&mes);
    impAct->setMes(impAct,mes);   
    
    printf("ingrese el importe la actividad.\n");
    scanf("%lf",&importe);
    impAct->setImporte(impAct,importe);    
    if(!impAct->saveObj(impAct))
    {
        printf("Ocurrio un error al agregar el importe de la actividad:\n%s\n",getLastError());
    }
    destroyObj(impAct);
}
///*

//----------------------------------------------------
//implementacion de actualizaciones
//----------------------------------------------------
void actualizarImporteActividad(){
	obj_ImporteActividad *impAct;
	impAct = ImporteActividad_new();
	
	int codigo,codTipoAct,anio,mes,i,confirma;
	double importe;
	
	printf("[ Actualizar Importe de Actividad ]\n Ingrese el codigo del importe de la actividad a modificar.\n");
	scanf("%d",&codigo);
	
	if(impAct->findbykey(impAct, codigo) != NOT_FOUND){ 
		
		do{
		system("cls");	
		printf("Ingrese lo que desea modificar.\n1 - codigo del tipo de actividad\n2 - año\n3 - mes\n4 - importe\n");
		scanf("%d",&i);
		switch(i){
			case 1:
	
				printf("Ingrese el nuevo codigo del tipo de actividad.\n");
				scanf("%d",&codTipoAct);
				impAct->setCodTipoAct(impAct,codTipoAct);
				if(!impAct->saveObj(impAct))
			  	{
			  		printf("Ocurrio un error al actualizar el codigo del tipo de actividad:\n%s\n",getLastError());
			  	}
			  	printf("Se actualizo el codigo del tipo de actividad.\n");
			  	break;
				  	
			case 2:
				
				printf("Ingrese el nuevo anio del importe de actividad.\n");
				scanf("%d",&anio);
				impAct->setAnio(impAct,anio);
				if(!impAct->saveObj(impAct))
			  		{
			  			printf("Ocurrio un error al actualizar el nuevo anio del importe de actividad:\n%s\n",getLastError());
			  		}
			  	printf("Se actualizo el anio del importe de actividad.\n");
			  	break;	
			  		
			case 3:
			 
				printf("Ingrese el nuevo mes del tipo de actividad.\n");
				scanf("%d",&mes);
				impAct->setMes(impAct,mes);
				if(!impAct->saveObj(impAct))
			  	{
			  		printf("Ocurrio un error al actualizar el nuevo mes del importe de actividad:\n%s\n",getLastError());
			  	}
			  	printf("Se actualizo el mes del importe de actividad.\n");
			  	break;
				
			case 4:
				
				printf("Ingrese el nuevo importe.\n");
				scanf("%lf",&importe);
				impAct->setImporte(impAct, importe);
				if(!impAct->saveObj(impAct))
			  	{
			  		printf("Ocurrio un error al actualizar el importe:\n%s\n",getLastError());
			  	}
			  	printf("Se actualizo el importe.\n");
			  	break;
			default:
				printf("ingrese un valor valido.\n");
				break;
		}
		printf("Desea seguir ingresando?\n - Presione cualquier tecla para si y 0 para no.\n");
		scanf("%d",&confirma);
		}while(confirma!=0);
	}else{
		system("cls");
		printf("No se encontro el importe de actividad.\n");
	}
	destroyObj(impAct);
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
  obj->setImporte 		= setImporteImporteActividad_Impl;
  
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

