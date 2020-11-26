/*
 *      Author: l.rojas
 */

#ifndef INFORMES_H_
#define INFORMES_H_

int controller_generarEstadisticas(LinkedList* listaAfiches,LinkedList* listaClientes,int opcion);
int controller_generarInforme(LinkedList* listaAfiches,LinkedList* listaClientes,char* nameFile,char* estadoVenta,char* firstRowFile);
int controller_ventaConMasAfichesVendidos(LinkedList* listaVentas,LinkedList* listaClientes);

#endif /* INFORMES_H_ */
