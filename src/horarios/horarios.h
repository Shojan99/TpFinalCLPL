#ifndef HOR_INCLUDED
	#define HOR_INCLUDED
	#define CNT_COL_HOR 6
	// POS 0 ES EL ID DE LA CLASE
	#define POS_DIA_HOR 1
	#define POS_COD_ACT_HOR 2
	#define POS_HORA_DESDE_HOR 3
	#define POS_HORA_HASTA_HOR 4
	#define POS_LUGAR_HOR 5	

	//----------------------------------------------------
	typedef struct {	    
		IOBJECT	 // crea definicion de propiedades comunes a Object .. Macro en orm.h     
	    getPropertyIntPtr   getCodigo;
		getPropertyIntPtr   getDia;
		getPropertyIntPtr   getCodAct;		
		getPropertyCharPtr  getHoraDesde;
		getPropertyCharPtr  getHoraHasta;
		getPropertyCharPtr  getLugar;
		
	    //-- setters
	    setPropertyIntPtr   setCodigo;
		setPropertyIntPtr   setDia;
		setPropertyIntPtr   setCodAct;		
		setPropertyCharPtr  setHoraDesde;
		setPropertyCharPtr  setHoraHasta;
		setPropertyCharPtr  setLugar;
		
	    // getter de objeto relacionado
		getActividadObjPtr  getActividadObj;
		//getLugarObjPtr  	getLugarObj;
	    obj_Actividad 		*actividad;
	}obj_Horario;
	// funcionalidad publica que se implementa en actividad_socio.c
	extern obj_Horario *Horario_new ();
	// meta data para acceder a las Horario  del Socio - definicion de las columnas de la tabla
	static Column cols_Horario[CNT_COL_HOR]=
	{ 
	//definicion del mapeo, por cada columna de la tabla con los atributos del pseudobjeto.
	// nombre de la columna, tipo, tamaño, si es clave, si es autonumerado.
	{"codigo",t_int,sizeof(int),true,true},	
	{"dia",t_int,sizeof(int),false,false},	
	{"cod_act",t_int,sizeof(int),false,false},	
	{"hora_desde",t_varchar,(sizeof(char)*MAXHORAMIN)+1,false,false},	
	{"hora_hasta",t_varchar,(sizeof(char)*MAXHORAMIN)+1,false,false},
	{"lugar",t_varchar,(sizeof(char)*MAX90)+1,false,false},
	};
	// plantilla para la Actividad.
	static Table table_Horario={"horarios",CNT_COL_HOR,0, cols_Horario,NULL};
	typedef obj_Horario *(*getHorarioObjPtr)(void *self);
#endif

