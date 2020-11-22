/*
 * parser.h
 *
 *  Created on: 1 nov. 2020
 *      Author: l.rojas
 */

#ifndef PARSER_H_
#define PARSER_H_

int parser_ClienteFromText(FILE* pFile , LinkedList* list);
int parser_VentasFromText(FILE* pFile , LinkedList* list);


int parser_EmployeeFromBinary(FILE* pFile , LinkedList* list);

#endif /* PARSER_H_ */
