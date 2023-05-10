#ifndef IMPACT_INCLUDED
	#define IMPACT_INCLUDED
	#define CNT_COL_IMPACT 5
	// POS 0 ES EL ID DE LA CLASE
	#define POS_CODTIPOACT_IMPACT 1
	#define POS_ANIO_IMPACT 2
	#define POS_MES_IMPACT 3
	#define POS_IMPORTE_IMPACT 4

	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    getPropertyIntPtr   getCodigo;
		getPropertyIntPtr   getCodTipoAct;
		getPropertyIntPtr   getAnio;
		getPropertyIntPtr   getMes;
		getPropertyFloatPtr getImporte;
		
	    //-- setters
	    setPropertyIntPtr   setCodigo;
		setPropertyIntPtr   setCodTipoAct;
		setPropertyIntPtr   setAnio;
		setPropertyIntPtr   setMes;
		setPropertyFloatPtr setImporte;
		
	    // getter de objeto relacionado
		getTipoActividadObjPtr  getTipoActividadObj;
	    obj_TipoActividad 		*tipo_actividad;
	}obj_ImporteActividad;
	// funcionalidad publica que se implementa en actividad_socio.c
	extern obj_ImporteActividad *ImporteActividad_new ();
	// meta data para acceder a las Actividades del Socio - definicion de las columnas de la tabla
	static Column cols_ImporteActividad[CNT_COL_IMPACT]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"codigo",t_int,sizeof(int),true,true},	
	{"cod_tipo_act",t_int,sizeof(int),false,false},	
	{"anio",t_int,sizeof(int),false,false},
	{"mes",t_int,sizeof(int),false,false},
	{"importe",t_float,sizeof(float),false,false}
	};
	// plantilla para la Actividad.
	static Table table_ImporteActividad={"actividad_socio",CNT_COL_IMPACT,0, cols_ImporteActividad,NULL};
	typedef obj_ImporteActividad *(*getImporteActividadObjPtr)(void *self);
#endif

