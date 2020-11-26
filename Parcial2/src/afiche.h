/*
 *      Author: l.rojas
 */

#ifndef AFICHE_H_
#define AFICHE_H_


#define LONG_NAME 128



typedef struct
{
    int id;
    int id_cliente;
    int cantidad_afiches;
	char nombre_archivo[SIZE];
    int zona_pegar_afiche;
	int a_cobrar;
}Afiche;

int Afiche_print(void* itemOne);
int Afiche_get_a_cobrar_INT(Afiche* this,int* a_cobrar);
int Afiche_set_a_cobrar_INT(Afiche* this,int a_cobrar);
int Afiche_get_zona_pegar_afiche_INT(Afiche* this,int* zona_pegar_afiche);
int Afiche_set_zona_pegar_afiche_INT(Afiche* this,int zona_pegar_afiche);
int Afiche_get_a_cobrarSTR(Afiche* this,char* a_cobrar);
int Afiche_set_a_cobrarSTR(Afiche* this, char* a_cobrar);
int Afiche_get_zona_pegar_aficheSTR(Afiche* this,char* zona_pegar_afiche);
int Afiche_set_zona_pegar_aficheSTR(Afiche* this, char* zona_pegar_afiche);
int Afiche_get_nombre_archivo(Afiche* this,char* nombre_archivo);
int Afiche_set_nombre_archivo(Afiche* this,char* nombre_archivo);
int Afiche_get_cantidad_afichesSTR(Afiche* this,char* cantidad_afiches);
int Afiche_set_cantidad_afichesSTR(Afiche* this, char* cantidad_afiches);
int Afiche_get_id_clienteSTR(Afiche* this,char* id_cliente);
int Afiche_set_id_clienteSTR(Afiche* this, char* id_cliente);
int Afiche_getIdStr(Afiche* this,char* id);
int Afiche_setIdStr(Afiche* this, char* id);
int  Afiche_getId(Afiche* this,int* id);
int Afiche_setId(Afiche* this,int id);
Afiche* Afiche_newParametros(char* id, char* id_cliente, char* cantidad_afiches, char* nombre_archivo, char* zona_pegar_afiche, char* a_cobrar);
void Afiche_delete(Afiche* this);
Afiche* Afiche_new();
int convertZona(char* in, char* out);
int convertACobrar(char* in, char* out);
int compararIDparaFiltrar(void* itemOne,void* itemTwo);
int afichesCobrados(void* itemOne,void* arg);
int devuelvoElementoPorID(void* itemOne,void* itemTwo,char* id_cliente);
int comparoID(void* itemOne,void* itemTwo);
int comparoID_cliente(void* itemOne,void* itemTwo);
int Afiche_get_cantidad_afichesINT(Afiche* this,int* cantidad_afiches);
int compararCantidadDeVentas(void* itemOne,void* itemTwo);

#endif /* AFICHE_H_ */
