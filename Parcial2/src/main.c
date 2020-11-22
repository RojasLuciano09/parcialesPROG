#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Cliente.h"
#include "utn.h"

/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.csv (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.csv (modo binario).
    10. Salir
*****************************************************/

int main(void)
{
	setbuf(stdout, NULL);
	LinkedList* listaCliente = ll_newLinkedList();

	LinkedList* listaVentas = ll_newLinkedList();

	//------Test
	controller_loadFromText("clientes.txt",listaCliente);
	controller_loadFromTextVentas("ventas.txt", listaVentas);


	//controller_addEmployee(listaCliente);
	//controller_printAfiche(listaVentas);
	//controller_printCliente(listaCliente);

	controller_vender_afiches(listaVentas,listaCliente);
	//controller_printAfiche(listaVentas);
	controller_modificar_Venta(listaVentas,listaCliente);



	//controller_calcularTotalDeSueldoConMap(listaEmpleados); //funciona
	//controller_ListEmployee(listaEmpleados);
	//controller_removeEmployeeBySalary(listaEmpleados); F U N C I O N A
	//controller_ListEmployee(listaEmpleados);


	//------Test
	/*

	id,nombre,horasTrabajadas,sueldo
	1,A,120,100
	2,B,180,100
	3,C,325,100
	4,D,120,100
	5,E,220,100








    printf("\nBienvenido al sistema de gestión de empleados.\n");
    do{
    	utn_getMenu(&option, ATTEMPTS, 1, 10);

        switch(option)
        {
            case 1:

                if(loadFlag==0 && controller_loadFromText("data.csv",listaEmpleados)==0)
                {
                	printf("\nDatos cargados.\n");
                	loadFlag=1;
                }
                else
                {
                	if(utn_getInt("\nLa lista ya existe, sobrescribir?: \n1-Si\n2-No \n>",ERROR,&optionFlag,ATTEMPTS,1,2)==0 &&
                		optionFlag==1 && controller_loadFromText("data.csv",listaEmpleados)==0	)
                	{
                		printf("\nDatos cargados.\n");
                	}
                	else
                	{
                		printf("\nNo hay datos cargados.\n");
                	}
                }
                break;

            case 2:

                if(loadFlag==0 && !controller_loadFromBinary("dataBinario.bin",listaEmpleados))
                {
                	printf("\nDatos cargados.\n");
                	loadFlag=1;
                }
                else
                {
                	if(utn_getInt("\nLa lista ya existe, sobrescribir?: \n1-Si\n2-No \n>",ERROR,&optionFlag,ATTEMPTS,1,2)==0 &&
                		optionFlag==1 && controller_loadFromBinary("dataBinario.bin",listaEmpleados)==0	)
                	{
                		printf("\nDatos cargados.\n");
                	}
                	else
                	{
                		printf("\nNo hay datos cargados.\n");
                	}
                }
                break;

            case 3:

                break;

            case 4:
            	controller_editEmployee(listaEmpleados);
                break;

            case 5:
            	controller_removeEmployee(listaEmpleados);
                break;

            case 6:
            	controller_ListEmployee(listaEmpleados);
                break;

            case 7:
            	controller_sortEmployee(listaEmpleados);
                break;

            case 8:
            	controller_saveAsText("data.csv",listaEmpleados);
                break;

            case 9:
            	controller_saveAsBinary("dataBinario.bin",listaEmpleados);
                break;


        }
    }while(option != 10);
    ll_deleteLinkedList(listaEmpleados);
    printf("\nExit");

    */
    return 0;
}

