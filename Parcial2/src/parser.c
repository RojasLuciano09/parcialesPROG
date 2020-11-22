#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Cliente.h"
#include "Afiche.h"


/* \brief Parse the employee data from the data.csv file (binary mode).
 *
 * \param pFile FILE* :  File from which the data will be obtained.
 * \param list LinkedList* : List in which the obtained data will be stored
 * \return int output : (-1) If there was an error (0) if the process was successful.

int parser_EmployeeFromBinary(FILE* pFile , LinkedList* list)
{
	int output = -1;
	Employee* bufferEmployee;
	int read;
	if(pFile != NULL && list != NULL)
	{
		do
		{
			bufferEmployee = employee_new();
			if(bufferEmployee != NULL)
			{
				read = fread(bufferEmployee,sizeof(Employee),1,pFile);
				if(read == 1)
				{
					ll_add(list, bufferEmployee);
				}
				else
				{
					employee_delete(bufferEmployee);
					break;
				}
			}
		}while(!feof(pFile));
		output = 0;
	}
	return output;
}
 */


/** \brief Parse the employee data from the data.csv file (text mode).
 *
 * \param pFile FILE* :  File from which the data will be obtained.
 * \param list LinkedList* : List in which the obtained data will be stored
 * \return int output : (-1) If there was an error (0) if the process was successful.
 */
int parser_ClienteFromText(FILE* pFile , LinkedList* list)
{
	int output=-1;
	char idAux[SIZE];
	char nombreAux[SIZE];
	char apellidoAux[SIZE];
	char cuitAux[SIZE];
	Cliente* bufferEmp;
	if(pFile!=NULL && list!=NULL)
	{
		ll_clear(list);
		do
		{

			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",idAux, nombreAux, apellidoAux, cuitAux)==4)
			{
				bufferEmp = Cliente_newParametros(idAux, nombreAux, apellidoAux, cuitAux);



				ll_add(list, bufferEmp);

				output=0;
			}
			else
			{
				Cliente_delete(bufferEmp);
			}
		}while(feof(pFile)==0);
	}
    return output;
}

int parser_VentasFromText(FILE* pFile , LinkedList* list)
{
	int output=-1;
	char idAux[SIZE];
	char id_clienteAux[SIZE];
	char cantidad_afichesAux[SIZE];
	char nombre_archivoAux[SIZE];
	char zona_pegar_aficheAux[SIZE];
	char a_cobrarAux[SIZE];

	Afiche* buffer;
	if(pFile!=NULL && list!=NULL)
	{
		ll_clear(list);
		do
		{

			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",idAux, id_clienteAux, cantidad_afichesAux, nombre_archivoAux,zona_pegar_aficheAux,a_cobrarAux)==6)
			{
				buffer = Afiche_newParametros( idAux, id_clienteAux, cantidad_afichesAux, nombre_archivoAux,zona_pegar_aficheAux,a_cobrarAux);
				ll_add(list, buffer);
				output=0;
			}
			else
			{
				Afiche_delete(buffer);
			}
		}while(feof(pFile)==0);
	}
    return output;
}
