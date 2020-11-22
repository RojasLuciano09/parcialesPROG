


int controller_editEmployee(LinkedList* list);
int controller_removeEmployee(LinkedList* list);
int controller_ListEmployee(LinkedList* list);
int controller_sortEmployee(LinkedList* list);
int controller_saveAsText(char* path , LinkedList* list);
int controller_saveAsBinary(char* path , LinkedList* list);
int controller_findById(LinkedList* list,int id, int *index);

int controller_removeEmployeeBySalary(LinkedList* list);
int controller_calcularTotalDeSueldoConMap(LinkedList* list);
//--------



int controller_loadFromText(char* path , LinkedList* list);
int controller_printCliente(LinkedList* list);
int controller_loadFromTextVentas(char* path , LinkedList* list);
int controller_printAfiche(LinkedList* pArrayListEmployee);
int controller_searchMaxId(LinkedList* pArrayListEmployee);
int controller_searchMaxId2(LinkedList* listAfiche);
int controller_addEmployee(LinkedList* pArrayListEmployee);

int primerBusqueda(LinkedList* pArrayListEmployee,void* element);
int estaRepetido(LinkedList* pArrayListEmployee,void* element_one);
int controller_findVentaFromID(LinkedList* listAfiche,void* arg);
int controller_vender_afiches(LinkedList* listAfiche,LinkedList* listcliente);
int controller_modificar_Venta(LinkedList* listAfiche,LinkedList* listcliente);



