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

int menu(char *msg, int tope){

    int opcion = 0;
    int leidos = 0;

    do {
        printf("//-----------------------------------------------------------------------\\ \n");
        printf("%s", msg);
        leidos = scanf("%d", &opcion);

        while (getchar() != '\n'); // Limpiar el búfer de entrada

        if (leidos != 1 || opcion < 0 || opcion > tope) {
        	system("cls");
            printf("Opcion invalida. Por favor, ingrese una opcion valida.\n");
        }
    } while (leidos != 1 || opcion < 0 || opcion > tope);

    return opcion;
}


int menuIngreso()
{
    int opcion = menu("Menu de ingreso de informacion.\n1 - Socios\n2 - Profesores\n3 - Actividades\n4 - Localidades\n5 - Horarios\n6 - Lugares\n7 - Tipo de Actividades\n8 - Inscribirse a una nueva actividad\n9 - Ingresar el importe de una actividad\n10 - Ingresar Cuota\n0 - Salir\n", 10);

    switch (opcion)
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
            ingresarImporteActividad();
            break;
        case 10:
            ingresarCuota();
            break;
        default:
            printf("Opcion invalida. Por favor, ingrese una opcion valida.\n");
            break;
    }
    return 1;
}

// Resto del código omitido por brevedad

int menuActualizar() 
{
    switch(menu("Menu de actualizacion de informacion.\n1 - Socios\n2 - Profesores\n3 - Actividades\n4 - Localidades\n5 - Horarios\n6 - Lugares\n7 - Tipo de Actividades\n8 - actividad de socio\n9 - Actualizar el importe de una actividad\n10 - Pagar Cuota\n11 - Anular Cuota\n0 - Salir\n", 11))
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
            actualizarActividad();
            break;
        case 4:
            actualizarLocalidad();
            break;
        case 5:
            //actualizarHorario();
            break;
        case 6:
            actualizarLugar();
            break;
        case 7:
            actualizarTipoActividad();
            break;
        case 8:
            actualizarActividadSocio();
            break;
        case 9:
            actualizarImporteActividad();
            break;
        case 10:
            //pagarCuota();
            break;
        case 11:
          //  anularCuota();
        default:
        	printf("Opcion invalida. Por favor, ingrese una opcion valida.\n");
            break;
    }
    return 1;
}

// Resto del código omitido por brevedad

int menuLista()
{
    int opcion = menu("Menu de listado de informacion.\n1 - Socios activos\n2 - Socios morosos\n3 - Horarios en la semana\n4 - Horarios en la semana de profesores\n5 - Horarios en la semana de socios\n6 - Actividades de x socio\n7 - Listado de cuotas\n0 - Salir\n", 7);

    switch (opcion)
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
            listarHorariosSemana();
            break;
        case 4:
            listarHorariosProfesorSemana();
            break;
        case 5:
            listarHorariosSocioSemana();
            break;
        case 6:
            listarActividadesSocio();
            break;
        case 7:
            ListarCuotas();
            break;
        default:
            printf("Opcion invalida. Por favor, ingrese una opción valida.\n");
            break;
    }
    return 1;
}

// Resto del código omitido por brevedad

int menuPrincipal()
{
    int opcion = menu("Menu de opciones.\n1 - Ingresos\n2 - Actualizaciones\n3 - Listados\n0 - Salir\n", 4);

    switch (opcion)
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
        default:
            printf("Opción invalida. Por favor, ingrese una opción valida.\n");
            break;
    }
    return 1;
}

int main(int argc, char *argv[])
{
	if(!init_config(argv[POS_CONFIG]))
  	exit(-1);
    // Resto del código omitido por brevedad
    while (menuPrincipal());
    system("PAUSE");
    return 0;
}

