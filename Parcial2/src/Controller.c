#include <stdio.h>
#include <stdlib.h>
#include "Controller.h"
#include "utn.h"
#include <string.h>
#include "LinkedList.h"
#include "cliente.h"
#include "afiche.h"


static int primerBusqueda(LinkedList* thisList,void* element);
static int estaRepetido(LinkedList* thisList,void* element_one);
static int controller_thisIdExist(LinkedList* thisList,void* arg);
static int controller_searchMaxIDVenta(LinkedList* listaVentas);
static int controller_findVentaFromID(LinkedList* listaVentas ,LinkedList* listaClientes,void* arg);
static int controller_findByIdAfiche(LinkedList* listaVentas ,void* arg,int* id_temp);
static int getClientByIDVenta(void* element,LinkedList* this);
static int controller_searchMaxIDCliente(LinkedList* thisList);
static int controller_searchMaxIDVenta(LinkedList* listaVentas);
static LinkedList* filtrarClientesByVentas(LinkedList* listaVentas,LinkedList* listaClientes);
static int controller_findById(LinkedList* listaClientes,void* arg);

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
				retornar = maxId;
			}
		}
	}
	return retornar;
}

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

static int estaRepetido(LinkedList* thisList,void* element_one)
{
	int out=0;
	void* element_two;
	if(thisList!=NULL && !ll_isEmpty(thisList))
	{
		for(int i=0; i<ll_len(thisList);i++)
		{
			element_two = ll_get(thisList, i);
			if(thisCuitExists(element_two,element_one)!=0)
			{
				printf("\nEse CUIT ya existe..\n");
				out=-1;
			}
		}
	}
	return out;
}

static int primerBusqueda(LinkedList* thisList,void* element)
{
	int out=-1;
	if(thisList!=NULL && !ll_isEmpty(thisList))
	{
		if(estaRepetido(thisList,element)!=0)
		{
			out=0;
		}
	}
	return out;
}

static int controller_thisIdExist(LinkedList* thisList,void* arg)
{
	int output=-1;
	if(thisList!=NULL && !ll_isEmpty(thisList))
	{
		if(ll_map2(thisList,veoSiExisteEsteID,arg)!=0)
		{
			output=0;
		}
	}
    return output;
}

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

static int controller_findByIdAfiche(LinkedList* listaVentas,void* arg,int* id_temp)
{
	int out=-1;

	if(listaVentas!=NULL)
	{
		*id_temp = ll_search(listaVentas, comparoID, arg);
		out=0;
	}
	return out;
}

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
				if(ll_map2(listaVentas, comparoID_cliente2, id_aux)==0)
				{
					ll_add(auxList, element);
				}
		}
	}
	return auxList;
}

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
		      primerBusqueda(thisList,cuitAux)!=0  									)
			{
			    sprintf(idAux, "%d",controller_searchMaxIDCliente(thisList));
			    printf("\nAlta exitosa, su id es: %s\n",idAux);
				buffer = Cliente_newParametros(idAux, nombreAux, apellidoAux, cuitAux);
				ll_add(thisList,buffer);
			}
			else
			{
				printf("\nHubo un erro en -> controller_addEmployee\n");
			}
		}
    return output;
}

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
				controller_thisIdExist(listaClientes,id_clienteAux)!=0      											&&
				utn_getIntStr("\ningrese cantidad afiches\n",ERROR, cantidad_afichesAux, ATTEMPTS, SIZE)==0 		&&
				utn_getFileName("\nIngrese nombre archivo", ERROR, nombre_archivoAux, ATTEMPTS, SIZE)==0 				&&
				utn_getIntStr("\ningrese zona_pegar_afiche 0(CABA) 1(ZONASUR 2(ZONANORTE))\n", ERROR, zona_pegar_aficheAux, ATTEMPTS, SIZE)==0	)
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

		if(ll_map2(listaModificadaVenta, comparoAfichesVendidos, &contador)==0)
		{
			if(i==1 || contador > contadorMax)
			{
				contadorMax = contador;
				bufferMax = element;
			}
		}
	}
	getClientByIDVenta(bufferMax, listaClientes);
	printf("\nCANTIDAD VENDIDOS: %d  ", contadorMax);
	return out;
}
