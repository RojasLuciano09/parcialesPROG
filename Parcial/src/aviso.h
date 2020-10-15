/* aviso.h
 * Author: Nicolas Luciano Rojas
 */
#ifndef AVISO_H_
#define AVISO_H_

#define TRUE 1
#define FALSE 0
#define ATTEMPTS 3
#define PRINT_BOTH_POST_STATUS 3
#define ERROR "\nError!, ingrese un dato valido: \n"
#define LONG_AVISO 64
#define MAX_RUBRO 10

/**
 * To check if a publication is ACTIVE
 */
#define AVISO_ACTIVE 1
#define AVISO_PAUSE 0

#include "cliente.h"

struct
{
	int id;
	int rubro;
	char textoAviso[LONG_AVISO];
	int estado;
	int isEmpty;
	int idCliente;
}typedef Aviso;

void Aviso_cargaAutomatica(Aviso *listAviso);

int Aviso_alta(Aviso *listAviso, int len,Cliente *listCliente, int lenCliente);
int Aviso_baja(Aviso *listAviso, int lenAviso,Cliente *listCliente, int lenCliente);
int Aviso_pausar(Aviso *listAviso, int len,Cliente *listCliente, int lenCliente);
int Aviso_activar(Aviso *listAviso, int len,Cliente *listCliente, int lenCliente);
int Aviso_isEmpty(Aviso *listAviso, int len);
int Aviso_printDataByIDClient(Aviso *listAviso, int len,int idCliente);
int Aviso_print(Aviso *listAviso, int lenAviso);

int Aviso_findByID_index(Aviso *listAviso,int lenAviso,int id,int *pIndex);
int Aviso_findID_ByPublicacion_index(Aviso *listAviso,int lenAviso,int idAviso,int *pID);
int Aviso_initList(Aviso *listAviso, int lenAviso);
int Aviso_searchFreeIndex(Aviso *listAviso, int lenAviso, int *pFreeIndex);
int Aviso_imprimirClienteJuntoACantidadDeAvisos(Aviso* listAviso, int lenAvisos,Cliente *listCliente,int lenCliente);

int Aviso_printDataFromBothEntities(Aviso *listAviso, Cliente *listCliente, int lenAviso, int lenCliente,int estado);

#endif /* AVISO_H_ */
