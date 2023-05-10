#include "config.h"
#include "../lib/utils/utils.h"
#include <string.h>
#include <stdio.h>
#include <malloc.h>

char path_ini[MAX];
char server[MAX];
char database[MAX];
char port[MAX];
char user[MAX];
char pwd[MAX];
//----------------------------------------------------
// recurso obtenido desde https://www.programmersought.com/article/4083888642/
/* 
    * Function name: GetIniKeyString 
         * Entry parameters: title 
         * Identification of a set of data in the configuration file 
    *                  key 
         * The identifier of the value to be read in this set of data 
    *                  filename 
         * File path to be read 
         * Return value: Find the value you need to check and return the correct result 0 
         * Otherwise -1 
*/  
int GetIniKeyString(char *title,char *key,char *filename,char *buf)  
{  
    FILE *fp;  
    int  flag = 0;  
    char sTitle[64], *wTmp;
    char sLine[1024];        
    sprintf(sTitle, "[%s]", title);
                     
    if(NULL == (fp = fopen(filename, "r"))) {  
        perror("fopen");  
        return -1;
    }
    while (NULL != fgets(sLine, 1024, fp)) {  
                 // This is the comment line  
        if (0 == strncmp("//", sLine, 2)) continue;  
        if ('#' == sLine[0])              continue;        
        wTmp = strchr(sLine, '=');  
        if ((NULL != wTmp) && (1 == flag)) {  
                if (0 == strncmp(key, sLine, strlen(key))) 
				{
                sLine[strlen(sLine) - 1] = '\0';  
                fclose(fp);
                while(*(wTmp + 1) == ' '){
                    wTmp++;
                }
                strcpy(buf,wTmp + 1);
                return 0;  
            }  
        } else {  
                         if (0 == strncmp(sTitle, sLine, strlen(sTitle))) 
						 { // The length depends on the file read  
                                 flag = 1; // find the title location  
            }  
        }  
    }  
    fclose(fp);  
    return -1;  
}
//----------------------------------------------------
bool init_config(char *pathinifile)
{	int ret;
	char portLoc[MAX];
	ret = GetIniKeyString("config","server",pathinifile,server);
	ret = GetIniKeyString("config","database",pathinifile,database);
	ret = GetIniKeyString("config","user",pathinifile,user);
	ret = GetIniKeyString("config","pwd",pathinifile,pwd);
	ret = GetIniKeyString("config","port",pathinifile,portLoc);	
	strcpy(path_ini,pathinifile);
	return true;
}
//----------------------------------------------------
char *getServer() { return server; }
char *getDataBase() { return database; }
char *getPort() { return port; }
char *getUser() { return user; }
char *getPwd() { return pwd; }
void setDebug(int vval)
{
	debug = vval;
}
int getDebug()
{
	return debug;
}

