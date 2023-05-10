#ifndef ACT_INCLUDED
	#define ACT_INCLUDED
	#define CNT_COL_ACT 5
	// POS 0 ES EL ID DE LA CLASE
	#define POS_CODTIPO_ACT 1
	#define POS_LEGAJO_PROFE_ACT 2
	#define POS_FECHA_DESDE_ACT 3
	#define POS_FECHA_FIN_ACT 4

	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    getPropertyIntPtr   getCodigo;
		getPropertyIntPtr   getCodTipoAct;
		getPropertyIntPtr   getLegajoProfe;
		getPropertyCharPtr  getFechaDesde;
		getPropertyCharPtr  getFechaFin;		
	    //-- setters
	    setPropertyIntPtr   setCodigo;
		setPropertyIntPtr   setCodTipoAct;
		setPropertyIntPtr   setLegajoProfe;
		setPropertyCharPtr  setFechaDesde;
		setPropertyCharPtr  setFechaFin;
		
	    // getter de objeto relacionado
		getTipoActividadObjPtr  getTipoActividadObj;
	    obj_TipoActividad *tipo_actividad;
	    getProfesorObjPtr getProfesorObj;
	    obj_Profesor *profesor;
	}obj_Actividad;
	// funcionalidad publica que se implementa en Actividad.c
	extern obj_Actividad *Actividad_new ();
	// meta data para acceder a las Actividades - definicion de las columnas de la tabla
	static Column cols_Actividad[CNT_COL_ACT]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"codigo",t_int,sizeof(int),true,true},	
	{"cod_tipo_act",t_int,sizeof(int),false,false},	
	{"legajo_profe",t_int,sizeof(int),false,false},
	{"fecha_desde",t_varchar,(sizeof(char)*MAXFECHA)+1,false,false},	
	{"fecha_fin",t_varchar,(sizeof(char)*MAXFECHA)+1,false,false}	
	};
	// plantilla para la Actividad.
	static Table table_Actividad={"actividad",CNT_COL_ACT,0, cols_Actividad,NULL};
	typedef obj_Actividad *(*getActividadObjPtr)(void *self);
#endif

