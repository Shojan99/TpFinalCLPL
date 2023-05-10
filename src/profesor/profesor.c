#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "profesor.h"

THIS(obj_Profesor)// crea definicion de funcion this para este modulo. .. Macro en config.h
//----------------------------------------------------
static void toString_ProfesorImpl(void *self)
{
     obj_Profesor *obj=this(self);          
     printf("DNI: %d  - ApyNom:%s, %s \n",
	 obj->getDni(obj),
	 obj->getApellido(obj),
	 obj->getNombres(obj)
	 );
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getLegajoProfesor_Impl(void *self)
{ return *((int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static int getDniProfesor_Impl(void *self)
{ return *((int *) getValue(self,POS_DNI_PROF)); }
//----------------------------------------------------
static char *getNombresProfesor_Impl(void *self)
{ return  (char *) getValue(self,POS_NOMBRES_PROF); }
//----------------------------------------------------
static char *getApellidoProfesor_Impl(void *self)
{ return  (char *) getValue(self,POS_APELLIDO_PROF); }
//----------------------------------------------------
static char *getDomicilioProfesor_Impl(void *self)
{ return  (char *) getValue(self,POS_DOMICILIO_PROF); }
//----------------------------------------------------
static char *getTelefonoProfesor_Impl(void *self)
{ return  (char *) getValue(self,POS_TELEFONO_PROF); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setLegajoProfesor_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setDniProfesor_Impl(void *self,int val)
{ setValue(self,POS_DNI_PROF,&val); }
//----------------------------------------------------
static void setNombresProfesor_Impl(void *self,char *nombres_Profesor)
{ setValue(self,POS_NOMBRES_PROF,nombres_Profesor); }
//----------------------------------------------------
static void setApellidoProfesor_Impl(void *self,char *apellido_Profesor)
{ setValue(self,POS_APELLIDO_PROF,apellido_Profesor); }
//----------------------------------------------------
static void setDomicilioProfesor_Impl(void *self,char *domicilio_Profesor)
{ setValue(self,POS_DOMICILIO_PROF,domicilio_Profesor); }
//----------------------------------------------------
static void setTelefonoProfesor_Impl(void *self,char *telefono_Profesor)
{ setValue(self,POS_TELEFONO_PROF,telefono_Profesor); }
//----------------------------------------------------
static void destroyInternalCli_Impl(void *self)
{
	///
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
void ingresarProfesor() //consultar el static void!!!
{
    obj_Profesor *prof;
    prof = Profesor_new();
    int dni;
    char nombre[80], apellido[90], domicilio[120], telefono[20];

    //prof->setActivo(soc,true);
    
    printf("Ingrese el apellido\n");
    fflush(stdin);
    fgets(apellido, 90, stdin);
    prof->setApellido(prof,apellido);
    
    printf("Ingrese el nombre\n");
    fflush(stdin);
    fgets(nombre, 90, stdin);
    prof->setNombres(prof,nombre);
    
    printf("ingrese el domicilio\n");
    fflush(stdin);
    fgets(domicilio, 120, stdin);
    prof->setDomicilio(prof,domicilio);
    
     printf("ingrese el dni\n");
    scanf("%d",&dni);
    prof->setDni(prof,dni);

    //fflush(stdin);
    printf("ingrese un telefono\n");
    fflush(stdin);
    fgets(telefono,20,stdin);
    prof->setTelefono(prof,telefono);
    
    //soc->setMoroso(soc,false);

    if(!prof->saveObj(prof))
    {
        printf("Ocurrio un error al agregar Localidad:\n%s\n",getLastError());
    }
    destroyObj(prof);
}
// shojan te quiero
void listarProfesores(){
    printf("[ Listado de profesores ]\n");
    int i;
     void *list;
      obj_Profesor *prof;    
      obj_Profesor *itm;
      prof = Profesor_new();
      int size = prof->findAll(prof,&list,NULL);
      for(i=0;i<size;++i)
      {
            itm = ((Object **)list)[i];    
        ((Object *)itm)->toString(itm);
     }
     destroyObjList(list,size);
      destroyObj(prof);
}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Profesor(void *self)
{
  obj_Profesor *obj     = this(self);  
  obj->ds  			    = &table_Profesor;
  obj->constructor 	    = Profesor_new;
  obj->sizeObj 		    = sizeof(obj_Profesor*);
  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_ProfesorImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getLegajo  	  	= getLegajoProfesor_Impl;  
  obj->getDni  	  		= getDniProfesor_Impl;    
  obj->getNombres 		= getNombresProfesor_Impl;
  obj->getApellido 		= getApellidoProfesor_Impl;
  obj->getDomicilio 	= getDomicilioProfesor_Impl;
  obj->getTelefono 		= getTelefonoProfesor_Impl;      
  /// setters  
  obj->setLegajo   		= setLegajoProfesor_Impl;
  obj->setDni     		= setDniProfesor_Impl;
  obj->setNombres 		= setNombresProfesor_Impl;
  obj->setApellido 		= setApellidoProfesor_Impl;
  obj->setDomicilio 	= setDomicilioProfesor_Impl;
  obj->setTelefono 		= setTelefonoProfesor_Impl;  
  
  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalCli_Impl;
  
  return obj;
}
//----------------------------------------------------
//constructor de Profesor
obj_Profesor *Profesor_new()
{
  return (obj_Profesor *)init_obj(sizeof(obj_Profesor), init_Profesor);
}
//----------------------------------------------------
void actualizarProfesor(){
	obj_Profesor *prof;
    prof = Profesor_new();
    int dni,i,confirma,legajo;
    char nombre[80], apellido[90], domicilio[120], telefono[20]; 
	printf("[ Actualizar profesor ]\n Ingrese el legajo del profesor a modificar\n");
	scanf("%d",&legajo);
	
	if(prof->findbykey(prof, legajo) != NOT_FOUND){ 
		
		do{
		system("cls");	
		printf("Ingrese lo que desea modificar\n1 - dni\n2 - nombre\n3 - apellido\n4 - domicilio\n5 - telefono\n");
		scanf("%d",&i);
		switch(i){
			case 1:
	
				printf("Ingrese el nuevo dni\n");
				scanf("%d",&dni);
				prof->setDni(prof,dni);
				if(!prof->saveObj(prof))
			  		{
			  			printf("Ocurrio un error al actualizar el dni:\n%s\n",getLastError());
			  		}
			  	printf("Se actualizo el dni\n");
			  	break;
				  	
			case 2:
				
				printf("Ingrese el nuevo nombre\n");
				fflush(stdin);
				fgets(nombre,80,stdin);
				prof->setNombres(prof,nombre);
				if(!prof->saveObj(prof))
			  		{
			  			printf("Ocurrio un error al actualizar el nombre:\n%s\n",getLastError());
			  		}
			  	printf("Se actualizo el nombre\n");
			  	break;	
			  		
			case 3:
			 
				printf("Ingrese el nuevo apellido\n");
				fflush(stdin);
				fgets(apellido,90,stdin);
				prof->setApellido(prof,apellido);
				if(!prof->saveObj(prof))
				  	{
				  	printf("Ocurrio un error al actualizar el apellido:\n%s\n",getLastError());
				  	}
				printf("Se actualizo el apellido\n");
				break;
				
			case 4:
				
				printf("Ingrese el nuevo domicilio\n");
				fflush(stdin);
				fgets(domicilio,120,stdin);
				prof->setDomicilio(prof,domicilio);
				if(!prof->saveObj(prof))
				  	{
				  	printf("Ocurrio un error al actualizar el domicilio:\n%s\n",getLastError());
				  	}
				printf("Se actualizo el domicilio\n");
				break;
			
			case 5:
				
				printf("Ingrese el nuevo telefono\n");
				fflush(stdin);
				fgets(telefono,20,stdin);
				prof->setTelefono(prof,telefono);
				if(!prof->saveObj(prof))
				  	{
				  	printf("Ocurrio un error al actualizar el telefono:\n%s\n",getLastError());
				  	}
				printf("Se actualizo el telefono\n");
			default:
				printf("ingrese un valor valido\n");
				break;
		}
		printf("Desea seguir ingresando?\n - Presione cualquier tecla para si y 0 para no\n");
		scanf("%d",&confirma);
		}while(confirma!=0);
	}else{
		system("cls");
		printf("No se encontro el profesor\n");
	}
	destroyObj(prof);
}
