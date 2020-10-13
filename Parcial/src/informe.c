/*
 * informe.c
 *
 *  Created on: 11 oct. 2020
 *      Author: l.rojas
 */

#include <stdio.h>
#include "utn.h"
#include "aviso.h"
#include "cliente.h"
#include "informe.h"


static int Informe_calcularAvisos(Aviso* listAviso, int lenAvisos,int id, int *pCountAviso,int estado);

/**
 * \brief Print the number of paused notices
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 * \param int estado: status of the publication of which you want to consult
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Informe_cantidadDeAvisosPausados(Aviso *listAviso, int lenAvisos,Cliente *listCliente,int lenCliente,int estado)
{
	int retorno = -1;
	int actualCounter;
	int maxContador;

	if(listAviso !=NULL && listCliente !=NULL && lenAvisos>0 && lenCliente>0 && Aviso_isEmpty(listAviso, lenAvisos)==0)
	{
		for(int i=0;i<lenCliente;i++)
		{
			Informe_calcularAvisos(listAviso,lenAvisos,listCliente[i].id,&actualCounter,estado);
			if(i==0 || actualCounter>maxContador)
			{
				maxContador = actualCounter;
			}
		}
		printf("\nCANTIDAD AVISOS PAUSADOS ->  %d\n",maxContador);
		retorno=0;
	}
	else
	{
		printf("\nNo hay datos cargados.\n");
	}
	return retorno;
}

/**
 * \brief Prints the number of active customer notices
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 * \param int estado: status of the publication of which you want to consult
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Informe_imprimirClienteAvisosACTIVOS(Aviso* listAviso, int lenAvisos,Cliente *listCliente,int lenCliente,int estado)
{
	int retorno = -1;
	int actualCounter;
	int maxContador;
	Cliente bufferMaxCliente;

	if(listAviso !=NULL && listCliente !=NULL && lenAvisos>0 && lenCliente>0  && Aviso_isEmpty(listAviso, lenAvisos)==0)
	{
		printf("\nNOMBRE          APELLIDO        CUIT             ID        CANTIDAD DE AVISOS  \n");
		for(int i=0;i<lenCliente;i++)
		{
			Informe_calcularAvisos(listAviso,lenAvisos,listCliente[i].id,&actualCounter,estado);
			if(i==0 || actualCounter>maxContador)
			{
				maxContador = actualCounter;
				bufferMaxCliente = listCliente[i];
			}
		}
		printf("\n%-15s %-15s %4s %7d %15d\n",bufferMaxCliente.nombre,bufferMaxCliente.apellido,bufferMaxCliente.cuit,bufferMaxCliente.id,maxContador);
		retorno=0;
	}
	else
	{
		printf("\nNo hay datos cargados.\n");
	}
	return retorno;
}

/**
 * \brief Calculate the amount of notice in a certain state
 * \param Aviso *listCliente: list to scrolls
 * \param int lenAvisos: Cliente array length
 * \param int id: Customer id to consult
 * \param int pCountAviso: Pointer that will have the number of notices that an ID has
 * \param int estado: status of the publication of which you want to consult
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int Informe_calcularAvisos(Aviso* listAviso, int lenAvisos,int id, int *pCountAviso,int estado)
{
	int retorno=-1;
	int avisosPorCliente=0;

	for(int i=0; i<lenAvisos; i++)
	{

		if(listAviso[i].isEmpty == FALSE   && listAviso[i].idCliente == id)
		{
			switch(estado)
			{
				case 1:
					if(listAviso[i].estado == 0)
					{
						avisosPorCliente++;
					}
				break;

				case 2:
					if(listAviso[i].estado == 1)
					{
						avisosPorCliente++;
					}
				break;

				default:avisosPorCliente++;
				break;
			}
		}
	}
	*pCountAviso = avisosPorCliente;
	retorno=0;
	return retorno;
}

/**
 * \brief Calculate the number of alerts in any state of an ID 			// JUST FOR TEST //
 * \param Aviso *listCliente: list to scrolls
 * \param int lenAvisos: Cliente array length
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \param int estado: status of the publication of which you want to consult
 * \return (-1) if something went wrong, (0) if everything is OK.

int Informe_cantidadDeAvisosMAX(Aviso *listAviso, int lenAvisos,Cliente *listCliente,int lenCliente,int estado)
{
	int retorno = -1;
	int actualCounter;
	int maxContador;
	Cliente bufferMaxCliente;

	if(listAviso !=NULL && listCliente !=NULL && lenAvisos>0 && lenCliente>0)
	{
		printf("\nNOMBRE          APELLIDO        CUIT             CANTIDAD DE AVISOS\n");
		for(int i=0;i<lenCliente;i++)
		{
			Informe_calcularAvisos(listAviso,lenAvisos,listCliente[i].id,&actualCounter,estado);
			if(i==0 || actualCounter>maxContador)
			{
				maxContador = actualCounter;
				bufferMaxCliente = listCliente[i];
			}
		}
		printf("\n>CANTIDAD DE AVISOS MAX  %d",maxContador);
		printf("\n%-15s %-15s %4s %15d \n",bufferMaxCliente.nombre,bufferMaxCliente.apellido,bufferMaxCliente.cuit,maxContador);
		retorno=0;
	}
	return retorno;
}
*/


/**
 * \brief Print the item with more active notices
 * \param Aviso *listCliente: list to scrolls
 * \param int lenAvisos: Aviso array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int informe_rubroConMasAviso(Aviso *listAviso, int lenAvisos)
{
	int functionReturn=-1;
	int contador=0;
	int maxContador;
	int aux;
	if(listAviso!=NULL && lenAvisos>0 && Aviso_isEmpty(listAviso, lenAvisos)==0)
	{
		for(int i=0;i<lenAvisos;i++)
		{
			if(listAviso[i].isEmpty == FALSE && informe_calcularRubroRepetido(listAviso,lenAvisos,listAviso[i].rubro, &contador)==0)
			{
				if(i==0 || contador>maxContador)
				{
					maxContador = contador;
					aux = listAviso[i].rubro;
					functionReturn=0;
				}
			}
		}
		printf("\nEl rubro con mas avisos es el: %d  con %d Publicaciones\n",aux,contador);
	}
	else
	{
		printf("\nNo hay datos cargados.\n");
	}
	return functionReturn;
}

/**
 * \brief Calculate the number of times an item exists
 * \param Aviso *listCliente: list to scrolls
 * \param int len: Aviso array length
 * \param int rubro: item to compare
 * \param int pCounter: Pointer that will have the number of times the item exists
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int informe_calcularRubroRepetido(Aviso *list, int len, int rubro, int *pCounter)
{
	int functionReturn=-1;
	int counter=0;
	if(list!=NULL && len>0)
	{
		for(int i=0;i<len;i++)
		{
			if(list[i].isEmpty == FALSE && list[i].rubro == rubro)
			{
				counter++;
				functionReturn=0;
			}
		}
		*pCounter = counter;
	}
	return functionReturn;
}






