/*
 *      Author: l.rojas
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_
#define LONG_NAME 128
#define SIZE 4096


typedef struct
{
    int id;
    char nombre[LONG_NAME];
    char apellido[LONG_NAME];
    char cuit [SIZE];
}Cliente;

int Cliente_sortID(void* itemOne,void* itemTwo);
int Cliente_sort(void* itemOne,void* itemTwo);
int Cliente_print(void* itemOne);
int Cliente_get_cuit(Cliente* this,char* cuit);
int Cliente_set_cuit(Cliente* this,char* cuit);
int Cliente_get_apellido(Cliente* this,char* apellido);
int Cliente_set_apellido(Cliente* this,char* apellido);
int Cliente_get_nombre(Cliente* this,char* nombre);
int Cliente_set_nombre(Cliente* this,char* nombre);
int Cliente_getIdStr(Cliente* this,char* id);
int Cliente_setIdStr(Cliente* this, char* id);
int  Cliente_getId(Cliente* this,int* id);
int Cliente_setId(Cliente* this,int id);
Cliente* Cliente_newParametros(char* id,char* nombre,char* apellido, char* cuit);
void Cliente_delete(Cliente* this);
Cliente* Cliente_new();

int thisCuitExists(void* itemOne,void* cuit);
int veoSiExisteEsteID(void* itemOne,void* id);
int Cliente_printById(void* itemOne,void* arg);
int comparoIDCliente(void* itemOne,void* itemTwo);
int Cliente_printCUIT(void* itemOne);












#endif /* CLIENTE_H_ */
