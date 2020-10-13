/*
 * informe.h
 *
 *  Created on: 11 oct. 2020
 *      Author: l.rojas
 */

#ifndef INFORME_H_
#define INFORME_H_

int Informe_imprimirClienteAvisosACTIVOS(Aviso* listAviso, int lenAvisos,Cliente *listCliente,int lenCliente,int estado);
int Informe_cantidadDeAvisosPausados(Aviso *listAviso, int lenAvisos,Cliente *listCliente,int lenCliente,int estado);
int Informe_cantidadDeAvisosMAX(Aviso *listAviso, int lenAvisos,Cliente *listCliente,int lenCliente,int estado);
int informe_rubroConMasAviso(Aviso *list, int len);
int informe_calcularRubroRepetido(Aviso *list, int len, int rubro, int *pCounter);
#endif /* INFORME_H_ */
