#ifndef CUOT_INCLUDED
	#define CUOT_INCLUDED
	#define CNT_COL_CUOT 8
	// POS 0 ES EL ID DE LA CLASE
	#define POS_COD_ACT_SOC_CUOT 1
	#define POS_ANIO_CUOT 2
	#define POS_MES_CUOT 3
	#define POS_EST_CUOT 4
	#define POS_IMPORTE_CUOT 5
	#define POS_FVENC_CUOT 6
	#define POS_FPAGO_CUOT 7

	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    getPropertyIntPtr   getCodigo;
		getPropertyIntPtr   getCodActSocio;
		getPropertyIntPtr   getAnio;
		getPropertyIntPtr   getMes;
		getPropertyCharPtr  getEstado;
		getPropertyFloatPtr getImporte;
		getPropertyCharPtr  getFechaVenc;
		getPropertyCharPtr  getFechaPago;
		
	    //-- setters
	    setPropertyIntPtr   setCodigo;
		setPropertyIntPtr   setCodActSocio;
		setPropertyIntPtr   setAnio;
		setPropertyIntPtr   setMes;
		setPropertyCharPtr  setEstado;
		setPropertyFloatPtr setImporte;
		setPropertyCharPtr  setFechaVenc;
		setPropertyCharPtr  setFechaPago;
		
	    // getter de objeto relacionado
		getActividadSocioObjPtr  getActividadSocioObj;
	    obj_ActividadSocio *actividad_socio;
	}obj_Cuotas;
	// funcionalidad publica que se implementa en actividad_socio.c
	extern obj_Cuotas *Cuotas_new ();
	// meta data para acceder a las Cuotas  del Socio - definicion de las columnas de la tabla
	static Column cols_Cuotas[CNT_COL_CUOT]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"codigo",t_int,sizeof(int),true,true},	
	{"cod_act_socio",t_int,sizeof(int),false,false},	
	{"anio",t_int,sizeof(int),false,false},
	{"mes",t_int,sizeof(int),false,false},
	{"estado",t_varchar,(sizeof(char)*MAX1)+1,false,false},	
	{"importe",t_float,sizeof(float),false,false},
	{"fecha_venc",t_varchar,(sizeof(char)*MAXFECHA)+1,false,false},	
	{"fecha_pago",t_varchar,(sizeof(char)*MAXFECHA)+1,false,false},	
	};
	// plantilla para la Actividad.
	static Table table_Cuotas={"cuotas",CNT_COL_CUOT,0, cols_Cuotas,NULL};
	typedef obj_Cuotas *(*getCuotasObjPtr)(void *self);
#endif

