/*
 *      Author: l.rojas
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cliente.h"
#include "utn.h"


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



/** \brief Función para solicitar un espacio de memoria.
 */
Cliente* Cliente_new()
{
	Cliente* this;
	this=(Cliente*)malloc(sizeof(Cliente));
	return this;
}

/** \brief Función para liberar el espacio de memoria.
 * \param this Employee* : Employee being removed
 */
void Cliente_delete(Cliente* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}

/**
 * \brief Función para crear un nuevo cliente con parametros.
 * \param char* id: valor a setear en ID
 * \param char* nombre: valor a setear en NOMBRE
 * \param char* apellido: valor a setear en APELLIDO
 * \param char* cuit: valor a setear en CUIT
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
Cliente* Cliente_newParametros(char* id,char* nombre,char* apellido, char* cuit)
{
	Cliente* this = Cliente_new();
	if(this!=NULL)
	{
		if(Cliente_setIdStr(this, id)==0 			&&
		   Cliente_set_nombre(this, nombre)==0  	&&
		   Cliente_set_apellido(this, apellido)==0  &&
		   Cliente_set_cuit(this, cuit)==0			)
		{
			return this;
		}
	}
	Cliente_delete(this);
	return NULL;
}

/**
 * \brief Función para setear el id a  un cliente.
 * \param Cliente* this: Puntero al elemento.
 * \param int id: Variable para setear el valor.
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_setId(Cliente* this,int id)
{
	int output=-1;
	if(this!=NULL && id>-1)
	{
		this->id = id;
		output=0;
	}
	return output;
}

/**
 * \brief Función para obtener el id de  un cliente.
 * \param Cliente* this: Puntero al elemento.
 * \param int* id: Puntero que obtendra el valor.
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int  Cliente_getId(Cliente* this,int* id)
{
	int output=-1;
	if(this!=NULL && id!=NULL)
	{
		*id = this->id;
		output=0;
	}
	return output;
}

/**
 * \brief Función para setear el id a  un cliente.
 * \param Cliente* this: Puntero al elemento.
 * \param char* id: Puntero que setear el valor.
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_setIdStr(Cliente* this, char* id)
{
	int retornar=-1;
	char bufferId[SIZE];
	if(this!=NULL &&  isInt(id)==1 && id!=NULL )
	{
		strncpy(bufferId, id, SIZE);
		this->id = atoi(bufferId);
		retornar=0;
	}
	return retornar;
}

/**
 * \brief Función para obtener el id de  un cliente.
 * \param Cliente* this: Puntero al elemento.
 * \param char* id: Puntero que obtendra el valor.
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_getIdStr(Cliente* this,char* id)
{
	int output=-1;

	if(this!=NULL && id!=NULL)
	{
		sprintf(id,"%d",this->id);
		output=0;
	}
	return output;
}

/**
 * \brief Función para setear el nombre a  un cliente.
 * \param Cliente* this: Puntero al elemento.
 * \param char* nombre: Puntero que setear el valor.
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_set_nombre(Cliente* this,char* nombre)
{
	int output=-1;
	if(this!=NULL && isString(nombre)==1 && nombre!=NULL)
	{
		UpperFirstChar(nombre);
		strncpy(this->nombre,nombre,LONG_NAME);
		output=0;
	}
	return output;
}

/**
 * \brief Función para obtener el nombre de  un cliente.
 * \param Cliente* this: Puntero al elemento.
 * \param char* nombre: Puntero que obtendra el valor.
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_get_nombre(Cliente* this,char* nombre)
{
	int output=-1;
	if(this!=NULL && nombre!=NULL)
	{
		strncpy(nombre, this->nombre, LONG_NAME);
		output=0;
	}
	return output;
}

/**
 * \brief Función para setear el apellido a  un cliente.
 * \param Cliente* this: Puntero al elemento.
 * \param char* apellido: Puntero que setear el valor.
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_set_apellido(Cliente* this,char* apellido)
{
	int output=-1;
	if(this!=NULL && isString(apellido)==1 && apellido!=NULL)
	{
		UpperFirstChar(apellido);
		strncpy(this->apellido,apellido,LONG_NAME);
		output=0;
	}
	return output;
}

/**
 * \brief Función para obtener el apellido de  un cliente.
 * \param Cliente* this: Puntero al elemento.
 * \param char* apellido: Puntero que obtendra el valor.
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_get_apellido(Cliente* this,char* apellido)
{
	int output=-1;
	if(this!=NULL && apellido!=NULL)
	{
		strncpy(apellido, this->apellido, LONG_NAME);
		output=0;
	}
	return output;
}

/**
 * \brief Función para setear el cuit a  un cliente.
 * \param Cliente* this: Puntero al elemento.
 * \param char* cuit: Puntero que setear el valor.
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_set_cuit(Cliente* this,char* cuit)
{
	int output=-1;
	if(this!=NULL && isCuit(cuit)==1 && cuit!=NULL)
	{
		strncpy(this->cuit,cuit,LONG_NAME);

		output=0;
	}
	return output;
}

/**
 * \brief Función para obtener el cuit de  un cliente.
 * \param Cliente* this: Puntero al elemento.
 * \param char* cuit: Puntero que obtendra el valor.
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_get_cuit(Cliente* this,char* cuit)
{
	int output=-1;
	if(this!=NULL && cuit!=NULL)
	{
		strncpy(cuit, this->cuit, LONG_NAME);
		output=0;
	}
	return output;
}

/**
 * \brief Función para imprimir por consola un cliente.
 * \param void* itemOne: Puntero al elemento a castear
 * \param void* arg: Puntero al elemento a comparar
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_print(void* itemOne)
{
	int output=-1;
	Cliente* buffer;
	buffer =(Cliente*)itemOne;
	char idAux[SIZE];
	char nombreAux[SIZE];
	char apellidoAux[SIZE];
	char cuitAux[SIZE];

	if(buffer!=NULL)
	{
		if( Cliente_getIdStr(buffer, idAux)==0			 	 &&
			Cliente_get_nombre(buffer, nombreAux)==0		 &&
			Cliente_get_apellido(buffer, apellidoAux)==0   	 &&
			Cliente_get_cuit(buffer, cuitAux)==0			 )
		{

			printf("%-6s %-11s %-15s %-17s\n", idAux, nombreAux, apellidoAux, cuitAux);
			output = 0;
		}
	}
	return output;
}

/**
 * \brief Función para imprimir por consola un cliente.
 * \param void* itemOne: Puntero al elemento a castear
 * \param void* arg: Puntero al elemento a comparar
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_printById(void* itemOne,void* arg)
{
	int output=-1;
	Cliente* buffer;
	buffer =(Cliente*)itemOne;
	char idAux[SIZE];
	char nombreAux[SIZE];
	char apellidoAux[SIZE];
	char cuitAux[SIZE];


	if(buffer!=NULL)
	{
		if( Cliente_getIdStr(buffer, idAux)==0			 	 &&
			strncmp(idAux,arg,SIZE)==0						 &&
			Cliente_get_nombre(buffer, nombreAux)==0		 &&
			Cliente_get_apellido(buffer, apellidoAux)==0   	 &&
			Cliente_get_cuit(buffer, cuitAux)==0			 )
		{

			printf("%-6s %-11s %-15s %-17s\n", idAux, nombreAux, apellidoAux, cuitAux);
			output = 0;
		}
	}
	return output;
}

/**
 * \brief Función para ordenar por nombre.
 * \param void* itemOne: Puntero al elemento a comparar
 * \param void* itemTwo: Puntero al elemento a comparar
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_sort(void* itemOne,void* itemTwo)
{
	int output=0;
	Cliente* buffer1;
	Cliente* buffer2;
	buffer1	 = itemOne;
	buffer2	 = itemTwo;
	char name_1[LONG_NAME];
	char name_2[LONG_NAME];

	if(Cliente_get_nombre(buffer1, name_1)==0   &&
	   Cliente_get_nombre(buffer2, name_2)==0	)
	{
		if( strncmp(name_1, name_2,LONG_NAME)>0)
		{
			output = 1;
		}
		else
		{
			output=-1;
		}
	}
	else
	{
		printf("\nThere was a mistake -> Cliente_sort(void* itemOne,void* itemTwo)");
	}

	return output;
}

/**
 * \brief Función para ordenar por id
 * \param void* itemOne: Puntero al elemento a comparar
 * \param void* itemTwo: Puntero al elemento a comparar
 * \return int output  (-1) Error
                       ( 0) todo ok.
 */
int Cliente_sortID(void* itemOne,void* itemTwo)
{
	int output=0;
	Cliente* buffer1;
	Cliente* buffer2;
	int id1;
	int id2;
	buffer1	 = itemOne;
	buffer2	 = itemTwo;

	if(Cliente_getId(buffer1, &id1)==0   &&
			Cliente_getId(buffer2, &id2)==0	  )
	{
		if(id1>id2)
			{
			output= 1;
			}
			else
			{
				if(id1<id2)
				{
					output= -1;
				}
				else
				{
					output= 0;
				}
			}
	}
	else
	{
		printf("\nThere was a mistake-> Cliente_sortID(void* itemOne,void* itemTwo)");
	}
	return output;
}

/**
 * \brief Función para imprimir por consola el cuit de un cliente.
 * \param void* itemOne: Puntero al elemento a comparar, es casteado a Cliente*
 * \return int output  (-1) Error: si no se pudo obtener los datos.
                       ( 0) todo ok.
 */
int Cliente_printCUIT(void* itemOne)
{
	int output=-1;
	Cliente* buffer;
	buffer =(Cliente*)itemOne;
	char cuitAux[SIZE];
	if(buffer!=NULL)
	{
		if(Cliente_get_cuit(buffer, cuitAux)==0	)
		{
			printf("%-6s",cuitAux);
			output = 0;
		}
	}
	return output;
}

/**
 * \brief Función para comparar id.
 * \param void* itemOne: Puntero al elemento a comparar, es casteado a Cliente*
 * \param void* itemTwo: Puntero que tendra el valor del id del cliente a comparar.
 * \return int output  (-1) Error: si no se pudo obtener los datos.
                       ( 0) todo ok.
 */
int comparoIDCliente(void* itemOne,void* itemTwo)
{
	int out=-1;
	Cliente* this;
	this =(Cliente*)itemOne;
	char id_obtenido[SIZE];


	if( Cliente_getIdStr(this,id_obtenido )==0  &&
	    strncmp(id_obtenido,itemTwo,SIZE)==0 )
	{
		out =0;
	}
	return out;
}

/**
 * \brief Función para corroborar si un cuit existe.
 * \param void* itemOne: Puntero al elemento.
 * \param void* id: Puntero que tendra el valor del id del cliente a comparar.
 * \return int output  (-1) Error: si no se pudo obtener los datos.
                       ( 0) todo ok.
 */
int thisCuitExists(void* itemOne,void* cuit)
{
	int output=-1;
	Cliente* buffer1;
	buffer1	 = itemOne;
	char cuit_1[LONG_NAME];

	if(Cliente_get_cuit(buffer1, cuit_1)==0)
	{
		if(strncmp(cuit_1, cuit,LONG_NAME)==0)
		{
			output=0;
		}
	}
	return output;
}

/**
 * \brief Función para corroborar si un id existe.
 * \param void* itemOne: Puntero al elemento.
 * \param void* id: Argumento que tendra el valor del id del cliente a comparar.
 * \return int output  (-1) Error: si no se pudo obtener los datos.
                       ( 0) todo ok.
 */
int veoSiExisteEsteID(void* itemOne,void* id)
{
	int output=-1;
	Cliente* buffer1;
	buffer1	 = itemOne;
	char idObtenido[SIZE];

	if(Cliente_getIdStr(buffer1, idObtenido)==0)
	{
		if(strncmp(idObtenido, id,SIZE)==0)
		{
			output =0;
		}
	}
	return output;
}

