/* aviso.c
 * Author: Nicolas Luciano Rojas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "utn.h"
#include "aviso.h"
#include "cliente.h"

static int Aviso_generateNewID(void);
static int unsubscribeAClientPostsById(Aviso *listAviso, int lenAviso, int id);
static int calculateAdsPerClient(Aviso* listAviso, int lenAvisos,int id, int *pCountAviso);
static int checkPostStatus(Aviso *listAviso,int lenAviso,int idCliente,int estado);
static int joinDataFromBothEntities(Aviso *listAviso, Cliente *listCliente, int lenAviso, int lenCliente,int posicionAviso,int estado);
static int unsubscribeAPostByItsId(Aviso *listAviso,int lenAviso,int idAviso,int estado);
static int printInACertainState(Aviso *listAviso, Cliente *listCliente,int posicionCliente,int posicion,int estado);

/**
 * \brief Function that scrolls through the list of notices in search of FALSE status
 * \param Aviso *listAviso: list to scrolls
 * \param int len: Aviso array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_isEmpty(Aviso *listAviso, int len)
{
	int functionReturn =-1;
	if(listAviso != NULL && len > 0)
	{
		for(int i=0; i<len; i++)
		{
			if(listAviso[i].isEmpty == FALSE)
			{
				functionReturn =0;
				break;
			}
		}
	}
	return functionReturn;
}

/** \brief Initialize the Aviso list
 * \param Aviso *listAviso : list to go
 * \param int len: Aviso array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_initList(Aviso *listAviso, int len)
{
	int functionReturn = -1;
	if (listAviso != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			listAviso[i].estado = -1;
			listAviso[i].id = -1;
			listAviso[i].isEmpty = TRUE;
		}
		functionReturn = 0;
	}
	return functionReturn;
}

/** \brief Generate a new ID
 */
static int Aviso_generateNewID(void)
{
	static int id = 0;
	id = id + 1;
	return id;
}

/** \brief Scrolls the list looking for a free position and return the index
 * \param Aviso *listAviso : list to go
 * \param int len: Aviso array length
 * \param int *pFreeIndex: Pointer that will have the free index
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_searchFreeIndex(Aviso *listAviso, int len, int *pFreeIndex) {
	int functionReturn = -1;
	if (listAviso != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			if (listAviso[i].isEmpty == TRUE && listAviso[i].id == -1)
			{
				*pFreeIndex = i;
				functionReturn = 0;
				break;
			}
		}
	}
	return functionReturn;
}

/** \brief Scroll through the list and print the data
 * \param Aviso *listAviso : list to go
 * \param int len: Aviso array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_print(Aviso *listAviso, int len) {
	int functionReturn = -1;
	char strTipo[8];
		if (listAviso != NULL && len > 0 && Aviso_isEmpty(listAviso, len)==0)
		{
			printf("\nREPORTE  PUBLICACIONES\n");
			printf("\nPUBLICACIONES    ID_AVISO      RUBRO        ESTADO       ID_CLIENTE \n");
			for (int i = 0; i<len; i++)
			{
				if (listAviso[i].isEmpty == FALSE)
				{
					if (listAviso[i].estado == 1 )
					{
						strncpy(strTipo,"ACTIVA",8);
					}
					else
					{
						strncpy(strTipo,"PAUSADA",8);
					}
					printf("%-15s %-6d %8d  %13s %8d\n",listAviso[i].textoAviso,listAviso[i].id,listAviso[i].rubro,strTipo,listAviso[i].idCliente);
				}
			}
			functionReturn = 0;
	    }
		else
		{
			printf("\nNo hay Avisos cargados.\n");
		}
	return functionReturn;
}

/** \brief Prints the data of the publications of an ID
 * \param Aviso *listAviso : list to go
 * \param int len: Aviso array length
 * \param int idCliente: ID from which the publications will be searched
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_printDataByIDClient(Aviso *listAviso, int len,int idCliente) {
	int functionReturn = -1;
	char strTipo[8];

		if (listAviso != NULL && len > 0 && Aviso_isEmpty(listAviso, len)==0 )
		{
			printf("\nPUBLICACIONES DEL CLIENTE N°: %d \n",idCliente);
			printf("\nCONTENIDO       ID_Aviso       RUBRO       ESTADO \n");
			for (int i = 0; i < len; i++)
			{
				if(listAviso[i].isEmpty == FALSE && listAviso[i].idCliente == idCliente)
				{
					if (listAviso[i].estado == 1 )
					{
						strncpy(strTipo,"ACTIVA",8);
					}
					else
					{
						strncpy(strTipo,"PAUSADA",8);
					}
					printf("%-18s %-6d %8d  %13s \n",listAviso[i].textoAviso,listAviso[i].id,listAviso[i].rubro,strTipo);
					functionReturn = 0;
				}
			}
	    }
	return functionReturn;
}

/** \brief Print all the publications each client has
 * \param Aviso *listAviso : list to go
 * \param Cliente *listCliente : list to go
 * \param int lenAvisos: Aviso array length
 * \param int lenCliente: Cliente array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_imprimirClienteJuntoACantidadDeAvisos(Aviso* listAviso, int lenAvisos,Cliente *listCliente,int lenCliente)
{
	int functionReturn = -1;
	int contadorPublicaciones=0;

	if(listAviso !=NULL && listCliente !=NULL && lenAvisos>0 && lenCliente>0 && Aviso_isEmpty(listAviso, lenAvisos)==0)
	{
		printf("\nPublicaciones activas de todos los clientes.\n");
		printf("\nNOMBRE          APELLIDO        CUIT             PUBLICACIONES ACTIVAS\n");
		for(int i=0;i<lenCliente;i++)
		{
			if(listCliente[i].isEmpty==FALSE)
			{
				calculateAdsPerClient(listAviso,lenAvisos,listCliente[i].id,&contadorPublicaciones);
				printf("%-15s %-15s %4s %15d \n",listCliente[i].nombre,listCliente[i].apellido,listCliente[i].cuit,contadorPublicaciones);
			}
		}
		functionReturn=0;
	}
	else
	{
		printf("\nNo hay datos cargados.\n");
	}
	return functionReturn;
}

/** \brief Calculate the number of posts of an ID
 * \param Aviso *listAviso : list to go
 * \param int lenAvisos: Aviso array length
 * \param int idCliente: ID from which the publications will be searched
 * \param int pCountAviso: Pointer that will have the number of publications of a client
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int calculateAdsPerClient(Aviso* listAviso, int lenAvisos,int id, int *pCountAviso)
{
	int functionReturn=-1;
	int avisosPorCliente=0;
	if(listAviso !=NULL && pCountAviso !=NULL && lenAvisos>0)
	{
	for(int i=0; i<lenAvisos; i++)
		{
			if(		listAviso[i].isEmpty == FALSE   &&
					listAviso[i].estado == 1 		&&
					listAviso[i].idCliente == id	)
			 {
				avisosPorCliente++;
			 }
		}
		*pCountAviso = avisosPorCliente;
		functionReturn=0;
	}
	return functionReturn;
}

/** \brief Search the id of a client through the publication id
 * \param Aviso *listAviso : list to go
 * \param int lenAvisos: Aviso array length
 * \param int idAviso: Id of a post
 * \param int pID: Pointer that will have the client ID
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_findID_ByPublicacion_index(Aviso *listAviso,int lenAviso,int idAviso,int *pID)
{
int functionReturn=-1;
int flag;
	if(listAviso!=NULL && lenAviso>0 && pID!=NULL)
	{
		flag=FALSE;
		for(int i=0; i<lenAviso;i++)
		{
			if(listAviso[i].id == idAviso)
			{
				*pID = listAviso[i].idCliente;
				functionReturn=0;
				flag=TRUE;
				break;
			}
		}
		if(flag == FALSE)
		{
			printf("\nEl aviso no existe.\n");
		}
	}
return functionReturn;
}

/** \brief Scrolls the list for an ID and returns the index
 * \param Aviso *listAviso : list to go
 * \param int lenAvisos: Aviso array length
 * \param int id: Id of a client
 * \param int pID: Pointer that will have the position of the ID
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_findByID_index(Aviso *listAviso,int lenAviso,int id,int *pIndex)
{
	int functionReturn=-1;

	if(listAviso!=NULL && lenAviso>0 && pIndex !=NULL)
	{
		for(int i=0;i<lenAviso;i++)
		{
			if(listAviso[i].id==id && listAviso[i].isEmpty == FALSE)
			{
				*pIndex=i;
				functionReturn=0;
				break;
			}
		}
	}
	return functionReturn;
}

/** \brief It will allow to create a new publication requesting the client's ID, its category and the content of the publication.
 * \param Aviso *listAviso : list to go
 * \param int len: Aviso array length
 * \param Cliente *listCliente : list to go
 * \param int lenCliente: Aviso array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_alta(Aviso *listAviso, int len,Cliente *listCliente, int lenCliente)
{
	int functionReturn = -1;
	int index;
	Aviso bufferAviso;

	if(listAviso!=NULL && len>0 && Aviso_searchFreeIndex(listAviso, len, &index)==0 && Cliente_isEmpty(listCliente, lenCliente)==0)
	{
		if(	utn_getInt("\nIngrese el ID del cliente: ",ERROR, &bufferAviso.idCliente, ATTEMPTS, INT_MIN, INT_MAX)==0    &&
			Cliente_findID(listCliente,lenCliente,bufferAviso.idCliente)==0									 	 		&&
			utn_getInt("\nIngrese rubro: ",ERROR,&bufferAviso.rubro, ATTEMPTS,0,MAX_RUBRO)==0 						    &&
			utn_getLetrasYEspacios(bufferAviso.textoAviso, LONG_AVISO, "\nTexto del aviso: ",ERROR, ATTEMPTS)==0	    )
		{
			listAviso[index] = bufferAviso;
			listAviso[index].estado = 1;
			listAviso[index].id= Aviso_generateNewID();
			listAviso[index].isEmpty=FALSE;
			printf("\nSu publicacion tiene el ID : %d\n",listAviso[index].id);
			functionReturn=0;
		}
		else
		{
		printf("\nERROR! Hubo en error en la toma de datos.\n");
		}
	}
	else
	{
		printf("\nERROR! No hay clientes cargados.\n");
	}
	return functionReturn;
}

/** \brief Unsubscribe all posts from an ID
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 * \param int id: Customer ID from which the publications will be downloaded
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int unsubscribeAClientPostsById(Aviso *listAviso, int lenAviso, int id)
{
int functionReturn = -1;
	if(listAviso!=NULL && lenAviso>0)
	{
		for(int i=0;i<lenAviso;i++)
		{
			if(listAviso[i].idCliente==id)
			{
				listAviso[i].isEmpty=TRUE;
			}
			functionReturn=0;
		}
	}
return functionReturn;
}

/** \brief Unsubscribe a client, his ID is requested, all his publications will be printed and if he makes the confirmation they will be unsubscribed
 * \param Aviso *listAviso : list to go
 * \param int len: Aviso array length
 * \param Cliente *listCliente : list to go
 * \param int lenCliente: Cliente array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_baja(Aviso *listAviso, int len,Cliente *listCliente, int lenCliente)
{
	int idToFind;
	int functionReturn = -1;
	int flagDelete;

	if (listAviso != NULL && len > 0 && Aviso_isEmpty(listAviso, len)==0 && Cliente_isEmpty(listCliente, lenCliente)==0)
	 {
			if( Aviso_printDataFromBothEntities(listAviso, listCliente, len, lenCliente,PRINT_BOTH_POST_STATUS)==0	 &&
				utn_getInt("\nIngrese ID del cliente a eliminar: ",ERROR, &idToFind, ATTEMPTS, INT_MIN,INT_MAX)==0   &&
				Cliente_findID(listCliente, lenCliente, idToFind)==0 												 &&
				Aviso_printDataByIDClient(listAviso, len,idToFind)==0                            					 )
			{
				utn_getInt("\nSeguro desea eliminar las publicaciones?: \n1)>SI\n2)>NO",ERROR, &flagDelete, ATTEMPTS, 1, 2);

				if(flagDelete==1 && unsubscribeAClientPostsById(listAviso, len, idToFind)==0)
				{
						Cliente_removeByID(listCliente, lenCliente, idToFind);
						printf("\nBAJA realizada con exito. \n");
						functionReturn=0;
				}
				else
				{
					printf("\nVolviendo al menu...\n");
				}
			}
			else
			{
				printf("\nERROR! No existe el ID...\n");
			}
	}
	else
	{
		printf("\nERROR! No hay publicaciones cargadas.\n");
	}
	return functionReturn;
}

/** \brief The id of a publication is requested and the information will be printed, confirmation will be requested to change its status to paused
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 * \param Cliente *listCliente : list to go
 * \param int lenCliente: Cliente array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_pausar(Aviso *listAviso, int lenAviso,Cliente *listCliente, int lenCliente)
{
		int functionReturn=-1;
		int idAviso=0;
		int idCliente;
		int flagModificarAviso;

			if(listAviso!=NULL && listCliente !=NULL && lenAviso>0 && lenCliente >0 && Cliente_isEmpty(listCliente, lenCliente)==0)
			{
				if( Aviso_printDataFromBothEntities(listAviso, listCliente, lenAviso, lenCliente,AVISO_ACTIVE)==0									&&
					utn_getInt("\nIngrese ID del Aviso a pausar: ",ERROR, &idAviso, ATTEMPTS,0,INT_MAX)==0  					  			  		&&
					Aviso_findID_ByPublicacion_index(listAviso, lenAviso, idAviso, &idCliente)==0 													&&
					checkPostStatus(listAviso, lenAviso, idAviso,AVISO_ACTIVE)==0																	&&
					Aviso_printDataByIDClient(listAviso, lenAviso,idCliente)==0									    								&&
					utn_getInt("\nQuiere cambiar el estado del aviso a  >PAUSADA< ? \n1)SI \n0)NO", ERROR, &flagModificarAviso, ATTEMPTS, 0,1)==0  	)
				{
					if(flagModificarAviso==1 && unsubscribeAPostByItsId(listAviso, lenAviso, idAviso,0)==0)
					{
						functionReturn=0;
						printf("\nCambios realizados exitosamente.\n");
					}
					else
					{
						printf("\nNo se realizaron cambios...\n");
					}
				}
				else
				{
					printf("\nHubo un error pausando el aviso.\n");
				}
			}
			else
			{
				printf("\nERROR! No hay publicaciones cargadas.\n");
			}

	return functionReturn;
}

/** \brief The id of a publication is requested and the information will be printed, confirmation will be requested to change its status to active
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 * \param Cliente *listCliente : list to go
 * \param int lenCliente: Cliente array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int unsubscribeAPostByItsId(Aviso *listAviso,int lenAviso,int idAviso,int estado)
{
	int functionReturn=-1;
	if(listAviso!=NULL && lenAviso>0 && idAviso >-1)
	{
		for(int i=0;i<lenAviso;i++)
		{
			if(listAviso[i].isEmpty== FALSE && listAviso[i].id==idAviso && listAviso[i].estado!=estado)
			{
				listAviso[i].estado=estado;
				functionReturn=0;
				break;
			}
		}
	}
	return functionReturn;
}

/** \brief The id of a publication is requested and the information will be printed, confirmation will be requested to change its status to active
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 * \param Cliente *listCliente : list to go
 * \param int lenCliente: Cliente array length
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_activar(Aviso *listAviso, int lenAviso,Cliente *listCliente, int lenCliente)
{
	int functionReturn=-1;
	int idAviso;
	int idCliente;
	int flagModificarAviso;

		if(listAviso!=NULL && listCliente !=NULL && lenAviso>0 && lenCliente >0 && Cliente_isEmpty(listCliente, lenCliente)==0)
		{			// HACER UN PRINT DE SOLO LAS PAUSADAS
			if( 	Aviso_printDataFromBothEntities(listAviso, listCliente, lenAviso, lenCliente,AVISO_PAUSE)==0								&&
					utn_getInt("\nIngrese ID del Aviso a activar",ERROR, &idAviso, ATTEMPTS, 0,INT_MAX)==0  									&&
					Aviso_findID_ByPublicacion_index(listAviso, lenAviso, idAviso, &idCliente)==0 												&&
					checkPostStatus(listAviso, lenAviso, idAviso,AVISO_PAUSE)==0																&&
					Aviso_printDataByIDClient(listAviso, lenAviso,idCliente)==0																	&&
					utn_getInt("\nQuiere cambiar el estado del aviso a  >ACTIVA< ?\n1)SI\n0)NO", ERROR, &flagModificarAviso, ATTEMPTS, 0,1)==0	)
			{
				if(flagModificarAviso==1 && unsubscribeAPostByItsId(listAviso, lenAviso, idAviso,1)==0)
				{
					functionReturn=0;
					printf("\nCambios realizados exitosamente.\n");
				}
				else
				{
					printf("\nNo se realizaron cambios...");
				}
			}
			else
			{
				printf("\nHubo un error activando el aviso.\n");
			}
		}
		else
		{
			printf("\nERROR! No hay publicaciones cargadas.\n");
		}
	return functionReturn;
}

/** \brief Request the id of a publication and check its status
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 * \param int idCliente: Customer id to check for paused posts
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int checkPostStatus(Aviso *listAviso,int lenAviso,int idCliente,int estado)
{
	int functionReturn=-1;
	int flag;
	if(listAviso!=NULL && lenAviso>0 && idCliente>0 && Aviso_isEmpty(listAviso, lenAviso)==0)
	{
		flag=FALSE;
		for(int i=0; i<lenAviso;i++)
		{
			if(listAviso[i].isEmpty==FALSE && listAviso[i].estado==estado && listAviso[i].id == idCliente)
			{
				functionReturn= 0;
				flag=TRUE;
			}
		}
		if(flag==FALSE)
		{
			printf("\nERROR! Revise el estado de la publicacion.\n");
		}
	}
return functionReturn;
}

/** \brief Prints the status of the publications and clients indexed by their id
 * \param Aviso *listAviso : list to go
 * \param Cliente *listCliente : list to go
 * \param int lenAviso: Aviso array length
 * \param int idCliente: Customer id to check for paused posts
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_printDataFromBothEntities(Aviso *listAviso, Cliente *listCliente, int lenAviso, int lenCliente,int estado)
{
	int functionReturn=-1;
	if(listAviso!=NULL && listCliente!=NULL && lenCliente>0 && lenAviso>0 &&  Aviso_isEmpty(listAviso, lenAviso)==0 && Cliente_isEmpty(listCliente, lenCliente)==0)
	{
		printf("\nAVISOS         ID_AVISO      ESTADO           NOMBRE          APELLIDO     ID_CLIENTE        CUIT      	       RUBRO");
		for(int i=0; i<lenAviso;i++)
		{
			joinDataFromBothEntities(listAviso, listCliente, lenAviso, lenCliente,i,estado);
		}
		functionReturn=0;
		printf("\n");
	}
	else
	{
		printf("\nNo hay publicaciones ó clientes cargados.\n");
	}
	return functionReturn;
}

/** \brief Join the data of both entities indexed by their id
 * \param Aviso *listAviso : list to go
 * \param Cliente *listCliente : list to go
 * \param int lenAviso: Aviso array length
 * \param int idCliente: Customer id to check for paused posts
 * \param int posicion: Position from which the information of the notice list will be searched
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int joinDataFromBothEntities(Aviso *listAviso, Cliente *listCliente, int lenAviso, int lenCliente,int posicionAviso,int estado)
{
	int functionReturn=-1;
	//char status[8];
	if(listAviso!=NULL && listCliente!=NULL && lenCliente>0 && lenAviso>0 &&  Aviso_isEmpty(listAviso, lenAviso)==0 && Cliente_isEmpty(listCliente, lenCliente)==0)
	{
		for(int x=0;x<lenCliente;x++)
		{
			if(listCliente[x].isEmpty==FALSE && listCliente[x].id == listAviso[posicionAviso].idCliente)
			{
				printInACertainState(listAviso, listCliente, x, posicionAviso, estado);
			}
		}
		functionReturn=0;
	}
	else
	{
		printf("\nNo hay datos cargados.");
	}
return functionReturn;
}

/** \brief Prints the status of the publications in a certain status, and clients indexed by their id
 * \param Aviso *listAviso : list to go
 * \param Cliente *listCliente : list to go
 * \param int lenAviso: Aviso array length
 * \param int idCliente: Customer id to check for paused posts
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int printInACertainState(Aviso *listAviso, Cliente *listCliente,int posicionCliente,int posicion,int estado)
{
	char status[8];
	int functionReturn=-1;
	switch(estado)
	{
	case 1:
		strncpy(status,"ACTIVA",8);
		printf("\n%-18s %-8d  %-15s  %-15s %-15s %-14d %-6s %6d",listAviso[posicion].textoAviso,listAviso[posicion].id,status,listCliente[posicionCliente].nombre,listCliente[posicionCliente].apellido,listCliente[posicionCliente].id,listCliente[posicionCliente].cuit,listAviso[posicion].rubro);
		functionReturn=0;
	break;

	case 0:
		strncpy(status,"PAUSADA",8);
		printf("\n%-18s %-8d  %-15s  %-15s %-15s %-14d %-6s %6d",listAviso[posicion].textoAviso,listAviso[posicion].id,status,listCliente[posicionCliente].nombre,listCliente[posicionCliente].apellido,listCliente[posicionCliente].id,listCliente[posicionCliente].cuit,listAviso[posicion].rubro);
		functionReturn=0;
	break;

	//Prints both status
	default:
		if (listAviso[posicion].estado == 1 )
		{
			strncpy(status,"ACTIVA",8);
		}
		else
		{
			strncpy(status,"PAUSADA",8);
		}
		printf("\n%-18s %-8d  %-15s  %-15s %-15s %-14d %-6s %6d",listAviso[posicion].textoAviso,listAviso[posicion].id,status,listCliente[posicionCliente].nombre,listCliente[posicionCliente].apellido,listCliente[posicionCliente].id,listCliente[posicionCliente].cuit,listAviso[posicion].rubro);
		functionReturn=0;
	break;
	}
	return functionReturn;
}

/** \brief Perform an automatic data upload. //JUST FOR TEST//
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 */
void Aviso_cargaAutomatica(Aviso *listAviso)
{
	strncpy(listAviso[1].textoAviso,"Venta de autos",LONG_AVISO);
			listAviso[1].id =Aviso_generateNewID();
			listAviso[1].estado = 1; //ACTIVA 1
			listAviso[1].idCliente =1;
			listAviso[1].isEmpty = FALSE;
			listAviso[1].rubro = 1;

	strncpy(listAviso[3].textoAviso,"Venta de motos",LONG_AVISO);
			listAviso[3].id =Aviso_generateNewID();
			listAviso[3].estado = 0; //PAUSA 0
			listAviso[3].idCliente =2;
			listAviso[3].isEmpty = FALSE;
			listAviso[3].rubro = 1;

	strncpy(listAviso[5].textoAviso,"Venta de trineos",LONG_AVISO);
			listAviso[5].id =Aviso_generateNewID();
			listAviso[5].estado = 1; //ACTIVA 1
			listAviso[5].idCliente =7;
			listAviso[5].isEmpty = FALSE;
			listAviso[5].rubro = 1;

	strncpy(listAviso[7].textoAviso,"Venta de skate",LONG_AVISO);
			listAviso[7].id =Aviso_generateNewID();
			listAviso[7].estado = 0; //ACTIVA 1
			listAviso[7].idCliente =7;
			listAviso[7].isEmpty = FALSE;
			listAviso[7].rubro = 2;

	strncpy(listAviso[9].textoAviso,"Venta de bicicleta",LONG_AVISO);
			listAviso[9].id =Aviso_generateNewID();
			listAviso[9].estado = 0; //ACTIVA 1
			listAviso[9].idCliente =7;
			listAviso[9].isEmpty = FALSE;
			listAviso[9].rubro = 3;

	strncpy(listAviso[11].textoAviso,"Venta de camion",LONG_AVISO);
			listAviso[11].id =Aviso_generateNewID();
			listAviso[11].estado = 1; //PAUSA 0
			listAviso[11].idCliente =7;
			listAviso[11].isEmpty = FALSE;
			listAviso[11].rubro =4;
/*
	strncpy(listAviso[13].textoAviso,"Venta de ruedas",LONG_AVISO);
			listAviso[13].id =Aviso_generateNewID();
			listAviso[13].estado = 1; //ACTIVA 1
			listAviso[13].idCliente =7;
			listAviso[13].isEmpty = FALSE;
			listAviso[13].rubro = 4;
*/
	strncpy(listAviso[15].textoAviso,"Venta de sillas",LONG_AVISO);
			listAviso[15].id =Aviso_generateNewID();
			listAviso[15].estado = 0; //ACTIVA 1
			listAviso[15].idCliente =10;
			listAviso[15].isEmpty = FALSE;
			listAviso[15].rubro =4;

	strncpy(listAviso[17].textoAviso,"Venta de monitor",LONG_AVISO);
			listAviso[17].id =Aviso_generateNewID();
			listAviso[17].estado = 0; //PAUSA 0
			listAviso[17].idCliente =10;
			listAviso[17].isEmpty = FALSE;
			listAviso[17].rubro =4;

	strncpy(listAviso[19].textoAviso,"Venta de gabinete",LONG_AVISO);
			listAviso[19].id =Aviso_generateNewID();
			listAviso[19].estado = 0; //ACTIVA 1
			listAviso[19].idCliente =10;
			listAviso[19].isEmpty = FALSE;
			listAviso[19].rubro = 4;

	strncpy(listAviso[21].textoAviso,"Venta de RAM",LONG_AVISO);
			listAviso[21].id =Aviso_generateNewID();
			listAviso[21].estado = 1; //ACTIVA 1
			listAviso[21].idCliente =2;
			listAviso[21].isEmpty = FALSE;
			listAviso[21].rubro = 4;

	strncpy(listAviso[23].textoAviso,"Venta de mouse",LONG_AVISO);
			listAviso[23].id =Aviso_generateNewID();
			listAviso[23].estado = 1; //PAUSA 0
			listAviso[23].idCliente =2;
			listAviso[23].isEmpty = FALSE;
			listAviso[23].rubro =4;

	strncpy(listAviso[25].textoAviso,"Venta de CPU",LONG_AVISO);
			listAviso[25].id =Aviso_generateNewID();
			listAviso[25].estado = 1; //ACTIVA 1
			listAviso[25].idCliente =2;
			listAviso[25].isEmpty = FALSE;
			listAviso[25].rubro = 4;

	strncpy(listAviso[28].textoAviso,"Venta de motos",LONG_AVISO);
			listAviso[28].id =Aviso_generateNewID();
					listAviso[28].estado = 1;
					listAviso[28].idCliente =2;
					listAviso[28].isEmpty = FALSE;
					listAviso[28].rubro = 1;

}
