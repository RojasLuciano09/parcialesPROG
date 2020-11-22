#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "Cliente.h"
#include "Afiche.h"

#include "utn.h"
#include <limits.h>
#include "parser.h"


/** \brief Loads employee data from data.csv file (text mode).
 *
 * \param path char* : Path of the file to upload
 * \param pArrayListEmployee LinkedList* : list to which the loaded data will belong
 * \return int output : (-1) If there was an error (0) if the process was successful
 */
int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	FILE* pFile;

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "r");
		if(pFile!=NULL && !parser_ClienteFromText(pFile, pArrayListEmployee))
		{
			output=0;
		}
		else
		{
			printf("\nThe file does not exists");
		}
	}
    return output;
}

int controller_loadFromTextVentas(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	FILE* pFile;

	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "r");
		if(pFile!=NULL && !parser_VentasFromText(pFile, pArrayListEmployee))
		{
			output=0;
		}
		else
		{
			printf("\nThe file does not exists");
		}
	}
    return output;
}

int controller_printCliente(LinkedList* pArrayListEmployee)
{
	int output=-1;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		printf("\nID     Nombre      Apellido        Cuit\n");
		ll_map(pArrayListEmployee, Cliente_print);
		output=0;
	}
    return output;
}

int controller_printAfiche(LinkedList* pArrayListEmployee)
{
	int output=-1;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		printf("\nID  id_cliente   cantidad_afiches  nombre_archivo  zona_pegar  estaCobrado\n");

		ll_map(pArrayListEmployee, Afiche_print);
		output=0;
	}
    return output;
}

int controller_searchMaxId(LinkedList* pArrayListEmployee)
{
	int retornar=-1;
	int len = ll_len(pArrayListEmployee);
	Cliente* bufferEmp;
	int id;
	int maxId;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		for(int i=0;i<len;i++)
		{
			bufferEmp = ll_get(pArrayListEmployee, i);
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

int controller_searchMaxId2(LinkedList* listAfiche)
{
	int retornar=-1;
	int len = ll_len(listAfiche);
	Afiche* bufferEmp;
	int id;
	int maxId;
	if(listAfiche!=NULL && !ll_isEmpty(listAfiche))
	{
		for(int i=0;i<len;i++)
		{
			bufferEmp = ll_get(listAfiche, i);
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

int estaRepetido(LinkedList* pArrayListEmployee,void* element_one)
{
	int out=0;
	void* element_two;

	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		for(int i=0; i<ll_len(pArrayListEmployee);i++)
		{
			element_two = ll_get(pArrayListEmployee, i);
			if(veoSiEstanRepetidos(element_two,element_one)!=0)
			{
				printf("\nEse CUIT ya existe..\n");
				out=-1;
			}
		}
	}
	return out;
}

int primerBusqueda(LinkedList* pArrayListEmployee,void* element)
{
	int out=-1;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		if(estaRepetido(pArrayListEmployee,element)!=0)
		{
			out=0;
		}
	}
	return out;
}


int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;

	char idAux[SIZE];
	char nombreAux[SIZE];
	char apellidoAux[SIZE];
	char cuitAux[SIZE];

	Cliente* buffer;
	if(pArrayListEmployee!=NULL  &&  !ll_isEmpty(pArrayListEmployee))
		{
			  strncpy(nombreAux,"AAA",SIZE);
			  strncpy(apellidoAux,"AAB",SIZE);
			  strncpy(cuitAux,"23-00033111-7",SIZE);
			//  strncpy(cuitAux,"23-37933040-9",SIZE);


		  if(/* utn_getString("\nNombre Cliente: \n", ERROR, nombreAux, ATTEMPTS, SIZE)==0 			&&
			  utn_getString("\nApellido Cliente: \n", ERROR, apellidoAux, ATTEMPTS, SIZE)==0 		&&
			  utn_getCuit("\nCuit Cliente: \n", ERROR, cuitAux, ATTEMPTS, SIZE)==0 			*/
				  primerBusqueda(pArrayListEmployee,cuitAux)!=0  )
			{

				sprintf(idAux, "%d",controller_searchMaxId(pArrayListEmployee));
				printf("\nYour id is: %s\n",idAux);
				buffer = Cliente_newParametros(idAux, nombreAux, apellidoAux, cuitAux);
				ll_add(pArrayListEmployee,buffer);
			}
			else
			{
				printf("\nThe operation couldn´t be completed at -> controller_addEmployee ");
			}
		}
    return output;
}

int controller_thisIdExist(LinkedList* pArrayListEmployee,void* arg)
{
	int output=-1;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		if(ll_map2(pArrayListEmployee,veoSiExisteEsteID,arg)!=0)
		{
			output=0;
		}
	}
    return output;
}


int controller_vender_afiches(LinkedList* listAfiche,LinkedList* listcliente)
{
	int out=-1;
	char idAux[SIZE];
	char id_clienteAux[SIZE];
	char cantidad_afichesAux[SIZE];
	char nombre_archivoAux[SIZE];
	char zona_pegar_aficheAux[SIZE];
	Afiche* buffer;
	if(listAfiche!=NULL )//&& !ll_isEmpty(listAfiche) && listcliente!=NULL && !ll_isEmpty(listcliente))
{
		strncpy(id_clienteAux,"2",5);
		strncpy(cantidad_afichesAux,"2",5);
		strncpy(nombre_archivoAux,"eee.txt",10);
		strncpy(zona_pegar_aficheAux,"0",10);

	if(controller_thisIdExist(listcliente,id_clienteAux)!=0                   )
			/*
		utn_getIntStr("\ningrese idcliente\n",ERROR, id_clienteAux, ATTEMPTS, SIZE)==0 						&&
		controller_thisIdExist(listcliente,id_clienteAux)!=0      											&&
		utn_getIntStr("\ningrese cantidad afiches\n",ERROR, cantidad_afichesAux, ATTEMPTS, SIZE)==0 		&&
		utn_getFileName("\nIngrese nombre archivo", ERROR, nombre_archivoAux, ATTEMPTS, SIZE)==0 				&&
		utn_getIntStr("\ningrese zona_pegar_afiche 0(CABA) 1(ZONASUR 2(ZONANORTE))\n", ERROR, zona_pegar_aficheAux, ATTEMPTS, SIZE)==0	)*/
	 {
		//printf("\n #### %s",idAux);
		sprintf(idAux, "%d",controller_searchMaxId2(listAfiche));
		printf("\nDatos cargados correctamente id del afiche: %s\n",idAux);
		buffer = Afiche_newParametros(idAux, id_clienteAux, cantidad_afichesAux, nombre_archivoAux, zona_pegar_aficheAux,"1");
		printf("\n %s %s %s %s %s %s\n",idAux,id_clienteAux,cantidad_afichesAux,nombre_archivoAux,zona_pegar_aficheAux,"1");
		ll_add(listAfiche,buffer);
	}
	else
	{
		printf("\nHubo un error en la carga de datos");
	}

}
	return out;
}

/*
Modificar venta: Se listarán todas las ventas en estado “a cobrar” (que son las que se pueden modificar)
 con todos sus campos.
Se pedirá el ID de la venta y se imprimirá (nombre. Apellido y y cuit),
luego se pedirá que se ingrese qué campo se quiere modificar y se deberá permitir modificarlo
 */
int controller_modificar_Venta(LinkedList* listAfiche,LinkedList* listcliente)
{
	int out=-1;
	char id_venta[SIZE];
	LinkedList* listaModificada;
	if(listAfiche!=NULL)
	{
		listaModificada = ll_filterBySomethingCloneAndReturn(listAfiche, afichesCobrados);

		strncpy(id_venta,"10",5);

		if(listaModificada!=NULL &&
		   controller_printAfiche(listaModificada)==0
		  // &&  utn_getIntStr("\nIngrese el ID de la venta: ",ERROR, id_venta, ATTEMPTS,SIZE)==0
		   && controller_findVentaFromID(listAfiche, id_venta)==0

		  )



		{

		}

			out=0;
	}
	return out;
}


int controller_findVentaFromID(LinkedList* listAfiche,void* arg)
{
	//pensarla con un ll_map que me devulve el elemento y ver que hacer con el.
	int out=-1;
	int len = ll_len(listAfiche);
	void* element;
	char id_cliente[SIZE];
	if(listAfiche!=NULL)
	{
		for(int i =0; i<len;i++)
		{
			element = ll_get(listAfiche, i);
			if(devuelvoElementoPorID(element,arg,id_cliente)==0)
			{
				printf("\n ## %s",id_cliente);
			}
		}
	}

	return out;
}















/**


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



\brief Loads employee data from data.csv file (binary mode).
 *
 * \param path char* : Path of the file to upload
 * \param pArrayListEmployee LinkedList* : list to which the loaded data will belong
 * \return int output : (-1) If there was an error (0) if the process was successful

int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	FILE* pFile;
	if(path!=NULL && pArrayListEmployee!=NULL)
	{
		pFile = fopen(path, "rb");
		if(pFile!=NULL && !parser_EmployeeFromBinary(pFile, pArrayListEmployee))
		{
			output=0;
		}
	}
	return output;
}







int controller_addEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	char bufferName[LONG_NAME];
	char bufferHours[SIZE];
	char bufferSalary[SIZE];
	char bufferID[SIZE];

	Employee* buffer;
	if(pArrayListEmployee!=NULL  &&  !ll_isEmpty(pArrayListEmployee))
	{
		if(//utn_getCadena("\nPlease write the name of the employee: ",ERROR,bufferName, ATTEMPTS, LONG_NAME)==0    &&
		  // utn_getCharInt("\nPlease enter the hours worked: ",ERROR,bufferHours, ATTEMPTS, SIZE)==0 	 	 &&
		   //utn_getCharInt("\nPlease enter salary: ",ERROR,bufferSalary, ATTEMPTS, SIZE)==0
				1)
		{
			sprintf(bufferID, "%d",controller_searchMaxId(pArrayListEmployee));
			printf("\nYour id is: %s\n",bufferID);
			buffer = employee_newParametros(bufferID, bufferName, bufferHours, bufferSalary);
			ll_add(pArrayListEmployee,buffer);
		}
		else
		{
			printf("\nThe operation couldn´t be completed at -> controller_addEmployee ");
		}
	}
	else
	{
		printf("\nYou must first upload the employee list.\n ");
	}
    return output;
}


int controller_findById(LinkedList* pArrayListEmployee,int id, int *index)
{
	int output=-1;
	int bufferId;
	int len = ll_len(pArrayListEmployee);
	Employee* buffer;

	if(pArrayListEmployee!=NULL)
	{
		for(int i=0;i<len;i++)
		{
			buffer = ll_get(pArrayListEmployee, i);
			if(employee_getId(buffer,&bufferId)==0 && bufferId == id )
			{
				output=0;
				*index = i;
				break;
			}
		}
	}
	return output;
}



int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int bufferId;
	int index;
	int option;
	char bufferName[LONG_NAME];
	char bufferHours[SIZE];
	char bufferSalary[SIZE];
	Employee* buffer;

	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee))
	{
		if(utn_getInt("\nEnter the id of the employee to modify: ",ERROR,&bufferId,ATTEMPTS,-1,INT_MAX)==0  &&
		   controller_findById(pArrayListEmployee, bufferId, &index)==0 && index>-1		    )
		{
			buffer = ll_get(pArrayListEmployee, index);
			employee_print(buffer);
			if(utn_getInt("\nSelect the field to modify: \n1)Name \n2)Hours \n3)Salary \n0)EXIT \n>:",ERROR,&option,ATTEMPTS,-1,3)==0)
			{
				switch(option)
				{
				case 1:
					if(utn_getString("\nEnter the new name: ",ERROR,bufferName,ATTEMPTS,LONG_NAME)==0 &&
					   employee_setNombre(buffer, bufferName)==0 											)
					{
						ll_set(pArrayListEmployee, index, buffer);
						output=0;
						printf("\nUpdated data...\n");
					}
				break;

				case 2:
					if(utn_getString("\nEnter the number of hours: ",ERROR,bufferHours,ATTEMPTS,LONG_NAME)==0   &&
					   employee_setHoursWorkedStr(buffer, bufferHours)==0                                            )
					{
						ll_set(pArrayListEmployee, index, buffer);
						output=0;
						printf("\nUpdated data...\n");
					}
				break;

				case 3:
					if(utn_getString("\nEnter the new salary: ",ERROR,bufferSalary,ATTEMPTS,LONG_NAME)==0 		&&
					   employee_setSalaryStr(buffer,bufferSalary)==0  												)
					{
						ll_set(pArrayListEmployee, index, buffer);
						output=0;
						printf("\nUpdated data...\n");
					}
				break;
				}
			}
		}
	}
	else
	{
		printf("\nNo data to edit...\n");
	}
	return output;
}



int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int bufferId;
	int index;
	int option;
	Employee* buffer;

	if(pArrayListEmployee!=NULL &&  !ll_isEmpty(pArrayListEmployee))
	{
		if(utn_getInt("\nEnter the id to unsubscribe: ",ERROR,&bufferId,ATTEMPTS,-1,INT_MAX)==0  &&
		   controller_findById(pArrayListEmployee, bufferId, &index)==0 && index>-1		      )
		{
			buffer = ll_get(pArrayListEmployee, index);
			employee_print(buffer);
			if(utn_getInt("\nPress 1 to delete.\nPress 2 to cancel.\n->:",ERROR,&option,ATTEMPTS,1,2)==0 	   &&
			   option==1																									)
			{
				ll_remove(pArrayListEmployee, index);
				output=0;
				printf("\nEmployee removed...");
			}else
			{
				printf("\nDeletion canceled, returning to the main menu..");
			}
		}else
		{
			printf("\nThe employee with that ID was not found.");
		}
	}
	else
	{
		printf("\nNo data to delete...\n");
	}
	return output;
}






int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	char bufferName[SIZE];
	char bufferId[SIZE];
	char bufferHours[SIZE];
	char bufferSalary[SIZE];
	int len = ll_len(pArrayListEmployee);
	FILE* pFile;
	Employee* buffer;

	if(path!=NULL && pArrayListEmployee!=NULL && ll_len(pArrayListEmployee)>0)
		{
			pFile = fopen(path, "w");
			if(pFile!=NULL)
			{
				printf("\nWork in progress..\n");
				ll_sort(pArrayListEmployee,employee_sortID,1);
				for(int i=0;i<len;i++)
				{
					buffer = ll_get(pArrayListEmployee, i);
					if( employee_getNombre(buffer, bufferName)==0			    	&&
						employee_getIdStr(buffer, bufferId)==0						&&
						employee_getHorasTrabajadasStr(buffer, bufferHours)==0   	&&
						employee_getSueldoStr(buffer, bufferSalary)==0			 	)
					{
						fprintf(pFile, "%s,%s,%s,%s\n",bufferId, bufferName, bufferHours, bufferSalary);
						output=0;
					}
				}
				fclose(pFile);
				printf("\nData saved successfully.\n");
			}
		}
		else
		{
			printf("\nNo data to save...\n");
		}
	return output;
}


int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int output=-1;
	char bufferName[LONG_NAME];
	int bufferId;
	int bufferHours;
	int bufferSalary;
	int len = ll_len(pArrayListEmployee);
	FILE* pFile;
	Employee* buffer;

	if(path!=NULL && pArrayListEmployee!=NULL  &&  !ll_isEmpty(pArrayListEmployee))
		{
			pFile = fopen(path, "wb");
			if(pFile!=NULL)
			{
				ll_sort(pArrayListEmployee,employee_sortID,1);
				for(int i=0;i<len;i++)
				{
					buffer = ll_get(pArrayListEmployee, i);
					if( employee_getNombre(buffer, bufferName)==0			    	&&
						employee_getId(buffer, &bufferId)==0						&&
						employee_getHorasTrabajadas(buffer, &bufferHours)==0   		&&
						employee_getSueldo(buffer, &bufferSalary)==0			     )
					{
						fwrite(&bufferId,sizeof(int),1,pFile);
						fwrite(bufferName, LONG_NAME,1,pFile);
						fwrite(&bufferHours,sizeof(int),1,pFile);
						fwrite(&bufferSalary,sizeof(int),1,pFile);
						output=0;
					}
				}
				fclose(pFile);
				printf("\nData saved successfully.\n");
			}
		}
		else
		{
			printf("\nNo data to save...\n");
		}
    return output;
}



int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int output=-1;
	int op;
	if(pArrayListEmployee!=NULL && !ll_isEmpty(pArrayListEmployee) &&  utn_getInt("\nSelect sort order \n1-Desc \n0-Asc \n>:",ERROR,&op,ATTEMPTS,-1,1)==0)
	{
		printf("\nWork in progress..\n");
		ll_sort(pArrayListEmployee,employee_sort,op);
		printf("\nData ordered alphabetically ...\n");
		output=0;
	}
	else
	{
		printf("\nNo data to sort..\n");
	}
return output;
}

 *
 *

int controller_removeEmployeeBySalary(LinkedList* pArrayListEmployee)
{
	int output=-1;
	if(pArrayListEmployee!=NULL)
	{
		ll_filterBorrarBajoUnaCondicion(pArrayListEmployee, employee_removeBy_Salary);
		output=0;
	}
	return output;
}


int controller_calcularTotalDeSueldoConMap(LinkedList* pArrayListEmployee)
{
	int output=-1;
	if(pArrayListEmployee!=NULL)
	{
		ll_reduce(pArrayListEmployee, employee_getSalarioTotal,&output);
		printf("Total de %d",output	);
		output=0;
	}
	return output;


}

 */












































