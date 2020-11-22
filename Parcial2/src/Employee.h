#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED


#define TRUE 1
#define FALSE 0
#define ATTEMPTS 3
#define CHOOSE_MENU "\n1) Cargar los datos de los empleados desde el archivo data.csv (modo texto).\n2) Cargar los datos de los empleados desde el archivo data.csv (modo binario).\n3) Alta de empleado\n4) Modificar datos de empleado\n5) Baja de empleado\n6) Listar empleados\n7) Ordenar empleados\n8) Guardar los datos de los empleados en el archivo data.csv (modo texto).\n9) Guardar los datos de los empleados en el archivo data.csv (modo binario).\n10) Salir\n>"


#define LONG_NAME 128
#define LONG_HRAS 12
#define LONG_SUELDO 20
#define LONG_ID 55

#define SIZE 4096


typedef struct
{
    int id;
    char nombre[LONG_NAME];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldoStr);
void employee_delete();

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);

//---new's
Employee* employee_newParameters(int id,char* name,int hours, int salary); //load binary
int employee_setIdStr(Employee* this, char* id);
int employee_getIdStr(Employee* this,char* id);
int employee_setHoursWorkedStr(Employee* this, char* horasTrabajadas);
int employee_getHorasTrabajadasStr(Employee* this,char* horasTrabajadas);
int employee_setSalaryStr(Employee* this, char* sueldo);
int employee_getSueldoStr(Employee* this,char* sueldo);
int employee_print(Employee* this);
//---
int employee_sort(void* itemOne,void* itemTwo);
int employee_sortID(void* itemOne,void* itemTwo);
int employee_removeBy_Salary(void* itemOne);

int employee_printConMap(void* itemOne);
int employee_getSalarioTotal(void* itemOne) ;


#endif // employee_H_INCLUDED
