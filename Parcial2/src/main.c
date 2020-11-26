/*
 *      Author: l.rojas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "cliente.h"
#include "afiche.h"
#include "parser.h"
#include "informes.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Agregar cliente
     2. Vender afiches
     3. Modificar venta
     4. Cobrar venta
     5. Generar informe de cobros
     6. Generar informe de deudas
     7. Generar estadisticas
     8. Salir
*****************************************************/

int main(void)
{
	setbuf(stdout, NULL);
	LinkedList* listaCliente = ll_newLinkedList();
	LinkedList* listaVentas = ll_newLinkedList();
	int opcion;
	int subOpcion;

	controller_loadOrSave("r", parser_ClienteFromText, "clientes.txt", listaCliente);
	controller_loadOrSave("r", parser_VentasFromText, "ventas.txt", listaVentas);


	do
	{
		if(utn_getMenu(menu, &opcion, 3,1,8)==0)
		{
			switch(opcion)
			{
			case 1:
				controller_addEmployee(listaCliente);
				break;

			case 2:
				controller_vender_afiches(listaVentas,listaCliente);
				break;

			case 3:
				controller_modificar_Venta(listaVentas,listaCliente,COBRADOS);
				break;

			case 4:
				controller_cobrar_venta(listaVentas, listaCliente);
				break;

			case 5:
				controller_generarInforme(listaVentas, listaCliente, COBRADOS_TXT, COBRADOS,firstRow_COBRADAS);
				break;

			case 6:
				controller_generarInforme(listaVentas, listaCliente, A_COBRAR_TXT, NO_COBRADOS, firstRow_A_COBRAR);
				break;

			case 7:
				if(utn_getMenu(subMenu, &subOpcion, 3,1,3)==0)
				{
					switch(subOpcion)
					{
					case 1:
						controller_generarEstadisticas(listaVentas, listaCliente,CLIENTE_AL_QUE_VENDIO_MAS_AFICHES);
						break;

					case 2:
						controller_generarEstadisticas(listaVentas, listaCliente,CLIENTE_AL_QUE_VENDIO_MENOS_AFICHES);
						break;

					case 3:
						controller_ventaConMasAfichesVendidos(listaVentas, listaCliente);
						break;
					}
				}

			}
		}
	}while(opcion!=8);
	controller_loadOrSave("w", parser_SaveClientToText, "clientes.txt", listaCliente);
	controller_loadOrSave("w", parser_SaveVentaToText, "ventas.txt", listaVentas);
    printf("\nExit");

    return 0;
}

