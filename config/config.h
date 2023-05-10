#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 

#ifndef __DEFOPTS__
#define __DEFOPTS__
typedef enum { false=0,true=1} bool;
#define POS_CONFIG 1
#define NOT_FOUND -1
#define MAX 80
#define MAX1 30
#define MAX2 80
#define MAX3 90
#define MAX4 2
#define MAXHORAMIN 5
#define MAXFECHA 12
#define MAX5 150
#define MAX20 20
#define MAX30 30
#define MAX40 40
#define MAX50 50
#define MAX60 60
#define MAX80 80
#define MAX90 90
#define MAX100 100
#define MAX10 10
#define MAX12 12
#define MAX120 120
#define MAX150 150
#define MAXOBS 250
#define MAX_SQL 800
#define MAX_WHERE_SQL 600
#define MAXERR 400
#define NULL_VALUE -100
#define SQL_STR "select $1 from $2"
#define SQL_INSERT "insert into $1 ($2) values ($3) RETURNING $4;"
#define SQL_UPDATE "update $1 set $2 where $3;"
#define SQL_MAX_ID "coalesce((select max($1)+1 from $2),1)"
#define WHERE_SQL(sql,c)   if(c!=NULL){\
     strcat(sql," where ");\
     strcat(sql, c );\
  }
#define THIS(clase) static clase *this(void *self){\
   return (clase*)self;\
}
#ifndef CLEAR
#define CLEAR(t,max) memset(t, '\0',max)
#endif
#define TOK1 "$1"
#define TOK2 "$2"
#define TOK3 "$3"
#define TOK4 "$4"
//config DabaBase Access
char *getServer();
char *getDataBase();
char *getPort();
char *getUser();
char *getPwd();
// variable publica que permite registro de depuracion en la ejecucion de las consultas SQL
static int debug=0;
void setDebug(int vval);
int getDebug();
#endif
// recurso obtenido desde https://www.programmersought.com/article/4083888642/
/*ini.h*/
#ifndef INI_H
#define INI_H
int GetIniKeyString(char *title,char *key,char *filename,char *buf);
#endif /*INI_H*/
