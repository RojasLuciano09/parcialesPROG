/* cliente.h
 * Author: Nicolas Luciano Rojas
 */
#ifndef CLIENTE_H_
#define CLIENTE_H_



#define TRUE 1
#define FALSE 0
#define ATTEMPTS 3
#define ERROR "\nError!, ingrese un dato valido: \n"
#define LONG_NAME 51
#define CUIT_SIZE 14


struct
{
	int id;
	char nombre[51];
	char apellido[51];
	char cuit [11];
	int isEmpty;
}typedef Cliente;

int Cliente_alta(Cliente *listCliente,int lenCliente);
int Cliente_modificar(Cliente *listCliente, int lenCliente);
int Cliente_removeByID(Cliente *listCliente, int lenCliente,int idToDelete);
int Cliente_isEmpty(Cliente *listCliente, int lenCliente);
int Cliente_findID_returnINDEX(Cliente *listCliente, int lenCliente,int idToFind,int *pIndex);
int Cliente_findID(Cliente *listCliente, int lenCliente,int idToFind);
int Cliente_initList(Cliente *listCliente, int lenCliente);
int Cliente_searchFreeIndex(Cliente *listCliente, int lenCliente, int *pFreeIndex);
int Cliente_print(Cliente *listCliente, int lenCliente);
int Cliente_findByCuit(Cliente *listCliente, int lenCliente,char *cuit);
void ClienteCargaAutomatica(Cliente *listCliente,int lenCliente);


#endif /* CLIENTE_H_ */
