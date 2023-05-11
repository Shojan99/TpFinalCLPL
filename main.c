#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h> 
#include <string.h>
#include <malloc.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "includes/includes.h"


int mostrarMenu(char * msg, int tope)
{
	int opcion = 0;
	do{
		printf("//-----------------------------------------------------------------------\\ \n");
		printf("%s", msg);
		scanf("%d",&opcion);
		system("cls");	
	}
	while(opcion < 0 || opcion > tope);
	return opcion;
}

int menuIngreso()
{
	switch(menu("Menu de ingreso de informacion\n1 - Socios\n2 - Profesores\n3 - Actividades\n4 - Localidades\n5 - Horarios\n6 - Lugares\n7 - Tipo de Actividades\n8 - Inscribirse a una nueva actividad\n9 - Salir\n", 9))
	{
		case 0:
			return 1;
 		case 1:
 			ingresarSocio();
			break;	
		case 2:
			ingresarProfesor();
			break;
		case 3:
			ingresarActividad();
			break;
		case 4:
			ingresarLocalidad();
			break;
		case 5:
			ingresarHorario();
			break;
		case 6:
			ingresarLugar();
			break;
		case 7:
			ingresarTipoActividad();
			break;
		case 8:
			ingresarActividadSocio();
			break;
		case 9:
			ingresarCuota();
			break;
	}
	return 1;
}

int menuActualizar() 
{
	switch(menu("Menu de actualizacion de informacion\n1 - Socios\n2 - Profesores\n3 - Actividades\n4 - Localidades\n5 - Horarios\n6 - Lugares\n7 - Tipo de Actividades\n8 - Inscribirse a una nueva actividad\n9 - Salir\n", 9))
	{
		case 0:
			return 1;
 		case 1:
 			actualizarSocio();
			break;	
		case 2:
			actualizarProfesor();
			break;
		case 3:
			//actualizarActividad();
			break;
		case 4:
			actualizarLocalidad();
			break;
		case 5:
			//actualizarHorario();
			break;
		case 6:
			//actualizarLugar();
			break;
		case 7:
			//actualizarTipoActividad();
			break;
		case 8:
			//actualizarActividadSocio();
			break;
		case 9:
			//actualizarCuota
			break;
	}
	return 1;
}

int menuLista()
{
	switch(menu("Menu de listado de informacion\n1 - Socios activos\n2 - Socios morosos\n3 - Horarios en la semana\n4 - Actividades de x socio\n5 - Listado de cuotas\n9 - Salir\n", 9))
	{
		case 0:
			return 1;
 		case 1:
 			listarSocios("activo=true");
			break;	
		case 2:
			listarSocios("moroso=true");
			break;
		case 3:
			listarHorarios();
			break;
		case 4:
			listarActividadesSocio();
			break;
		case 5:
			//ListarCuotas();
			break;
	}
	return 1;
}

int menuPrincipal()
{
	switch(menu("Menu de opciones\n1 - Ingresos\n2 - Actualizaciones\n3 - Listados\n4 - Salir\n", 4))
	{
		case 0:
			return 0;
	 	case 1:
	 		menuIngreso();	
	 		break;
		case 2:
			menuActualizar();
			break;
		case 3:
			menuLista();
			break;
	}
	return 1;
}

int main(int argc, char *argv[])
{ 
	obj_Localidad *loc;
	obj_Socio *soc;
  
	void *list,*itm;
	int i=0,size=0, sizeEnf=0;
  
	if(!init_config(argv[POS_CONFIG]))
  		exit(-1);
  
	setDebug(true);
  	soc = Socio_new();
  	if(soc->findbykey(soc,1) != NOT_FOUND)
  	{
  		soc->toString(soc);
  		//soc->setActivo(soc,true);
  		//soc->saveObj(soc);
  	}
  	destroyObj(soc);
	while(menuPrincipal());		
	system("PAUSE");
  	return 0;
}
