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
static int Aviso_bajarTodasLasPublicacionDeunID(Aviso *listAviso, int lenAviso, int id);
static int Aviso_calcularNumeroAvisosUnCliente(Aviso* listAviso, int lenAvisos,int id, int *pCountAviso);
static int thisIdHasPausedPosts(Aviso *listAviso,int lenAviso,int idCliente);
static int thisIdHasActivePosts(Aviso *listAviso,int lenAviso,int idCliente);

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
			printf("\nCONTENIDO    ID_Aviso      RUBRO        ESTADO        \n"); //Completar con lo que pidan en el reporte.

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
					printf("%-15s %-6d %8d  %13s \n",listAviso[i].textoAviso,listAviso[i].id,listAviso[i].rubro,strTipo);
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
int AvisoCliente_print(Aviso *listAviso, int len,int idCliente) {
	int functionReturn = -1;
	char strTipo[8];

		if (listAviso != NULL && len > 0 && Aviso_isEmpty(listAviso, len)==0 )
		{
			printf("\nPUBLICACIONES DEL CLIENTE N°: %d \n",idCliente);
			printf("\nCONTENIDO    ID_Aviso      RUBRO      ESTADO \n");
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
					printf("%-15s %-6d %8d  %13s \n",listAviso[i].textoAviso,listAviso[i].id,listAviso[i].rubro,strTipo);

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
	int retorno = -1;
	int contadorPublicaciones=0;

	if(listAviso !=NULL && listCliente !=NULL && lenAvisos>0 && lenCliente>0 && Aviso_isEmpty(listAviso, lenAvisos)==0)
	{
		printf("\nPublicaciones activas de todos los clientes.\n");
		printf("\nNOMBRE          APELLIDO        CUIT             PUBLICACIONES ACTIVAS\n");
		for(int i=0;i<lenCliente;i++)
		{
			if(listCliente[i].isEmpty==FALSE)
			{
				Aviso_calcularNumeroAvisosUnCliente(listAviso,lenAvisos,listCliente[i].id,&contadorPublicaciones);
				printf("%-15s %-15s %4s %15d \n",listCliente[i].nombre,listCliente[i].apellido,listCliente[i].cuit,contadorPublicaciones);
			}
		}
		retorno=0;
	}
	else
	{
		printf("\nNo hay datos cargados.\n");
	}
	return retorno;
}

/** \brief Calculate the number of posts of an ID
 * \param Aviso *listAviso : list to go
 * \param int lenAvisos: Aviso array length
 * \param int idCliente: ID from which the publications will be searched
 * \param int pCountAviso: Pointer that will have the number of publications of a client
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int Aviso_calcularNumeroAvisosUnCliente(Aviso* listAviso, int lenAvisos,int id, int *pCountAviso)
{
	int retorno=-1;
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
		retorno=0;
	}
	return retorno;
}

/** \brief Search the id of a client through the publication id
 * \param Aviso *listAviso : list to go
 * \param int lenAvisos: Aviso array length
 * \param int idPublicacion: Id of a post
 * \param int pID: Pointer that will have the client ID
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
int Aviso_findID_ByPublicacion_index(Aviso *listAviso,int lenAviso,int idPublicacion,int *pID)
{
int retorno=-1;

	if(listAviso!=NULL && lenAviso>0 && pID!=NULL)
	{
		for(int i=0; i<lenAviso;i++)
		{
			if(listAviso[i].id == idPublicacion)
			{
				*pID = listAviso[i].idCliente;
				retorno=0;
				break;
			}
		}

	}
return retorno;
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
	int retorno=-1;

	if(listAviso!=NULL && lenAviso>0 && pIndex !=NULL)
	{
		for(int i=0;i<lenAviso;i++)
		{
			if(listAviso[i].id==id && listAviso[i].isEmpty == FALSE)
			{
				*pIndex=i;
				retorno=0;
				break;
			}
		}
	}
	return retorno;
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
		if(	utn_getInt("\nIngrese el ID del cliente: ",ERROR, &bufferAviso.idCliente, ATTEMPTS, INT_MIN, INT_MAX)==0 &&
			Cliente_findID(listCliente,lenCliente,bufferAviso.idCliente)==0									 	 &&
			utn_getInt("\nIngrese rubro: ",ERROR,&bufferAviso.rubro, ATTEMPTS,0,MAX_RUBRO)==0 						 &&
			utn_getLetrasYEspacios(bufferAviso.textoAviso, LONG_AVISO, "\nTexto del aviso: ",ERROR, ATTEMPTS)==0	 )
		{
			listAviso[index] = bufferAviso;
			listAviso[index].estado = 1;
			listAviso[index].id= Aviso_generateNewID();
			listAviso[index].isEmpty=FALSE;
			printf("\nSu publicacion tiene el ID : %d\n",listAviso[index].id);
			functionReturn=0;
		}
		printf("\nERROR! Hubo en error en la toma de datos.\n");
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
static int Aviso_bajarTodasLasPublicacionDeunID(Aviso *listAviso, int lenAviso, int id)
{
int retorno = -1;
	if(listAviso!=NULL && lenAviso>0)
	{
		for(int i=0;i<lenAviso;i++)
		{
			if(listAviso[i].idCliente==id)
			{
				listAviso[i].isEmpty=TRUE;
			}
			retorno=0;
		}
	}
return retorno;
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
	int indexToDelete;
	int functionReturn = -1;
	int flagDelete;

	if (listAviso != NULL && len > 0 && Aviso_isEmpty(listAviso, len)==0 && Cliente_isEmpty(listCliente, lenCliente)==0)
	 {
			if( utn_getInt("\nIngrese ID de cliente a eliminar: ",ERROR, &idToFind, ATTEMPTS, INT_MIN,INT_MAX)==0   &&
				Cliente_findID_returnINDEX(listCliente, lenCliente, idToFind, &indexToDelete)==0    				&&
				AvisoCliente_print(listAviso, len,idToFind)==0                            )
			{
				utn_getInt("\nSeguro desea eliminar las publicaciones?: \n1)>SI\n2)>NO",ERROR, &flagDelete, ATTEMPTS, 1, 2);

				if(flagDelete==1 && Aviso_bajarTodasLasPublicacionDeunID(listAviso, len, idToFind)==0)
				{
						Cliente_removeByID(listCliente, lenCliente, idToFind);
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
		int retorno=-1;
		int idPublicacion=0;
		int idCliente;
		int index;
		int flagModificarAviso;

			if(listAviso!=NULL && listCliente !=NULL && lenAviso>0 && lenCliente >0 && Cliente_isEmpty(listCliente, lenCliente)==0)
			{
				if( utn_getInt("\nIngrese ID Publicacion: ",ERROR, &idPublicacion, ATTEMPTS, 0,INT_MAX)==0  					    &&
					Aviso_findID_ByPublicacion_index(listAviso, lenAviso, idPublicacion, &idCliente)==0 								    &&
					Aviso_findByID_index(listAviso, lenAviso, idCliente, &index)==0 													    &&
					thisIdHasActivePosts(listAviso, lenAviso, idCliente)==0															&&
					AvisoCliente_print(listAviso, lenAviso,idCliente)==0									    &&
					utn_getInt("\nCambiar publicacion a >pausada< ""\n1)SI""\n0)NO", ERROR, &flagModificarAviso, ATTEMPTS, 0,1)==0  )
				{
					if(flagModificarAviso==1)
					{
						listAviso[index].estado=0;
						retorno=0;
						printf("\nCambios realizados exitosamente.");
					}
					else
					{
						printf("\nNo se realizaron cambios...");
					}
				}
			}
			else
			{
				printf("\nERROR! No hay publicaciones cargadas.\n");
			}

	return retorno;
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
	int retorno=-1;
	int idPublicacion;
	int idCliente;
	int index;
	int flagModificarAviso;

		if(listAviso!=NULL && listCliente !=NULL && lenAviso>0 && lenCliente >0 && Cliente_isEmpty(listCliente, lenCliente)==0)
		{
			if( utn_getInt("\nIngrese ID Publicacion: ",ERROR, &idPublicacion, ATTEMPTS, 0,INT_MAX)==0  					    &&
					Aviso_findID_ByPublicacion_index(listAviso, lenAviso, idPublicacion, &idCliente)==0 						&&
					Aviso_findByID_index(listAviso, lenAviso, idCliente, &index)==0 											&&
					thisIdHasPausedPosts(listAviso, lenAviso, idCliente)==0														&&
					AvisoCliente_print(listAviso, lenAviso,idCliente)==0								&&
					utn_getInt("\nCambiar publicacion a >activa< ""\n1)SI""\n0)NO", ERROR, &flagModificarAviso, ATTEMPTS, 0,1)==0)
			{
				if(flagModificarAviso==1)
				{
					listAviso[index].estado=1;
					retorno=0;
					printf("\nCambios realizados exitosamente.");
				}
				else{printf("\nNo se realizaron cambios...");}
			}
		}else
		{
			printf("\nERROR! No hay datos cargados.\n");
		}
	return retorno;
}


/** \brief Request a customer id and check if you have posts in paused state
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 * \param int idCliente: Customer id to check for paused posts
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int thisIdHasPausedPosts(Aviso *listAviso,int lenAviso,int idCliente)
{
	int functionReturn=-1;
	int flag;
	if(listAviso!=NULL && lenAviso>0 && idCliente>0 && Aviso_isEmpty(listAviso, lenAviso)==0)
	{
		flag=FALSE;
		for(int i=0; i<lenAviso;i++)
		{
			if(listAviso[i].isEmpty==FALSE && listAviso[i].estado== 0 && listAviso[i].idCliente == idCliente)
			{

				functionReturn= 0;
				flag=TRUE;
			}

		}
		if(flag==FALSE)
		{
			printf("\nERROR! El id no tiene publicaciones pausadas\n");
		}
	}
return functionReturn;
}

/** \brief Request a customer id and check if you have posts in active state
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 * \param int idCliente: Customer id to check for paused posts
 * \return (-1) if something went wrong, (0) if everything is OK.
 */
static int thisIdHasActivePosts(Aviso *listAviso,int lenAviso,int idCliente)
{
	int functionReturn=-1;
	int flag;
	if(listAviso!=NULL && lenAviso>0 && idCliente>0 && Aviso_isEmpty(listAviso, lenAviso)==0)
	{
		flag=FALSE;
		for(int i=0; i<lenAviso;i++)
		{
			if(listAviso[i].isEmpty==FALSE && listAviso[i].estado==1 && listAviso[i].idCliente == idCliente)
			{

				functionReturn= 0;
				flag=TRUE;
			}

		}
		if(flag==FALSE)
		{
			printf("\nERROR! El id no tiene publicaciones activas.\n");
		}
	}
return functionReturn;
}

/** \brief Perform an automatic data upload. //JUST FOR TEST//
 * \param Aviso *listAviso : list to go
 * \param int lenAviso: Aviso array length
 */
void Aviso_cargaAutomatica(Aviso *listAviso)
{
	strncpy(listAviso[1].textoAviso,"Aviso1",LONG_AVISO);
			listAviso[1].id =Aviso_generateNewID();
			listAviso[1].estado = 1;
			listAviso[1].idCliente =1;
			listAviso[1].isEmpty = FALSE;
			listAviso[1].rubro = 1;

	strncpy(listAviso[3].textoAviso,"Aviso2",LONG_AVISO);
			listAviso[3].id =Aviso_generateNewID();
			listAviso[3].estado = 1;
			listAviso[3].idCliente =2;
			listAviso[3].isEmpty = FALSE;
			listAviso[3].rubro = 1;

	strncpy(listAviso[5].textoAviso,"Aviso3",LONG_AVISO);
			listAviso[5].id =Aviso_generateNewID();
			listAviso[5].estado = 1;
			listAviso[5].idCliente =3;
			listAviso[5].isEmpty = FALSE;
			listAviso[5].rubro = 1;

	strncpy(listAviso[7].textoAviso,"Aviso4",LONG_AVISO);
			listAviso[7].id =Aviso_generateNewID();
			listAviso[7].estado = 1; //activa
			listAviso[7].idCliente =4;
			listAviso[7].isEmpty = FALSE;
			listAviso[7].rubro = 2;

	strncpy(listAviso[9].textoAviso,"Aviso5",LONG_AVISO);
			listAviso[9].id =Aviso_generateNewID();
			listAviso[9].estado = 1; //activa
			listAviso[9].idCliente =5;
			listAviso[9].isEmpty = FALSE;
			listAviso[9].rubro = 3;

	strncpy(listAviso[11].textoAviso,"Aviso6",LONG_AVISO);
			listAviso[11].id =Aviso_generateNewID();
			listAviso[11].estado = 1; //activa
			listAviso[11].idCliente =6;
			listAviso[11].isEmpty = FALSE;
			listAviso[11].rubro =4;

	strncpy(listAviso[13].textoAviso,"Aviso7",LONG_AVISO);
			listAviso[13].id =Aviso_generateNewID();
			listAviso[13].estado = 1; //activa
			listAviso[13].idCliente =7;
			listAviso[13].isEmpty = FALSE;
			listAviso[13].rubro = 4;

	strncpy(listAviso[15].textoAviso,"Aviso8",LONG_AVISO);
			listAviso[15].id =Aviso_generateNewID();
			listAviso[15].estado = 1; //activa
			listAviso[15].idCliente =8;
			listAviso[15].isEmpty = FALSE;
			listAviso[15].rubro =4;

	strncpy(listAviso[17].textoAviso,"Aviso9",LONG_AVISO);
			listAviso[17].id =Aviso_generateNewID();
			listAviso[17].estado = 0; //activa
			listAviso[17].idCliente =9;
			listAviso[17].isEmpty = FALSE;
			listAviso[17].rubro =4;

	strncpy(listAviso[19].textoAviso,"Aviso10",LONG_AVISO);
			listAviso[19].id =Aviso_generateNewID();
			listAviso[19].estado = 1; //activa
			listAviso[19].idCliente =10;
			listAviso[19].isEmpty = FALSE;
			listAviso[19].rubro = 4;

	strncpy(listAviso[21].textoAviso,"Aviso11",LONG_AVISO);
			listAviso[21].id =Aviso_generateNewID();
			listAviso[21].estado = 1;
			listAviso[21].idCliente =1;
			listAviso[21].isEmpty = FALSE;
			listAviso[21].rubro = 4;

	strncpy(listAviso[23].textoAviso,"Aviso12",LONG_AVISO);
			listAviso[23].id =Aviso_generateNewID();
			listAviso[23].estado = 1;
			listAviso[23].idCliente =1;
			listAviso[23].isEmpty = FALSE;
			listAviso[23].rubro =4;
}
