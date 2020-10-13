/*
 * utn.c
 *
 *  Created on: 23 sep. 2020
 *      Author: l.rojas
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE 4096
#define LONG_NOMBRE 50




static int myGets(char cadena[], int longitud);
static int isString(char cadena[]);
static int isInt(char cadena[]);
static int isFloat(char string[]);
static int esLetrasYEspacios(char* cadena, int len);
static int getLetrasYEspacios(char *pResultado, int len);
static int isCuit(char string[]);

/*
 * \brief convierte la cadena recibida en un número flotante con la función atof.
 * \param puntero con el string validado.
 * \param longitud del string.
 * \return 0 si ha salido ok. -1 si no.
 */
static int getLetrasYEspacios(char *pResultado, int len)
{
	int retorno=-1;
	char buffer[50];
	if(pResultado != NULL &&
		myGets(buffer, sizeof(buffer))==0 &&
		esLetrasYEspacios(buffer, sizeof(buffer))==1)
	{
		retorno=0;
		strncpy(pResultado, buffer, len);
	}
	return retorno;
}

/*
 * \brief Valida que la cadena recibida está compuesta únicamente por letras o espacios.
 * \param puntero con el string validado.
 * \param longitud del string.
 * \return 1 (verdadero) si solo tiene letras y espacios. 0 (falso) si no.
 */
static int esLetrasYEspacios(char* cadena, int len)
{
	int retorno = 1;
	int i;

	for(i=0 ;  i<len && cadena[i] != '\0'; i++)
	{
		if((cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			(cadena[i] != ' ') &&
			(cadena[i] < 'á' || cadena[i] > 'ú') &&
			(cadena[i] != 'é'))
		{
			retorno = 0;
			break;
		}
	}
	return retorno;
}

/*
 * \brief solicita una cadena de valores.
 * \param puntero con la cadena.
 * \param mensaje para solicitar la cadena..
 * \param mensaje de error si no cumple las condiciones preestablecidas.
 * \param cantidad de reintentos para introducir un valor válido.
 * \return 0 si ha salido ok. -1 si no.
 */
int utn_getLetrasYEspacios(char* pResultado,int len,char* mensaje,char* mensajeError,int reintentos)
{
	int retorno = -1;
	char buffer[4096];
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && reintentos > 0)
	{
		do{
			printf("%s",mensaje);
			if(getLetrasYEspacios(buffer, len)==0  && strlen(buffer) < len)
			{
				strncpy(pResultado,buffer,len-1);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);
	}
	return retorno;
}





/**
 * \brief Funcion para obtener un string
 * \param char cadena[]: Donde se va a guardar el string
 * \param int longitud: El tamaño del array de caracteres para no sobrepasarlo
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int myGets(char cadena[], int longitud)
{
	int retorno=-1;
	if(cadena != NULL && longitud >0 && fgets(cadena,longitud,stdin)==cadena)
	{
		fflush(stdin);
		if(cadena[strlen(cadena)-1] == '\n' && cadena[0] != '\n')
		{
		cadena[strlen(cadena)-1] = '\0';

		}
		retorno=0;
	}
	return retorno;
}

/**
 * \brief Funcion para validar si el array de caracteres que recibe es una cadena de texto y no otra cosa
 * \param char string[]: Es el string que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int isString(char string[])
{
	int retorno = 1;
	if(string != NULL && strlen(string) > 0)
	{
		for(int i = 0;string[i] != '\0'; i++)
		{
			if((string[i] < 'a' || string[i] > 'z') && (string[i] < 'A' || string[i] > 'Z') && string[i] != 32)
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Funcion para validar si la cadena de caracteres que recibimos corresponde a un float
 * \char string[]: Es la cadena de caracteres que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int isFloat(char string[])
{
	int retorno = 1;
	int i = 0;
	int commaCounter=0;

	if(string != NULL && strlen(string) > 0)
	{
		if(string[0] == '-')
		{
			i = 1;
		}

		for(;string[i] != '\0' ; i++)
		{
			if(string[i] == '.')
			{
				commaCounter++;
			}
			if(commaCounter>1 || ((string[i] > '9' || string[i] < '0') && string[i] != '.'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

/**
 * \brief Funcion para validar si la cadena de caracteres que recibimos corresponde a un entero
 * \char string[]: Es la cadena de caracteres que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int isInt(char string[])
{
	int retorno = 1;
	int i = 0;

	if(string != NULL && strlen(string) > 0)
	{
		if(string[0] == '-')
		{
			i = 1;
		}
		for(;string[i] != '\0' ; i++)
		{
			if(string[i] > '9' || string[i] < '0')
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}


/**
 * \brief FALTA CORREGUIR LAS VALIDACIONES.
 * \char string[]: Es la cadena de caracteres que vamos a validar
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
static int isCuit(char string[])
{
	int retorno;
	int dashCounter=0;
	if(string != NULL && strlen(string) > 0 && string[2] == '-' && string[11] == '-' && string[12] != '\0')
	{
		retorno = 1;
		for(int i = 0;string[i] != '\0'; i++)
		{
			if(string[i] == '-')
			{
				dashCounter++;
			}
			if(dashCounter>2 || ((string[i] < '0' || string[i] > '9') && string[i] != '-'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}

int utn_getCuit(char msg[], char msgError[], char pResult[], int attemps, int limit)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0)
	{
		do
		{
			printf("\n%s", msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isCuit(bufferString) == 1 && strnlen(bufferString, sizeof(bufferString)) < limit)
			{
				retorno = 0;
				strncpy(pResult, bufferString, limit);
				break;
			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}
		}while(attemps >= 0);
	}
	return retorno;
}



/**
 * \brief Funcion para pedirle al usuario un string
 * \param char msg[]: Puntero a una cadena de texto
 * \param char msgError[]: Puntero a una cadena de texto en caso de error
 * \param char pResult[]: El string que vamos a devolver
 * \param int attemps: Reintentos que va a tener la funcion en caso de error
 * \param int limit: Es el tamaño para no sobrepasar la cadena de texto
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int utn_getString(char msg[], char msgError[], char pResult[], int attemps, int limit)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0)
	{
		do
		{
			printf("\n%s", msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isString(bufferString) == 1 && strnlen(bufferString, sizeof(bufferString)) < limit)
			{
				retorno = 0;
				strncpy(pResult, bufferString, limit);
				break;
			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}
		}while(attemps >= 0);
	}
	return retorno;
}

/**
 * \brief Funcion para pedirle al usuario un numero entero
 * \param char msg[]: Puntero a una cadena de texto
 * \param char msgError[]: Puntero a una cadena de texto en caso de error
 * \param int *pResult: Puntero del entero que vamos a devolver
 * \param int attemps: Reintentos que va a tener la funcion en caso de error
 * \param int min: Es el minimo permitido para el numero
 * \param int max: Es el maximo permitido para el numero
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int utn_getInt(char msg[], char msgError[], int *pResult, int attemps, int min, int max)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	int bufferInt;

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf("%s", msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isInt(bufferString) == 1)
			{
				bufferInt = atoi(bufferString);
				if(bufferInt >= min && bufferInt<= max)
				{
					*pResult = bufferInt;
					retorno = 0;
					break;
				}
				else
				{
					printf("%s", msgError);
					attemps--;
				}

			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}

		}while(attemps >= 0);
	}
	return retorno;
}

/**
 * \brief Funcion para pedirle al usuario un numero flotante
 * \param char msg[]: Puntero a una cadena de texto
 * \param char msgError[]: Puntero a una cadena de texto en caso de error
 * \param float *pResult: Puntero del flotante que vamos a devolver
 * \param int attemps: Reintentos que va a tener la funcion en caso de error
 * \param int min: Es el minimo permitido para el numero
 * \param int max: Es el maximo permitido para el numero
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int utn_getFloat(char msg[], char msgError[], float *pResult, int attemps, int min, int max)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	float bufferFloat;

	if(msg != NULL && msgError != NULL && pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf("%s", msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isFloat(bufferString) == 1)
			{
				bufferFloat = atof(bufferString);
				if(bufferFloat >= min && bufferFloat<= max)
				{
					*pResult = bufferFloat;
					retorno = 0;
					break;
				}
				else
				{
					printf("%s", msgError);
					attemps--;
				}

			}
			else
			{
				printf("%s", msgError);
				attemps--;
			}

		}while(attemps >= 0);
	}
	return retorno;
}

/**
 * \brief Funcion que me imprime el menu en el main.c
 * \param int *pResult: Puntero que hace referencia a la opcion del menu elegida
 * \param int attemps: Cantidad de reintentos
 * \param int min: Es el minimo permitido para el numero
 * \param int max: Es el maximo permitido para el numero
 * \return (-1) si algo salio mal (0) si todo esta OK
 */
int utn_getMenu(char msg[],int *pResult, int attemps, int min, int max)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];
	int bufferInt;

	if(pResult != NULL && attemps >= 0 && min <= max)
	{
		do
		{
			printf(msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isInt(bufferString) == 1)
			{
				bufferInt = atoi(bufferString);
				if(bufferInt >= min && bufferInt<= max)
				{
					*pResult = bufferInt;
					retorno = 0;
					break;
				}
				else
				{
					printf("\nError! elija una opcion valida");
					attemps--;
				}

			}
			else
			{
				printf("Error! elija una opcion valida");
				attemps--;
			}
		}while(attemps >= 0);
	}
	return retorno;
}
