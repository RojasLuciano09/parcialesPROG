/*
 *      Author: l.rojas
 */
#include "LinkedList.h"


#define AFICHE_PRINT "\nID  id_cliente   cantidad_afiches  nombre_archivo  zona_pegar  estaCobrado\n"
#define CLIENTE_PRINT "\nID     Nombre      Apellido        Cuit\n"
#define COBRADOS "1"
#define NO_COBRADOS "0"
#define CLIENTE_AL_QUE_VENDIO_MAS_AFICHES 1
#define CLIENTE_AL_QUE_VENDIO_MENOS_AFICHES 0
#define COBRADOS_TXT "cobrados.txt"
#define A_COBRAR_TXT "a_cobrar.txt"
#define firstRow_A_COBRAR "id,nombre,apellido,cuit,a_cobrar\n"
#define firstRow_COBRADAS "id,nombre,apellido,cuit,ventas_cobradas\n"
#define CUIT_EXISTS "\nEse cuit ya existe\n"

#define menu "\nElija una opcion: \n1) Agregar cliente\n2) Vender afiches\n3) Modificar venta\n4) Cobrar venta\n5) Generar informe de cobros\n6) Generar informe de deudas\n7) Generar estadisticas\n8)EXIT\n> OPCION: "
#define subMenu "\nElija una opcion: \n1) Cliente al que se le vendió mas afiches\n2) Cliente al que se le vendió menos afiches\n3) Venta con mas afiches vendidos \n4) EXIT\n> OPCION: "


typedef int (*parserFunction)(FILE*, LinkedList*);
int controller_loadOrSave(char* openType, parserFunction pFunc,char* path, LinkedList* list);   	// 0
int controller_addEmployee(LinkedList* listaClientes);												// 1
int controller_vender_afiches(LinkedList* listaAfiches,LinkedList* listaClientes);					// 2
int controller_modificar_Venta(LinkedList* listaVentas,LinkedList* listaClientes,void* arg);
int controller_cobrar_venta(LinkedList* listaAfiches,LinkedList* listaClientes); 					// 4
int controller_print(LinkedList* thisList,int(*pFunc)(void*),char* selectEntity); // vale para todo.









