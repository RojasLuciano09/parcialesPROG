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


int main(void) {
	setbuf(stdout, NULL);


	int opcion=0;
	int subOpcion=0;
	Cliente ClienteList[lenCliente];
	Cliente_initList(ClienteList, lenCliente);
	Aviso listAviso[lenAviso];
	Aviso_initList(listAviso, lenAviso);

	do{
	utn_getMenu("\n1) Alta de cliente: "
				"\n2) Modificar datos de cliente: "
				"\n3) Baja de cliente: "
				"\n4) Publicar: "
				"\n5) Pausar publicación: "
				"\n6) Reanudar publicación:"
				"\n7) Imprimir Clientes:"
				"\n8) Informar:"
				"\n9) Print normal: "
				"\n10) CargaAutomatica: "
				"\n0)Salir",&opcion, ATTEMPTS, 0, 20);
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
		utn_getMenu("\n1) Cliente con más aviso."
					"\n2) Cantidad de avisos pausados."
					"\n3) Rubro con mas avisos. "
					,&subOpcion, ATTEMPTS, 1, 3);
						switch(subOpcion)
						{
						case 1:
							Informe_imprimirClienteAvisosACTIVOS(listAviso, lenAviso, ClienteList, lenCliente,2);
							break;

						case 2:
							Informe_cantidadDeAvisosPausados(listAviso, lenAviso, ClienteList, lenCliente,1);
							break;

						case 3:
							informe_rubroConMasAviso(listAviso, lenAviso);
						break;
						}
	break;

	case 9: //Estos prints informan los datos cargados de Clientes y Avisos.
		Cliente_print(ClienteList, lenCliente);
		Aviso_print(listAviso, lenAviso);
	break;

	case 10://Realizan una carga automatica de datos linkeados por ID
		ClienteCargaAutomatica(ClienteList);
		Aviso_cargaAutomatica(listAviso);
		break;
		}
	}while(opcion!=0);
		printf("\nFuera\n");
	return EXIT_SUCCESS;
}
