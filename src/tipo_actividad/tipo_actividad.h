#ifndef TIPOACT_INCLUDED
	#define TIPOACT_INCLUDED
	#define CNT_COL_TIPOACT 2
	// POS 0 ES EL ID DE LA CLASE
	#define POS_NOMBRE_TIPOACT 1	

	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    getPropertyIntPtr   getCodigo;
		getPropertyCharPtr  getNombre;		
	    //-- setters
	    setPropertyIntPtr   setCodigo;		
		setPropertyCharPtr  setNombre;		
		
	}obj_TipoActividad;
	// funcionalidad publica que se implementa en TipoActividad.c
	extern obj_TipoActividad *TipoActividad_new ();
	// meta data para acceder a las TipoActividades - definicion de las columnas de la tabla
	static Column cols_TipoActividad[CNT_COL_TIPOACT]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"codigo",t_int,sizeof(int),true,true},		
	{"nombre",t_varchar,(sizeof(char)*MAX90)+1,false,false}	
	};
	// plantilla para la TipoActividad.
	static Table table_TipoActividad={"tipo_actividad",CNT_COL_TIPOACT,0, cols_TipoActividad,NULL};
	typedef obj_TipoActividad *(*getTipoActividadObjPtr)(void *self);
#endif

