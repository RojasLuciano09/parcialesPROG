/*
 *      Author: l.rojas
 */
#include "LinkedList.h"
#ifndef PARSER_H_
#define PARSER_H_

#define SIZE 4096


int parser_ClienteFromText(FILE* pFile , LinkedList* list);
int parser_VentasFromText(FILE* pFile , LinkedList* list);
int parser_SaveClientToText(FILE* pFile, LinkedList* listClient);
int parser_SaveVentaToText(FILE* pFile, LinkedList* listAfiche);


int parser_EmployeeFromBinary(FILE* pFile , LinkedList* list);

#endif /* PARSER_H_ */
