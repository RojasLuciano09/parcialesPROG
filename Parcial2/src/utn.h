/*
 *      Author: l.rojas
 */

#ifndef UTN_H_
#define UTN_H_
#define SIZE 4096
#define ERROR "\nError!, ingrese una opcion valida..\n"
#define ATTEMPTS 3
#include <limits.h>


int utn_getIntStr(char msg[], char msgError[], char pResult[], int attemps, int limit);
int utn_getString(char msg[], char msgError[], char pResult[], int attemps, int limit);
int utn_getMenu(char msg[],int *pResult, int attemps, int min, int max);
int utn_getFloat(char msg[], char msgError[], float *pResult, int attemps, int min, int max);
int utn_getInt(char msg[], char msgError[], int *pResult, int attemps, int min, int max);
int utn_getCuit(char msg[], char msgError[], char pResult[], int attemps, int limit);
int utn_getLetrasYEspacios(char* pResultado,int len,char* mensaje,char* mensajeError,int reintentos);
int utn_getFileName(char* pMensaje, char* pMensajeError, char* pResultado, int reintentos, int limite);


int isAlphaNum(char* pResultado);
int utn_getCuit(char msg[], char msgError[], char pResult[], int attemps, int limit);
int esLetrasYEspacios(char* cadena, int len);
int isInt(char string[]);
int isString(char string[]);
int isCuit(char string[]);
int esUnArchivo(char* cadena);
int esNumericaInt(char* cadena, int len);

#endif /* UTN_H_ */
