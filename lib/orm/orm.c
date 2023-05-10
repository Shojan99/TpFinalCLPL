#include "../../config/config.h"
#include "../utils/utils.h"
#include "orm.h"
#include <string.h>
#include <malloc.h>
static char msg_ERROR_DB[MAXERR];
//----------------------------------------------------
void clearError(){
	strcpy(msg_ERROR_DB,"");
}
//----------------------------------------------------
void setError(char *err)
{
	strcpy(msg_ERROR_DB,err);
}
//----------------------------------------------------
char *getLastError()
{
	return msg_ERROR_DB;
}
//----------------------------------------------------
int findAllImpl(
void *self, //puntero generico
void **list, //lista donde se devolvera el resultado
char *criteria //criterio a aplicar si se envia NULl, no se usa.
)
{
	return execute_get_DB(self,criteria,list,((Object *)self)->sizeObj,((Object *)self)->constructor);
}
//----------------------------------------------------
int findImpl(void *self)
{
	return execute_get_DB(self,NULL,NULL,NULL,NULL);
}
//----------------------------------------------------
int findByIdImpl(void *self, int k)
{
   int size=0; 
   Object *obj = (Object *)(self);
   // inicializar Id en columna clave (campo Id)
   obj->setIdObj(obj,k);
   size = findImpl(self);
   if(!size) // en find by key rellenar obj que invoca, con tupla 0 si hay.
   	 size = NOT_FOUND;
	return size;
}
//----------------------------------------------------
int execute_get_DB(
Object *self, //puntero de tipo Object // representacion base
char *sql, //cadena sql
void **list, // lista de retorno
size_t t, //tamaño del objeto a almcenar
void *(*fcConstructor) () //puntero a funcion del constructor para crear instancias en la lista de salida.
)
{
    PGconn *conn;
    void *obj;
    bool doFindByKey = (fcConstructor == NULL?true:false);// si no se pasa referencia a Pseudo objeto invocador, es FindAll
	char cadsql[MAX_SQL];
	CLEAR(cadsql,MAX_SQL);
    //Conexion con la base de datos 
	if ((conn = connectdb(getServer(),getPort(),getDataBase(),getUser(),getPwd())) == NULL){
        exit(-1);
    }
    int tuplas=0,rowi=0;        
    PGresult *res; //Instancia para contener los datos de ejecucion de consulta
	    
    if(doFindByKey) 
	  strcpy(cadsql , (char*)getFindByKeySQL((Object*)self));
    else
    {
    	Table *tt = ((Object*)self)->ds;  
  		strcpy(cadsql,selectSQL((Object*)self));
  		WHERE_SQL(cadsql,sql);
	}
    if(getDebug())
		  printf("(SQL) - %s\n",cadsql);
    res = PQexec(conn, cadsql);
    
	if(doFindByKey) 
	  free(sql);
    if (res != NULL && PGRES_TUPLES_OK == PQresultStatus(res)) {
        tuplas = PQntuples(res);
        // si tengo puntero a funcion del constructor estoy resolviendo FindAll, sino un findByKey
        if(!doFindByKey) 
		  *list = malloc(t * tuplas); // solicitar memoria para array de pseudo Objetos.
	
        if(tuplas!=0) 
		{
			// crear lista de pseudo objetos - dimensionar a la cantidad de tuplas            
            int i=0;
            for (rowi = 0; rowi<tuplas; rowi++) 
            {
              obj = (doFindByKey? self : fcConstructor());  
			  // para el invocador setear data desde la BD
              Table *tt = ((Object *)obj)->ds;
			  
			  // verificar si se trata de findAll o findByKey
			  for(i=0;i<tt->canColumns;++i)
    		  {
    		    void *dato;    		    
    		    Column col = ((Column *)tt->columns)[i];
    		    // pasar de formato desde un PGresult a columns (generico) sin distincion de la clase.
    		    dato = malloc(col.size);
				  
				if(col.tipo == t_int) 
    		      *((int*)dato) = atoi(PQgetvalue(res,rowi,i));
				if(col.tipo == t_bool) 
				{
					char *dato_bool;
					dato_bool = malloc(sizeof(char)*10);
					dato_bool = rtrim(PQgetvalue(res,rowi,i),' ');
					if( dato_bool[0]=='t' || dato_bool[0]=='T')
					  *((int*)dato) = true;
					else
					  *((int*)dato) = false;
					free(dato_bool);
				}				  
				if(col.tipo == t_varchar || col.tipo == t_date)
				  dato = rtrim(PQgetvalue(res,rowi,i),' ');
				
				if(col.tipo == t_float)
    		      *((float*)dato) = atof(PQgetvalue(res,rowi,i));
				
				setValue(obj,i,dato);
				//free(dato);
		 	  }
		 	  ((Object*)self)->isNewObj=false;
		 	  if(!doFindByKey)
		 	    ((Object **)*list)[rowi] = obj;
			}
        }		
        PQclear(res);
   }
   disconnectdb(conn);
   return tuplas;
}
//----------------------------------------------------
bool hasAutonum(void *self)
{
	int i;
	Table *tt = ((Object*)self)->ds;
	for(i=0;i<tt->canColumns;++i)
     if(((Column *)tt->columns)[i].autonum)    
	   return true;
    return false;
}
//----------------------------------------------------
char *selectSQL(Object *o)
{
  Table *tt = o->ds;
  int size=0,i=0;
  char *sql, str_where[MAX_WHERE_SQL],fields[MAX_SQL];
  sql = (char*)malloc(MAX_SQL*sizeof(char));
  //blanquear cadenas
  CLEAR(sql,MAX_SQL);
  CLEAR(fields,MAX_SQL);
  
  //ver si hay criterio para agregar 
  strcpy(sql,SQL_STR);
  //recorrer cada nombre de columna(armar listado de campos)
  for(i=0;i<tt->canColumns;++i)
  {
     strcat(fields , ((Column *)tt->columns)[i].nombre);
     strcat(fields,(i<tt->canColumns-1)?",":"");
  }
  //reemplazar listado de campos y nombre de tabla.
  strcpy(sql ,(char*) str_replace(sql,TOK1,fields));  
  strcpy(sql ,(char*)str_replace(sql,TOK2,tt->nombre));
  return sql;
}
//----------------------------------------------------
bool saveObjImpl(
void *self  // puntero generico al que aplica
)
{
   PGconn *conn;
   PGresult *res; 
   int code=0;
   int newId;
   bool hasAutonumCol=false;
   char values[MAX_WHERE_SQL], where[MAX_WHERE_SQL],*sql;   
   Object *obj = (Object *) self;
   clearError();
    //Conexion con la base de datos 
   if ((conn = connectdb(getServer(),getPort(),getDataBase(),getUser(),getPwd())) == NULL){
        exit(-1);
   }
   hasAutonumCol = hasAutonum(self);
   //Si esta marcado como nuevo objeto, es decir se creo instancia y no fue obtenido de la BD,
   if(obj->getIsNewObj(obj))
   {// insert
		sql = (char*)getInsertSQL(obj);
		if(getDebug())
		  printf("(SQL) - %s\n",sql);
		res = PQexec(conn, sql);
		code = PQresultStatus(res);		
		if (!(code == PGRES_COMMAND_OK || code== 2)) 
		   setError(PQerrorMessage(conn));
		if(hasAutonumCol)
		  newId = atoi(PQgetvalue(res,0,0));	
		PQclear(res);
		free(sql);
		obj->isNewObj=false;// marcar que esta guardado en la BD.
		if(hasAutonumCol)
		  obj->setIdObj(obj,newId);
  }
  else
  {// update
      sql = (char*)getUpdateSQL(obj);
      if(getDebug())
		  printf("(SQL) - %s\n",sql);
      res = PQexec(conn, sql) ;
      code = PQresultStatus(res);
      if (code != PGRES_COMMAND_OK) 
		 setError(PQerrorMessage(conn));	  
      PQclear(res);	  
	  free(sql);
  }
  disconnectdb(conn);     
  if ( code == PGRES_COMMAND_OK  || code ==2)
     return true;
    else
     return false;
}
//----------------------------------------------------
// Obtener cadena SQL con Where por Clave primaria.
//----------------------------------------------------
char *getFindByKeySQL(void *self)
{
  Table *tt = ((Object*)self)->ds;
  int size=0,i=0;
  char *sql,where[MAX_WHERE_SQL];
  CLEAR(where,MAX_WHERE_SQL);
  sql = (char *)malloc(sizeof(char)*MAX_SQL); //liberar despues de usar
  //blanquear cadena
  CLEAR(sql,MAX_SQL);
  strcat(sql,selectSQL((Object*)self));
  //verificar columnas key de la clase para armar el where de la consulta sql.
  for(i=0;i<tt->canColumns;++i)
  {
    if(((Column *)tt->columns)[i].pkey)
    {
     snprintf(where, MAX_WHERE_SQL,"%s=", ((Column *)tt->columns)[i].nombre);
     getValueByPos(self,where, i);// obtener value en forma generica desde configuracion de las columnas dadas en el .h de la clase
    }
  }
  WHERE_SQL(sql,where);
  return sql;
}
//----------------------------------------------------
char *getUpdateSQL(void *self)
{
  Table *tt = ((Object*)self)->ds;
  int size=0,i=0;
  char *sqlRet,sql[MAX_SQL],fields[MAX_WHERE_SQL],where[MAX_WHERE_SQL],field[MAX_WHERE_SQL],values[MAX_WHERE_SQL];
      
  //blanquear cadenas
  CLEAR(sql,MAX_SQL);
  CLEAR(where,MAX_WHERE_SQL);
  CLEAR(field,MAX_WHERE_SQL);
  CLEAR(fields,MAX_WHERE_SQL);
  CLEAR(values,MAX_WHERE_SQL);

  //ver si hay criterio para agregar 
  strcpy(sql,SQL_UPDATE);
  //cant de columnas clave y cant de columnas datos
  //recorrer cada nombre de columna(armar listado de campos y where)
  for(i=0;i<tt->canColumns;++i)
  {
  	if(((Column *)tt->columns)[i].pkey) // campo clave conforma el where donde aplicar el cambio
  	{
  	  snprintf( where , MAX_WHERE_SQL,"%s=", ((Column *)tt->columns)[i].nombre);
  	  getValueByPos(self, where, i);
	  strcat(values,where);
	  strcat(values," and ");  
    }
	else // no clave son seteos 
	{
		snprintf(field, MAX_WHERE_SQL,"%s=", ((Column *)tt->columns)[i].nombre);
		getValueByPos(self, field, i);
	    strcat(fields,field);
	    strcat(fields,",");
    } 	 
  } 
  //reemplazar listado de campos y nombre de tabla.
  strcpy(sql ,(char*)str_replace(sql,TOK1,tt->nombre));
  strcpy(sql ,(char*)str_replace(sql,TOK2,fields));
  strcpy(sql ,(char*)str_replace(sql,TOK3,values));
  strcpy(sql ,(char*)str_replace(sql,", where "," where "));
  strcpy(sql ,(char*)str_replace(sql," and ;",";"));
  sqlRet = (char*)malloc(strlen(sql)+1*sizeof(char*));
  strcpy(sqlRet,sql);
  return sqlRet;
}
//----------------------------------------------------
char *getInsertSQL(void *self)
{
  Table *tt = ((Object*)self)->ds;
  int size=0,i=0,isAutoNum=0;
  char *sqlRet,sql[MAX_SQL],fields[MAX_WHERE_SQL],where[MAX_WHERE_SQL],field[MAX_WHERE_SQL],values[MAX_WHERE_SQL],col_autonum[MAX];
  //blanquear cadenas
  CLEAR(sql,MAX_SQL);
  CLEAR(where,MAX_WHERE_SQL);
  CLEAR(field,MAX_WHERE_SQL);
  CLEAR(fields,MAX_WHERE_SQL);
  CLEAR(values,MAX_WHERE_SQL);
  CLEAR(col_autonum,MAX);
  
  //ver si hay criterio para agregar 
  strcpy(sql,SQL_INSERT);   
  //cant de columnas clave y cant de columnas datos
  //recorrer cada nombre de columna(armar listado de campos y where)
  for(i=0;i<tt->canColumns;++i)
  {
     //si la columna es clave. generar consulta sql para obtener el siguiente id +1
     snprintf(field, MAX_WHERE_SQL,"%s", ((Column *)tt->columns)[i].nombre);
     strcat(field, ",");
     strcat(fields,field);
     isAutoNum = isAutoNum || (((Column *)tt->columns)[i].autonum);
     
     if(((Column *)tt->columns)[i].pkey && ((Column *)tt->columns)[i].autonum) //si es la columna clave primaria, debe cambiar el value del insert.
       {
         strcat(values,SQL_MAX_ID);
         strcpy(values ,(char*)str_replace(values,TOK1,((Column *)tt->columns)[i].nombre));//reemplazar nombre de columna clave
         strcpy(values ,(char*)str_replace(values,TOK2,tt->nombre));//reemplazar nombre de tabla
         strcpy(col_autonum, ((Column *)tt->columns)[i].nombre);
       }
     else     
	 getValueByPos(self, values,i);
     
     strcat(values, ",");
  }
  strcpy(sql ,(char*)str_replace(sql,TOK1,tt->nombre));
  strcpy(sql ,(char*)str_replace(sql,TOK2,fields));
  strcpy(sql ,(char*)str_replace(sql,TOK3,values));
  strcpy(sql ,(char*)str_replace(sql,",)",")"));
  if(!isAutoNum)
    strcpy(sql ,(char*)str_replace(sql," RETURNING $4;",";"));
  else
    strcpy(sql ,(char*)str_replace(sql,TOK4,col_autonum));
  sqlRet = (char*)malloc(strlen(sql)+1*sizeof(char*));
  strcpy(sqlRet,sql);
  return sqlRet;
}
//----------------------------------------------------
void *init_obj(size_t t_obj,void*(*init)(void *o))
{
   	 // pedir memoria para el objeto gral
    void *obj = malloc(t_obj);
	((Object*)obj)->destroyInternal=NULL;//poner puntero a funcion en NULL, la invocacion de init de cada pseudoobjeto debe crear su version de detroyInternal
    void *oobj = init(obj);//usar puntero a funcion del inicializador mas especializado
    int i;
    Table *tt = ((Object*)oobj)->ds;
    ((Object*)oobj)->col_value =  (Value **)malloc(sizeof(Value) * tt->canColumns );
    //setear implementaciones genericas para ejecutar las funciones: findByKey, findAll, saveObj
	((Object*)oobj)->findAll    	= findAllImpl;
    ((Object*)oobj)->getIsNewObj	= getIsNewObjImpl;
    ((Object*)oobj)->saveObj    	= saveObjImpl;
    ((Object*)oobj)->findbykey  	= findByIdImpl;
    ((Object*)oobj)->setIdObj		= setIdObjImpl;  
	for(i=0;i<tt->canColumns;++i)
    {  	
  	  Column col = ((Column *)tt->columns)[i];
  	  ((Value *)(((Object*)oobj)->col_value))[i].pos = i;
  	  ((Value *)(((Object*)oobj)->col_value))[i].value = malloc(col.size);
    }
    ((Object*)oobj)->isNewObj = true;//marcar como objeto nuevo, si se crea nueva instancia
	return oobj;
}
//----------------------------------------------------
void destroyObj(void *objFree)
{
	int i;
	Object *obj = (Object *)objFree;
	if(obj->destroyInternal!=NULL)
		obj->destroyInternal(obj);
    Table *tt = obj->ds;
   
   for(i=0;i<tt->canColumns;++i)
   {
   	free(((Value *)obj->col_value)[i].value);//liberar punteros de los valores
   } 
    free(obj->col_value);
	//free(obj->ds);
	free(obj);
}
//----------------------------------------------------
void destroyObjList(void **list,int size)
{
	int i=0;
	for(i=0;i< size;++i)
	{
		destroyObj(list[i]);		
	}
	free(list);
}
//----------------------------------------------------
void listObj(void *objList, char *criteria, int freeObj, void(*lstFunc)(void *o))//sobreescribir funcion toString....
{
	Object *obj = (Object *)objList;
	int i=0,size=0;
	void *list;
	Object *rw;
    size = obj->findAll(obj,&list,NULL);
	for(i=0;i<size;++i)
	{
		rw = ((Object **)list)[i];
		if(lstFunc!=NULL)
			lstFunc(rw);
		else
  		    rw->toString(rw);
	}
	if(freeObj)
	{
		destroyObjList(list,size);
		destroyObj(objList);
	}
}
//----------------------------------------------------
void *getValue(void *self,int pos)
{  
  Object *obj =  (Object *)self;
  Value *val = &(((Value*)obj->col_value)[pos]);
  return val->value;
}
//----------------------------------------------------
void setValue(void *self, int pos, void *valset)
{
  Object *obj =  (Object *)self;
  Table *tt=obj->ds;
  Value *vval = &(((Value*)obj->col_value)[pos]);
  memcpy(vval->value,  valset,((Column *)tt->columns)[pos].size);
}
//----------------------------------------------------
void getValueByPos(void *self,char *cad, int pos)
{
  char field[MAX_WHERE_SQL];
  Object *obj =  (Object *)self;
  Table *tt=obj->ds;
  CLEAR(field,MAX_WHERE_SQL);
  Value *dato = &(((Value*)obj->col_value)[pos]);
  int datoInt = 0;
  char *datoChar;
  float datoFloat = 0.0;
  int tipo = ((Column *)tt->columns)[pos].tipo;
  
  if( tipo == t_int )
  {
  	datoInt = *((int*)(dato->value)); 
  	snprintf( field, MAX_WHERE_SQL, FRMTYPE(tipo), datoInt);
  }
  if( tipo == t_bool )
  {
  	datoInt = *((int*)(dato->value)); 
  	snprintf( field, MAX_WHERE_SQL, "%s", (datoInt==1?"true":"false"));
  }
  if( tipo == t_varchar || tipo == t_date )
  {
  	datoChar = ((char*)(dato->value)); 
  	snprintf( field, MAX_WHERE_SQL, FRMTYPE(tipo), datoChar);
  }
  if( tipo == t_float )
  {
  	datoFloat = *((float*)(dato->value)); 
  	snprintf( field, MAX_WHERE_SQL, FRMTYPE(tipo), datoFloat);
  }
  strcat(cad,field);
}
//----------------------------------------------------
bool getIsNewObjImpl(void *self)
{
	return ((Object *)self)->isNewObj;
}
//----------------------------------------------------
void setIdObjImpl(void *self,int val)
{
	setValue(self,POS_ID,&val);	
}
