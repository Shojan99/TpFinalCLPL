typedef struct
{
	char *t;//nombre de la tabla donde aplica el criterio
	char *al; //alias a usar para reducir codigo sql
	char *sql; // sentencia sql a enviar al motor.
	char *fList;
	char *joins;
	char *whereOpt;
	void (*toList)(void* q,char *cr);
	void (*addAnd)(void* q,char *cr);
	char *(*getSQL)(void *q);
} obj_Query;

extern obj_Query *Query_new(char *);

