#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "socio.h"

THIS(obj_Socio)// crea definicion de funcion this para este modulo. .. Macro en config.h

//----------------------------------------------------
static void toString_SocioImpl(void *self)
{
     obj_Socio *obj=this(self);     
     obj_Localidad *loc = obj->getLocalidadObj(obj);
     // version con algunos datos, ver como gestionar la posibilidad de listar mas informacion.
     printf("Nro.Socio: %d - Dni: %d - Apellido,Nombres:%s,%s - Activo:%d  - Localidad:%s\n",
	 obj->getNroSocio(obj), 
	 obj->getDni(obj),
	 obj->getApellido(obj), 
	 obj->getNombres(obj),
	 obj->getActivo(obj),
	 loc->getNombre(loc)
	 ); // 1:true(en la base) - 0:false(en la base) -- activo / moroso
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getNroSocio_Impl(void *self)
{ return *((int *) getValue(self,POS_ID)); }
//----------------------------------------------------
static int getDniSocio_Impl(void *self)
{ return *((int *) getValue(self,POS_DNI_SOC)); }
//----------------------------------------------------
static char *getNombresSocio_Impl(void *self)
{ return  (char *) getValue(self,POS_NOMBRES_SOC); }
//----------------------------------------------------
static char *getApellidoSocio_Impl(void *self)
{ return  (char *) getValue(self,POS_APELLIDO_SOC); }
//----------------------------------------------------
static char *getDomicilioSocio_Impl(void *self)
{ return  (char *) getValue(self,POS_DOMICILIO_SOC); }
//----------------------------------------------------
static char *getTelefonoSocio_Impl(void *self)
{ return  (char *) getValue(self,POS_TELEFONO_SOC); }
//----------------------------------------------------
static int getCodPostalSocio_Impl(void *self)
{ return *( (int *) getValue(self,POS_COD_POSTAL_SOC)); }
//----------------------------------------------------
static char *getObservacionesSocio_Impl(void *self)
{ return  (char *) getValue(self,POS_OBS_SOC); }
//----------------------------------------------------
static int getActivoSocio_Impl(void *self)
{ return *( (int *) getValue(self,POS_ACTIVO_SOC)); }
//----------------------------------------------------
static int getMorosoSocio_Impl(void *self)
{ return *( (int *) getValue(self,POS_MOROSO_SOC)); }
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setNroSocio_Impl(void *self,int val)
{ setValue(self,POS_ID,&val); }
//----------------------------------------------------
static void setDniSocio_Impl(void *self,int val)
{ setValue(self,POS_DNI_SOC,&val); }
//----------------------------------------------------
static void setNombresSocio_Impl(void *self,char *nombres_Socio)
{ setValue(self,POS_NOMBRES_SOC,nombres_Socio); }
//----------------------------------------------------
static void setApellidoSocio_Impl(void *self,char *apellido_Socio)
{ setValue(self,POS_APELLIDO_SOC,apellido_Socio); }
//----------------------------------------------------
static void setDomicilioSocio_Impl(void *self,char *domicilio_Socio)
{ setValue(self,POS_DOMICILIO_SOC,domicilio_Socio); }
//----------------------------------------------------
static void setTelefonoSocio_Impl(void *self,char *telefono_Socio)
{ setValue(self,POS_TELEFONO_SOC,telefono_Socio); }
//----------------------------------------------------
static void setCodPostalSocio_Impl(void *self,int val)
{ setValue(self,POS_COD_POSTAL_SOC,&val); }
//----------------------------------------------------
static void setObservacionesSocio_Impl(void *self,char *obs)
{ setValue(self,POS_OBS_SOC,obs); }
//----------------------------------------------------
static void setActivoSocio_Impl(void *self,int val)
{ setValue(self,POS_ACTIVO_SOC,&val); }
//----------------------------------------------------
static void setMorosoSocio_Impl(void *self,int val)
{ setValue(self,POS_MOROSO_SOC,&val); }
//----------------------------------------------------
static void destroyInternalCli_Impl(void *self)
{
	obj_Socio *obj = this(self);	
	// finalizar cada referencia inicializada - no NULL
	if(obj->localidad!=NULL)
	{
		destroyObj(obj->localidad);
		obj->localidad= NULL;
	}	
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
/// ....
obj_Localidad *getLocalidadSocioObj_Impl(void *self)
{
	obj_Socio *obj = this(self);	
	if(obj->localidad == NULL)
	{
		obj->localidad = Localidad_new();
		obj->localidad->findbykey(obj->localidad,obj->getCodPostal(obj));
		return obj->localidad;
	}
	//acceso a la informacion relacionada
	return NULL;
}
//----------------------------------------------------
//implementacion ingresos
//----------------------------------------------------
void ingresarSocio() //consultar el static void!!!
{
    obj_Socio *soc;
    soc = Socio_new();
    int cod_postal, dni;
    char nombre[80], apellido[90], domicilio[120], telefono[20], observaciones[250];

    soc->setActivo(soc,true);
    
    printf("Ingrese el apellido\n");
    fflush(stdin);
    fgets(apellido, 90, stdin);
    soc->setApellido(soc,apellido);
    
    printf("Ingrese el nombre\n");
    fflush(stdin);
    fgets(nombre, 90, stdin);
    soc->setNombres(soc,nombre);
    
    printf("ingrese el domicilio\n");
    fflush(stdin);
    fgets(domicilio, 120, stdin);
    soc->setDomicilio(soc,domicilio);
    
     printf("ingrese el dni\n");
    scanf("%d",&dni);
    soc->setDni(soc,dni);
    
    //fflush(stdin);
    printf("ingrese una observacion\n");
    fflush(stdin);
    fgets(observaciones,250,stdin);
    soc->setObservaciones(soc,observaciones);

    printf("ingrese codigo postal\n");
    scanf("%d",&cod_postal);
    soc->setCodPostal(soc,cod_postal);

    //fflush(stdin);
    printf("ingrese un telefono\n");
    fflush(stdin);
    fgets(telefono,20,stdin);
    soc->setTelefono(soc,telefono);
    
    soc->setMoroso(soc,false);

    if(!soc->saveObj(soc))
    {
        printf("Ocurrio un error al agregar Socio:\n%s\n",getLastError());
    }
    destroyObj(soc);
}

void actualizarSocio(){
	int i,nro_socio,cod_postal, dni,confirma;
	char nombre[80], apellido[90], domicilio[120], telefono[20];
	obj_Socio *soc; 
	soc = Socio_new(); 
	printf("[ Actualizar socio ]\n Ingrese el numero del socio a modificar\n");
	scanf("%d",&nro_socio);
	
	if(soc->findbykey(soc, nro_socio) != NOT_FOUND){ 
		
		do{
		//system("cls");	
		printf("Ingrese lo que desea modificar\n1 - dni\n2 - nombre\n3 - apellido\n4 - domicilio\n5 - telefono\n");
		scanf("%d",&i);
		switch(i){
			case 1:
				printf("Ingrese el nuevo dni\n");
				scanf("%d",&dni);
				soc->setDni(soc,dni);
				if(!soc->saveObj(soc))
			  		{
			  			printf("Ocurrio un error al actualizar el dni:\n%s\n",getLastError());
			  		}
			  	printf("Se actualizo el dni\n");
			  	break;
				  	
			case 2:				
				printf("Ingrese el nuevo nombre\n");
				fflush(stdin);
				fgets(nombre,80,stdin);
				soc->setNombres(soc,nombre);
				if(!soc->saveObj(soc))
			  		{
			  			printf("Ocurrio un error al actualizar el nombre:\n%s\n",getLastError());
			  		}
			  	printf("Se actualizo el nombre\n");
			  	break;	
			  		
			case 3:
				printf("Ingrese el nuevo apellido\n");
				fflush(stdin);
				fgets(apellido,90,stdin);
				soc->setApellido(soc,apellido);
				if(!soc->saveObj(soc))
				  	{
				  	printf("Ocurrio un error al actualizar el apellido:\n%s\n",getLastError());
				  	}
				printf("Se actualizo el apellido\n");
				break;
				
			case 4:
				printf("Ingrese el nuevo domicilio\n");
				fflush(stdin);
				fgets(domicilio,120,stdin);
				soc->setDomicilio(soc,domicilio);
				if(!soc->saveObj(soc))
				  	{
				  	printf("Ocurrio un error al actualizar el domicilio:\n%s\n",getLastError());
				  	}
				printf("Se actualizo el domicilio\n");
				break;
			
			case 5:
				printf("Ingrese el nuevo telefono\n");
				fflush(stdin);
				fgets(telefono,20,stdin);
				soc->setTelefono(soc,telefono);
				if(!soc->saveObj(soc))
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
		printf("No se encontro el socio\n");
	}
	destroyObj(soc);	
	
}

void listarSocios(char filtro[]){
    printf("[ Listado de socios ]\n");
    int i;
    void *list;
    obj_Socio *soc;
    obj_Socio *itm;
    soc = Socio_new();
    int size = soc->findAll(soc,&list,filtro);
    for(i=0;i<size;++i)
    {
    	itm = ((Object **)list)[i];
    	((Object *)itm)->toString(itm);

    }
    destroyObjList(list,size);
    destroyObj(soc);
}

//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Socio(void *self)
{
  obj_Socio *obj      = this(self);
  obj->ds  			    = &table_Socio;
  obj->constructor 	    = Socio_new;
  obj->sizeObj 		    = sizeof(obj_Socio*);
  // inicializar cada puntero a una referencia relacionada, para ver cuando se busca por el id..
  obj->localidad 	    = NULL;
  //incializacion de la interfaz de la entidad
  obj->toString    		= toString_SocioImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getNroSocio 		= getNroSocio_Impl;
  obj->getDni  	  		= getDniSocio_Impl;
  obj->getNombres 		= getNombresSocio_Impl;
  obj->getApellido 		= getApellidoSocio_Impl;
  obj->getDomicilio 	= getDomicilioSocio_Impl;
  obj->getTelefono 		= getTelefonoSocio_Impl;    
  obj->getCodPostal 	= getCodPostalSocio_Impl;  
  obj->getObservaciones	= getObservacionesSocio_Impl;  
  obj->getActivo 		= getActivoSocio_Impl;
  obj->getMoroso 		= getMorosoSocio_Impl;
  /// setters  
  obj->setNroSocio 		= setNroSocio_Impl;
  obj->setDni     		= setDniSocio_Impl;    
  obj->setNombres 		= setNombresSocio_Impl;
  obj->setApellido 		= setApellidoSocio_Impl;
  obj->setDomicilio 	= setDomicilioSocio_Impl;
  obj->setTelefono 		= setTelefonoSocio_Impl;  
  obj->setCodPostal     = setCodPostalSocio_Impl;  
  obj->setObservaciones = setObservacionesSocio_Impl;
  obj->setActivo 		= setActivoSocio_Impl;
  obj->setMoroso 		= setMorosoSocio_Impl;
  // implementar detroy internal para liberar recursos  
  obj->destroyInternal 	= destroyInternalCli_Impl;
  //---- acceso a relaciones  
  obj->getLocalidadObj 	= getLocalidadSocioObj_Impl;  
  return obj;
}
//----------------------------------------------------
//constructor de Socio
obj_Socio *Socio_new()
{
  return (obj_Socio *)init_obj(sizeof(obj_Socio), init_Socio);
}
//----------------------------------------------------

