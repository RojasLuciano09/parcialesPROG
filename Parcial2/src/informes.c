/*
 *      Author: l.rojas
 */
#include <stdio.h>
#include <stdlib.h>
#include "Controller.h"
#include "utn.h"
#include <string.h>
#include "LinkedList.h"
#include "cliente.h"
#include "afiche.h"
#include "informes.h"

static LinkedList* filtrarClientesByVentas(LinkedList* listaVentas,LinkedList* listaClientes);
static int getClientByIDVenta(void* element,LinkedList* this);

/**
 * \brief Función para filtrar clientes por una lista de ventas.
 * \param LinkedList* listaVentas: Puntero a la lista de ventas.
 * \param LinkedList* listaClientes: Puntero a la lista de clientes.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
static LinkedList* filtrarClientesByVentas(LinkedList* listaVentas,LinkedList* listaClientes)
{
	LinkedList* auxList = NULL;
	void* element;
	char id_aux[SIZE];
	if(listaVentas!=NULL && listaClientes!=NULL)
	{
		auxList = ll_newLinkedList();
		for(int i=0; i<ll_len(listaClientes);i++)
		{
			element = ll_get(listaClientes, i);
			Cliente_getIdStr(element, id_aux);
				if(ll_map2(listaVentas, compararIDparaFiltrar, id_aux)==0)
				{
					ll_add(auxList, element);
				}
		}
	}
	return auxList;
}

/**
 * \brief Función para encontrar un cliente por un id de venta.
 * \param LinkedList* listaVentas: Puntero a la lista de ventas.
 * \param LinkedList* listaClientes: Puntero a la lista de clientes.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
static int getClientByIDVenta(void* element,LinkedList* this)
{
	void* pElement;
	char afiche_id_cliente[SIZE];
	char afiche_id_venta[SIZE];
	char cliente_id[SIZE];

	if(this!=NULL)
	{
		Afiche_get_id_clienteSTR(element, afiche_id_cliente);
		Afiche_getIdStr(element,afiche_id_venta);
		for(int i =0; i<ll_len(this);i++)
		{
			pElement = ll_get(this, i);
			Cliente_getIdStr(pElement, cliente_id);
			if(strncmp(afiche_id_cliente,cliente_id,SIZE)==0)
			{
				printf("\nVenta con mas afiches vendidos \nID VENTA: %s \nCUIT CLIENTE: ",afiche_id_venta);
				Cliente_printCUIT(pElement);
			}
		}

	}
return 0;
}

/**
 * \brief Función para encontrar generar un informe segun el estado de venta.
 * \param LinkedList* listaVentas: Puntero a la lista de ventas.
 * \param LinkedList* listaClientes: Puntero a la lista de clientes.
 * \param char* nameFile:  .
 * \param char* estadoVenta:  .
 * \param char* firstRowFile:  .
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
int controller_generarInforme(LinkedList* listaVentas,LinkedList* listaClientes,char* nameFile,char* estadoVenta,char* firstRowFile)
{
	int out=-1;
	Cliente* buffer;
	FILE* pFile;
	LinkedList* listaModificada;
	int len = ll_len(listaClientes);
	char idAux[SIZE];
	char nombreAux[SIZE];
	char apellidoAux[SIZE];
	char cuitAux[SIZE];
	int contador;

	if(listaVentas!=NULL && !ll_isEmpty(listaVentas) && listaClientes!=NULL && !ll_isEmpty(listaClientes))
	{
		pFile = fopen(nameFile,"w");
		if(pFile!=NULL)
		{
			listaModificada = ll_filterBySomethingCloneAndReturn(listaVentas, afichesCobrados,estadoVenta);

			fprintf(pFile,firstRowFile);
			for(int i=0; i<len;i++)
			{
				buffer = ll_get(listaClientes, i);
				if(buffer!=NULL 									 &&
				   Cliente_getIdStr(buffer, idAux)==0			     &&
				   Cliente_get_nombre(buffer, nombreAux)==0		 	 &&
				   Cliente_get_apellido(buffer, apellidoAux)==0   	 &&
				   Cliente_get_cuit(buffer, cuitAux)==0			      )
				{
					if(ll_reduce2(listaModificada, comparoID_cliente,idAux, &contador)!=0 && contador!=0)
					{
						fprintf(pFile,"%s,%s,%s,%s,%d\n",idAux,nombreAux,apellidoAux,cuitAux,contador);
						out=0;
					}
				}
			}
		}
		fclose(pFile);
	}
	else
	{
		printf("\nNo hay datos cargados\n");
	}
	return out;
}

/**
 * \brief Función para encontrar generar un informe sobre el mayor y menor cliente con ventas cobradas.
 * \param LinkedList* listaVentas: Puntero a la lista de ventas.
 * \param LinkedList* listaClientes: Puntero a la lista de clientes.
 * \param int opcion: Variable para indicar que se imprimira por consola.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
int controller_generarEstadisticas(LinkedList* listaVentas,LinkedList* listaClientes,int opcion)
{
	int out=-1;
	int len = ll_len(listaClientes);
	Cliente* buffer;
	Cliente* bufferMax;
	Cliente* bufferMIn;
	int contador=0;
	int contadorMax;
	int contadorMin;
	char id_aux[SIZE];
	LinkedList* listaModificadaVenta;
	LinkedList* listaModificadaCliente;


	if(listaVentas!=NULL && !ll_isEmpty(listaVentas) && listaClientes!=NULL && !ll_isEmpty(listaClientes))
	{
		listaModificadaVenta = ll_filterBySomethingCloneAndReturn(listaVentas, afichesCobrados,COBRADOS);
		listaModificadaCliente = filtrarClientesByVentas(listaModificadaVenta, listaClientes);

		for(int i=0;i<len;i++)
		{
			buffer = ll_get(listaModificadaCliente, i);
			if(buffer!=NULL && Cliente_getIdStr(buffer, id_aux)==0  			&&
			ll_reduce2(listaModificadaVenta, comparoID_cliente,id_aux, &contador))
			{
				if(i==1 || contador > contadorMax)
				{
					contadorMax = contador;
					bufferMax = buffer;
				}else if (contador < contadorMin)
				{
					contadorMin = contador;
					bufferMIn = buffer;
				}
			}
		}

		if(opcion==1)
		{
			printf("\n Cliente al que se le vendio mas afiches.. \n");
			printf("\n CANTIDAD   ID     Nombre      Apellido        CUIT");
			printf("\n     %d      ", contadorMax);
			Cliente_print(bufferMax);
			out=0;
		}else
		{
			printf("\n Cliente al que se le vendio menos afiches.. \n");
			printf("\n CANTIDAD   ID     Nombre      Apellido        CUIT");
			printf("\n     %d      ", contadorMin);
			Cliente_print(bufferMIn);
			out=0;
		}
	}
	return out;
}


/**
 * \brief Función para encontrar generar un informe sobre la venta con mayor cantidad de COBRADAS.
 * \param LinkedList* listaVentas: Puntero a la lista de ventas.
 * \param LinkedList* listaClientes: Puntero a la lista de clientes.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
int controller_ventaConMasAfichesVendidos(LinkedList* listaVentas,LinkedList* listaClientes)
{
	int out=-1;
	int contador;
	int contadorMax;
	Afiche* element;
	Afiche* bufferMax;
	LinkedList* listaModificadaVenta=NULL;

	listaModificadaVenta = ll_filterBySomethingCloneAndReturn(listaVentas, afichesCobrados,COBRADOS);

	for(int i=0; i<ll_len(listaModificadaVenta);i++)
	{
		element = ll_get(listaModificadaVenta, i);
		Afiche_get_cantidad_afichesINT(element, &contador);

		if(ll_map2(listaModificadaVenta, compararCantidadDeVentas, &contador)==0)
		{
			if(i==1 || contador > contadorMax)
			{
				contadorMax = contador;
				bufferMax = element;
			}
		}
	}
	getClientByIDVenta(bufferMax, listaClientes);
	printf("\nCANTIDAD VENDIDOS: %d  \n", contadorMax);
	return out;
}
