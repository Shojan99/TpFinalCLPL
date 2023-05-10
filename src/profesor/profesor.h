#ifndef PROF_INCLUDED
	#define PROF_INCLUDED
	#define CNT_COL_PROF 6
	#define POS_DNI_PROF 1
	#define POS_NOMBRES_PROF 2
	#define POS_APELLIDO_PROF 3
	#define POS_DOMICILIO_PROF 4
	#define POS_TELEFONO_PROF 5	
	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    //-- getters	    
		getPropertyIntPtr   getLegajo;		
		getPropertyIntPtr   getDni;		
		getPropertyCharPtr  getNombres;
		getPropertyCharPtr  getApellido;
		getPropertyCharPtr  getDomicilio;
		getPropertyCharPtr  getTelefono;		
	    //-- setters
		setPropertyIntPtr   setLegajo;
		setPropertyIntPtr   setDni;
		setPropertyCharPtr  setNombres;
		setPropertyCharPtr  setApellido;
		setPropertyCharPtr  setDomicilio;
		setPropertyCharPtr  setTelefono;		
	}obj_Profesor;
	// funcionalidad publica que se implementa en Profesor.c
	extern obj_Profesor *Profesor_new ();
	// meta data para acceder a las Profesores - definicion de las columnas de la tabla
	static Column cols_Profesor[CNT_COL_PROF]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"legajo",t_int,sizeof(int),true,true},	
	{"dni",t_int,sizeof(int),false,false},		
	{"nombres",t_varchar,(sizeof(char)*MAX80)+1,false,false},
	{"apellido",t_varchar,(sizeof(char)*MAX90)+1,false,false},	
	{"domicilio",t_varchar,(sizeof(char)*MAX120)+1,false,false},
	{"telefono",t_varchar,(sizeof(char)*MAX20)+1,false,false}	
	};
	// plantilla para la Profesor.
	static Table table_Profesor={"profesor",CNT_COL_PROF,0, cols_Profesor,NULL};
	typedef obj_Profesor *(*getProfesorObjPtr)(void *self);
#endif
