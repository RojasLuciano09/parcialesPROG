


int controller_editEmployee(LinkedList* list);
int controller_removeEmployee(LinkedList* list);
int controller_ListEmployee(LinkedList* list);
int controller_sortEmployee(LinkedList* list);
int controller_saveAsText(char* path , LinkedList* list);
int controller_saveAsBinary(char* path , LinkedList* list);


int controller_removeEmployeeBySalary(LinkedList* list);
int controller_calcularTotalDeSueldoConMap(LinkedList* list);
//--------

int controller_findById(LinkedList* listcliente,void* arg);

int controller_loadFromText(char* path , LinkedList* list);

int controller_loadFromTextVentas(char* path , LinkedList* list);
int controller_printAfiche(LinkedList* pArrayListEmployee);
int controller_searchMaxId(LinkedList* pArrayListEmployee);
int controller_searchMaxId2(LinkedList* listAfiche);
int controller_addEmployee(LinkedList* pArrayListEmployee);

int primerBusqueda(LinkedList* pArrayListEmployee,void* element);
int estaRepetido(LinkedList* pArrayListEmployee,void* element_one);

int controller_vender_afiches(LinkedList* listAfiche,LinkedList* listcliente);
int controller_modificar_Venta(LinkedList* listAfiche,LinkedList* listcliente);

int filterCliente(LinkedList* listAfiche,LinkedList* listcliente);

int controller_printCliente(LinkedList* pArrayListEmployee);

int controller_findVentaFromID(LinkedList* listAfiche,LinkedList* listcliente,void* arg);

int controller_findByIdAfiche(LinkedList* listAfiche,void* arg,int* id_temp);
int controller_cobrar_venta(LinkedList* listAfiche,LinkedList* listcliente);

int controller_generarInformeDeudas(LinkedList* listAfiche,LinkedList* listcliente);
int controller_generarInforme(LinkedList* listAfiche,LinkedList* listcliente);
int controller_generar_estadisticas(LinkedList* listAfiche,LinkedList* listcliente);
int controller_calcularAlQueSeLeVendioMas(LinkedList* listAfiche,LinkedList* listcliente);
