#ifndef LOC_INCLUDED
	#define LOC_INCLUDED
	#define CNT_COL_LOC 2
	#define POS_DESCRIPCION 1
	//----------------------------------------------------
	typedef struct {
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    //-- getters
	    getPropertyIntPtr getId;
		getPropertyCharPtr getNombre;	    
	    //-- setters
	    setPropertyIntPtr setId;
		setPropertyCharPtr setNombre;  
	}obj_Localidad;
	// funcionalidad publica que se implementa en Localidad.c
	extern obj_Localidad *Localidad_new ();
	// meta data para acceder a las Localidads - definicion de las columnas de la tabla
	static Column cols_Localidad[CNT_COL_LOC]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"cod_postal",t_int,sizeof(int),true,false}, 
	{"nombre",t_varchar,(sizeof(char)*MAX60)+1,false,false}
	};
	// plantilla para la Localidad.
	static Table table_Localidad={"localidad",CNT_COL_LOC,0, cols_Localidad,NULL};
	// generar PunteroGenerico para usar puntero funcion que obtenga pseudoObjeto Localidad
	typedef obj_Localidad *(*getLocalidadObjPtr)(void *self);
#endif
