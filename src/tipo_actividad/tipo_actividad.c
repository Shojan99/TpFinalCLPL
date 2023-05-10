#include "../../includes/includelib.h"

#include "tipo_actividad.h"

THIS(obj_TipoActividad)// crea definicion de funcion this para este modulo. .. Macro en config.h
//----------------------------------------------------
static void toString_TipoActividadImpl(void *self)
{
     obj_TipoActividad *obj=this(self);
     printf("%d\n",obj->getCodigo(obj));
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getCodigoTipoActividad_Impl(void *self)
{
  return *( (int *) getValue(self,POS_ID));
}
//----------------------------------------------------
static char *getNombreTipoActividad_Impl(void *self)
{
  return  (char *) getValue(self,POS_NOMBRE_TIPOACT);
}
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setCodigoTipoActividad_Impl(void *self,int val)
{ 
	setValue(self,POS_ID,&val);
}
//----------------------------------------------------
static void setNombreTipoActividad_Impl(void *self,char *nombre)
{ 
	setValue(self,POS_NOMBRE_TIPOACT,nombre);
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
void ingresarTipoActividad(){
    obj_TipoActividad *tAct; 
    tAct = TipoActividad_new(); 
    char nombreTAct[90];
    fflush(stdin);
    printf("Ingrese tipo de actividad\n");
    fgets(nombreTAct,90,stdin);

    tAct->setNombre(tAct,nombreTAct);
    if(!tAct->saveObj(tAct))
    {
        printf("Ocurrio un error al agregar tipo de actividad:\n%s\n",getLastError());
    }
    destroyObj(tAct);

}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_TipoActividad(void *self)
{
  obj_TipoActividad *obj  = this(self);
  obj->ds  				  = &table_TipoActividad;
  obj->constructor 		  = TipoActividad_new;
  obj->sizeObj 			  = sizeof(obj_TipoActividad*);
  //incializacion de la interfaz de la entidad  
  obj->toString    		  = toString_TipoActividadImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getCodigo  		  = getCodigoTipoActividad_Impl;
  obj->getNombre		  = getNombreTipoActividad_Impl;  
  /// setters  
  obj->setCodigo     	  = setCodigoTipoActividad_Impl;
  obj->setNombre   		  = setNombreTipoActividad_Impl;  
  return obj;
}
//----------------------------------------------------
//constructor de TipoActividad
obj_TipoActividad *TipoActividad_new()
{
  return (obj_TipoActividad *)init_obj(sizeof(obj_TipoActividad), init_TipoActividad);
}
//----------------------------------------------------
void actualizarTipoActividad(){
	obj_TipoActividad *tAct; 
    tAct = TipoActividad_new(); 
    char nombreTAct[90];
    int cod,i,confirma;
    
	printf("[ Actualizar profesor ]\n Ingrese el codigo del tipo de actividad a modificar\n");
	scanf("%d",&cod);
	
	if(tAct->findbykey(tAct, cod) != NOT_FOUND){ 
		
		do{
		system("cls");	
		printf("Ingrese lo que desea modificar\n1 - nombre \n");
		scanf("%d",&i);
		switch(i){
			case 1:
				
				printf("Ingrese el nuevo nombre\n");
				fflush(stdin);
				fgets(nombreTAct,60,stdin);
				tAct->setNombre(tAct,nombreTAct);
				if(!tAct->saveObj(tAct))
			  		{
			  			printf("Ocurrio un error al actualizar el nombre:\n%s\n",getLastError());
			  		}
			  	printf("Se actualizo el nombre\n");
			  	break;	
			default:
				printf("ingrese un valor valido\n");
				break;
		}
		printf("Desea seguir ingresando?\n - Presione cualquier tecla para si y 0 para no\n");
		scanf("%d",&confirma);
		}while(confirma!=0);
	}else{
		system("cls");
		printf("No se encontro el tipo de actividad\n");
	}
	destroyObj(tAct);
	
}

