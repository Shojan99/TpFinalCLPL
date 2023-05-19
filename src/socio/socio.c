#include "../../includes/includelib.h"
#include "../localidad/localidad.h"
#include "socio.h"
#include <stdlib.h>

THIS(obj_Socio)// crea definicion de funcion this para este modulo. .. Macro en config.h
//int confirmaImpresion=0;
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

static void toFile_SocioImpl(void *self, FILE *fd)
{
     obj_Socio *obj=this(self);     
     
     obj_Localidad *loc = obj->getLocalidadObj(obj);
     // version con algunos datos, ver como gestionar la posibilidad de listar mas informacion.
     fprintf(fd,"Nro.Socio: %d - Dni: %d - Apellido,Nombres:%s,%s - Activo:%d  - Localidad:%s\n",
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
    
    printf("Ingrese el apellido.\n");
    fflush(stdin);
    fgets(apellido, 90, stdin);
    	if(apellido[0]=='\n'){
			printf("No se ingreso un apellido.\n");
		return;
		}
    soc->setApellido(soc,apellido);
    
    printf("Ingrese el nombre.\n");
    fflush(stdin);
    fgets(nombre, 90, stdin);
    	if(nombre[0]=='\n'){
			printf("No se ingreso un nombre.\n");
		return;
		}
    soc->setNombres(soc,nombre);
    
    printf("ingrese el domicilio.\n");
    fflush(stdin);
    fgets(domicilio, 120, stdin);
    	if(domicilio[0]=='\n'){
			printf("No se ingreso un domicilio.\n");
		return;
		}
    soc->setDomicilio(soc,domicilio);
    
     printf("ingrese el dni.\n");
    scanf("%d",&dni);
    soc->setDni(soc,dni);
    
    //fflush(stdin);
    printf("ingrese una observacion.\n");
    fflush(stdin);
    fgets(observaciones,250,stdin);
    	if(nombre[0]=='\n'){
			printf("No se ingreso una observacion.\n");
		return;
				}
    soc->setObservaciones(soc,observaciones);

    printf("ingrese codigo postal.\n");
    scanf("%d",&cod_postal);
    soc->setCodPostal(soc,cod_postal);

    //fflush(stdin);
    printf("ingrese un telefono.\n");
    fflush(stdin);
    fgets(telefono,20,stdin);
    	if(nombre[0]=='\n'){
			printf("No se ingreso un telefono.\n");
		return;
				}
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
	printf("[ Actualizar socio ]\n Ingrese el numero del socio a modificar.\n");
	scanf("%d",&nro_socio);
	
	if(soc->findbykey(soc, nro_socio) != NOT_FOUND){ 
		
		do{
		//system("cls");	
		printf("Ingrese lo que desea modificar.\n1 - dni\n2 - nombre\n3 - apellido\n4 - domicilio\n5 - telefono\n6 - dar de baja\n");
		scanf("%d",&i);
		switch(i){
			case 1:
				printf("Ingrese el nuevo dni.\n");
				scanf("%d",&dni);
				soc->setDni(soc,dni);
				if(!soc->saveObj(soc))
			  		{
			  			printf("Ocurrio un error al actualizar el dni:\n%s\n",getLastError());
			  		}
			  	printf("Se actualizo el dni.\n");
			  	break;
				  	
			case 2:				
				printf("Ingrese el nuevo nombre.\n");
				fflush(stdin);
				fgets(nombre,80,stdin);
					if(nombre[0]=='\n'){
						printf("No se ingreso un nombre.\n");
					break;
				}
				soc->setNombres(soc,nombre);
				if(!soc->saveObj(soc))
			  		{
			  			printf("Ocurrio un error al actualizar el nombre:\n%s\n",getLastError());
			  		}
			  	printf("Se actualizo el nombre.\n");
			  	break;	
			  		
			case 3:
				printf("Ingrese el nuevo apellido.\n");
				fflush(stdin);
				fgets(apellido,90,stdin);
					if(apellido[0]=='\n'){
						printf("No se ingreso un apellido.\n");
					break;
				}
				soc->setApellido(soc,apellido);
				if(!soc->saveObj(soc))
				  	{
				  	printf("Ocurrio un error al actualizar el apellido:\n%s\n",getLastError());
				  	}
				printf("Se actualizo el apellido.\n");
				break;
				
			case 4:
				printf("Ingrese el nuevo domicilio.\n");
				fflush(stdin);
				fgets(domicilio,120,stdin);
					if(domicilio[0]=='\n'){
						printf("No se ingreso un domicilio.\n");
					break;
				}
				soc->setDomicilio(soc,domicilio);
				if(!soc->saveObj(soc))
				  	{
				  	printf("Ocurrio un error al actualizar el domicilio:\n%s\n",getLastError());
				  	}
				printf("Se actualizo el domicilio.\n");
				break;
			
			case 5:
				printf("Ingrese el nuevo telefono.\n");
				fflush(stdin);
				fgets(telefono,20,stdin);
					if(telefono[0]=='\n'){
						printf("No se ingreso un telefono.\n");
					break;
				}
				soc->setTelefono(soc,telefono);
				if(!soc->saveObj(soc))
				  	{
				  	printf("Ocurrio un error al actualizar el telefono:\n%s\n",getLastError());
				  	}
				printf("Se actualizo el telefono.\n");
			case 6:
				  soc->setActivo(soc, false);
				  if (!soc->saveObj(soc)) {
				    printf("Ocurrió un error al dar de baja al socio:\n%s\n", getLastError());
				  } else {
				    printf("Se dio de baja al socio.\n");
				  }
				  break;
			default:
				printf("ingrese un valor valido.\n");
				break;
		}
		printf("Desea seguir ingresando?\n - Presione cualquier tecla para si y 0 para no.\n");
		scanf("%d",&confirma);
		}while(confirma!=0);
	}else{
		printf("No se encontro el socio.\n");
	}
	destroyObj(soc);	
	
}
int comparaDescendente(const void *a, const void *b) {
   const obj_Socio *socio_a = *(const obj_Socio **)a;
    const obj_Socio *socio_b = *(const obj_Socio **)b;

    return strcmp(socio_a->getNombres(socio_a), socio_b->getNombres(socio_b));
}
int comparaAscendente(const void *a, const void * b)
{
	const obj_Socio *socio_a = *(const obj_Socio **)a;
    const obj_Socio *socio_b = *(const obj_Socio **)b;

    return strcmp(socio_b->getNombres(socio_b), socio_a->getNombres(socio_a));
}
	
void listarSocios(char filtro[]) {
    int aux;
    int i, confirma;
    void *list;
    obj_Socio *soc;
    obj_Socio *itm;
    soc = Socio_new();
    int size = soc->findAll(soc, &list, filtro);

    do {
        printf("Como desea ordenarlos? Ascendente: presione 1, Descendente: presione 2\n");
        scanf("%d", &aux);
        printf("[Listado de socios]\n");

        switch (aux) {
            case 1:
                qsort(list, size, sizeof(obj_Socio*), comparaAscendente);
                for (i = 0; i < size; ++i) {
                    itm = ((obj_Socio **)list)[i];
                    soc->toString(itm);
                }
                break;
            case 2:
                qsort(list, size, sizeof(obj_Socio*), comparaDescendente);
                for (i = 0; i < size; ++i) {
                    itm = ((obj_Socio **)list)[i];
                    soc->toString(itm);
                }
                break;
            default:
                system("cls");
                printf("Ingrese un valor valido\n");
        }
    } while (aux != 2 && aux != 1);

    // ARCHIVO
    printf("Desea crear un archivo de salida? Ingrese 0 para no, o cualquier otro valor para si\n");
    scanf("%d", &confirma);
    if (confirma) {
        FILE *archivo;
        archivo = fopen("salida.txt", "w");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo.\n");
            destroyObjList(list, size); // Liberar la memoria antes de salir
            destroyObj(soc);
            return;
        }

        for (i = 0; i < size; ++i) {
            itm = ((obj_Socio **)list)[i];
            fprintf(archivo, "Nro.Socio: %d - Dni: %d - Apellido,Nombres:%s,%s - Activo:%d\n",
                    itm->getNroSocio(itm),
                    itm->getDni(itm),
                    itm->getApellido(itm),
                    itm->getNombres(itm),
                    itm->getActivo(itm));
        }
        fclose(archivo);
        printf("Archivo de salida creado exitosamente.\n");
    }

    destroyObjList(list, size);
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
  //obj->toFile    		= toFile_SocioImpl;
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

