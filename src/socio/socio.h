#ifndef SOC_INCLUDED
	#define SOC_INCLUDED
	#define CNT_COL_SOC 10
	// POS 0 ES EL ID DE LA CLASE
	#define POS_DNI_SOC 1
	#define POS_NOMBRES_SOC 2
	#define POS_APELLIDO_SOC 3
	#define POS_DOMICILIO_SOC 4
	#define POS_TELEFONO_SOC 5
	#define POS_COD_POSTAL_SOC 6
	#define POS_OBS_SOC 7
	#define POS_ACTIVO_SOC 8
	#define POS_MOROSO_SOC 9
	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    getPropertyIntPtr   getNroSocio;
		getPropertyIntPtr   getDni;
		getPropertyCharPtr  getNombres;
		getPropertyCharPtr  getApellido;
		getPropertyCharPtr  getDomicilio;
		getPropertyCharPtr  getTelefono;
		getPropertyIntPtr   getCodPostal;
		getPropertyCharPtr  getObservaciones;
		getPropertyIntPtr   getActivo;
		getPropertyIntPtr   getMoroso;
	    //-- setters
	    setPropertyIntPtr   setNroSocio;
		setPropertyIntPtr   setDni;
		setPropertyCharPtr  setNombres;
		setPropertyCharPtr  setApellido;
		setPropertyCharPtr  setDomicilio;
		setPropertyCharPtr  setTelefono;
		setPropertyIntPtr   setCodPostal;		
		setPropertyCharPtr  setObservaciones;	
		setPropertyIntPtr   setActivo;
		setPropertyIntPtr   setMoroso;
	    // getter de objeto relacionado
		getLocalidadObjPtr  getLocalidadObj;
	    obj_Localidad 		*localidad;
	}obj_Socio;
	// funcionalidad publica que se implementa en Socio.c
	extern obj_Socio *Socio_new ();
	// meta data para acceder a las Socios - definicion de las columnas de la tabla
	static Column cols_Socio[CNT_COL_SOC]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"nro_socio",t_int,sizeof(int),true,true},	
	{"dni",t_int,sizeof(int),false,false},	
	{"nombres",t_varchar,(sizeof(char)*MAX80)+1,false,false},
	{"apellido",t_varchar,(sizeof(char)*MAX90)+1,false,false},	
	{"domicilio",t_varchar,(sizeof(char)*MAX120)+1,false,false},
	{"telefono",t_varchar,(sizeof(char)*MAX20)+1,false,false},
	{"cod_postal",t_int,sizeof(int),false,false},
	{"observaciones",t_varchar,(sizeof(char)*MAXOBS)+1,false,false},
	{"activo",t_bool,sizeof(int),false,false},
	{"moroso",t_bool,sizeof(int),false,false},
	};
	// plantilla para la Socio.
	static Table table_Socio={"socio",CNT_COL_SOC,0, cols_Socio,NULL};
	typedef obj_Socio *(*getSocioObjPtr)(void *self);
#endif

