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


static int checkIfExist(LinkedList* thisList,int(*pFunc)(void*,void*),void* element,char* msg);

static int controller_searchMaxIDVenta(LinkedList* listaVentas);
static int controller_findVentaFromID(LinkedList* listaVentas ,LinkedList* listaClientes,void* arg);
static int controller_findByIdAfiche(LinkedList* listaVentas ,void* arg,int* index);
static int controller_searchMaxIDCliente(LinkedList* thisList);
static int controller_searchMaxIDVenta(LinkedList* listaVentas);
static int controller_findById(LinkedList* listaClientes,void* arg);

/**
 * \brief Función para encontrar el id maximo en una lista.
 * \param LinkedList* listaVentas: Puntero a la lista de clientes.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
static int controller_searchMaxIDCliente(LinkedList* thisList)
{
	int retornar=-1;
	int len = ll_len(thisList);
	Cliente* bufferEmp;
	int id;
	int maxId;
	if(thisList!=NULL && !ll_isEmpty(thisList))
	{
		for(int i=0;i<len;i++)
		{
			bufferEmp = ll_get(thisList, i);
			Cliente_getId(bufferEmp, &id);
			if(i==0 || id>maxId)
			{
				maxId = id;
				retornar = maxId+1;
			}
		}
	}
	return retornar;
}

/**
 * \brief Función para encontrar el id maximo en una lista.
 * \param LinkedList* listaVentas: Puntero a la lista de ventas.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
static int controller_searchMaxIDVenta(LinkedList* listaVentas)
{
	int retornar=-1;
	int len = ll_len(listaVentas);
	Afiche* bufferEmp;
	int id;
	int maxId;
	if(listaVentas!=NULL && !ll_isEmpty(listaVentas))
	{
		for(int i=0;i<len;i++)
		{
			bufferEmp = ll_get(listaVentas, i);
			Afiche_getId(bufferEmp, &id);

			if(i==0 || id>maxId)
			{
				maxId = id;
				retornar = maxId+1;
			}
		}
	}
	return retornar;
}

/**
 * \brief Función generica para ver si un elemento existe en una lista.
 * \param LinkedList* thisList: Puntero a la lista.
 * \param void* element_one: Argumento que tendra el valor a buscar.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
static int checkIfExist(LinkedList* thisList,int(*pFunc)(void*,void*),void* element,char* msg) ///////////------------------------------
{
	int out=-1;
	if(thisList!=NULL && !ll_isEmpty(thisList))
	{
		if(ll_map2(thisList, pFunc,element)==0)
		{
			printf(msg);
			out=0;
		}
	}
	return out;
}

/**
 * \brief Función para buscar un id en la lista de ventas.
 * \param LinkedList* listaVentas: Puntero a la lista de clientes.
 * \param void* arg: Argumento que tendra el valor del id del cliente a buscar.
 * \param int* index: Puntero que contiene el indice.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
static int controller_findVentaFromID(LinkedList* listaVentas,LinkedList* listaClientes,void* arg)
{
	int out=-1;
	int len = ll_len(listaVentas);
	void* element;
	char id_cliente[SIZE];
	if(listaVentas!=NULL)
	{
		for(int i =0; i<len;i++)
		{
			element = ll_get(listaVentas, i);
			if(devuelvoElementoPorID(element,arg,id_cliente)==0)
			{
				controller_findById(listaClientes, id_cliente);
				out=0;
			}
		}
	}
	return out;
}

/**
 * \brief Función para buscar un id en la lista de ventas y devuelve su indice.
 * \param LinkedList* listaVentas: Puntero a la lista de clientes.
 * \param void* arg: Argumento que tendra el valor del id del cliente a buscar.
 * \param int* index: Puntero que contiene el indice.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
static int controller_findByIdAfiche(LinkedList* listaVentas,void* arg,int* index)
{
	int out=-1;

	if(listaVentas!=NULL)
	{
		*index = ll_search(listaVentas, comparoID, arg);
		out=0;
	}
	return out;
}

/**
 * \brief Función para buscar un id en la lista de clientes.
 * \param LinkedList* listaClientes: Puntero a la lista de clientes.
 * \param void* arg: Argumento que tendra el valor del id del cliente a buscar.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
static int controller_findById(LinkedList* listaClientes,void* arg)
{
	int out=-1;
	printf("\nID     Nombre      Apellido        Cuit\n");
	if(listaClientes!=NULL && !ll_isEmpty(listaClientes))
	{
		if(ll_map2(listaClientes, Cliente_printById,arg)==0)
		{
			out=0;
		}
	}
	return out;
}

/**
 * \brief Función generica cargar datos.
 * \param LinkedList* list: Puntero a la lista.
 * \param parserFunction pFunc: Recibe una funcion criterio del tipo parser.
 * \param char* openType: Tipo de lectura o escritura para los archivos.
 * \param char* path: Ruta del archivo.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
int controller_loadOrSave(char* openType,  parserFunction pFunc,char* path, LinkedList* list)
{
	int out=-1;
	FILE* pFile;
	if(list != NULL && path != NULL)
	{
		pFile = fopen(path, openType);
		if(pFile != NULL)
		{
			pFunc(pFile,list);
			out=0;
			fclose(pFile);
		}
	}
	return out;
}

/**
 * \brief Función generica para imprimir por consola.
 * \param LinkedList* thisList: Puntero a la lista.
 * \param int(*pFunc)(void*): Funcion criterio para imprimir los datos.
 * \param char* selectEntity: Cadena de caracteres para mostrar la informacion.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
int controller_print(LinkedList* thisList,int(*pFunc)(void*),char* selectEntity)
{
	int out=-1;
	if(thisList!=NULL && !ll_isEmpty(thisList))
	{
		printf(selectEntity);
		ll_map(thisList, pFunc);
		out=0;
	}
	return out;
}

/**
 * \brief Función para agregar un cliente pidiendo nombre, apellido y cuit. El id se genera automáticamente
 * \param LinkedList* thisList: Puntero a la lista
 * \return int output  (-1) Error: si el puntero a la listas es NULL
                       ( 0) todo ok
 */
int controller_addEmployee(LinkedList* thisList)
{
	int output=-1;
	char idAux[SIZE];
	char nombreAux[SIZE];
	char apellidoAux[SIZE];
	char cuitAux[SIZE];
	Cliente* buffer;

	if(thisList!=NULL  &&  !ll_isEmpty(thisList))
		{
		  if( utn_getString("\nNombre Cliente: \n", ERROR, nombreAux, ATTEMPTS, SIZE)==0 			&&
			  utn_getString("\nApellido Cliente: \n", ERROR, apellidoAux, ATTEMPTS, SIZE)==0 		&&
			  utn_getCuit("\nCuit Cliente: \n", ERROR, cuitAux, ATTEMPTS, SIZE)==0 					&&
		      checkIfExist(thisList, thisCuitExists, cuitAux,CUIT_EXISTS)!=0						)
			{
			    sprintf(idAux, "%d",controller_searchMaxIDCliente(thisList));
			    printf("\nAlta exitosa, su id es: %s\n",idAux);
				buffer = Cliente_newParametros(idAux, nombreAux, apellidoAux, cuitAux);
				ll_add(thisList,buffer);
			}
			else
			{
				printf("\nHubo un error en la toma de datos...\n");
			}
		}
    return output;
}

/**
 * \brief Función para vender para realizar una venta pidiendo id del cliente, cant. de afiches, nombre del archivo y la zona a pegar. El id de la venta se genera automáticamente
 * \param LinkedList* listaVentas: Puntero a la lista de ventas
 * \param LinkedList* listaClientes: Puntero a la lista de clientes
 * \return int output  (-1) Error: si el puntero a la listas es NULL
                       ( 0) todo ok
 */
int controller_vender_afiches(LinkedList* listaVentas,LinkedList* listaClientes)
{
	int out=-1;
	char idAux[SIZE];
	char id_clienteAux[SIZE];
	char cantidad_afichesAux[SIZE];
	char nombre_archivoAux[SIZE];
	char zona_pegar_aficheAux[SIZE];
	Afiche* buffer;
	if(listaVentas!=NULL &&  listaClientes!=NULL &&  !ll_isEmpty(listaVentas) && !ll_isEmpty(listaClientes))
	{
		if(		utn_getIntStr("\ningrese idcliente\n",ERROR, id_clienteAux, ATTEMPTS, SIZE)==0 						&&
				checkIfExist(listaClientes, veoSiExisteEsteID, id_clienteAux, "\nEl id si existe!\n")==0     		&&
				utn_getIntStr("\ningrese cantidad afiches\n",ERROR, cantidad_afichesAux, ATTEMPTS, SIZE)==0 		&&
				utn_getFileName("\nIngrese nombre archivo", ERROR, nombre_archivoAux, ATTEMPTS, SIZE)==0 			&&
				utn_getIntStr("\ningrese zona_pegar_afiche 0(CABA) 1(ZONASUR 2(ZONANORTE))\n", ERROR, zona_pegar_aficheAux, ATTEMPTS, SIZE)==0	 )
		{
			sprintf(idAux, "%d",controller_searchMaxIDVenta(listaVentas));
			printf("\nDatos cargados correctamente id de la venta es: %s\n",idAux);
			buffer = Afiche_newParametros(idAux, id_clienteAux, cantidad_afichesAux, nombre_archivoAux, zona_pegar_aficheAux,"1");
			ll_add(listaVentas,buffer);
		}
		else
		{
			printf("\nHubo un error en la carga de datos");
		}
	}else
	{
		printf("\nNo hay datos cargados");
	}
	return out;
}

/**
 * \brief Función para modificar una venta en un estado.
 * \param LinkedList* listaVentas: Puntero a la lista de ventas.
 * \param LinkedList* listaClientes: Puntero a la lista de clientes.
 * \param void* arg: Argumento para filtrar la lista de ventas por un estado.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
int controller_modificar_Venta(LinkedList* listaVentas,LinkedList* listaClientes,void* arg)
{
	int out=-1;
	int indexAfiche;
	int option;
	char id_venta[SIZE];
	char cantidad_afiches[SIZE];
	char nombre_archivo[SIZE];
	char ZONA[SIZE];
	Afiche* buffer;
	LinkedList* listaModificada;

	if(listaVentas!=NULL && !ll_isEmpty(listaVentas) && listaClientes!=NULL && !ll_isEmpty(listaClientes))
	{
		listaModificada = ll_filterBySomethingCloneAndReturn(listaVentas, afichesCobrados,arg);

		if(listaModificada!=NULL && controller_print(listaModificada,Afiche_print,AFICHE_PRINT)==0
				&&  utn_getIntStr("\nIngrese el ID de la venta: ",ERROR, id_venta, ATTEMPTS,SIZE)==0
				&& controller_findVentaFromID(listaVentas,listaClientes, id_venta)==0
				&& controller_findByIdAfiche(listaVentas, id_venta, &indexAfiche)==0              )
		{
			buffer = ll_get(listaVentas, indexAfiche);
		do {

			if(buffer!=NULL && utn_getInt("\n Que desea modificar: \n1)CANTIDAD AFICHES \n2)NOMBRE ARCHIVO \n3)ZONA: 0(CABA) 1(ZONASUR) 2(ZONANORTE) \n0)EXIT \n>:",ERROR,&option,ATTEMPTS,-1,3)==0)
			{
				switch(option)
				{
				case 1:
					if(utn_getIntStr("\nIngrese la nueva cantidad de afiches : ",ERROR,cantidad_afiches,ATTEMPTS,LONG_NAME)==0 &&
							Afiche_set_cantidad_afichesSTR(buffer, cantidad_afiches)==0 							)
					{
						ll_set(listaVentas, indexAfiche, buffer);
						out=0;
						printf("\nDatos actualizados...\n");
					}
					break;

				case 2:
					if(utn_getFileName("\nIngrese el nuevo nombre del archivo: ",ERROR,nombre_archivo,ATTEMPTS,LONG_NAME)==0 &&
							Afiche_set_nombre_archivo(buffer, nombre_archivo)==0 							)
					{
						ll_set(listaVentas, indexAfiche, buffer);
						out=0;
						printf("\nDatos actualizados...\n");
					}
					break;

				case 3:
					if(utn_getFileName("\nIngrese la nueva zona a pegar \n0(CABA) 1(ZONASUR) 2(ZONANORTE) : ",ERROR,nombre_archivo,ATTEMPTS,LONG_NAME)==0 &&
							Afiche_set_zona_pegar_aficheSTR(buffer, ZONA)==0 									)
					{
						ll_set(listaVentas, indexAfiche, buffer);
						out=0;
						printf("\nDatos actualizados...\n");
					}
					break;
				}
			}
		} while (option!=0);
		out=0;

		}else
		{
			printf("\n Hubo un error en la toma de datos, o el id no existe.");
		}
	}else
	{
		printf("\nNo hay datos para editar\n");
	}
	return out;
}

/**
 * \brief Función para cobrar una venta, solicita un ID cliente y si desea cambiar el estado de la venta.
 * \param LinkedList* listaVentas: Puntero a la lista de ventas.
 * \param LinkedList* listaClientes: Puntero a la lista de clientes.
 * \param void* arg: Argumento para filtrar la lista de ventas por un estado.
 * \return int output  (-1) Error: si el puntero a la listas es NULL.
                       ( 0) todo ok.
 */
int controller_cobrar_venta(LinkedList *listaVentas, LinkedList *listaClientes) {
	int out = -1;
	char id_venta[SIZE];
	int indexAfiche;
	int option;
	Afiche *buffer;
	LinkedList *listaModificada;

	if (listaVentas != NULL && !ll_isEmpty(listaVentas) && listaClientes != NULL && !ll_isEmpty(listaClientes))
	{
		listaModificada = ll_filterBySomethingCloneAndReturn(listaVentas, afichesCobrados,NO_COBRADOS);

		if (listaModificada != NULL
				&& controller_print(listaModificada,Afiche_print,AFICHE_PRINT) == 0
				&& utn_getIntStr("\nIngrese el ID de la venta: ", ERROR,id_venta, ATTEMPTS, SIZE) == 0
				&& controller_findVentaFromID(listaVentas, listaClientes, id_venta)== 0
				&& controller_findByIdAfiche(listaVentas, id_venta, &indexAfiche)== 0)
		{
			buffer = ll_get(listaVentas, indexAfiche);

			if (buffer != NULL && utn_getInt("\nDesea modificar a cobrada?: \n1)SI \n2)NO  \n0)EXIT \n>:",ERROR, &option, ATTEMPTS, -1, 3) == 0 && option == 1
				&& Afiche_set_a_cobrar_INT(buffer, option) == 0)
			{
				ll_set(listaVentas, indexAfiche, buffer);
				out = 0;
				printf("\nDatos actualizados\n");

			} else {
				printf("\nNo hubo cambios realizados, volviendo al menu..\n");
				out = 0;
			}

		} else {
			printf("\n Hubo un error en la toma de datos\n");
		}

	}else
	{
		printf("\n No hay datos cargados.\n");
	}
	return out;
}
