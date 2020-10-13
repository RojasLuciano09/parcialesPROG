/*
 * utn.h
 *
 *  Created on: 10 oct. 2020
 *      Author: l.rojas
 */

#ifndef UTN_H_
#define UTN_H_


int utn_getCuit(char msg[], char msgError[], char pResult[], int attemps, int limit);
int utn_getString(char mensaje[], char mensajeError[], char pResultado[], int attemps, int limit);
int utn_getInt(char msg[], char msgError[], int *pResult, int attemps, int min, int max);
int utn_getMenu(char [],int *pResult, int attemps, int min, int max);
int utn_getFloat(char msg[], char msgError[], float *pResult, int attemps, int min, int max);
int utn_getLetrasYEspacios(char* pResultado,int len,char* mensaje,char* mensajeError,int reintentos);

#endif /* UTN_H_ */
