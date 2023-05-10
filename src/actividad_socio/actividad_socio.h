#ifndef ACTSOCIO_INCLUDED
	#define ACTSOCIO_INCLUDED
	#define CNT_COL_ACTSOCIO 5
	// POS 0 ES EL ID DE LA CLASE
	#define POS_NROSOCIO_ACTSOCIO 1
	#define POS_COD_ACT_ACTSOCIO 2
	#define POS_FECHA_INICIO_ACTSOCIO 3
	#define POS_FECHA_FIN_ACTSOCIO 4

	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    getPropertyIntPtr   getCodigo;
		getPropertyIntPtr   getNroSocio;
		getPropertyIntPtr   getCodAct;
		getPropertyCharPtr  getFechaInicio;
		getPropertyCharPtr  getFechaFin;		
	    //-- setters
	    setPropertyIntPtr   setCodigo;
		setPropertyIntPtr   setNroSocio;
		setPropertyIntPtr   setCodAct;
		setPropertyCharPtr  setFechaInicio;
		setPropertyCharPtr  setFechaFin;
		
	    // getter de objeto relacionado
		getActividadObjPtr  getActividadObj;
	    obj_Actividad 		*actividad;
	    getSocioObjPtr 		getSocioObj;
	    obj_Socio			*socio;
	}obj_ActividadSocio;
	// funcionalidad publica que se implementa en actividad_socio.c
	extern obj_ActividadSocio *ActividadSocio_new ();
	// meta data para acceder a las Actividades del Socio - definicion de las columnas de la tabla
	static Column cols_ActividadSocio[CNT_COL_ACTSOCIO]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"codigo",t_int,sizeof(int),true,true},	
	{"nro_socio",t_int,sizeof(int),false,false},	
	{"cod_act",t_int,sizeof(int),false,false},
	{"fecha_inicio",t_varchar,(sizeof(char)*MAXFECHA)+1,false,false},	
	{"fecha_fin",t_varchar,(sizeof(char)*MAXFECHA)+1,false,false}	
	};
	// plantilla para la Actividad.
	static Table table_ActividadSocio={"actividad_socio",CNT_COL_ACTSOCIO,0, cols_ActividadSocio,NULL};
	typedef obj_ActividadSocio *(*getActividadSocioObjPtr)(void *self);
#endif

