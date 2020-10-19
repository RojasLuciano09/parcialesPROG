/*
 ============================================================================
 Name        : Parcial.c
 Author      : Nicolas Luciano Rojas
 Version     : final
 Copyright   :
 Description : Primer parcial Programacion.
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn.h"
#include "cliente.h"
#include "aviso.h"
#include "informe.h"

#define lenCliente 100
#define lenAviso   1000
#define PRINT_ACTIVE 1
#define PRINT_PAUSED 0
#define PRINT_IN_ANY_STATE 3

int main(void) {
	setbuf(stdout, NULL);

	int opcion=0;
	int subOpcion=0;
	Cliente ClienteList[lenCliente];
	Cliente_initList(ClienteList, lenCliente);
	Aviso listAviso[lenAviso];
	Aviso_initList(listAviso, lenAviso);

	do{
	utn_getMenu("\n  ->Opciones<-   "
				"\n1) Alta de cliente: "
				"\n2) Modificar datos de cliente: "
				"\n3) Baja de cliente: "
				"\n4) Publicar: "
				"\n5) Pausar publicación: "
				"\n6) Reanudar publicación:"
				"\n7) Imprimir Clientes:"
				"\n8) Informar:"
				"\n9) Print normal: "
				"\n10) CargaAutomatica: "
				"\n0)Salir",&opcion, ATTEMPTS, 0, 10);
	switch(opcion)
		{

	case 1:
		Cliente_alta(ClienteList, lenCliente);
	break;

	case 2:
		Cliente_modificar(ClienteList, lenCliente);
	break;

	case 3:
		Aviso_baja(listAviso, lenAviso,ClienteList,lenCliente);
	break;

	case 4:
		Aviso_alta(listAviso, lenAviso,ClienteList,lenCliente);
	break;

	case 5:
		Aviso_pausar(listAviso, lenAviso, ClienteList, lenCliente);
	break;

	case 6:
		Aviso_activar(listAviso, lenAviso, ClienteList, lenCliente);
	break;

	case 7:
		Aviso_imprimirClienteJuntoACantidadDeAvisos(listAviso, lenAviso, ClienteList, lenCliente);
	break;

	case 8:
		utn_getMenu("\n1) Cliente con más avisos:"
					"\n2) Cantidad de avisos pausados."
					"\n3) Rubro con mas avisos. "
					"\n4) Cliente con más avisos pausados. "
					"\n5) Cliente con más avisos activos:"
					,&subOpcion, ATTEMPTS, 1, 5);
						switch(subOpcion)
						{
						case 1:
							printf("\nCliente con mas avisos: ");
							Informe_imprimirAvisosEnUnCiertoEstado(listAviso, lenAviso, ClienteList, lenCliente,PRINT_IN_ANY_STATE);
							break;

						case 2:
							Informe_cantidadDeAvisosPausados(listAviso, lenAviso, ClienteList, lenCliente);
							break;

						case 3:
							informe_rubroConMasAviso(listAviso, lenAviso);
						break;

						case 4:
							printf("\nCliente con mas avisos pausados.");
							Informe_imprimirAvisosEnUnCiertoEstado(listAviso, lenAviso, ClienteList, lenCliente,PRINT_PAUSED);
						break;

						case 5:
							printf("\nCliente con mas avisos activos.");
							Informe_imprimirAvisosEnUnCiertoEstado(listAviso, lenAviso, ClienteList, lenCliente,PRINT_ACTIVE);
						break;

						}
	break;

	case 9: //Informa los datos cargados de   Clientes y Aviso indexados por su ID.  3 -> imprime ambos estados de las publicaciones.
		Aviso_printDataFromBothEntities(listAviso, ClienteList, lenAviso, lenCliente,3);
	break;

	case 10://Realizan una carga automatica de datos linkeados por ID
		ClienteCargaAutomatica(ClienteList,lenCliente);
		Aviso_cargaAutomatica(listAviso);
		break;

		}
	}while(opcion!=0);
		printf("\nFuera\n");
	return EXIT_SUCCESS;
}
