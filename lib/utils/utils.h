extern PGconn *conn;
PGconn * connectdb(char *servidor,char *port,char *base,char *usuario,char *password);
void disconnectdb(PGconn *);

// funciones sobre Cadena
char* rtrim(char* string, char junk);
char** fStrSplit(char *str, const char *delimiters);
char* fStrJoin(char **str, const char *delimiters, int sz_opt);
// funciones para informacion de Fecha
char * getFechaHora();
char * getFecha();
char * getDiaFecha(char *fecha);

