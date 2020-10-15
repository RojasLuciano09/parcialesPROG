/* cliente.c
 * Author: Nicolas Luciano Rojas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "utn.h"
#include "cliente.h"

static int UpperFirstChar(char *string);

/**
 * \brief Function to converts an string to lowercase and it first letter to uppercase
 * \param char *string: receive an string, preferents a name
 */
static int UpperFirstChar(char *string)
{
	int retornar = -1;
	char bufferName[LONG_NAME];
	strncpy(bufferName, string, LONG_NAME);
	bufferName[0] = toupper(bufferName[0]);
	for(int i=1;i<LONG_NAME;i++)
	{
		bufferName[i] = tolower(bufferName[i]);
	}
	strncpy(string, bufferName, LONG_NAME);
	retornar = 0;
	return retornar;
}

/**
 * \brief Function that scrolls through the list of notices in search of FALSE status
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Cliente_isEmpty(Cliente *listCliente, int lenCliente)
{
	int functionReturn=-1;
		if(listCliente!=NULL && lenCliente>0)
		{
			for(int i=0;i<lenCliente;i++)
			{
				if(listCliente[i].isEmpty==FALSE)
				{
					functionReturn=0;
					break;
				}
			}
		}
	return functionReturn;
}

/**
 * \brief Returns the position of an id
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \param int pIndex: Pointer that will have the position of the id
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Cliente_findID_returnINDEX(Cliente *listCliente, int lenCliente,int idToFind,int *pIndex)
{
	int functionReturn=-1;
	if(listCliente!=NULL && lenCliente>0 && idToFind >0 && pIndex!=NULL)
	{
		for(int i=0;i<lenCliente;i++)
		{
			if(listCliente[i].id == idToFind && listCliente[i].isEmpty==FALSE)
			{
				*pIndex = i;
				functionReturn=0;
				break;
			}
		}
	}
	return functionReturn;
}

/**
 * \brief Scroll through the list for an id to check if it exists
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \param int idToFind: id which will be searched
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Cliente_findID(Cliente *listCliente, int lenCliente,int idToFind)
{
	int functionReturn=-1;
	if(listCliente!=NULL && lenCliente>0 && idToFind >0)
	{
		for(int i=0;i<lenCliente;i++)
		{
			if(listCliente[i].id == idToFind && listCliente[i].isEmpty==FALSE)
			{
				functionReturn=0;
				break;
			}
		}
	}
	return functionReturn;
}

/**
 * \brief initialize the list
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Cliente_initList(Cliente *listCliente, int lenCliente)
{
	int functionReturn=-1;
	if(listCliente!=NULL && lenCliente>0)
	{
		for(int i=0; i<lenCliente;i++)
		{
			listCliente[i].id= -1;
			listCliente[i].isEmpty=TRUE;
		}
		functionReturn=0;
	}
	return functionReturn;
}

/**
 * \brief Generate a new ID
 */
static int Cliente_generateNewID()
{
	static int id=0;
	id=id+1;
	return id;
}

/**
 * \brief Scroll through the list looking for a free position
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \param int pFreeIndex: Pointer that will have the free position
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Cliente_searchFreeIndex(Cliente *listCliente, int lenCliente, int *pFreeIndex)
{
	int functionReturn =-1;
	if(listCliente != NULL && lenCliente>0 && pFreeIndex!=NULL)
	{
		for (int i = 0; i < lenCliente; i++)
		{
			if (listCliente[i].isEmpty == TRUE && listCliente[i].id == -1)
			{
				*pFreeIndex = i;
				functionReturn = 0;
				break;
			}
		}
	}
	return functionReturn;
}

/**
 * \brief Print customer information
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Cliente_print(Cliente *listCliente, int lenCliente)
{
	int functionReturn=-1;
	if(listCliente!=NULL && lenCliente>0 && Cliente_isEmpty(listCliente, lenCliente)==0)
	{
		printf("\nNOMBRE          APELLIDO         CUIT            ID \n");
		for(int i=0; i<lenCliente;i++)
		{
			if(listCliente[i].isEmpty==FALSE)
			{
				printf("%-15s %-15s  %-15s %-6d \n",listCliente[i].nombre,listCliente[i].apellido,listCliente[i].cuit,listCliente[i].id);
			}
		}
		printf("\n");
		functionReturn=0;
	}
	else
	{
		printf("\nNo hay Clientes cargados.\n");
	}
	return functionReturn;
}

/**
 * \brief Delete the requested id
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \param int idToDelete: ID to delete
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Cliente_removeByID(Cliente *listCliente, int lenCliente,int idToDelete)
{
	int functionReturn=-1;
	int indexToDelete;
	if(listCliente!=NULL && lenCliente>0)
	{
		for(int i=0;i<lenCliente;i++)
		{
			if(Cliente_findID_returnINDEX(listCliente,lenCliente,idToDelete,&indexToDelete)==0)
			{
				listCliente[indexToDelete].isEmpty=TRUE;
				functionReturn=0;
			}
		}
	}
	return functionReturn;
}

/**
 * \brief Request name, surname and cuit to register a new client, if the data is correct it will inform the ID of the same
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Cliente_alta(Cliente *listCliente,int lenCliente)
{
	int functionReturn=-1;
	int freeIndex;
	Cliente bufferCliente;
	printf("\nALTA CLIENTE\n");
	if(listCliente!=NULL && lenCliente>0 && Cliente_searchFreeIndex(listCliente,lenCliente,&freeIndex)==0)
	{
		if( utn_getString("\nNombre: ",ERROR,bufferCliente.nombre,ATTEMPTS,LONG_NAME)==0 	 	&&
			utn_getString("\nApellido: ",ERROR,bufferCliente.apellido,ATTEMPTS,LONG_NAME)==0 	&&
			utn_getCuit("Ingrese Cuit: ", ERROR, bufferCliente.cuit, ATTEMPTS,CUIT_SIZE)==0	 	&&
			Cliente_findByCuit(listCliente, lenCliente, bufferCliente.cuit)!=0					)
		 {
			UpperFirstChar(bufferCliente.nombre);
			UpperFirstChar(bufferCliente.apellido);
			listCliente[freeIndex] = bufferCliente;
			listCliente[freeIndex].id= Cliente_generateNewID();
			listCliente[freeIndex].isEmpty=FALSE;
			printf("\nDatos cargados correctamente. Su ID es: %d \n",listCliente[freeIndex].id);
			functionReturn=0;
		}
		else
		{
			printf("\nHubo un error en la toma de datos.\n");
		}
	}
	else
	{
		printf("\nNo hay espacio disponible..\n");
	}
	return functionReturn;
}

/**
 * \brief Find a client by CUIT and returns 0 if CUIT is found
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \param int cuit: cuit to search
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Cliente_findByCuit(Cliente *listCliente, int lenCliente,char *cuit)
{
	int retorno = -1;
	if (listCliente != NULL && lenCliente > 0 && cuit > 0)
	{
		for (int i = 0; i < lenCliente; i++)
		{
			if(listCliente[i].isEmpty == FALSE && strcmp(listCliente[i].cuit,cuit) == 0)
			{
				printf("Ese cuit ya existe.");
				retorno = 0;
				break;
			}
		}
	}
	return retorno;;
}

/**
 * \brief Request the id of a client to modify
 * \param Cliente *listCliente: list to scrolls
 * \param int lenCliente: Cliente array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Cliente_modificar(Cliente *listCliente, int lenCliente)
{
	int functionReturn=-1;
	int idToModify=2;
	int indexToModify;
	Cliente bufferCliente;
	if(listCliente != NULL && lenCliente>0 && Cliente_isEmpty(listCliente, lenCliente)==0)
	{

		Cliente_print(listCliente, lenCliente);
		if(
				utn_getInt("Ingrese el ID del cliente a modificar: ",ERROR,&idToModify,ATTEMPTS,INT_MIN,INT_MAX)==0 	&&
				Cliente_findID_returnINDEX(listCliente,lenCliente,idToModify,&indexToModify)==0				&&
				utn_getString("\nNombre: ",ERROR, bufferCliente.nombre, ATTEMPTS, LONG_NAME)==0      	 	&&
				utn_getString("\nApellido: ",ERROR, bufferCliente.apellido, ATTEMPTS, LONG_NAME)==0   		&&
				utn_getCuit("\nCUIT: ", ERROR, bufferCliente.cuit,ATTEMPTS,CUIT_SIZE)==0					&&
				Cliente_findByCuit(listCliente, lenCliente, bufferCliente.cuit)!=0							)
		{
			strncpy(listCliente[indexToModify].nombre,bufferCliente.nombre, LONG_NAME);
			strncpy(listCliente[indexToModify].apellido,bufferCliente.apellido, LONG_NAME);
			strncpy(listCliente[indexToModify].cuit,bufferCliente.cuit, CUIT_SIZE);
			functionReturn = 0;
			printf("\nSe actualizo correctamente el empleado\n");
		}
		else
		{
		printf("\nHubo un error en la toma de datos.\n");
		}
	}
	else
	{
		printf("\nNo hay espacio disponible ó no hay datos cargados.\n");
	}
	return functionReturn;
}


/**
 * \brief Make an automatic client load.  // JUST FOR TEST //
 */
void ClienteCargaAutomatica(Cliente *listCliente,int lenCliente)
{
strncpy(listCliente[2].nombre,"mauro",LONG_NAME);
strncpy(listCliente[2].apellido,"viale",LONG_NAME);
strncpy(listCliente[2].cuit,"23-37933047-1",LONG_NAME);
	    listCliente[2].id = Cliente_generateNewID();
	    listCliente[2].isEmpty = FALSE;

strncpy(listCliente[4].nombre,"usuario2",LONG_NAME);
strncpy(listCliente[4].apellido,"usuario2",LONG_NAME);
strncpy(listCliente[4].cuit,"23-37933047-2",LONG_NAME);
	    listCliente[4].id = Cliente_generateNewID();
	    listCliente[4].isEmpty = FALSE;

strncpy(listCliente[6].nombre,"usuario3",LONG_NAME);
strncpy(listCliente[6].apellido,"usuario3",LONG_NAME);
strncpy(listCliente[6].cuit,"23-37933047-3",LONG_NAME);
	    listCliente[6].id = Cliente_generateNewID();
	    listCliente[6].isEmpty = FALSE;

strncpy(listCliente[8].nombre,"alberto",LONG_NAME);
strncpy(listCliente[8].apellido,"nisman",LONG_NAME);
strncpy(listCliente[8].cuit,"23-37933047-4",LONG_NAME);
	    listCliente[8].id = Cliente_generateNewID();
	    listCliente[8].isEmpty = FALSE;

strncpy(listCliente[10].nombre,"elba",LONG_NAME);
strncpy(listCliente[10].apellido,"zurita",LONG_NAME);
strncpy(listCliente[10].cuit,"23-37933047-5",LONG_NAME);
	    listCliente[10].id = Cliente_generateNewID();
	    listCliente[10].isEmpty = FALSE;

strncpy(listCliente[12].nombre,"aquiles",LONG_NAME);
strncpy(listCliente[12].apellido,"bailo",LONG_NAME);
strncpy(listCliente[12].cuit,"23-37933047-6",LONG_NAME);
	    listCliente[12].id = Cliente_generateNewID();
	    listCliente[12].isEmpty = FALSE;

strncpy(listCliente[14].nombre,"elsa",LONG_NAME);
strncpy(listCliente[14].apellido,"capunta",LONG_NAME);
strncpy(listCliente[14].cuit,"23-37933047-7",LONG_NAME);
	    listCliente[14].id = Cliente_generateNewID();
	    listCliente[14].isEmpty = FALSE;

strncpy(listCliente[16].nombre,"zoila",LONG_NAME);
strncpy(listCliente[16].apellido,"cerda",LONG_NAME);
strncpy(listCliente[16].cuit,"23-37933047-8",LONG_NAME);
	    listCliente[16].id = Cliente_generateNewID();
	    listCliente[16].isEmpty = FALSE;

strncpy(listCliente[18].nombre,"luz",LONG_NAME);
strncpy(listCliente[18].apellido,"rojas",LONG_NAME);
strncpy(listCliente[18].cuit,"23-37933047-9",LONG_NAME);
	    listCliente[18].id = Cliente_generateNewID();
	    listCliente[18].isEmpty = FALSE;

strncpy(listCliente[20].nombre,"marcia",LONG_NAME);
strncpy(listCliente[20].apellido,"ana",LONG_NAME);
strncpy(listCliente[20].cuit,"23-37933041-1",LONG_NAME);
	    listCliente[20].id = Cliente_generateNewID();
	    listCliente[20].isEmpty = FALSE;

	for(int i=0; i<lenCliente;i++)
	{
		UpperFirstChar(listCliente[i].nombre);
		UpperFirstChar(listCliente[i].apellido);
	}
}
