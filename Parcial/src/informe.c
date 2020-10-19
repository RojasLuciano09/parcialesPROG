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

static int calculateNumberOfPostsInCertainState(Aviso* listAviso, int lenAvisos,int id, int *pCountAviso,int estado);
static int calculateRepeatedItem(Aviso *listAviso, int lenAviso, int rubro, int *pContador);

/**
 * \brief Print the number of paused notices
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 * \param int estado: status of the publication of which you want to consult
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Informe_cantidadDeAvisosPausados(Aviso *listAviso, int lenAvisos,Cliente *listCliente,int lenCliente)
{
	int functionReturn = -1;
	int contador=0;

	if(listAviso !=NULL && listCliente !=NULL && lenAvisos>0 && lenCliente>0 && Aviso_isEmpty(listAviso, lenAvisos)==0)
	{
		for(int i=0; i<lenAvisos; i++)
		{
			if(listAviso[i].isEmpty == FALSE)
			{
				if(listAviso[i].estado == 0)
				{
					contador++;
				}
			}
		}
		printf("\nCANTIDAD AVISOS PAUSADOS ->  %d \n",contador);
	}
	else
	{
		printf("\nERROR! No hay datos cargados.\n");
	}
	return functionReturn;
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
int Informe_imprimirAvisosEnUnCiertoEstado(Aviso* listAviso, int lenAvisos,Cliente *listCliente,int lenCliente,int estado)
{
	int functionReturn = -1;
	int contador;
	int maxContador;
	Cliente bufferMaxCliente;
	if(listAviso !=NULL && listCliente !=NULL && lenAvisos>0 && lenCliente>0  && Aviso_isEmpty(listAviso, lenAvisos)==0)
	{
		printf("\nNOMBRE          APELLIDO        CUIT               ID         CANTIDAD");
		for(int i=0;i<lenCliente;i++)
		{
			calculateNumberOfPostsInCertainState(listAviso,lenAvisos,listCliente[i].id,&contador,estado);
			if(i==0 || contador>maxContador )
			{
				maxContador = contador;
				bufferMaxCliente = listCliente[i];
			}
		}
		printf("\n%-15s %-15s %4s %7d %15d\n",bufferMaxCliente.nombre,bufferMaxCliente.apellido,bufferMaxCliente.cuit,bufferMaxCliente.id,maxContador);
		functionReturn=0;
	}
	else
	{
		printf("\nERROR! No hay datos cargados.\n");
	}
	return functionReturn;
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
static int calculateNumberOfPostsInCertainState(Aviso* listAviso, int lenAvisos,int id, int *pCountAviso,int estado)
{
	int functionReturn=-1;
	int avisosPorCliente=0;

	for(int i=0; i<lenAvisos; i++)
	{
		if(listAviso[i].isEmpty == FALSE   && listAviso[i].idCliente == id)
		{
			switch(estado)
			{
				case 0:
					if(listAviso[i].estado == 0)
					{
						avisosPorCliente++;
					}
				break;

				case 1:
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
	functionReturn=0;
	return functionReturn;
}


/**
 * \brief Print the item with more active notices
 * \param Aviso *listCliente: list to scrolls
 * \param int lenAvisos: Aviso array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int informe_rubroConMasAviso(Aviso *listAviso, int lenAvisos)
{
	int functionReturn=-1;
	int contador;
	int maxContador;
	int aux;
	if(listAviso!=NULL && lenAvisos>0 && Aviso_isEmpty(listAviso, lenAvisos)==0)
	{
		for(int i=0;i<lenAvisos;i++)
		{
			if(listAviso[i].isEmpty == FALSE && calculateRepeatedItem(listAviso,lenAvisos,listAviso[i].rubro, &contador)==0)
			{
				if(i==0 || contador>maxContador)
				{
					maxContador = contador;
					aux = listAviso[i].rubro;
					functionReturn=0;
				}
			}
		}
		printf("\nEl rubro con mas avisos es el  %d  con  %d publicaciones.\n",aux,contador);
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
 * \param int lenAviso: Aviso array length
 * \param int rubro: item to compare
 * \param int pContador: Pointer that will have the number of times the item exists
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int calculateRepeatedItem(Aviso *listAviso, int lenAviso, int rubro, int *pContador)
{
	int functionReturn=-1;
	int contador=0;
	if(listAviso!=NULL && lenAviso>0)
	{
		for(int i=0;i<lenAviso;i++)
		{
			if(listAviso[i].isEmpty == FALSE && listAviso[i].rubro == rubro)
			{
				contador++;
				functionReturn=0;
			}
		}
		*pContador = contador;
	}
	return functionReturn;
}
