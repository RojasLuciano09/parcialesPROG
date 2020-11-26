#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"



static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */

LinkedList* ll_newLinkedList(void)
{
    LinkedList* this = NULL;

    this=(LinkedList*)malloc(sizeof(LinkedList));  //tamaño de la lista.

    if(this!=NULL)
    {
        this->size=0;                    // el size aun es 0.
        this->pFirstNode=NULL;          //si la inicio, el primero nodo es null.
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista,
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int size = -1;
    if(this!=NULL)
    {
        size=this->size;
    }
    return size;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */


static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* node = NULL;

    if(this!=NULL && nodeIndex>=0 && nodeIndex<ll_len(this))
    {
        node = this->pFirstNode;                              //node es igual al primer nodo de la lista.
        for(int i = 0 ; i < nodeIndex; i++)
        {
                node = node->pNextNode;						//uso el bucle para ir llegando al indice.
        }
    }
    return node;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */

static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int retorno=-1;
    Node* pNewNode;
    Node* pPreviousNode;

    if(this!=NULL && nodeIndex>=0 && nodeIndex<=ll_len(this))
    {
        pNewNode = (Node*)malloc(sizeof(Node));							  					// creo espacio en memoria.
        if(pNewNode !=NULL)
        {
                pNewNode->pElement = pElement;												//el nuevo elemento sera el elemento del nodo.

                        if(nodeIndex == 0)													//quiero agregar nodo en la primera posicion
                        {
                                pNewNode->pNextNode = this->pFirstNode;
                                this->pFirstNode = pNewNode;

                        }
                        else																//quiero agregar nodo en otra posicion
                        {
                                pPreviousNode = getNode(this, nodeIndex-1);					//obtengo el previo
                                pNewNode->pNextNode = pPreviousNode->pNextNode;				// el nuevo apunta al siguiente del previo.
                                pPreviousNode->pNextNode = pNewNode;						// el siguiente del previo va a ser el nuevo.

                        }

                        this->size++;
                        retorno = 0;
        }
    }
    return retorno;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int retorno = -1;
    int len=ll_len(this);
    if(this!=NULL && len>-1)
    {
        addNode(this,len,pElement);       //añado a la lista
        retorno=0;
    }
    return retorno;
}

/**
 * @fn void ll_get*(LinkedList*, int)
 * @brief Devuelve un puntero a la direccion de memoria donde se encuentra un elemento de tipo Empleado
 * @param this La LinkedList
 * @param index El indice donde se encuentra el elemento de tipo Empleado
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;

    int len = ll_len(this);

	Node* auxNode=NULL;

    if(this!=NULL && index>-1 && len>index)
    {

    	auxNode = getNode(this, index);		//obtengo el nodo
    	if(auxNode!=NULL)
    	{
    		returnAux = auxNode->pElement; //return aux va a ser al elemento del nodo obtenido
    	}
    }
    return returnAux;
}



/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* auxNode=NULL;
    if(this!=NULL && index>-1 && index<ll_len(this))
    {
    	auxNode = getNode(this, index);
    	if(auxNode!=NULL)
    	{

			returnAux=0;
    		auxNode->pElement = pElement;
    	}
    }
    return returnAux;
}

/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* pAuxNode=NULL;
    Node* pPrevNode=NULL;
    if(this!=NULL && index>-1 && index<ll_len(this))
    {
    	pAuxNode = getNode(this,index);
    	if(pAuxNode!=NULL && index==0)
		{
			this->pFirstNode=pAuxNode->pNextNode;
		}
    	else
    	{
			pPrevNode = getNode(this, index-1);
			if(pPrevNode!=NULL)
			{
				pPrevNode->pNextNode = pAuxNode->pNextNode;
			}
    	}
		returnAux = 0;
		this->size--;
		free(pAuxNode);
    }
    return returnAux;
}

/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int output = -1;

    if(this!=NULL)
    {
        while(ll_len(this)!=0)
        {
            ll_remove(this,0);
        }
        this->pFirstNode=NULL;
        output=0;
    }
    return output;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int output = -1;

    if(this!=NULL)
    {
        while(ll_len(this)!=0)
        {
            ll_remove(this,0);
        }
        free(this);
        output=0;
    }
    return output;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
 {
	int output = -1;
	int len = ll_len(this);
	void* tempAux;

	if (this != NULL)
	{
		for (int i = 0; i < len; i++)
		{
			tempAux = ll_get(this, i);
			if (tempAux == pElement)    //
			{
				output = i;
				break;
			}
		}
	}
	return output;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList *this) {
	int output = -1;
	int len = ll_len(this);

	if (this != NULL)
	{
		output = 1;
		if (len != 0)
		{
			output = 0;
		}
	}
	return output;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int output = -1;
    int len = ll_len(this);

    if(this!=NULL && index >= 0 && index <= len)
    {
       if(!addNode(this,index,pElement))
       {
    	   output=0;
       }
    }
    return output;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */

void* ll_pop(LinkedList* this,int index)
{
    void* output = NULL;
    int len = ll_len(this);

    if(this!=NULL && index >= 0 && index<len)
    {
        output = ll_get(this,index);
        if(ll_remove(this,index))
        {
                output = NULL;
        }
    }
    return output;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/

int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int indexElement = -1;
    if(this != NULL)
    {
    	indexElement = ll_indexOf(this, pElement);
    	if(indexElement >=0)
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int output = -1;
    int len;

    if(this!=NULL && this2!=NULL)
    {
        output=1;
        len=ll_len(this2);
        for(int i=0; i<len; i++)
        {
            if(!ll_contains(this,ll_get(this2,i))) // si los elementos no estan
            {
                output=0;
                break;
            }
        }
    }
    return output;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/

LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList *cloneArray = NULL;
    Node* pNodeToAdd = NULL;
    if(this != NULL && from >=0 && to <= ll_len(this))
    {
        cloneArray = (LinkedList*)malloc(sizeof(LinkedList));
        if(cloneArray != NULL)
        {
            for(int x = 0; x < to; x++)
            {
                pNodeToAdd = getNode(this, from);
                if(pNodeToAdd != NULL)
                {
                    addNode(cloneArray, x, pNodeToAdd->pElement);
                    from++;
                }
            }
        }
    }
    return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/

LinkedList* ll_clone(LinkedList* this)
{
    LinkedList *cloneArray = NULL;
    if(this != NULL)
    {
        cloneArray = (LinkedList*)malloc(sizeof(LinkedList));
        if(cloneArray != NULL)
        {
            cloneArray = this;
        }
    }
    return cloneArray;
}

/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                        ( 0) Si ok
*/
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    void* pFirstNode=NULL;
    void* pSecondNode=NULL;
    int len=ll_len(this);
    int flagSwap;
    if(this!=NULL && pFunc!=NULL && (order==1 || order==0))
    {

    	do
    	{
    		flagSwap=1;
			for(int i=0;i<len-1;i++)
			{

				pFirstNode=ll_get(this, i);
				pSecondNode=ll_get(this, i+1);
				if(pFirstNode!=NULL && pSecondNode!=NULL)
				{
					if( (order==1 && pFunc(pFirstNode,pSecondNode)<0) ||
						(order==0 && pFunc(pFirstNode, pSecondNode)>0))
					{

						ll_set(this, i, pSecondNode);
						ll_set(this, i+1, pFirstNode);
						flagSwap=0;
					}
				}
			}
    	}while(flagSwap==0);
    	returnAux=0;
    }
    return returnAux;
}

/** \brief  crea una nueva lista con todos los elementos que pasan la prueba implementada por la función criterio.
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return   NULL   = algo salio mal
             Linkdlist*= OK.
 */
LinkedList* ll_filterBySomethingCloneAndReturn(LinkedList* this, int (*pFunc)(void*,void*),void* arg)
{
	int len = ll_len(this);
	LinkedList* auxList = NULL;
	void* pElement=NULL;

	if(this!=NULL && pFunc!=NULL)
	{
		auxList = ll_newLinkedList();
		if(auxList!=NULL)
		{
			for(int i=0; i<len;i++)
			{
				pElement = ll_get(this, i);
				if(pElement!=NULL && pFunc(pElement,arg)==0)
				{

					ll_add(auxList, pElement);
				}
			}
		}
	}
	return auxList;
}

/** \brief  ejecuta una función reductora en cada elemento de la lista, lo que da como resultado un valor de salida único.
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return   NULL   = algo salio mal
             Linkdlist*= OK.
 */
int ll_reduceInt(LinkedList* this, int (*pFunc)(void*),int* pResultado)
{
	int output=-1;
	int acumulador=0;
	void* element;
	if(this!=NULL && pFunc!=NULL)
	{
		for(int i = 0; i< ll_len(this);i++)
		{
			element = ll_get(this, i);
			if(element!=NULL)
			{
				acumulador += pFunc(element);
			}
		}
		*pResultado = acumulador;
	}
	return output;
}

/** \brief  ejecuta una función reductora en cada elemento de la lista, lo que da como resultado un valor de salida único.
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return   NULL   = algo salio mal
             Linkdlist*= OK.
 */
float ll_reduceFloat(LinkedList* this, float (*pFunc)(void*))
{
	float returnAux =0;
	int len = ll_len(this);
	void* pElemento;
	if(this!=NULL)
	{
		for (int i = 0;i<len;i++)
		{
			pElemento=ll_get(this, i);
			returnAux= returnAux + pFunc(pElemento);
		}
	}
	return returnAux;
}


int ll_map(LinkedList* this, int (*pFunc)(void*))
{
	int output=-1;
	int len = ll_len(this);
	void* pElement;
	if(this!=NULL && pFunc != NULL)
	{
		for(int i = 0; i < len ; i++)
		{
			pElement = ll_get(this, i);
			pFunc(pElement);
		}
		output = 0 ;
	}
	return output;
}

/** \brief Recorre la lista y retorna 0 cuando se cumpla la funcion criterio
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 *  \param void* arg:  Valor a comparar.
 * \return int output  (-1) Error:
                       ( 0) todo ok.
 */
int ll_map2(LinkedList* this, int (*pFunc)(void*,void*),void* arg)
{
	int output=-1;
	int len = ll_len(this);
	void* pElement;
	if(this!=NULL && pFunc != NULL)
	{
		for(int i = 0; i < len ; i++)
		{
			pElement = ll_get(this, i);
			if(pFunc(pElement,arg)==0)
			{
				output = 0;
				break;
			}
		}
	}
	return output;
}

/** \brief Devuelve el indice del elemento que cumple la funcion criterio
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 *  \param void* arg:  Valor a comparar.
 * \return int output  (-1) Error:
                       ( 0) todo ok.
 */
int ll_search(LinkedList* this,int(*pFunc)(void*,void*), void* arg)
{
	int out=-1;
	void* element;
	if(this!=NULL)
	{
		for(int i=0;i<ll_len(this);i++)
		{
			element=ll_get(this, i);
			if(pFunc(element,arg)==0)
			{
				out=i;
				break;
			}
		}
	}
	return out;
}

/** \brief  ejecuta una función acumuladora de cada elemento de la lista, lo que da como resultado un valor de salida único.
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \return int output  (-1) Error:
                       ( 0) todo ok.
 */
int ll_reduce2(LinkedList* this, int (*pFunc)(void*,void*),void* arg,int* pResultado)
{
	int output=-1;
	int acumulador=0;
	void* element;
	if(this!=NULL && pFunc!=NULL)
	{
		for(int i = 0; i< ll_len(this);i++)
		{
			element = ll_get(this, i);
			if(element!=NULL)
			{
				acumulador = acumulador +  pFunc(element,arg);
			}
		}
		*pResultado = acumulador;
	}
	return output;
}
