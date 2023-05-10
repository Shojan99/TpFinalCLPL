typedef enum {t_int=1,t_varchar,t_bool,t_float,t_date} tipo_dato;
#define FRMTYPE(t) (t==t_int || t==t_bool ? "%d":(t==t_float?"%f":"'%s'"))
#define POS_ID 0 
typedef struct  {
	int pos;
	void *value;
}Value;
//----------------------------------------------------
//Formato de una columna: nombre, tipo, es primary key? tamaño para varchar
typedef struct{
  char nombre[MAX];
  tipo_dato tipo;
  size_t size;
  bool pkey;
  bool autonum;
}Column;
//----------------------------------------------------
typedef struct {
	char nombre[MAX]; // nombre de la tabla
	int canColumns; //cantidad de columnas
    int cant_rows; // cantidad de filas
    void *columns; //coleccion de columnas
    void *rows; //coleccion de filas
}Table;
//----------------------------------------------------
// Estructura de pseudoobjeto genérico: Object 
typedef struct 
{
 Table *ds;
 //estructura estatica
 Value **col_value;
 size_t sizeObj;
 void *constructor;
 int  (*findAll)(void *self, void **list,char *criteria);
 void (*toString)(void *self);
 bool (*getIsNewObj)(void *self);
 bool (*saveObj)(void *self);
 void (*destroyInternal)(void *self);
 bool isNewObj;
 int (*findbykey)(void *self,int);
 void (*setIdObj)(void *self,int);
}Object;
//----------------------------------------------------
// IMPLEMENTACION PARA DAR SOPORTE A COMPORTAMIENTO GENERICO - ABSTRACT.
// Implementacion en  "orm.c"
// manejo interno de cadenas SQL para Seleccionar por criterio, por id, Insertar Actualizar 
char *selectSQL(Object *o);
char *getUpdateSQL(void *self);
char *getInsertSQL(void *self);
char *getFindByKeySQL(void *self);
// funciones para obtener detalle de error en la ejecucion de consulta.
void clearError();
void setError(char*);
char *getLastError(); 
// manejo generico para guardar un pseudo objeto
bool saveObjImpl(void *);
// manejo generico para buscar por Id
int findImpl(void *self);
// manejo generico para buscar todos los elementos de una clase dada
int findAllImpl(void *self,void **list, char *criteria);
// manejo generico para inicializar un pseudo objeto
void *init_obj(size_t, void*(*)(void *));
// manejo generico para listar
void listObj(void *objList, char *criteria, int freeObj,void(*lstFunc)(void *o));
// manejo generico para liberar memoria de un pseudo objeto
void destroyObj(void *);
// manejo generico para liberar recurso de un listado.
void destroyObjList(void **,int);
// manejo generico para obtener valor de propiedad por posicion
void *getValue(void *self,int pos);
// manejo generico para poner valor a propiedad por posicion
void setValue(void *self, int pos, void *valset);
// manejo generico para poder obtener datos por posicion
void getValueByPos(void *self,char *cad, int pos);
// manejo generico para obtener si pseudo objeto esta recientemente instanciado o recuperado desde la base de datos.
bool getIsNewObjImpl(void *self);
// manejo generico para setear el id de un pseudo-objeto
void setIdObjImpl(void *self,int val);
// manejo generico para la busqueda por Clave
int findByIdImpl(void *self, int k);
// Implementacion en "utils.c"
char *getFecha();
char *getFechaHora();
//definicion de tipos de punteros a funcion que puede tener un pseudoObjeto
typedef int  (*findAllPtr)(void *self, void **list,char *criteria);
typedef void (*toStringPtr)(void *self);
typedef bool (*getIsNewObjPtr)(void *self);
typedef bool (*saveObjPtr)(void *self);
typedef void (*destroyInternalPtr)(void *self);
typedef int  (*findbykeyPtr)(void *self,int id);
typedef void (*setIdObjPtr)(void *self,int id);
// definicion para propiedades getter y setters.
typedef int    (*getPropertyIntPtr)(void *self);
typedef char  *(*getPropertyCharPtr)(void *self);
typedef float  (*getPropertyFloatPtr)(void *self);
typedef void   (*setPropertyIntPtr)(void *self,int val);
typedef void   (*setPropertyCharPtr)(void *self,char *val);
typedef void   (*setPropertyFloatPtr)(void *self,float val);
//Macro que define la interface comun de todos las propiedades comunes a Object
#define IOBJECT Table      *ds;\
		Value              **col_value;\
		size_t             sizeObj;\
		void               *constructor;\
		findAllPtr         findAll;\
		toStringPtr        toString;\
		getIsNewObjPtr     getIsNewObj;\
		saveObjPtr         saveObj;\
		destroyInternalPtr destroyInternal;\
		bool               isNewObj;\
		findbykeyPtr       findbykey;\
		setIdObjPtr        setIdObj;\
		

