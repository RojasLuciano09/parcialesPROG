#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Controller.h"
#include "cliente.h"
#include "afiche.h"
#include "parser.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
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
				if(utn_getMenu(menu, &subOpcion, 3,1,3)==0)
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

