/*
 *      Author: l.rojas
 */
#include <stdio.h>
#include <stdlib.h>
#include "parser.h"
#include "Controller.h"
#include "LinkedList.h"
#include "cliente.h"
#include "afiche.h"
#include "utn.h"


/** \brief Parsea los datos de un cliente desde un archivo  (text mode).
 * \param pFile FILE* :  Archivo de donde se obtendra la informacion.
 * \param list LinkedList* list: Lista en la cual los datos seran guardados.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
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

			if(fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n",idAux, nombreAux, apellidoAux, cuitAux)==4 && isInt(idAux)==1)
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

/** \brief Parsea los datos de una venta desde un archivo  (text mode).
 * \param pFile FILE* :  Archivo de donde se obtendra la informacion.
 * \param list LinkedList* list: Lista en la cual los datos seran guardados.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/** \brief Funcion para guardar los archivos en modo texto
 * \param pFile FILE* :  Archivo de donde se guardaran la informacion.
 * \param list LinkedList* list: Lista de la cual los datos seran obtenidos.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
int parser_SaveClientToText(FILE* pFile, LinkedList* listClient)
{
	int out=-1;
	Cliente* cliente;
	char idAux[SIZE];
	char nombreAux[SIZE];
	char apellidoAux[SIZE];
	char cuitAux[SIZE];

	if(pFile != NULL && listClient != NULL)
	{
		fprintf(pFile,"ID,NOMBRE,APELLIDO,CUIT\n");
		for(int i = 0; i< ll_len(listClient);i++)
		{
			cliente = (Cliente*)ll_get(listClient,i);

			if(cliente != NULL &&
				Cliente_getIdStr(cliente, idAux)==0			 	 &&
				Cliente_get_nombre(cliente, nombreAux)==0		 &&
				Cliente_get_apellido(cliente, apellidoAux)==0    &&
				Cliente_get_cuit(cliente, cuitAux)==0			 )
			{
				fprintf(pFile,"%s,%s,%s,%s\n", idAux, nombreAux, apellidoAux, cuitAux);
				out=0;
			}
		}
		fclose(pFile);
	}
	return out;
}

/** \brief Funcion para guardar los archivos en modo texto
 * \param pFile FILE* :  Archivo de donde se guardaran la informacion.
 * \param list LinkedList* list: Lista de la cual los datos seran obtenidos.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
int parser_SaveVentaToText(FILE* pFile, LinkedList* listAfiche)
{
	int out=-1;
	Afiche* buffer;
	char idAux[SIZE];
	char id_clienteAux[SIZE];
	char cantidad_afichesAux[SIZE];
	char nombre_archivoAux[SIZE];
	char zona_pegar_aficheAux[SIZE];
	char a_cobrarAux[SIZE];
	char zona[SIZE];
	char cobrar[SIZE];

	if(pFile != NULL && listAfiche != NULL)
	{
		fprintf(pFile,"ID,ID_CLIENTE,CANTIDAD_AFICHES,NOMBRE_ARCHIVO,ZONA_PEGAR,ESTA_COBRADO\n");
		for(int i = 0; i< ll_len(listAfiche);i++)
		{
			buffer = (Afiche*)ll_get(listAfiche,i);
			if(buffer != NULL &&
					Afiche_getIdStr(buffer, idAux)==0 									 	&&
					Afiche_get_id_clienteSTR(buffer, id_clienteAux)==0 					 	&&
					Afiche_get_cantidad_afichesSTR(buffer, cantidad_afichesAux)==0 		 	&&
					Afiche_get_nombre_archivo(buffer, nombre_archivoAux)==0 				&&
					Afiche_get_zona_pegar_aficheSTR(buffer, zona_pegar_aficheAux)==0	    &&
					Afiche_get_a_cobrarSTR(buffer, a_cobrarAux)==0						 	&&
					convertZona(zona_pegar_aficheAux, zona)==0								&&
					convertACobrar(a_cobrarAux, cobrar)==0									)
			{
				printf("%-3s %-12s %-17s %-14s  %-11s %-11s \n", idAux, id_clienteAux, cantidad_afichesAux, nombre_archivoAux,zona,cobrar);

				fprintf(pFile,"%s,%s,%s,%s,%s,%s\n", idAux,id_clienteAux,cantidad_afichesAux,nombre_archivoAux,zona,cobrar);
				out=0;
			}
		}
		fclose(pFile);
	}
	return out;
}


