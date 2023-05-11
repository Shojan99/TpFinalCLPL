#include "../../includes/includelib.h"

#include "lugar.h"

THIS(obj_Lugar)// crea definicion de funcion this para este modulo. .. Macro en config.h
//----------------------------------------------------
static void toString_LugarImpl(void *self)
{
     obj_Lugar *obj=this(self);
     printf("%d\n",obj->getCodigo(obj));
}
//----------------------------------------------------
//implementacion de getters
//----------------------------------------------------
static int getCodigoLugar_Impl(void *self)
{
  return *( (int *) getValue(self,POS_ID));
}
//----------------------------------------------------
static char *getNombreLugar_Impl(void *self)
{
  return  (char *) getValue(self,POS_NOMBRE_LUGAR);
}
//----------------------------------------------------
//implementacion setters
//----------------------------------------------------
static void setCodigoLugar_Impl(void *self,int val)
{ 
	setValue(self,POS_ID,&val);
}
//----------------------------------------------------
static void setNombreLugar_Impl(void *self,char *nombre)
{ 
	setValue(self,POS_NOMBRE_LUGAR,nombre);
}
//----------------------------------------------------
//implementacion de relaciones
//----------------------------------------------------
void ingresarLugar(){
    obj_Lugar *lug; 
    lug = Lugar_new(); 
    char nombreLugar[90];
    fflush(stdin);
    printf("Ingrese el nombre del lugar\n");
    fgets(nombreLugar,90,stdin);

    lug->setNombre(lug,nombreLugar);
    if(!lug->saveObj(lug))
    {
        printf("Ocurrio un error al agregar el lugar:\n%s\n",getLastError());
    }
    destroyObj(lug);

}
//----------------------------------------------------
//implementacion constructor
//----------------------------------------------------
static void *init_Lugar(void *self)
{
  obj_Lugar *obj          = this(self);
  obj->ds  				  = &table_Lugar;
  obj->constructor 		  = Lugar_new;
  obj->sizeObj 			  = sizeof(obj_Lugar*);
  //incializacion de la interfaz de la entidad  
  obj->toString    		  = toString_LugarImpl;
  // Inicializar handlers de getters y setters
  /// getters
  obj->getCodigo  		  = getCodigoLugar_Impl;
  obj->getNombre		  = getNombreLugar_Impl;  
  /// setters  
  obj->setCodigo     	  = setCodigoLugar_Impl;
  obj->setNombre   		  = setNombreLugar_Impl;  
  return obj;
}
//----------------------------------------------------
//constructor de TipoActividad
obj_Lugar *Lugar_new()
{
  return (obj_Lugar *)init_obj(sizeof(obj_Lugar), init_Lugar);
}
//----------------------------------------------------
