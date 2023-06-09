#include "../../includes/includelib.h"
#include "localidad.h"

THIS(obj_Localidad)// crea definicion de funcion this para este modulo. .. Macro en config.h
//----------------------------------------------------
static void toString_LocalidadImpl(void *self)
{
     obj_Localidad *obj=this(self);
     printf("Cod Localidad: %d  Nom.Localidad:%s \n",
	 obj->getId(obj),
	 obj->getNombre(obj)
	 );
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getIdLocalidad_Impl(void *self)
{
  return *( (int *) getValue(self,POS_ID));
}
//----------------------------------------------------
static char *getNombreLocalidad_Impl(void *self)
{
  return  (char *) getValue(self,POS_DESCRIPCION);
}
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setIdLocalidad_Impl(void *self,int val)
{ 
	setValue(self,POS_ID,&val);
}
//----------------------------------------------------
static void setNombreLocalidad_Impl(void *self,char *descripcion_Localidad)
{ 
	setValue(self,POS_DESCRIPCION,descripcion_Localidad);
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
void ingresarLocalidad()
{
    obj_Localidad *loc;
    loc = Localidad_new();
	int codigopostal;
    char nombre[60];
    
    printf("Ingrese el codigo postal de la localidad.\n");
    scanf("%d",&codigopostal);
    loc->setId(loc, codigopostal);
    
    printf("Ingrese el nombre de la localidad.\n");
    fflush(stdin);
    fgets(nombre, 60, stdin);
    	if(nombre[0]=='\n'){
			printf("No se ingreso un nombre.\n");
			return;
			}
    loc->setNombre(loc,nombre);

    if(!loc->saveObj(loc))
    {
        printf("Ocurrio un error al agregar Localidad:\n%s\n",getLastError());
    }
    destroyObj(loc);
}

void listarLocalidades(){
    printf("[ Listado de localidades ]\n");
    int i;
    void *list;
    obj_Localidad *loc;    
    obj_Localidad *itm;
    loc = Localidad_new();
    int size = loc->findAll(loc,&list,NULL);
    for(i=0;i<size;++i)
    {
    	itm = ((Object **)list)[i];
    	((Object *)itm)->toString(itm);
    }
    destroyObjList(list,size);
    destroyObj(loc);
    
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Localidad(void *self)
{
  obj_Localidad *obj 	  = this(self);
  obj->ds  				  = &table_Localidad;
  obj->constructor 		  = Localidad_new;
  obj->sizeObj 			  = sizeof(obj_Localidad*);
  //incializacion de la interfaz de la entidad  
  obj->toString    		  = toString_LocalidadImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getId  	  		  = getIdLocalidad_Impl;
  obj->getNombre		  = getNombreLocalidad_Impl;  
  /// setters  
  obj->setId     		  = setIdLocalidad_Impl;
  obj->setNombre   		  = setNombreLocalidad_Impl;  
  return obj;
}
//----------------------------------------------------
//constructor de Localidad
obj_Localidad *Localidad_new()
{
  return (obj_Localidad *)init_obj(sizeof(obj_Localidad), init_Localidad);
}
//----------------------------------------------------
void actualizarLocalidad(){
	obj_Localidad *loc;
    loc = Localidad_new();
    int cod,i,confirma;
    char nombre[60]; 
	printf("[ Actualizar localidad ]\n Ingrese el codigo postal de la localidad a modificar.\n");
	scanf("%d",&cod);
	
	if(loc->findbykey(loc, cod) != NOT_FOUND){ 
		
		do{
		system("cls");	
		printf("Ingrese lo que desea modificar\n1 - codigo postal\n2 - nombre\n");
		scanf("%d",&i);
		switch(i){
			case 1:
	
				printf("Ingrese el nuevo codigo postal.\n");
				scanf("%d",&cod);
			
				if(loc->findbykey(loc,cod) != NOT_FOUND)
  				{
  				loc->toString(loc);
		  		system("cls");
		  		printf("Ya existe la localidad\n");
				}else{
					loc->setId(loc,cod);
					if(!loc->saveObj(loc))
				  		{
				  			printf("Ocurrio un error al actualizar el codigo postal:\n%s\n",getLastError());
				  		}
				  	printf("Se actualizo el codigo postal.\n");
				}
			  	break;
				  	
			case 2:
				
				printf("Ingrese el nuevo nombre.\n");
				fflush(stdin);
				fgets(nombre,60,stdin);
				if(nombre[0]=='\n'){
					printf("No se ingreso un nombre.\n");
					break;
				}
				
				loc->setNombre(loc,nombre);
				if(!loc->saveObj(loc))
			  		{
			  			printf("Ocurrio un error al actualizar el nombre:\n%s\n",getLastError());
			  		}
			  	printf("Se actualizo el nombre.\n");
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
		printf("No se encontro la localidad.\n");
	}
	destroyObj(loc);
}
