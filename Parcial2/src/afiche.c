/*
 * afiche.c
 *
 *  Created on: 21 nov. 2020
 *      Author: l.rojas
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>
#include "Afiche.h"
#include "utn.h"

Afiche* Afiche_new()
{
	Afiche* this;
	this = (Afiche*)malloc(sizeof(Afiche));
	if(this!=NULL)
	{
		return this;
	}
	return NULL;
}

void Afiche_delete(Afiche* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}


Afiche* Afiche_newParametros(char* id, char* id_cliente, char* cantidad_afiches, char* nombre_archivo, char* zona_pegar_afiche, char* a_cobrar)
{
	Afiche* this = Afiche_new();
	if(this!=NULL)
	{
		if(     Afiche_setIdStr(this, id)==0 										&&
				Afiche_set_id_clienteSTR(this, id_cliente)==0 					&&
				Afiche_set_cantidad_afichesSTR(this, cantidad_afiches) ==0 		&&
				Afiche_set_nombre_archivo(this, nombre_archivo) ==0 			&&
				Afiche_set_zona_pegar_aficheSTR(this, zona_pegar_afiche) ==0 	&&
				Afiche_set_a_cobrarSTR(this, a_cobrar)==0 						)
		{
			return this;
		}
	}
	Afiche_delete(this);
	return NULL;
}


int Afiche_setId(Afiche* this,int id)
{
	int output=-1;
	if(this!=NULL && id>-1)
	{
		this->id = id;
		output=0;
	}
	return output;
}

int  Afiche_getId(Afiche* this,int* id)
{
	int output=-1;
	if(this!=NULL && id!=NULL)
	{
		*id = this->id;
		output=0;
	}
	return output;
}

int Afiche_setIdStr(Afiche* this, char* id)
{
	int retornar=-1;
	char bufferId[SIZE];
	if(this!=NULL && isInt(id)==1 && id!=NULL  )
	{
		strncpy(bufferId, id, SIZE);
		this->id = atoi(bufferId);
		retornar=0;
	}
	return retornar;
}

int Afiche_getIdStr(Afiche* this,char* id)
{
	int output=-1;

	if(this!=NULL && id!=NULL)
	{
		sprintf(id,"%d",this->id);
		output=0;
	}
	return output;
}

int Afiche_set_id_clienteSTR(Afiche* this, char* id_cliente)
{
	int retornar=-1;
	char bufferId[SIZE];
	if(this!=NULL && id_cliente!=NULL && isInt(id_cliente)==1)
	{
		strncpy(bufferId, id_cliente, SIZE);
		this->id_cliente = atoi(bufferId);
		retornar=0;
	}
	return retornar;
}

int Afiche_get_id_clienteSTR(Afiche* this,char* id_cliente)
{
	int output=-1;

	if(this!=NULL && id_cliente!=NULL)
	{
		sprintf(id_cliente,"%d",this->id_cliente);
		output=0;
	}
	return output;
}










int Afiche_set_cantidad_afichesSTR(Afiche* this, char* cantidad_afiches)
{
	int output=-1;
	char buffer[SIZE];
	if(this!=NULL && cantidad_afiches!=NULL && isInt(cantidad_afiches)==1)
	{
			strncpy(buffer, cantidad_afiches, SIZE);
			this->cantidad_afiches=atoi(buffer);
			output=0;
	}
	return output;
}

int Afiche_get_cantidad_afichesSTR(Afiche* this,char* cantidad_afiches)
{
	int output=-1;
	if(this!=NULL && cantidad_afiches!=NULL)
	{
		sprintf(cantidad_afiches,"%d",this->cantidad_afiches);
		output=0;
	}
	return output;
}

int Afiche_set_nombre_archivo(Afiche* this,char* nombre_archivo)
{
	int output=-1;
	if(this!=NULL && esUnArchivo(nombre_archivo)==1)//isString(nombre_archivo)==1 && nombre_archivo!=NULL)
	{
		strncpy(this->nombre_archivo,nombre_archivo,LONG_NAME);
		output=0;
	}
	return output;
}

int Afiche_get_nombre_archivo(Afiche* this,char* nombre_archivo)
{
	int output=-1;
	if(this!=NULL && nombre_archivo!=NULL)
	{
		strncpy(nombre_archivo, this->nombre_archivo, LONG_NAME);
		output=0;
	}
	return output;
}

int Afiche_set_zona_pegar_aficheSTR(Afiche* this, char* zona_pegar_afiche)
{
	int output=-1;
	char buffer[SIZE];
	if(this!=NULL && zona_pegar_afiche!=NULL && isInt(zona_pegar_afiche)==1)
	{
			strncpy(buffer, zona_pegar_afiche, SIZE);
			this->zona_pegar_afiche=atoi(buffer);
			output=0;
	}
	return output;
}

int Afiche_get_zona_pegar_aficheSTR(Afiche* this,char* zona_pegar_afiche)
{
	int output=-1;
	if(this!=NULL && zona_pegar_afiche!=NULL)
	{
		sprintf(zona_pegar_afiche,"%d",this->zona_pegar_afiche);
		output=0;
	}
	return output;
}

int Afiche_set_a_cobrarSTR(Afiche* this, char* a_cobrar)
{
	int output=-1;
	char buffer[SIZE];
	if(this!=NULL && a_cobrar!=NULL && isInt(a_cobrar)==1)
	{
			strncpy(buffer, a_cobrar, SIZE);
			this->a_cobrar=atoi(buffer);
			output=0;
	}
	return output;
}

int Afiche_get_a_cobrarSTR(Afiche* this,char* a_cobrar)
{
	int output=-1;
	if(this!=NULL && a_cobrar!=NULL)
	{
		sprintf(a_cobrar,"%d",this->a_cobrar);
		output=0;
	}
	return output;
}

int Afiche_set_zona_pegar_afiche_INT(Afiche* this,int zona_pegar_afiche)
{
	int output=-1;
	if(this!=NULL && zona_pegar_afiche>0)
	{
		this->zona_pegar_afiche = zona_pegar_afiche;
		output=0;
	}
	return output;

}

int Afiche_get_zona_pegar_afiche_INT(Afiche* this,int* zona_pegar_afiche)
{
	int output=-1;
	if(this!=NULL && zona_pegar_afiche!=NULL)
	{
		*zona_pegar_afiche = this->zona_pegar_afiche;
		output=0;
	}
	return output;

}

int Afiche_set_a_cobrar_INT(Afiche* this,int a_cobrar)
{
	int output=-1;
	if(this!=NULL && a_cobrar>0)
	{
		this->a_cobrar = a_cobrar;
		output=0;
	}
	return output;
}

int Afiche_get_a_cobrar_INT(Afiche* this,int* a_cobrar)
{
	int output=-1;
	if(this!=NULL && a_cobrar!=NULL)
	{
		*a_cobrar = this->a_cobrar;
		output=0;
	}
	return output;
}

int Afiche_print(void* itemOne)
{
	int output=-1;
	Afiche* buffer;
	buffer =(Afiche*)itemOne;

	char idAux[SIZE];
	char id_clienteAux[SIZE];
	char cantidad_afichesAux[SIZE];
	char nombre_archivoAux[SIZE];
	char zona_pegar_aficheAux[SIZE];
	char a_cobrarAux[SIZE];
	char zona[SIZE];
	char cobrar[SIZE];



	if(buffer!=NULL)
	{
		if( 	Afiche_getIdStr(buffer, idAux)==0 									 &&
				Afiche_get_id_clienteSTR(buffer, id_clienteAux)==0 					 &&
				Afiche_get_cantidad_afichesSTR(buffer, cantidad_afichesAux)==0 		 &&
				Afiche_get_nombre_archivo(buffer, nombre_archivoAux)==0 				 &&
				Afiche_get_zona_pegar_aficheSTR(buffer, zona_pegar_aficheAux)==0		 &&
				Afiche_get_a_cobrarSTR(buffer, a_cobrarAux)==0						 	&&
				convertZona(zona_pegar_aficheAux, zona)==0								&&
				convertACobrar(a_cobrarAux, cobrar)==0										)
		{

			printf("%-3s %-12s %-17s %-14s  %-11s %-11s \n", idAux, id_clienteAux, cantidad_afichesAux, nombre_archivoAux,zona,cobrar);
			output = 0;
		}
	}
	return output;
}


int afichesCobrados(void* itemOne)
{
	int out=-1;
	Afiche* this;
	this =(Afiche*)itemOne;
	char esta_cobrado[SIZE];

	if(Afiche_get_a_cobrarSTR(this, esta_cobrado)==0 &&
	   strncmp(esta_cobrado,"1",SIZE)==0)
	{
		out =0;
	}
	return out;
}

int devuelvoElementoPorID(void* itemOne,void* itemTwo,char* id_cliente)
{
	int out=-1;
	Afiche* this;
	this =(Afiche*)itemOne;
	char id_in[SIZE];
	char id_obtenido[SIZE];


	if( Afiche_getIdStr(this, id_in)==0  &&
	    strncmp(id_in,itemTwo,SIZE)==0  	  )
	{
		Afiche_get_id_clienteSTR(this, id_obtenido);
		strncpy(id_cliente,id_obtenido,SIZE);
		out =0;
	}


	return out;
}








int convertZona(char* in, char* out)
{
	int output=-1;

	if(strncmp(in,"0",4096)==0)
	{
		strncpy(out,"CABA",5);
		output = 0;
	}
	else if(strncmp(in,"1",4096)==0)
	{
		strncpy(out,"ZONA_SUR",10);
		output = 0;
	}else
	{
		strncpy(out,"ZONA_OESTE",15);
		output = 0;
	}
	return output;
}

int convertACobrar(char* in, char* out)
{
	int output=-1;

	if(strncmp(in,"0",10)==0)
	{
		strncpy(out,"NO",5);
		output = 0;
	}
	else if(strncmp(in,"1",5)==0)
	{
		strncpy(out,"SI",10);
		output = 0;
	}
	return output;
}
