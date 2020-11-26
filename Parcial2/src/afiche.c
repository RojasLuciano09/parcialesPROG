/*
 *      Author: l.rojas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "afiche.h"


/**
 * \brief Función para solicitar espacio en memoria
 * \return  this  (Afiche) Devuelve memoria del tamaño de la entidad
                  (NULL) No se pudo obtener memoria.
 */
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

/**
 * \brief Función para liberar espacio en memoria de la entidad.
 */
void Afiche_delete(Afiche* this)
{
	if(this!=NULL)
	{
		free(this);
	}
}


/**
 * \brief Función crear un nueva venta.
 */
Afiche* Afiche_newParametros(char* id, char* id_cliente, char* cantidad_afiches, char* nombre_archivo, char* zona_pegar_afiche, char* a_cobrar)
{
	Afiche* this = Afiche_new();
	if(this!=NULL)
	{
		if(     Afiche_setIdStr(this, id)==0 								&&
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

/**
 * \brief Función setear un id a la venta
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param int id: Valor a setear.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función obtener un id a la venta por puntero
 * \param Afiche* this: Puntero a la estructura a la cual obtener un valor.
 * \param int* id: Puntero que obtendra el valor.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función setear un id a la venta
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param char* id: Valor a setear.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función obtener un id de la venta que devolvera por puntero.
 * \param Afiche* this: Puntero a la estructura a la cual obtener un valor.
 * \param char* id: Puntero que obtendra el valor.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función setear un id cliente a la venta
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param char* id_cliente: Valor a setear.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función obtener un id cliente de la venta que devolvera por puntero.
 * \param Afiche* this: Puntero a la estructura a la cual obtener un valor.
 * \param char* id: Puntero que obtendra el valor.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función setear una cantidad de afiches a la venta
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param char* cantidad_afiches: Valor a setear.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función obtener una cantidad de afiches a la venta
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param char* cantidad_afiches: Puntero que obtendra el valor.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función obtener una cantidad de afiches a la venta
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param int* cantidad_afiches: Puntero que obtendra el valor.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
int Afiche_get_cantidad_afichesINT(Afiche* this,int* cantidad_afiches)
{
	int output=-1;
	if(this!=NULL && cantidad_afiches!=NULL)
	{
		*cantidad_afiches = this->cantidad_afiches;
		output=0;
	}
	return output;
}

/**
 * \brief Función setear un nombre de archivo a la venta
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param char* nombre_archivo: Valor a setear.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
int Afiche_set_nombre_archivo(Afiche* this,char* nombre_archivo)
{
	int output=-1;
	if(this!=NULL && esUnArchivo(nombre_archivo)==1)
	{
		strncpy(this->nombre_archivo,nombre_archivo,LONG_NAME);
		output=0;
	}
	return output;
}

/**
 * \brief Función obtener una cantidad de afiches a la venta
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param char* nombre_archivo: Puntero que obtendra el valor.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función para setear una zona a la venta.
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param char* zona_pegar_afiche: Valor a setear.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función obtener una zona donde pegar el afiche de la venta
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param char* zona_pegar_afiche: Puntero que obtendra el valor.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función para setear el valor a cobrar a la venta.
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param char* a_cobrar: Valor a setear.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función obtener el valor de cobro de la venta.
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param char* a_cobrar: Puntero que obtendra el valor.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función para setear la zona donde pegar.
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param int zona_pegar_afiche: Valor a setear.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función obtener el valor de la zona donde pegar.
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param int* zona_pegar_afiche: Puntero que obtendra el valor.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función para setear la zona donde pegar.
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param int zona_pegar_afiche: Valor a setear.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función obtener el valor a cobrar.
 * \param Afiche* this: Puntero a la estructura a la cual asignar un valor.
 * \param int* a_cobrar: Puntero que obtendra el valor.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función para mostrar en consola.
 * \param void* itemOne: Puntero a imprimir.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función para verifica el estado de un afiche.
 * \param void* itemOne: Puntero a comparar y es casteado a Afiche*.
 * \param void* arg: Puntero a comparar.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
int afichesCobrados(void* itemOne,void* arg)
{
	int out=-1;
	Afiche* this;
	this =(Afiche*)itemOne;
	char esta_cobrado[SIZE];

	if(Afiche_get_a_cobrarSTR(this, esta_cobrado)==0 &&
	   strncmp(esta_cobrado,arg,SIZE)==0)
	{
		out =0;
	}
	return out;
}

/**
 * \brief Función para obtener por puntero el id_cliente de un afiche
 * \param void* itemOne: Puntero a comparar y es casteado a Afiche*.
 * \param void* arg: Puntero a comparar.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
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

/**
 * \brief Función para comparar id
 * \param void* itemOne: Puntero a comparar y es casteado a Afiche*.
 * \param void* itemTwo: Puntero a comparar.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
int comparoID(void* itemOne,void* itemTwo)
{
	int out=-1;
	Afiche* this;
	this =(Afiche*)itemOne;
	char id_obtenido[SIZE];


	if( Afiche_getIdStr(this,id_obtenido )==0  &&
	    strncmp(id_obtenido,itemTwo,SIZE)==0  	 )
	{

		out =0;
	}
	return out;
}


/**
 * \brief Función para comparar id cliente
 * \param void* itemOne: Puntero a comparar y es casteado a Afiche*.
 * \param void* itemTwo: Puntero a comparar.
 * \return int output  (1) si son iguales
                       ( 0) si no lo son.
 */
int comparoID_cliente(void* itemOne,void* itemTwo)
{
	int out=0;
	Afiche* this;
	this =(Afiche*)itemOne;
	char id_obtenido[SIZE];



	if( Afiche_get_id_clienteSTR(this,id_obtenido )==0  &&
	    strncmp(id_obtenido,itemTwo,SIZE)==0  	 		)
	{
		out =1;
	}
	return out;
}

/**
 * \brief Función para comparar y filtrar id
 * \param void* itemOne: Puntero a comparar y es casteado a Afiche*.
 * \param void* itemTwo: Puntero a comparar.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
int compararIDparaFiltrar(void* itemOne,void* itemTwo)
{
	int out=-1;
	Afiche* this;
	this =(Afiche*)itemOne;
	char id_obtenido[SIZE];

	if( Afiche_get_id_clienteSTR(this,id_obtenido )==0  &&
	    strncmp(id_obtenido,itemTwo,SIZE)==0  	 		)
	{
		out =0;
	}
	return out;
}


/**
 * \brief Función para comparar la cantidad de afiches vendidos
 * \param void* itemOne: Puntero a comparar y es casteado a Afiche*.
 * \param void* itemTwo: Puntero a comparar.
 * \return int output  (-1) Error.
                       ( 0) si es menor.
 */
int compararCantidadDeVentas(void* itemOne,void* itemTwo)
{
	int out=-1;
	Afiche* this;
	this =(Afiche*)itemOne;
	int cantidadAux;
	int temp;
	temp = *(int *)itemTwo;
	Afiche_get_cantidad_afichesINT(this, &cantidadAux);
	if(cantidadAux <  temp)
	{
		out =0;
	}
	return out;
}



/**
 * \brief Función para convertir el valor de la zona
 * \param char* in: Puntero de ingreso.
 * \param char* out: Puntero de salida.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
int convertZona(char* in, char* out)
{
	int output=-1;

	if(strncmp(in,"0",SIZE)==0)
	{
		strncpy(out,"CABA",SIZE);
		output = 0;
	}
	else if(strncmp(in,"1",SIZE)==0)
	{
		strncpy(out,"ZONA_SUR",SIZE);
		output = 0;
	}else
	{
		strncpy(out,"ZONA_OESTE",SIZE);
		output = 0;
	}
	return output;
}

/**
 * \brief Función para convertir el valor de si esta cobrado
 * \param char* in: Puntero de ingreso.
 * \param char* out: Puntero de salida.
 * \return int output  (-1) Error.
                       ( 0) todo ok.
 */
int convertACobrar(char* in, char* out)
{
	int output=-1;

	if(strncmp(in,"0",SIZE)==0)
	{
		strncpy(out,"NO",SIZE);
		output = 0;
	}
	else if(strncmp(in,"1",SIZE)==0)
	{
		strncpy(out,"SI",SIZE);
		output = 0;
	}
	return output;
}
